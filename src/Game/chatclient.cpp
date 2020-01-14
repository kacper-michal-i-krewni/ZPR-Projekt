#include "chatclient.h"
#include <QTcpSocket>
#include <QDataStream>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

ChatClient::ChatClient(QObject *parent)
    : QObject(parent)
    , m_clientSocket(new QTcpSocket(this))
    , m_loggedIn(false)
    ,_sessionId("null")
{
    // Forward the connected and disconnected signals
    connect(m_clientSocket.get(), &QTcpSocket::connected, this, &ChatClient::connected);
    connect(m_clientSocket.get(), &QTcpSocket::disconnected, this, &ChatClient::disconnected);
    // connect readyRead() to the slot that will take care of reading the data in
    connect(m_clientSocket.get(), &QTcpSocket::readyRead, this, &ChatClient::onReadyRead);
    // Forward the error signal, QOverload is necessary as error() is overloaded, see the Qt docs
    connect(m_clientSocket.get(), QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &ChatClient::error);
    // Reset the m_loggedIn variable when we disconnec. Since the operation is trivial we use a lambda instead of creating another slot
    connect(m_clientSocket.get(), &QTcpSocket::disconnected, this, [this]()->void{m_loggedIn = false;});
}

const QString ChatClient::getNickname() const
{
    return nickname;
}

std::shared_ptr<QTcpSocket> ChatClient::getQTcpSocket() const
{
    return m_clientSocket;
}

void ChatClient::connectToServer(const QHostAddress &address, quint16 port)
{
    m_clientSocket->connectToHost(address, port);
}


void ChatClient::setSessionId(QString &sessionId)
{
    _sessionId = sessionId;
}

QString ChatClient::getSessionId()
{
    return _sessionId;
}

void ChatClient::setTurnId(QString &turnId)
{
    _turnId = turnId;
}

QString ChatClient::getTurnId()
{
    return _turnId;
}

QVector<QString> ChatClient::getCurrentBlockers()
{
    return _currentBlockers;
}


void ChatClient::login(const QString &userName)
{
    if (m_clientSocket->state() == QAbstractSocket::ConnectedState) { // if the client is connected
        // create a QDataStream operating on the socket
        // ! QDataStream clientStream(m_clientSocket);
        // set the version so that programs compiled with different versions of Qt can agree on how to serialise
        // ! clientStream.setVersion(QDataStream::Qt_5_7);
        // Create the JSON we want to send
        QJsonObject message;
        message["type"] = QStringLiteral("login");
        message["username"] = userName;
        nickname = userName;
        this->sendMessageToServer(message);
        // send the JSON using QDataStream
        // ! clientStream << QJsonDocument(message).toJson(QJsonDocument::Compact);
    }
}

void ChatClient::sendMessageToServer(const QJsonObject &message)
{
    // create a QDataStream operating on the socket
    QDataStream clientStream(m_clientSocket.get());
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    clientStream.setVersion(QDataStream::Qt_5_7);

    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson(QJsonDocument::Compact);
}

void ChatClient::sendChatMessage(const QString &text)
{
    if (text.isEmpty())
        return; // We don't send empty messages

    QJsonObject message;
    message["type"] = QStringLiteral("message");
    message["text"] = text;

    this->sendMessageToServer(message);
}

void ChatClient::disconnectFromHost()
{
    m_clientSocket->disconnectFromHost();
}

void ChatClient::disconnect()
{
    m_clientSocket->disconnectFromHost();
}

void ChatClient::onReadyRead()
{
    // prepare a container to hold the UTF-8 encoded JSON we receive from the socket
    QByteArray jsonData;
    // create a QDataStream operating on the socket
    QDataStream socketStream(m_clientSocket.get());
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    socketStream.setVersion(QDataStream::Qt_5_7);
    // start an infinite loop
    for (;;) {
        // we start a transaction so we can revert to the previous state in case we try to read more data than is available on the socket
        socketStream.startTransaction();
        // we try to read the JSON data
        socketStream >> jsonData;
        if (socketStream.commitTransaction()) {
            // we successfully read some data
            // we now need to make sure it's in fact a valid JSON
            QJsonParseError parseError;
            // we try to create a json document with the data we received
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                // if the data was indeed valid JSON
                if (jsonDoc.isObject()) // and is a JSON object
                    jsonReceived(jsonDoc.object()); // parse the JSON
            }
            // loop and try to read more JSONs if they are available
        } else {
            // the read failed, the socket goes automatically back to the state it was in before the transaction started
            // we just exit the loop and wait for more data to become available
            break;
        }
    }
}

