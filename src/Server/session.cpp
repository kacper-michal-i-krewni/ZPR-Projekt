#include "session.h"

Session::Session(std::shared_ptr<ServerWorker> owner, int playersLimit):
    _owner(owner),
    _id(QUuid::createUuid()),
    _playersLimit(playersLimit)
{
    _players.push_back(owner);
}

Session::~Session()
{

}

void Session::start()
{
    // THIS IS FOR TESTING PURPOSES
    m_Timer = new QTimer(this);
    connect(m_Timer, &QTimer::timeout, this,  &Session::sendToAllOnTimeout);
    m_Timer->start(Session::ROUNDTIMEOUT);

    _currentPlayer = _players.first();
    turnOf(_currentPlayer);


}

QVector<std::shared_ptr<ServerWorker> >  Session::getPlayers()
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


void Session::sendToAll(QJsonObject &message)
{
    for(auto p: _players)
    {
        p->sendJson(message);
    }
}

void Session::sendToAllOnTimeout()
{
//   THIS IS FOR TESTING PURPOSES
    nextPlayer();
    turnOf(_currentPlayer);
}

void Session::nextPlayer()
{
    for(auto p: _players)
    {
        if(p==_currentPlayer){
            if(p==_players.last())
            {
                _currentPlayer = _players.first();
                break;
            }else
            {
                int index = _players.indexOf(p) + 1;
                _currentPlayer = _players[index];
                break;
            }
        }
    }
}

void Session::turnOf(std::shared_ptr<ServerWorker> &player)
{
    QJsonObject message;
    message["type"] = QStringLiteral("sessionMessage");
    message["subtype"] = QStringLiteral("newTurn");
    message["player"] = _currentPlayer->getUserName();
    sendToAll(message);

//    QJsonObject message2;
//    message2["type"] = QStringLiteral("sessionMessage");
//    message2["subtype"] = QStringLiteral("yourTurn");
//    player->sendJson(message2);
}
