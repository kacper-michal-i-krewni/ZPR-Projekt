#include "session.h"

Session::Session(ServerWorker* owner, int& num)
{
    this->_numOfPlayers = num;
    this->_owner = owner;
    this->_players.push_back(owner);

}
void Session::blockRequest(const Player &p1, const Player &p2)
{

}
void Session::actionRequest(const Action &a, const Player &p)
{

}
void Session::targetedActionRequest(const Action &a, const Player &player, const Player &target)
{

}
