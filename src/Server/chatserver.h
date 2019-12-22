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
    void broadcast(const QJsonObject &message, ServerWorker *exclude);
    /*!
     * \brief jsonReceived is function that handle message recived in json
     * \param sender is a pointer on user that send message
     * \param doc is an object that has message in json format
     */
    void sessionBroadcast(Session &sess, const QJsonObject &message, ServerWorker* exclude);

    void jsonReceived(ServerWorker *sender, const QJsonObject &doc);
    /*!
     * \brief userDisconnected is a function that handle user disconnecting
     * \param sender is an user that disconnect
     */
    void userDisconnected(ServerWorker *sender);
    /*!
     * \brief userError handle all errors from user
     * \param sender is an user that cause the error
     */
    void userError(ServerWorker *sender);
private:
    /*!
     * \brief jsonFromLoggedOut is a function that handle disconnecting
     * \param sender is an user that disconnects
     * \param doc is an object that has message in json format
     */
    void jsonFromLoggedOut(ServerWorker *sender, const QJsonObject &doc);
    /*!
     * \brief jsonFromLoggedIn is a function that handle conneting
     * \param sender is an user that connects
     * \param doc is an object that has message in json format
     */
    void jsonFromLoggedIn(ServerWorker *sender, const QJsonObject &doc);
    /*!
     * \brief sendJson is a function that send json message to a specific user
     * \param destination is an user who recive a message
     * \param message is a message that is send
     */
    void sendJson(ServerWorker *destination, const QJsonObject &message);
    QVector<ServerWorker *> m_clients;
    std::shared_ptr<Actions> _actions;
    QVector<std::shared_ptr<Session>> _sessions;
};

#endif // CHATSERVER_H
