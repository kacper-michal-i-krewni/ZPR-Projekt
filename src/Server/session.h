#ifndef SESSION_H
#define SESSION_H

#include<QVector>
#include<QObject>
#include "serverworker.h"

class Session: public QObject
{
    Q_OBJECT

public:
    Session(QVector <ServerWorker *> players);
private:
    //Session parameters
    QVector<ServerWorker *> allPlayers;

    int maxPlayerNum;
    bool opened;
    bool started;

public:
signals:
    void sessionCreated();
    void sessionStarted();
    void sessionEnded();

private slots:
    void messagePlayers();


};
#endif // SESSION_H
