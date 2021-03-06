#include "chatserver.h"
#include "serverworker.h"
#include <QThread>
#include <functional>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QTimer>
#include <QJsonArray>
#include "session.h"
#include "actions.h"
#include "player.h"

ChatServer::ChatServer(QObject *parent)
    : QTcpServer(parent),
       _actions( new Actions())
{

}

void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    std::shared_ptr<ServerWorker> worker (new ServerWorker(this));
    if (!worker->setSocketDescriptor(socketDescriptor))
    {
        worker->deleteLater();
        return;
    }
    connect(worker.get(), &ServerWorker::disconnectedFromClient, this, std::bind(&ChatServer::userDisconnected, this, worker));
    connect(worker.get(), &ServerWorker::error, this, std::bind(&ChatServer::userError, this, worker));
    connect(worker.get(), &ServerWorker::jsonReceived, this, std::bind(&ChatServer::jsonReceived, this, worker, std::placeholders::_1));
    connect(worker.get(), &ServerWorker::logMessage, this, &ChatServer::logMessage);
    m_clients.append(worker);
    emit logMessage(QStringLiteral("New client Connected"));
}
void ChatServer::sendJson(std::shared_ptr<ServerWorker> destination, const QJsonObject &message)
{
    Q_ASSERT(destination);
    destination->sendJson(message);
}

void ChatServer::updateGameStatus(std::shared_ptr<Session> sess)
{
    QVector<std::shared_ptr<ServerWorker>> players = sess->getPlayers();
    for ( std::shared_ptr<ServerWorker> x : players)
    {
        QJsonObject updateMessage;
        updateMessage["type"] = QStringLiteral("update");
        updateMessage["player"] = x->getUserName();
        updateMessage["lifes"] = x->getPlayer()->getLifes();
        updateMessage["money"] = x->getPlayer()->getMoney();
        sessionBroadcast(sess, updateMessage, nullptr);
    }

}
void ChatServer::broadcast(const QJsonObject &message, std::shared_ptr<ServerWorker> exclude)
{
    for (std::shared_ptr<ServerWorker> worker : m_clients)
    {
        Q_ASSERT(worker);
        if (worker == exclude)
            continue;
        sendJson(worker, message);
    }
}

void ChatServer::sessionBroadcast(std::shared_ptr<Session> sess, const QJsonObject &message, std::shared_ptr<ServerWorker> exclude)
{
    for(std::shared_ptr<ServerWorker> worker : sess->getPlayers())
    {
        Q_ASSERT(worker);
        if(worker == exclude)
            continue;
        sendJson(worker, message);
    }
}

void ChatServer::jsonReceived(std::shared_ptr<ServerWorker> sender, const QJsonObject &doc)
{
    Q_ASSERT(sender);
    emit logMessage("JSON received " + QString::fromUtf8(QJsonDocument(doc).toJson()));
    if (sender->getUserName().isEmpty())
        return jsonFromLoggedOut(sender, doc);
    jsonFromLoggedIn(sender, doc);
}

void ChatServer::userDisconnected(std::shared_ptr<ServerWorker> sender)
{
    m_clients.removeAll(sender);
    const QString userName = sender->getUserName();
    std::shared_ptr<Session> s;
    if (!userName.isEmpty())
    {
        QJsonObject disconnectedMessage;
        disconnectedMessage["type"] = QStringLiteral("userdisconnected");
        disconnectedMessage["username"] = userName;
        for ( std::shared_ptr<Session> _s : _sessions )
        {
            if(_s->searchForPlayer(sender->getUserName()) !=  nullptr)
            {
                if ( _s->getOwner() == sender )
                    _sessions.removeOne(_s);
                 else
                    _s->removePlayer(_s->searchForPlayer(sender->getUserName()));
            }
        }
        broadcast(disconnectedMessage, nullptr);

        emit logMessage(userName + " disconnected");

    }
    //sender->deleteLater()

}

void ChatServer::userError(std::shared_ptr<ServerWorker> sender)
{
    Q_UNUSED(sender)
    emit logMessage("Error from " + sender->getUserName());
}

void ChatServer::stopServer()
{
    for (std::shared_ptr<ServerWorker> worker : m_clients) {
        worker->disconnectFromClient();
    }
    close();
}

