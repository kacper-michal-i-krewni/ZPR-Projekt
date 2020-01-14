#include "player.h"

Player::Player(QString nick, int money, int lifes, bool enabled): _nick(nick), _money(money), _lifes(lifes), _enabled(enabled)
{
//    _nick = nick;
//    _money = money;
//    _lifes = lifes;
//    _enabled = enabled;

}

int Player::getMoney()
{
    return _money;
}
void Player::setMoney( int amount )
{
    _money = amount;
}
const QString Player::getNick()
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

QVector<std::shared_ptr<Card> > Player::getCards()
{
    return _cards;
}
//bool Player::isGameOwner()
//{
//    return _gameOwner;
//}

//void Player::setAsGameOwner(bool &b)
//{
//    _gameOwner = b;
//}

Player::~Player()
{

}
