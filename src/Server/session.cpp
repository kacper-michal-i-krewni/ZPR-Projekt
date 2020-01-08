#include "session.h"

Session::Session(std::shared_ptr<ServerWorker> owner, int& num)
{
    this->_numOfPlayers = num;
    this->_owner = owner;
    this->_players.push_back(owner);

}

QJsonObject Session::toJSON()
{
    QJsonObject json;
    json["numOfPlayers"] = _numOfPlayers;
    json["owner"] = _owner->getUserName();
    return json;
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
