#include "session.h"

Session::Session(std::shared_ptr<ServerWorker> owner, int playersLimit): _id(QUuid::createUuid()), _owner(owner), _playersLimit(playersLimit)
{
    _players.push_back(owner);
}

Session::~Session()
{

}

QVector<std::shared_ptr<ServerWorker>>  Session::getPlayers()
{
    return _players;
}



void Session::addPlayer(const std::shared_ptr<ServerWorker> player)
{
     _players.push_back(player);
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


int Session::getNumOfPlayers()
{
    return _players.size();
}

std::shared_ptr<ServerWorker> Session::getOwner()
{
    return _owner;
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

QString Session::getId()
{
    return _id.toString();
}

QJsonObject Session::toJSON()
{
    QJsonObject json;
    json["id"] = getId();
    json["numOfPlayers"] = getNumOfPlayers();
    json["playersLimit"] = _playersLimit;
    json["owner"] = getOwner()->getUserName();
    return json;
}
