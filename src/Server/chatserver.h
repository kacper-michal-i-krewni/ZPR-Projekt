#ifndef CHATSERVER_H
#define CHATSERVER_H

#include "session.h"

#include <QTcpServer>
#include <QVector>
#include <memory>

class QThread;
class ServerWorker;
class Actions;
/*!
 * \brief The ChatServer class is a class that is responsible for Server actions like reciving jsons, send messages to everyone etc
 */
class ChatServer : public QTcpServer
{
    Q_OBJECT
    Q_DISABLE_COPY(ChatServer)
public:
    /*!
     * \brief ChatServer constructor
     * \param parent
     */
    explicit ChatServer(QObject *parent = nullptr);
protected:
    /*!
     * \brief incomingConnection is an override function from QTcpServer
     * \param socketDescriptor
     *
     * It is responsible conneting right signals to slots
     */
    void incomingConnection(qintptr socketDescriptor) override;
signals:
    /*!
     * \brief logMessage is a signal that forward signal to ServerWorker::logMessage
     * \param msg is a message that is displays on the log screen
     */
    void logMessage(const QString &msg);
public slots:
    /*!
     * \brief stopServer is a function that disconnects all clients from server
     *
     */
    void stopServer();
private slots:
    /*!
     * \brief broadcast is a function that sends message to everyone but can exlude user
     * \param message is a message that is send
     * \param exclude is a pointer to user that we want to exclude from broadcast
     */
    void broadcast(const QJsonObject &message, std::shared_ptr<ServerWorker> exclude);
    /*!
     * \brief sessionBroadcast is a function that send message to everyone in session but can exclude an user
     * \param sess is a pointer to session we want to send broadcast
     * \param message is a message to send
     * \param exclude is an user we want to skip
     */
    void sessionBroadcast(std::shared_ptr<Session> sess, const QJsonObject &message, std::shared_ptr<ServerWorker> exclude);
    /*!
     * \brief jsonReceived is function that handle message recived in json
     * \param sender is a pointer on user that send message
     * \param doc is an object that has message in json format
     */
    void jsonReceived(std::shared_ptr<ServerWorker> sender, const QJsonObject &doc);
    /*!
     * \brief userDisconnected is a function that handle user disconnecting
     * \param sender is an user that disconnect
     */
    void userDisconnected(std::shared_ptr<ServerWorker> sender);
    /*!
     * \brief userError handle all errors from user
     * \param sender is an user that cause the error
     */
    void userError(std::shared_ptr<ServerWorker> sender);
    /*!
     * \brief sendUpdate is a function that sends info about update in the end of turn
     * \param sess is a session we want to update
     */
    void sendUpdate(std::shared_ptr<Session> sess);
private:
    /*!
     * \brief handleChatMessage is a function that take care of message that is identified as chat message
     * \param sender person who recive a message
     * \param docObj is a message we build
     */
    void handleChatMessage(std::shared_ptr<ServerWorker> sender, const QJsonObject &docObj);
    /*!
     * \brief handleSessionMessage is a function that take care of message that is identified as session message
     * \param sender person who recive a message
     * \param docObj is a message we build
     */
    void handleSessionMessage(std::shared_ptr<ServerWorker> sender, const QJsonObject &docObj);
    /*!
     * \brief handleActionMessage is a function that take care of message that is identified as action message
     * \param sender person who recive a message
     * \param docObj is a message we build
     */
    void handleActionMessage(std::shared_ptr<ServerWorker> sender, const QJsonObject &docObj);
    /*!
     * \brief handleCaunterActionMessage is a function that take care of message that is identified as action counter message
     * \param sender person who recive a message
     * \param docObj is a message we build
     */
    void handleCaunterActionMessage(std::shared_ptr<ServerWorker> sender, const QJsonObject &docObj);
    /*!
     * \brief handleReadyMessage is a function that take care of message that is identified as ready message
     * \param sender person who recive a message
     * \param docObj is a message we build
     */
    void handleReadyMessage(std::shared_ptr<ServerWorker> sender, const QJsonObject &docObj);
    /*!
     * \brief jsonFromLoggedOut is a function that handle disconnecting
     * \param sender is an user that disconnects
     * \param doc is an object that has message in json format
     */
    void jsonFromLoggedOut(std::shared_ptr<ServerWorker> sender, const QJsonObject &doc);
    /*!
     * \brief sessionOfPlayer returns a pointer to session connected with a player
     * \param player is a pointer to player we want a session
     * \return a pointer to a session
     */
    std::shared_ptr<Session> sessionOfPlayer(std::shared_ptr<ServerWorker> player);
    /*!
     * \brief checkIfPlayerIsInSession checks if player is in this session
     * \param sender a pointer to player
     * \return true or false
     */
    bool checkIfPlayerIsInSession(std::shared_ptr<ServerWorker> sender);
    /*!
     * \brief jsonFromLoggedIn is a function that handle conneting
     * \param sender is an user that connects
     * \param doc is an object that has message in json format
     */
    void jsonFromLoggedIn(std::shared_ptr<ServerWorker> sender, const QJsonObject &doc);
    /*!
     * \brief sendJson is a function that send json message to a specific user
     * \param destination is an user who recive a message
     * \param message is a message that is send
     */
    void sendJson(std::shared_ptr<ServerWorker> destination, const QJsonObject &message);
    /*!
     * \brief updateGameStatus is sending update status to all players in session
     * \param sess is a session we want to update
     */
    void updateGameStatus(std::shared_ptr<Session> sess);
    /*!
     * \brief m_clients is a vector of all clients in server
     */
    QVector<std::shared_ptr<ServerWorker> > m_clients;
    /*!
     * \brief sendSessionsInfoForDialog sends ifo about session to clients so they can display it
     * \param sender is a person who wants data
     */
    void sendSessionsInfoForDialog(std::shared_ptr<ServerWorker> sender);
    /*!
     * \brief _actions is a pointer to actions object who execute actions
     */
    std::shared_ptr<Actions> _actions;
    /*!
     * \brief _sessions is a vector of all sessions in server
     */
    QVector<std::shared_ptr<Session> > _sessions;
};

#endif // CHATSERVER_H