void ChatClient::jsonReceived(const QJsonObject &docObj)
{
    // actions depend on the type of message
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return; // a message with no type was received so we just ignore it
    if (typeVal.toString().compare(QLatin1String("login"), Qt::CaseInsensitive) == 0)  //It's a login message
    {
        if (m_loggedIn)
            return; // if we are already logged in we ignore
        // the success field will contain the result of our attempt to login
        const QJsonValue resultVal = docObj.value(QLatin1String("success"));
        if (resultVal.isNull() || !resultVal.isBool())
            return; // the message had no success field so we ignore
        const bool loginSuccess = resultVal.toBool();
        if (loginSuccess)
        {
            // we logged in succesfully and we notify it via the loggedIn signal
            emit loggedIn();
            return;
        }
        // the login attempt failed, we extract the reason of the failure from the JSON
        // and notify it via the loginError signal
        const QJsonValue reasonVal = docObj.value(QLatin1String("reason"));
        emit loginError(reasonVal.toString());
    }
    else if (typeVal.toString().compare(QLatin1String("message"), Qt::CaseInsensitive) == 0)  //It's a chat message
    {
        // we extract the text field containing the chat text
        const QJsonValue textVal = docObj.value(QLatin1String("text"));
        // we extract the sender field containing the username of the sender
        const QJsonValue senderVal = docObj.value(QLatin1String("sender"));
        if (textVal.isNull() || !textVal.isString())
            return; // the text field was invalid so we ignore
        if (senderVal.isNull() || !senderVal.isString())
            return; // the sender field was invalid so we ignore
        // we notify a new message was received via the messageReceived signal
        emit messageReceived(senderVal.toString(), textVal.toString());
    }
    else if (typeVal.toString().compare(QLatin1String("newuser"), Qt::CaseInsensitive) == 0) // A user joined the chat
    {
        // we extract the username of the new user
        const QJsonValue usernameVal = docObj.value(QLatin1String("username"));
        if (usernameVal.isNull() || !usernameVal.isString())
            return; // the username was invalid so we ignore
        // we notify of the new user via the userJoined signal
        emit userJoined(usernameVal.toString());
    }
    else if (typeVal.toString().compare(QLatin1String("userdisconnected"), Qt::CaseInsensitive) == 0) // A user left the chat
    {
         // we extract the username of the new user
        const QJsonValue usernameVal = docObj.value(QLatin1String("username"));
        if (usernameVal.isNull() || !usernameVal.isString())
            return; // the username was invalid so we ignore
        // we notify of the user disconnection the userLeft signal
        emit userLeft(usernameVal.toString());
    }
    else if (typeVal.toString().compare(QLatin1String("action"), Qt::CaseInsensitive) == 0) // A user action
    {

        const QJsonValue textVal = docObj.value(QLatin1String("text"));
        // we extract the sender field containing the username of the sender
        const QJsonValue senderVal = docObj.value(QLatin1String("sender"));
        if (textVal.isNull() || !textVal.isString())
            return; // the text field was invalid so we ignore
        if (senderVal.isNull() || !senderVal.isString())
            return; // the sender field was invalid so we ignore

        emit actionExecute(senderVal.toString(), textVal.toString());
    }

    else if (typeVal.toString().compare(QLatin1String("sessionDialogInfo"), Qt::CaseInsensitive) == 0) // A session info
    {
        QJsonArray sessionArray = docObj["sessions"].toArray();

        QVector<Session> sVector;
        for (int sIndex = 0; sIndex < sessionArray.size(); ++sIndex) {
                QJsonObject sObject = sessionArray[sIndex].toObject();
                Session s;
                s.readValuesFromJSON(sObject);
                sVector.push_back(s);
        }

        emit sessionListComplete(sVector);
    }
    else if (typeVal.toString().compare(QLatin1String("sessionCreated"), Qt::CaseInsensitive) == 0)
    {
        QJsonValue success = docObj.value(QLatin1String("success"));
        bool b = success.toBool();
        if(b)
        {
            QJsonValue id = docObj.value(QLatin1String("id"));
            QString s = id.toString();
            emit sessionCreated(b, s);
        }
        else
        {
            QString s = QStringLiteral("null");
            emit sessionCreated(b, s);
        }
    }

    else if (typeVal.toString().compare(QLatin1String("update"), Qt::CaseInsensitive) == 0) // An update message
    {
        const QJsonValue playersNick = docObj.value(QLatin1String("player"));
        if (playersNick.isNull() || !playersNick.isString())
            return; // the text field was invalid so we ignore
        const QJsonValue playersLifes = docObj.value(QLatin1String("lifes"));
        if (playersLifes.isNull())
            return; // the text field was invalid so we ignore
        const QJsonValue playersMoney= docObj.value(QLatin1String("money"));
        if (playersMoney.isNull() || !playersMoney.isDouble())
            return; // the text field was invalid so we ignore
    }

    else if (typeVal.toString().compare(QLatin1String("sessionMessage"), Qt::CaseInsensitive) == 0)
    {
        handleSessionMessage(docObj);
    }
    else if (typeVal.toString().compare(QLatin1String("sessionAcceptance"), Qt::CaseInsensitive) == 0) // A user joined the chat
    {
        // we extract the username of the new user
        const QJsonValue usernameVal = docObj.value(QLatin1String("player"));
        if (usernameVal.isNull() || !usernameVal.isString())
            return; // the username was invalid so we ignore
        // we notify of the new user via the userJoined signal
        const QJsonValue accept = docObj.value(QLatin1String("success"));
        if (accept.isNull() || accept.toBool() != true)
            return; // the session connection try was invalid so we ignore it
        emit userJoined(usernameVal.toString());
    }
    else if (typeVal.toString().compare(QLatin1String("ready"), Qt::CaseInsensitive) == 0)
    {
        const QJsonValue usernameVal = docObj.value(QLatin1String("player"));
        if (usernameVal.isNull() || !usernameVal.isString())
            return; // the username was invalid so we ignore

        emit userReady(usernameVal.toString());
    }
    else if (typeVal.toString().compare(QLatin1String("playerInfo"), Qt::CaseInsensitive) == 0) // A user joined the chat
    {
        // we extract the username of the new pleyer joined session
        const QJsonValue usernameVal = docObj.value(QLatin1String("nickname"));
        if (usernameVal.isNull() || !usernameVal.isString())
            return; // the username was invalid so we ignore
        emit joinedSession(usernameVal.toString());
    }
    else if (typeVal.toString().compare(QLatin1String("cardsDealing"), Qt::CaseInsensitive) == 0) // A user joined the chat
    {
        // we extract the username of the new pleyer joined session
        const QJsonValue first = docObj.value(QLatin1String("first"));
        if (first.isNull() || !first.isString())
            return;
        const QJsonValue second = docObj.value(QLatin1String("second"));
        if (second.isNull() || !second.isString())
            return;
        emit cardsDealing(first.toString(), second.toString());
    }
}

