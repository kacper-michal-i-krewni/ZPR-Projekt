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

ChatServer::ChatServer(QObject *parent)
    : QTcpServer(parent),
       _actions( new Actions())
{

}

void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    ServerWorker *worker = new ServerWorker(this);
    if (!worker->setSocketDescriptor(socketDescriptor))
    {
        worker->deleteLater();
        return;
    }
    connect(worker, &ServerWorker::disconnectedFromClient, this, std::bind(&ChatServer::userDisconnected, this, worker));
    connect(worker, &ServerWorker::error, this, std::bind(&ChatServer::userError, this, worker));
    connect(worker, &ServerWorker::jsonReceived, this, std::bind(&ChatServer::jsonReceived, this, worker, std::placeholders::_1));
    connect(worker, &ServerWorker::logMessage, this, &ChatServer::logMessage);
    m_clients.append(worker);
    emit logMessage(QStringLiteral("New client Connected"));
}
void ChatServer::sendJson(ServerWorker *destination, const QJsonObject &message)
{
    Q_ASSERT(destination);
    destination->sendJson(message);
}
void ChatServer::broadcast(const QJsonObject &message, ServerWorker *exclude)
{
    for (ServerWorker *worker : m_clients)
    {
        Q_ASSERT(worker);
        if (worker == exclude)
            continue;
        sendJson(worker, message);
    }
}

void ChatServer::sessionBroadcast(Session &sess, const QJsonObject &message, ServerWorker* exclude)
{
    for(ServerWorker* worker : sess.getPlayers()){
        Q_ASSERT(worker);
        if(worker == exclude)
            continue;
        sendJson(worker, message);
    }
}

void ChatServer::jsonReceived(ServerWorker *sender, const QJsonObject &doc)
{
    Q_ASSERT(sender);
    emit logMessage("JSON received " + QString::fromUtf8(QJsonDocument(doc).toJson()));
    if (sender->userName().isEmpty())
        return jsonFromLoggedOut(sender, doc);
    jsonFromLoggedIn(sender, doc);
}

void ChatServer::userDisconnected(ServerWorker *sender)
{
    m_clients.removeAll(sender);
    const QString userName = sender->userName();
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

void ChatServer::userError(ServerWorker *sender)
{
    Q_UNUSED(sender)
    emit logMessage("Error from " + sender->userName());
}

void ChatServer::stopServer()
{
    for (ServerWorker *worker : m_clients) {
        worker->disconnectFromClient();
    }
    close();
}

void ChatServer::jsonFromLoggedOut(ServerWorker *sender, const QJsonObject &docObj)
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
    for (ServerWorker *worker : qAsConst(m_clients))
    {
        if (worker == sender)
            continue;
        if (worker->userName().compare(newUserName, Qt::CaseInsensitive) == 0)
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
}

void ChatServer::jsonFromLoggedIn(ServerWorker *sender, const QJsonObject &docObj)
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

void ChatServer::handleChatMessage(ServerWorker *sender, const QJsonObject &docObj)
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
    message["sender"] = sender->userName();
    broadcast(message, sender);
}


void ChatServer::handleSessionMessage(ServerWorker *sender, const QJsonObject &docObj) // <-----TODO
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
    message["sender"] = sender->userName();
    broadcast(message, sender);
}

void ChatServer::handleActionMessage(ServerWorker *sender, const QJsonObject &docObj)
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
    message["sender"] = sender->userName();
    //broadcast(message, sender);
    broadcast(message, nullptr);
}
