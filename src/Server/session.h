#ifndef SESSION_H
#define SESSION_H

#include "../../Mutual/action.h"
#include "../../Mutual/player.h"
#include <memory>
#include <QTimer>

#include <QObject>

class Session: public QObject
{
//    Q_OBJECT
public:
    Session();
    enum PlayerData{
        MONEY, LIFES, ACTION, /*ACTION_DESTINATION,*/ CARDS
    };
    std::vector<Player> getPlayers();
    virtual ~Session(){}

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
    std::vector<std::shared_ptr<Player>> _players;
    QTimer _timer;
    //void wait();




};

#endif // SESSION_H