void ChatServer::jsonFromLoggedOut(std::shared_ptr<ServerWorker> sender, const QJsonObject &docObj)
{
    Q_ASSERT(sender);
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return;
    if (typeVal.toString().compare(QLatin1String("login"), Qt::CaseInsensitive)  != 0)
        return;
    const QJsonValue usernameVal = docObj.value(QLatin1String("username"));
    if (usernameVal.isNull() || !usernameVal.isString())
        return;
    const QString newUserName = usernameVal.toString().simplified();
    if (newUserName.isEmpty())
        return;
    for (std::shared_ptr<ServerWorker> worker : qAsConst(m_clients))
    {
        if (worker == sender)
            continue;
        if (worker->getUserName().compare(newUserName, Qt::CaseInsensitive) == 0)
        {
            QJsonObject message;
            message["type"] = QStringLiteral("login");
            message["success"] = false;
            message["reason"] = QStringLiteral("duplicate username");
            sendJson(sender, message);
            return;
        }
    }
    sender->setUserName(newUserName);
    QJsonObject successMessage;
    successMessage["type"] = QStringLiteral("login");
    successMessage["success"] = true;
    sendJson(sender, successMessage);
}



void ChatServer::jsonFromLoggedIn(std::shared_ptr<ServerWorker> sender, const QJsonObject &docObj)
{
    Q_ASSERT(sender);
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return;
    if ( typeVal.toString().compare(QLatin1String("action"), Qt::CaseInsensitive) == 0)
    {
        handleActionMessage(sender, docObj);
    }

    if (typeVal.toString().compare(QLatin1String("message"), Qt::CaseInsensitive) == 0)
    {
        handleChatMessage(sender, docObj);
    }
    if(typeVal.toString().compare(QLatin1String("session"), Qt::CaseInsensitive) == 0)
    {
        handleSessionMessage(sender, docObj);
    }
    if(typeVal.toString().compare(QLatin1String("ready"), Qt::CaseInsensitive) == 0)
    {
        handleReadyMessage(sender, docObj);
    }
    if (typeVal.toString().compare(QLatin1String("caunterAction"), Qt::CaseInsensitive) == 0)
    {
        handleCaunterActionMessage(sender, docObj);
    }

}

void ChatServer::handleChatMessage(std::shared_ptr<ServerWorker> sender, const QJsonObject &docObj)
{
    const QJsonValue textVal = docObj.value(QLatin1String("text"));
    if (textVal.isNull() || !textVal.isString())
        return;
    const QString text = textVal.toString().trimmed();
    if (text.isEmpty())
        return;
    QJsonObject message;
    message["type"] = QStringLiteral("message");
    message["text"] = text;
    message["sender"] = sender->getUserName();
    for ( auto s  : _sessions)
    {
        if ( s->checkIfPlayerIsInSession(sender))
        {
            sessionBroadcast(s, message, sender);
        }
    }
}


