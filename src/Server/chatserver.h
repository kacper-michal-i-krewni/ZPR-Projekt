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
     * \brief jsonReceived is function that handle message recived in json
     * \param sender is a pointer on user that send message
     * \param doc is an object that has message in json format
     */
    void sessionBroadcast(std::shared_ptr<Session> sess, const QJsonObject &message, std::shared_ptr<ServerWorker> exclude);

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
    void sendUpdate(std::shared_ptr<Session> sess);
private:
    /*!
     * \brief jsonFromLoggedOut is a function that handle disconnecting
     * \param sender is an user that disconnects
     * \param doc is an object that has message in json format
     */

    void handleChatMessage(std::shared_ptr<ServerWorker> sender, const QJsonObject &docObj);
    void handleSessionMessage(std::shared_ptr<ServerWorker> sender, const QJsonObject &docObj);
    void handleActionMessage(std::shared_ptr<ServerWorker> sender, const QJsonObject &docObj);
    void handleCaunterActionMessage(std::shared_ptr<ServerWorker> sender, const QJsonObject &docObj);
    void handleReadyMessage(std::shared_ptr<ServerWorker> sender, const QJsonObject &docObj);
    void jsonFromLoggedOut(std::shared_ptr<ServerWorker> sender, const QJsonObject &doc);
    std::shared_ptr<Session> sessionOfPlayer(std::shared_ptr<ServerWorker> player);
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
    void updateGameStatus(std::shared_ptr<Session> sess);
    QVector<std::shared_ptr<ServerWorker> > m_clients;
    void sendSessionsInfoForDialog(std::shared_ptr<ServerWorker> sender);

    std::shared_ptr<Actions> _actions;
    QVector<std::shared_ptr<Session> > _sessions;
};

#endif // CHATSERVER_H