void ChatClient::handleSessionMessage(const QJsonObject &doc)
{
    const QJsonValue subtypeVal = doc.value(QLatin1String("subtype"));
    if (subtypeVal.toString().compare(QLatin1String("newTurn"), Qt::CaseInsensitive) == 0)
    {
        const QJsonValue turnId = doc.value(QLatin1String("turnId"));
        _turnId = turnId.toString();
        const QJsonValue playerVal = doc.value(QLatin1String("player"));
        QString player = playerVal.toString();
        if (player.compare(this->nickname, Qt::CaseInsensitive) == 0)
            emit myTurn();
        else
            emit turnOf(player);
    }

    if(subtypeVal.toString().compare(QLatin1String("targetSpecify"), Qt::CaseInsensitive) == 0)
    {

        QJsonArray playerArray = doc["players"].toArray();
        QVector<QString> pVector;
        for (int sIndex = 0; sIndex < playerArray.size(); ++sIndex) {
                QString p = playerArray[sIndex].toString();
                pVector.push_back(p);
        }

        QString action = doc.value(QLatin1String("action")).toString();
        emit actionTargetSpecify(action, pVector);
    }

    if(subtypeVal.toString().compare(QLatin1String("notEnoughMoney"), Qt::CaseInsensitive) == 0)
    {
        emit notEnoughMoney();
    }

    if(subtypeVal.toString().compare(QLatin1String("youAreATarget"), Qt::CaseInsensitive) == 0)
    {
         const QJsonValue sender = doc.value(QLatin1String("sender"));
         const QJsonValue action = doc.value(QLatin1String("action"));
         const QJsonArray blockerArray = doc["blockers"].toArray();
         QVector<QString> blockers;
         for (int sIndex = 0; sIndex < blockerArray.size(); ++sIndex) {
                 QString p = blockerArray[sIndex].toString();
                 blockers.push_back(p);
         }
         QString s_action = action.toString();
         QString s_sender = sender.toString();

         _currentBlockers = blockers;
         emit youAreATarget(s_action, s_sender, blockers);
    }

    if(subtypeVal.toString().compare(QLatin1String("actionCompleted"), Qt::CaseInsensitive) == 0)
    {
        const QJsonValue sender = doc.value(QLatin1String("sender"));
        const QJsonValue action = doc.value(QLatin1String("action"));
        QString s_action = action.toString();
        QString s_sender = sender.toString();
        emit actionCompleted(s_action, s_sender);
    }

    if(subtypeVal.toString().compare(QLatin1String("actionPending"), Qt::CaseInsensitive) == 0)
    {
        const QJsonValue sender = doc.value(QLatin1String("sender"));
        const QJsonValue action = doc.value(QLatin1String("action"));
        QString s_action = action.toString();
        QString s_sender = sender.toString();
        emit actionPending(s_action, s_sender);
    }
}






