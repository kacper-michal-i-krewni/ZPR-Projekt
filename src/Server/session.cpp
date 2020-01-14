#include "session.h"

#include <QJsonArray>

Session::Session(std::shared_ptr<ServerWorker> owner, int playersLimit):
    _cardstack(new CardStack()),
    _timer(new QTimer(this)),
    _blockTimer(new QTimer(this)),
    _owner(owner),
    _actions(new Actions()),
    _id(QUuid::createUuid()),
    _playersLimit(playersLimit),
    _this(this)
{
    _players.push_back(owner);
    connect(_timer.get(), &QTimer::timeout, this,  &Session::callOnTimeout);
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

int Session::getPlayersLimit()
{
    return _playersLimit;
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

bool Session::checkIfPlayerIsInSession(std::shared_ptr<ServerWorker> sender)
{
    for(auto p: _players)
    {
        if(p==sender)
        {
            return true;
        }
    }
    return false;
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
    emit sendUpdate(_this);
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

bool Session::checkAction(std::shared_ptr<ServerWorker> &player,const QString &action)
{
    QVector<std::shared_ptr<Card> > playerCards = player->getPlayer()->getCards();
    for(auto c: playerCards)
    {
        if(c->getType().compare(action, Qt::CaseInsensitive) == 0)
            return true;
    }
    return false;
}


void Session::callOnTimeout()
{
    _timer->stop();
    const std::string actionName =_pendingAction.toUtf8().constData();
    std::map<std::string, Actions::functionPointer> actions = _actions->getMap();
    Actions::functionPointer x = actions[actionName];
    ((_actions.get())->*x)(_currentPlayer->getPlayer(), std::shared_ptr<Player>(nullptr));

    QJsonObject message;
    message["type"] = QStringLiteral("sessionMessage");
    message["subtype"] = QStringLiteral("actionCompleted");
    message["sender"] = _currentPlayer->getPlayer()->getNick();
    message["action"] = _pendingAction;

    sendToAll(message);
    nextTurn();
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
            _pendingAction = action;

            std::shared_ptr<ServerWorker> targetPlayer = searchForPlayer(target);
            QJsonObject message;
            message["type"] = QStringLiteral("sessionMessage");
            message["subtype"] = QStringLiteral("youAreATarget");
            message["sender"] = sender->getUserName();
            message["action"] = action;
            QJsonArray blockerArray;
            QVector<QString> blockers = _actions->getActionsThatBlock(action);
            for(auto b : blockers)
            {
                blockerArray.append(b);
            }

            message["blockers"] = blockerArray;
            targetPlayer->sendJson(message);

            _timer->start(Session::BLOCKTIMEOUT);

            QJsonObject messageToNonTargets;
            messageToNonTargets["type"] = QStringLiteral("sessionMessage");
            messageToNonTargets["subtype"] = QStringLiteral("actionCompleted");
            messageToNonTargets["sender"] = sender->getUserName();
            messageToNonTargets["action"] = action;

            sendToAllExcept(targetPlayer, messageToNonTargets);
        }
    }
    else // (!isTargeted)
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

            QJsonObject message;
            message["type"] = QStringLiteral("sessionMessage");
            message["subtype"] = QStringLiteral("actionPending");
            message["sender"] = sender->getUserName();
            message["action"] = qActionName;
            sendToAll(message);

            _timer->start(Session::CHECKTIMEOUT);
        }
    }
}

void Session::handleCaunterActionMessage(std::shared_ptr<ServerWorker> &sender, const QJsonObject &docObj)
{
    const QJsonValue turnId = docObj.value(QLatin1String("turnId"));
    if(!(_turnId.toString().compare(turnId.toString(), Qt::CaseInsensitive) == 0))
        return;
    const QJsonValue subtype = docObj.value(QLatin1String("subtype"));
    if(subtype.toString().compare("block", Qt::CaseInsensitive) == 0)
    {

    }
    if(subtype.toString().compare("check", Qt::CaseInsensitive) == 0)
    {
       _timer->stop();
       QJsonObject message;
       message["type"] = QStringLiteral("sessionMessage");
       message["subtype"] = QStringLiteral("checkResult");
       message["checking"] = sender->getPlayer()->getNick();
       message["checked"] = _currentPlayer->getPlayer()->getNick();

       //const QString action = docObj.value(QLatin1String("action")).toString();
       if(checkAction(_currentPlayer,_pendingAction))
       {
           sender->getPlayer()->DecrementLifes();
           message["result"] = true;
       }
       else
       {
           _currentPlayer->getPlayer()->DecrementLifes();
           message["result"] = false;
       }

       sendToAll(message);
       nextTurn();

    }
}
