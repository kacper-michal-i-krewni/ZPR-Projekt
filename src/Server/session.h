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
    Session(std::shared_ptr<ServerWorker> owner, int& plNum);
    virtual ~Session(){}
    QVector<std::shared_ptr<ServerWorker> > getPlayers(){return _players;}
    int getNumOfPlayers(){return _numOfPlayers;}
    std::shared_ptr<ServerWorker> getOwner(){return _owner;}
    QJsonObject toJSON();

public slots:
     void blockRequest(const Player &p1, const Player &p2);
     void actionRequest(const Action &a, const Player &p);
     void targetedActionRequest(const Action &a, const Player &player, const Player &target);



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
    QVector<std::shared_ptr<ServerWorker>> _players;
    std::shared_ptr<ServerWorker> _owner;
    int _numOfPlayers;
    QUuid _id;
    //QTimer _timer;
    //void wait();




};

#endif // SESSION_H
