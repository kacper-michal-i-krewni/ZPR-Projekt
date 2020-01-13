#include "session.h"

#include <QJsonArray>

Session::Session(std::shared_ptr<ServerWorker> owner, int playersLimit):
    _cardstack(new CardStack()),
    _checkTimer(new QTimer(this)),
    _blockTimer(new QTimer(this)),
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
//    connect(_timer.get(), &QTimer::timeout, this,  &Session::sendToAllOnTimeout);
//    _timer->start(Session::ROUNDTIMEOUT);

    for(auto p: _players)
    {
        QString nick = p->getUserName();
        p->setPlayer(std::shared_ptr<Player>(new Player(nick, Session::STARTING_MONEY, 2, false)));
        _cardstack->dealCards(p->getPlayer());

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

void Session::sendToAllExcept(std::shared_ptr<ServerWorker> &player, QJsonObject &message)
{
    for(auto p: _players)
    {
        if(p != player)
            p->sendJson(message);
    }
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

    _turnId = QUuid::createUuid();
    message["turnId"] = _turnId.toString();
    sendToAll(message);

//    QJsonObject message2;
//    message2["type"] = QStringLiteral("sessionMessage");
//    message2["subtype"] = QStringLiteral("yourTurn");
//    player->sendJson(message2);
}

void Session::nextTurn()
{
    nextPlayer();
    turnOf(_currentPlayer);
}


bool Session::actionCanBeChecked(QString &action)
{
    const std::string actionS = action.toUtf8().constData();
    for(std::string a : _actions->getCards())
    {
        if(actionS.compare(a) == 0 )
            return true;
    }
    return false;
}

void Session::startCheckTimer()
{
    connect(_checkTimer.get(), &QTimer::timeout, this,  &Session::callOnCheckTimeout);
    _checkTimer->start(Session::CHECKTIMEOUT);
}

void Session::callOnCheckTimeout()
{
    _checkTimer->stop();
    const std::string actionName =_pendingAction.toUtf8().constData();
    std::map<std::string, Actions::functionPointer> actions = _actions->getMap();
    Actions::functionPointer x = actions[actionName];
    ((_actions.get())->*x)(_currentPlayer->getPlayer(), std::shared_ptr<Player>(nullptr));

    QJsonObject message;
    message["type"] = QStringLiteral("sessionMessage");
    message["sybtype"] = QStringLiteral("actionCompleted");
    message["action"] = _pendingAction;

    sendToAll(message);
    nextPlayer();
    turnOf(_currentPlayer);
}


void Session::handleActionMessage(std::shared_ptr<ServerWorker> &sender, const QJsonObject &docObj)
{
    const QJsonValue turnId = docObj.value(QLatin1String("turnId"));
    if(!(_turnId.toString().compare(turnId.toString(), Qt::CaseInsensitive) == 0))
        return;
    const QJsonValue isTargetedVal = docObj.value(QLatin1String("targeted"));
    const bool isTargeted = isTargetedVal.toBool();
    if (isTargeted)
    {
        const QString action = docObj.value(QLatin1String("text")).toString();
        std::string cost = action.toUtf8().constData();
        if(sender->getPlayer()->getMoney() < _actions->howMuchActionCosts(cost))
        {
            QJsonObject message;
            message["type"] = QStringLiteral("sessionMessage");
            message["subtype"] = QStringLiteral("notEnoughMoney");
            sender->sendJson(message);
            return;
        }

        QString target = docObj.value(QLatin1String("target")).toString();
        if (target.isNull())
        {
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
            std::shared_ptr<ServerWorker> targetPlayer = searchForPlayer(target);
            QJsonObject message;
            message["type"] = QStringLiteral("sessionMessage");
            message["subtype"] = QStringLiteral("youAreATarget");
            message["sender"] = sender->getUserName();
            message["action"] = action;
            targetPlayer->sendJson(message);
            //TODO


        }
    }
    if (!isTargeted)
    {
        QString qActionName =  docObj.value(QLatin1String("text")).toString();
        if(!actionCanBeChecked(qActionName))
        {
               const std::string actionName =qActionName.toUtf8().constData();
               std::map<std::string, Actions::functionPointer> actions = _actions->getMap();
               Actions::functionPointer x = actions[actionName];
               ((_actions.get())->*x)(sender->getPlayer(), std::shared_ptr<Player>(nullptr));

               QJsonObject message;
               message["type"] = QStringLiteral("sessionMessage");
               message["subtype"] = QStringLiteral("actionCompleted");
               message["sender"] = sender->getUserName();
               message["action"] = qActionName;

               sendToAll(message);
               nextTurn();
        }

        if(actionCanBeChecked(qActionName))
        {

            _pendingAction = qActionName;
            startCheckTimer();

            QJsonObject message;
            message["type"] = QStringLiteral("sessionMessage");
            message["subtype"] = QStringLiteral("actionPending");
            message["sender"] = sender->getUserName();
            message["action"] = qActionName;

            sendToAll(message);
        }

        //TODO: for debugging purposes
//        int money = sender->getPlayer()->getMoney();
//        QJsonObject temp;
//        temp["money"] = money;
//        sender->sendJson(temp);

    }
}
