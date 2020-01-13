#include "actions.h"
#include "player.h"


Actions::Actions()
{
    fillMap();
    fillCards();
}


Actions::~Actions()
{

}




std::map<std::string, Actions::functionPointer> Actions::getMap()
{
    return _actionsMap;
}

QVector<std::string> Actions::getCards()
{
    return _cards;
}

const int Actions::howMuchActionCosts(std::string &action)
{
    if(action.compare("protest") == 0)
        return Actions::PROTEST_PRICE;
    else if (action.compare("affair") == 0)
        return Actions::AFFAIR_PRICE;
    else
        return 0;
}

void Actions::affair(std::shared_ptr<Player> executer,  std::shared_ptr<Player> victim)
{

}
void Actions::eu(std::shared_ptr<Player>executer, std::shared_ptr<Player> victim)
{

}
void Actions::localBiznesman(std::shared_ptr<Player> executer, std::shared_ptr<Player> victim)
{

}
void Actions::media(std::shared_ptr<Player> executer, std::shared_ptr<Player> victim)
{

}
void Actions::onz(std::shared_ptr<Player> executer, std::shared_ptr<Player> victim)
{

}
void Actions::police(std::shared_ptr<Player> executer, std::shared_ptr<Player> victim)
{

}
void Actions::protest(std::shared_ptr<Player> executer, std::shared_ptr<Player> victim)
{

}
void Actions::russia(std::shared_ptr<Player> executer, std::shared_ptr<Player> victim)
{

}
void Actions::usa(std::shared_ptr<Player> executer, std::shared_ptr<Player> victim)
{
    int additionalMoney = 100;
    executer->setMoney(executer->getMoney() + additionalMoney);
}

void Actions::fillMap()
{
    _actionsMap["affair"] = &Actions::affair;
    _actionsMap["eu"] = &Actions::eu;
    _actionsMap["localbiznesman"] = &Actions::localBiznesman;
    _actionsMap["media"] = &Actions::media;
    _actionsMap["onz"] = &Actions::onz;
    _actionsMap["police"] = &Actions::police;
    _actionsMap["protest"] = &Actions::protest;
    _actionsMap["russia"] = &Actions::russia;
    _actionsMap["usa"] = &Actions::usa;

}


void Actions::fillCards()
{
    _cards.push_front("eu");
    _cards.push_front("media");
    _cards.push_front("onz");
    _cards.push_front("police");
    _cards.push_front("protest");
    _cards.push_front("russia");

}

