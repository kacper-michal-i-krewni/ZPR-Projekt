#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include <QObject>
#include <QTcpSocket>
#include "player.h"


class QJsonObject;
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
     * \brief setSocketDescriptor
     * \param socketDescriptor
     * \return
     */
    virtual bool setSocketDescriptor(qintptr socketDescriptor);
    /*!
     * \brief userName is a typical function getter
     * \return m_userName
     */
    QString userName() const;
    /*!
     * \brief setUserName is a function that sets m_userName field
     * \param userName is a new m_userName
     */
    void setUserName(const QString &userName);
    /*!
     * \brief sendJson send json message
     * \param jsonData is a data that is sended.
     */
    void sendJson(const QJsonObject &jsonData);

    void setPlayer(const std::shared_ptr<Player*> player);
    std::shared_ptr<Player*> getPlayer();
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
    QTcpSocket *m_serverSocket;
    /*!
     * \brief m_userName is a string with nickname of user
     */
    QString m_userName;

    std::shared_ptr<Player*> _player;
};

#endif // SERVERWORKER_H
