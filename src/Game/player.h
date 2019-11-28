#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>



class Player
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

    virtual ~Player();
private:
    const std::string _Nick;
    double _money;
    int _lifes;
    bool _enabled;

};

#endif // PLAYER_H
