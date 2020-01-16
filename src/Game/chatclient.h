#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include "session.h"

#include <QObject>
#include <QTcpSocket>
#include <memory>
class QHostAddress;
class QJsonDocument;

/*!
 * \brief The ChatClient class
 *
 * ChatClient class states the client side of client-server relation.
 * It is responsible for sending siglals to server about the connection info, messages, message statues etc.
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
    /*!
     * \brief setTurnId is a function that sets ID of this turn
     * \param turnId is a ID generated from server to protect turn from delayed messages
     */
    void setTurnId(QString &turnId);
    /*!
     * \brief setSessionId is a function that sets ID of the session
     * \param sessionId is a ID generated from server to protect session from messages that are not directed to this session
     */
    void setSessionId(QString &sessionId);
    /*!
     * \brief getTurnId is a getter of turn id
     * \return turn ID
     */
    QString getTurnId();
    /*!
     * \brief getSessionId
     * \return
     */
    QString getSessionId();
    QVector<QString> getCurrentBlockers();
    std::shared_ptr<QTcpSocket> getQTcpSocket() const;
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
    void sendMessageToServer(const QJsonObject &message);
    void sendChatMessage(const QString &text);
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
    /*!
     * \brief joinedSession - signal emited when message is about joining the session
     * \param username
     */
    void joinedSession(const QString &username);
    /*!
     * \brief userReady - signal is emited to log message about readiness of user
     * \param username is a nick of user that is ready
     */
    void userReady(const QString &username);
    /*!
     * \brief sessionCreated signal is emited when message about creating session is recived
     * \param success parameter says if session was created or not
     * \param id is QString that represents ID of the session
     */
    void sessionCreated(bool &success, QString &id);
    /*!
     * \brief sessionListComplete signal is emited when message with a list of actual sessions is recieved
     * \param sessVec
     */
    void sessionListComplete(QVector<Session> &sessVec);
    /*!
     * \brief myTurn is a signal that enable interface, because it is turn of player connected with this client
     */
    void myTurn();
    /*!
     * \brief turnOf
     * \param player is a QString that represents players nickname
     */
    void turnOf(QString &player);
    /*!
     * \brief actionTargetSpecify signal is emited when player sends an incomplete request - there's no target indication
     * \param action
     * \param pVector
     */
    void actionTargetSpecify(QString &action, QVector<QString> &pVector);
    /*!
     * \brief updatePlayerInterface
     * \param player
     * \param money
     * \param lifes
     */
    void updatePlayerInterface(const QString &player, const double money, const double lifes);
    /*!
     * \brief notEnoughMoney is a signal that is emited if player has not enough money to make an action
     */
    void notEnoughMoney();
    /*!
     * \brief youAreATarget signal that is emitef if someone indicate you as a target in action
     * \param action is a string with name of action
     * \param sender is a string with nickname of player
     * \param blockers is Vector that contians strings with blocker's names
     */
    void youAreATarget(QString &action, QString &sender, QVector<QString> &blockers);
    /*!
     * \brief actionCompleted signal emited when any kind of action is completed
     * \param action
     * \param sender
     */
    void actionCompleted(QString &action, QString &sender);
    /*!
     * \brief actionPending signal is emited when an action that is able o be checked is pending for execution
     * \param action
     * \param sender
     */
    void actionPending(QString &action, QString &sender);
    /*!
     * \brief cardsDealing is signal when server send dealing cards
     * \param first is a name of first card
     * \param second is a name of second card
     */
    void cardsDealing(QString first, QString second);
    /*!
     * \brief checkResult signal is emited when the reasul of action check is recieved
     * \param checked
     * \param checking
     * \param result
     */
    void checkResult(QString &checked, QString &checking, bool &result);
private:
    /*!
     * \brief m_clientSocket - the socket that is bound to the specific client.
     * It's a core field of a class
     */
    std::shared_ptr<QTcpSocket> m_clientSocket;
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
     * \brief handleSessionMessage is a function that is unpacking message and emiting right signal
     * \param doc
     */
    void handleSessionMessage(const QJsonObject &doc);
    /*!
     * \brief nickname of a player
     */
    QString nickname;
    /*!
     * \brief _sessionId is a session ID
     */
    QString _sessionId;
    /*!
     * \brief _turnId is a turn ID
     */
    QString _turnId;
    /*!
     * \brief _currentBlockers is a vector of strings that contains names of actions that can blocks this
     */
    QVector<QString> _currentBlockers;
};

#endif // CHATCLIENT_H