void ChatServer::handleSessionMessage(std::shared_ptr<ServerWorker> sender, const QJsonObject &docObj)
{
    const QJsonValue requestVal = docObj.value(QLatin1String("request"));


    if ( requestVal.toString().compare(QLatin1String("createRequest"), Qt::CaseInsensitive) == 0)
    {
        QJsonObject message;
        message["type"] = QStringLiteral("sessionCreated");
        if (sender->isInGame() || sender->isGameOwner())
        {
            message["success"] = false;
        }
        else
        {
            const QJsonValue numOfPlayers = docObj.value(QLatin1String("playerNumber"));
            if (numOfPlayers.isNull() || !numOfPlayers.isString())
                return;
            int num = std::stoi(numOfPlayers.toString().toStdString());
            std::shared_ptr<Session> s(new Session(sender, num));
            _sessions.push_back(s);
            sender->setAsGameOwner(true);
            sender->setAsInGame(true);
            message["success"] = true;
            message["id"] = s->getId();
            connect(s.get(), &Session::sendUpdate, this, &ChatServer::sendUpdate);
        }
        sendJson(sender, message);
    }

    if ( requestVal.toString().compare(QLatin1String("startRequest"), Qt::CaseInsensitive) == 0)
    {
        const QJsonValue id = docObj.value(QLatin1String("id"));
        for (auto s: _sessions)
        {
            if(id.toString().compare(s->getId(), Qt::CaseInsensitive) == 0)
            {
                if(s->getOwner() == sender)
                {
                    s->start();
                    QJsonObject message;
                    message["type"] = QStringLiteral("sessionStarted");
                    message["success"] = true;
                    s->sendToAll(message);
                    for ( auto player : s->getPlayers())
                    {
                        QJsonObject cards;
                        cards["type"] = QStringLiteral("cardsDealing");
                        cards["first"] = player->getPlayer()->getCards().first()->getType();
                        cards["second"] = player->getPlayer()->getCards().last()->getType();
                        sendJson(player, cards);
                    }
                }
                else
                {
                    QJsonObject message;
                    message["type"] = QStringLiteral("sessionStarted");
                    message["success"] = false;
                    s->sendToAll(message);
                }
            return;
            }
        }
        QJsonObject message;
        message["type"] = QStringLiteral("sessionStarted");
        message["success"] = false;
        sendJson(sender, message);
    }


    if ( requestVal.toString().compare(QLatin1String("showSessionsRequest"), Qt::CaseInsensitive) == 0)
    {
        sendSessionsInfoForDialog(sender);
    }



    if ( requestVal.toString().compare(QLatin1String("joinRequest"), Qt::CaseInsensitive) == 0)
    {
        QJsonObject message;

        message["type"] = QStringLiteral("sessionAcceptance");
        if (sender->isInGame() || sender->isGameOwner())
        {
            message["success"] = false;
        }
        else
        {
            const QJsonValue sessionId = docObj.value(QLatin1String("id"));
            for (auto s: _sessions)
            {
                if (sessionId.toString().compare( s->getId(), Qt::CaseInsensitive) == 0)
                {
                    if(!(s->getNumOfPlayers() == s->getPlayersLimit()))
                    {
                        message["success"] = true;
                        s->addPlayer(sender);
                        sender->setAsInGame(true);
                        message["player"] = sender->getUserName();
                        sessionBroadcast(s, message, std::shared_ptr<ServerWorker>(nullptr));
                        for ( auto player : s->getPlayers() )
                        {
                            QJsonObject update_message;
                            update_message["type"] = QStringLiteral("playerInfo");
                            update_message["nickname"] = player->getUserName();
                            sendJson(sender, update_message);
                        }
                        return;
                    }
                }
            }
            sendJson(sender, message);
        }
    }
}

void ChatServer::handleReadyMessage(std::shared_ptr<ServerWorker> sender, const QJsonObject &docObj)
{
    for ( auto s: _sessions)
    {
        if ( s->searchForPlayer(sender->getUserName()))
            sessionBroadcast(s, docObj, std::shared_ptr<ServerWorker>(nullptr));
    }
}

bool ChatServer::checkIfPlayerIsInSession(std::shared_ptr<ServerWorker> sender)
{
    for(auto s: _sessions)
    {
        for (auto p: s->getPlayers())
        {
            if(p == sender) return true;
        }
    }
    return false;
}


void ChatServer::sendSessionsInfoForDialog(std::shared_ptr<ServerWorker> sender)
{
    QJsonObject sessionMessage;
    sessionMessage["type"] = QStringLiteral("sessionDialogInfo");
    QJsonArray sessionArray;
    for(auto s : _sessions)
    {
        sessionArray.append(s->toJSON());
    }
    sessionMessage["sessions"] = sessionArray;
    sendJson(sender, sessionMessage);
}

void ChatServer::handleActionMessage(std::shared_ptr<ServerWorker> sender, const QJsonObject &docObj)
{
    if(!checkIfPlayerIsInSession(sender))
        return;
    std::shared_ptr<Session> s = sessionOfPlayer(sender);
    s->handleActionMessage(sender,docObj);
}

void ChatServer::handleCaunterActionMessage(std::shared_ptr<ServerWorker> sender, const QJsonObject &docObj)
{
    if(!checkIfPlayerIsInSession(sender))
        return;
    //handle action message powinno być w sesji
    std::shared_ptr<Session> s = sessionOfPlayer(sender);
    s->handleCaunterActionMessage(sender,docObj);
}


std::shared_ptr<Session> ChatServer::sessionOfPlayer(std::shared_ptr<ServerWorker> player)
{
    for(auto s: _sessions)
    {
        for (auto p: s->getPlayers())
        {
            if(p == player)
                return s;
        }
    }
    return nullptr;
}

void ChatServer::sendUpdate(std::shared_ptr<Session> sess)
{
    updateGameStatus(sess);
}




