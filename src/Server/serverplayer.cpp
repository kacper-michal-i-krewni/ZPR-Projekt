#include "serverplayer.h"

ServerPlayer::ServerPlayer( std::string nick, double money, int lifes, bool enabled): _nick(nick), _money(money), _lifes(lifes), _enabled(enabled)
{

}

double ServerPlayer::getMoney()
{
    return _money;
}
double ServerPlayer::setMoney( double amount )
{
    _money = amount;
    return _money;
}
const std::string ServerPlayer::getNick()
{
    return _nick;
}
int ServerPlayer::getLifes()
{
    return _lifes;
}
int ServerPlayer::DecrementLifes()
{
    return --_lifes;
}
int ServerPlayer::setLifes( int amount )
{
    return _lifes=amount;
}

//void Player::setServerWorker( ServerWorker* serverWorker )
//{
//    *_serverWorker = serverWorker;
//}

ServerPlayer::~ServerPlayer()
{

}
