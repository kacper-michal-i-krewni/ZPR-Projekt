#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include <QObject>
#include <QTcpSocket>
#include "player.h"


class QJsonObject;
/*!
 * \brief The ServerWorker class is responsible for every message sent and coordinate game
 */
class ServerWorker : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ServerWorker)
public:
    /*!
     * \brief ServerWorker
     * \param parent
     */
    explicit ServerWorker(QObject *parent = nullptr);
    /*!
     * \brief setSocketDescriptor sets socket descriptor
     * \param socketDescriptor a socket descriptor
     * \return
     */
    virtual bool setSocketDescriptor(qintptr socketDescriptor);
    /*!
     * \brief userName is a typical function getter
     * \return m_userName
     */
    QString getUserName();
    /*!
     * \brief setUserName is a function that sets m_userName field
     * \param userName is a new m_userName
     */
    void setUserName(const QString &getUserName);
    /*!
     * \brief sendJson send json message
     * \param jsonData is a data that is sended.
     */
    void sendJson(const QJsonObject &jsonData);
    /*!
     * \brief setPlayer is setting _player field
     * \param player is an arg we want to set as _player
     */
    void setPlayer(const std::shared_ptr<Player> player);
    /*!
     * \brief getPlayer is a getter of _player
     * \return _player
     */
    std::shared_ptr<Player> getPlayer();
    /*!
     * \brief isGameOwner checks if this serverworker is game owner
     * \return true of false
     */
    bool isGameOwner();
    /*!
     * \brief setAsGameOwner sets_isGameOwner field to true of false
     * \param b true or false
     */
    void setAsGameOwner(const bool &b);
    /*!
     * \brief isInGame checks if player pley a game right know
     * \return true or false
     */
    bool isInGame();
    /*!
     * \brief setAsInGame sets _isInGame field
     * \param b true or false
     */
    void setAsInGame(const bool &b);

signals:
    /*!
     * \brief jsonReceived is a signal that handle reciving messages.
     * \param jsonDoc is a data that is recived
     */
    void jsonReceived(const QJsonObject &jsonDoc);
    /*!
     * \brief disconnectedFromClient is a signal that handle disconnecting
     */
    void disconnectedFromClient();
    /*!
     * \brief error is a signal that inform about eror
     */
    void error();
    /*!
     * \brief logMessage is a signal that execute logMessage on server
     * \param msg is a message that is displayed on log out.
     */
    void logMessage(const QString &msg);
public slots:
    /*!
     * \brief disconnectFromClient is function that handle disconnecting
     */
    void disconnectFromClient();
private slots:
    /*!
     * \brief receiveJson is a function that is resposible for reciving message
     * in json format
     */
    void receiveJson();
private:
    /*!
     * \brief m_serverSocket is a variable that add functions of sockets
     */
    std::shared_ptr<QTcpSocket> m_serverSocket;
    /*!
     * \brief m_userName is a string with nickname of user
     */
    QString m_userName;
    /*!
     * \brief _player a pointer to player object
     */
    std::shared_ptr<Player> _player;
    /*!
     * \brief _isGameOwner says if player is game owner
     */
    bool _isGameOwner;
    /*!
     * \brief _isInGame says if player is in game
     */
    bool _isInGame;
};

#endif // SERVERWORKER_H
