#include "gameplayer.h"

GamePlayer::GamePlayer( ChatClient *chatClient, std::string nick, double money, int lifes, bool enabled): _chatClient(chatClient),  _nick(nick), _money(money), _lifes(lifes), _enabled(enabled)
{

}

double GamePlayer::getMoney()
{
    return _money;
}
double GamePlayer::setMoney( double amount )
{
    _money = amount;
    return _money;
}
const std::string GamePlayer::getNick()
{
    return _nick;
}
int GamePlayer::getLifes()
{
    return _lifes;
}
int GamePlayer::DecrementLifes()
{
    return --_lifes;
}
int GamePlayer::setLifes( int amount )
{
    return _lifes=amount;
}

//void Player::setServerWorker( ServerWorker* serverWorker )
//{
//    *_serverWorker = serverWorker;
//}

ChatClient* GamePlayer::getChatClient() const
{
    return _chatClient;
}

GamePlayer::~GamePlayer()
{

}
