#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"

#include <memory>
#include <QObject>



class Player:public QObject
{
    Q_OBJECT
public:
    Player( std::string Nick = "", double money = 3, int lifes = 2, bool enabled = false);
    double getMoney();
    double changeMoney( double difference );
    double setMoney( double amount );

    const std::string getNick();

    int getLifes();
    int DecrementLifes();
    int setLifes( int amount );

    ~Player(){}
private:
    const std::string _nick;
    double _money;
    int _lifes;
    bool _enabled;
    std::vector<std::shared_ptr<Card>> _cards;

};

#endif // PLAYER_H
