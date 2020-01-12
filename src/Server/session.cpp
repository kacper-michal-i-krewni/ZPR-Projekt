#include "session.h"

#include <QJsonArray>

Session::Session(std::shared_ptr<ServerWorker> owner, int playersLimit):
    _timer(new QTimer(this)),
    _owner(owner),
    _actions(new Actions()),
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
    connect(_timer.get(), &QTimer::timeout, this,  &Session::sendToAllOnTimeout);
    _timer->start(Session::ROUNDTIMEOUT);

    for(auto p: _players)
    {
        QString nick = p->getUserName();
        p->setPlayer(std::shared_ptr<Player>(new Player(nick, 2, 2, false)));
    }
    _currentPlayer = _players.first();
    turnOf(_currentPlayer);


}

std::shared_ptr<ServerWorker> Session::searchForPlayer(QString nickname)
{
    for ( std::shared_ptr<ServerWorker> _p : _players)
    {
        if(_p->getUserName().compare(nickname, Qt::CaseInsensitive) == 0 )
        {
            return _p;
        }
    }
    return std::shared_ptr<ServerWorker>(nullptr);
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
    //for(int p = 0; p < _players.size(); p++)
    //{
    //    if(_players[p]==player)
    //    {
    //        _players.removeAt(p);
    //        return;
    //    }
    //}
    _players.removeOne(player);
}


int Session::getNumOfPlayers()
{
    return _players.size();
}

std::shared_ptr<ServerWorker> Session::getOwner()
{
    return _owner;
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

void Session::handleActionMessage(std::shared_ptr<ServerWorker> &sender, const QJsonObject &docObj)
{
    const QJsonValue isTargetedVal = docObj.value(QLatin1String("targeted"));
    const bool isTargeted = isTargetedVal.toBool();
    if (isTargeted)
    {
        QString target = docObj.value(QLatin1String("target")).toString();
        if (target.isNull())
        {
            QString action = docObj.value(QLatin1String("text")).toString();
            QJsonObject message;
            message["type"] = QStringLiteral("sessionMessage");
            message["subtype"] = QStringLiteral("targetSpecify");
            message["action"] = action;
            QJsonArray playerArray;
            for(auto p : _players)
            {
                playerArray.append(p->getUserName());
            }
            message["players"] = playerArray;
            sender->sendJson(message);
        }
        else
        {
            std::shared_ptr<ServerWorker> player = searchForPlayer(target);

            //TODO


        }
    }
    if (!isTargeted)
    {
        const std::string actionName = docObj.value(QLatin1String("text")).toString().toUtf8().constData();
        std::map<std::string, Actions::functionPointer> actions = _actions->getMap();
        Actions::functionPointer x = actions[actionName];
        ((_actions.get())->*x)(sender->getPlayer(), std::shared_ptr<Player>(nullptr));

        //TODO: for debugging purposes
        int money = sender->getPlayer()->getMoney();
        QJsonObject temp;
        temp["money"] = money;
        sender->sendJson(temp);

    }
}
