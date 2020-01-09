#include "player.h"

Player::Player( std::string nick, double money, int lifes, bool enabled): _nick(nick), _money(money), _lifes(lifes), _enabled(enabled)
{

}

double Player::getMoney()
{
    return _money;
}
double Player::setMoney( double amount )
{
    _money = amount;
    return _money;
}
const std::string Player::getNick()
{
    return _nick;
}
int Player::getLifes()
{
    return _lifes;
}
int Player::DecrementLifes()
{
    return --_lifes;
}
int Player::setLifes( int amount )
{
    return _lifes=amount;
}
void Player::takeCard(std::shared_ptr<Card> card)
{
    _cards.push_back(card);
}

Player::~Player()
{

}
