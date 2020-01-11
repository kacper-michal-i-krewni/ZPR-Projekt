#include "session.h"

Session::Session(std::shared_ptr<ServerWorker> owner, int& num)
{
    this->_id = QUuid::createUuid();
    this->_numOfPlayers = num;
    this->_owner = owner;
    this->_players.push_back(owner);
}

QJsonObject Session::toJSON()
{
    QJsonObject json;
    json["id"] = _id.toString();
    json["numOfPlayers"] = _numOfPlayers;
    json["owner"] = _owner->getUserName();
    return json;
}

void Session::removePlayer(const std::shared_ptr<ServerWorker> player)
{
    for(int p = 0; p < _players.size(); p++)
    {
        if(_players[p]==player)
        {
            _players.removeAt(p);
            return;
        }
    }
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
