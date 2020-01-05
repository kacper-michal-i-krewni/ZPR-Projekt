#include "chatserver.h"
#include "serverworker.h"
#include <QThread>
#include <functional>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QTimer>
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

void ChatServer::updateGameStatus(Session &sess)
{
    QVector<std::shared_ptr<ServerWorker>> players = sess.getPlayers();
    for ( std::shared_ptr<ServerWorker> x : players)
    {
        QJsonObject updateMessage;
        updateMessage["type"] = QStringLiteral("update");
        updateMessage["player"] = x->getUserName();
        updateMessage["lifes"] = x->getPlayer().getLifes();
        updateMessage["money"] = x->getPlayer().getMoney();
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

void ChatServer::sessionBroadcast(Session &sess, const QJsonObject &message, std::shared_ptr<ServerWorker> exclude)
{
    for(std::shared_ptr<ServerWorker> worker : sess.getPlayers()){
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
    if (!userName.isEmpty())
    {
        QJsonObject disconnectedMessage;
        disconnectedMessage["type"] = QStringLiteral("userdisconnected");
        disconnectedMessage["username"] = userName;
        broadcast(disconnectedMessage, nullptr);
        emit logMessage(userName + " disconnected");
    }
    sender->deleteLater();
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
    if (typeVal.toString().compare(QLatin1String("login"), Qt::CaseInsensitive) != 0)
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
    QJsonObject connectedMessage;
    connectedMessage["type"] = QStringLiteral("newuser");
    connectedMessage["username"] = newUserName;
    broadcast(connectedMessage, sender);

    sendSessionsInfoForDialog(sender);

}

void ChatServer::sendSessionsInfoForDialog(std::shared_ptr<ServerWorker> sender)
{
    for(std::shared_ptr<Session> s: _sessions)
    {
        QJsonObject sessionMessage;
        sessionMessage["type"] = QStringLiteral("sessionDialogInfo");
        sessionMessage["numberOfPlayers"] = s->getNumOfPlayers();
        sessionMessage["owner"] = s->getOwner()->getUserName();
        sendJson(sender, sessionMessage);
    }
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
    broadcast(message, sender);
}


void ChatServer::handleSessionMessage(std::shared_ptr<ServerWorker> sender, const QJsonObject &docObj) // <-----TODO
{
    const QJsonValue numOfPlayers = docObj.value(QLatin1String("playerNumber"));
    if (numOfPlayers.isNull() || !numOfPlayers.isString())
        return;
    int num = numOfPlayers.toInt();

    std::shared_ptr<Session> s(new Session(sender, num));
    _sessions.push_back(s);

    QJsonObject message;
    message["type"] = QStringLiteral("message");
    message["text"] = QStringLiteral("czambo");
    message["sender"] = sender->getUserName();
    broadcast(message, sender);
}

void ChatServer::handleActionMessage(std::shared_ptr<ServerWorker> sender, const QJsonObject &docObj)
{
    const QJsonValue textVal = docObj.value(QLatin1String("text"));
    if (textVal.isNull() || !textVal.isString())
        return;
    const QString text = textVal.toString().trimmed();
    if (text.isEmpty())
        return;
    QJsonObject message;
    //_actions->getMap[text](sender);
    message["type"] = QStringLiteral("action");
    message["text"] = text;
    message["sender"] = sender->getUserName();
    //broadcast(message, sender);
    broadcast(message, nullptr);
}
