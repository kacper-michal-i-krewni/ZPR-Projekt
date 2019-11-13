#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include "player.h"

#include <QObject>
#include <QTcpSocket>
#include <QUuid>
//#include "session.h"

class QJsonObject;
class ServerWorker : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ServerWorker)
//fields
private:
    QTcpSocket *m_serverSocket;
    Player *player;


//methods
public:
    explicit ServerWorker(QObject *parent = nullptr);
    virtual bool setSocketDescriptor(qintptr socketDescriptor);
    QString userName() const;
    void setUserName(const QString &userName);
    void sendJson(const QJsonObject &jsonData);
    //void isInSession(const Session &session);
signals:
    void jsonReceived(const QJsonObject &jsonDoc);
    void disconnectedFromClient();
    void error();
    void logMessage(const QString &msg);
public slots:
    void disconnectFromClient();
private slots:
    void receiveJson();


};

#endif // SERVERWORKER_H
