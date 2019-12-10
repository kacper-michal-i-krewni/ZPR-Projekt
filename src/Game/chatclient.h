#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>
class QHostAddress;
class QJsonDocument;

/*!
 * \brief The ChatClient class
 *
 * ChatClient class states the client side of client-server relation.
 * It is responsible for sending siglnals to server about the connection info, messages, message statues etc.
 */
class ChatClient : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ChatClient)
public:
    /*!
     * \brief ChatClient constructor
     * \param parent - null, needed for the constructor of the super class
     * Creates a  new client TCP socket and creates configuration for it.
     */
    explicit ChatClient(QObject *parent = nullptr);
    /*!
     * \brief getNickname - method to get nickname of a client
     * \return nickname of client
     */
    const QString getNickname() const;


    QTcpSocket* getQTcpSocket() const;
public slots:
    /*!
     * \brief connectToServer - connects client application to a specific host
     * \param address - server address
     * \param port - server port
     */
    void connectToServer(const QHostAddress &address, quint16 port);
    /*!
     * \brief login - if client is connected, sends info to server with username in order to log in
     * \param userName
     */
    void login(const QString &userName);
    /*!
     * \brief sendMessage - sends message to server in order to forward this to other clients
     * \param text
     */
    void sendMessage(const QString &text);
    /*!
     * \brief disconnectFromHost - disconnects client socket from server
     */
    void disconnectFromHost();
    /*!
     * \brief disconnect
     */
    void disconnect();
private slots:
    /*!
     * \brief onReadyRead - listens for the json data from the server.
     * When data is present on an input channel, jsonRecieved method is evoked
     */
    void onReadyRead();
signals:
    /*!
     * \brief connected - signal bound to the signal - QTcpSocket::connected
     */
    void connected();
    /*!
     * \brief loggedIn - signal emited when recieved data states that login was successful
     */
    void loggedIn();
    /*!
     * \brief loginError - signal emited when recieved data states that login failed
     * \param reason
     */
    void loginError(const QString &reason);
    /*!
     * \brief disconnected - signal bound to the signal - QTcpSocket::disconnected
     */
    void disconnected();
    /*!
     * \brief messageReceived - signal emited when recieved data is a message
     * \param sender
     * \param text
     */
    void messageReceived(const QString &sender, const QString &text);
    /*!
     * \brief error - signal bound to the signal - QAbstractSocket::error
     * \param socketError
     */
    void error(QAbstractSocket::SocketError socketError);
    /*!
     * \brief userJoined - signal emited when data states that user joined the server
     * \param username
     */
    void userJoined(const QString &username);
    /*!
     * \brief userLeft - signal emited when data states that user left the server
     * \param username
     */
    void userLeft(const QString &username);
private:
    /*!
     * \brief m_clientSocket - the socket that is bound to the specific client.
     * It's a core field of a class
     */
    QTcpSocket *m_clientSocket;
    /*!
     * \brief m_loggedIn - a flag that states if user is logged in or not
     */
    bool m_loggedIn;
    /*!
     * \brief jsonReceived - the core logic method of the class. Interprets recieved data and emits signals
     * that correspond to the specific input categories
     * \param doc
     */
    void jsonReceived(const QJsonObject &doc);
    /*!
     * \brief nickname
     */
    QString nickname;
};

#endif // CHATCLIENT_H
