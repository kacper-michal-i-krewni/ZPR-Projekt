#ifndef SESSION_H
#define SESSION_H

#include "../Mutual/action.h"
#include "serverworker.h"
#include <memory>
#include <QTimer>
#include <QJsonObject>

#include <QObject>
#include <QUuid>

class Player;
class Session: public QObject
{
    Q_OBJECT
public:
    Session(std::shared_ptr<ServerWorker> owner, int playersLimit);
    virtual ~Session();
    QVector<std::shared_ptr<ServerWorker> > getPlayers();
    void sendToAll(QJsonObject &message);
    void addPlayer(const std::shared_ptr<ServerWorker> player);
    void removePlayer(const std::shared_ptr<ServerWorker> player);
    int getNumOfPlayers();
    std::shared_ptr<ServerWorker> getOwner();
    QString getId();
    QJsonObject toJSON();
    void start();

    int ROUNDTIMEOUT = 5*1000;

public slots:

     void blockRequest(const Player &p1, const Player &p2);
     void actionRequest(const Action &a, const Player &p);
     void targetedActionRequest(const Action &a, const Player &player, const Player &target);
     void sendToAllOnTimeout();



signals:
    void hasTurn(const Player &p);
    //TODO: what type should dataRequest return?
//    void dataRequest(const QString &playerId, const PlayerData &pData);
//    void actionPlayed(const Action &a, const Player &p);
//    void targetedActionPlayed(const Action &a, const Player &p, const Player &target);
    void checkCard();
    void blockEnable(const Player &current);
    void blockDisable(); //wysyla do serwera info
    void checkEnable(const Player &current);
    void checkDisable();


private:
    QTimer* m_Timer;
    QVector<std::shared_ptr<ServerWorker> > _players;
    std::shared_ptr<ServerWorker> _owner;
    QUuid _id;
    int _playersLimit;
    //QTimer _timer;
    //void wait();




};

#endif // SESSION_H
