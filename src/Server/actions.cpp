#include "actions.h"


Actions::Actions()
{
    fillMap();
}


Actions::~Actions()
{

}

std::map<std::string, Actions::functionPointer> Actions::getMap()
{
    return _actionsMap;
}

void Actions::affair(Player *executer, Player *victim)
{

}
void Actions::eu(Player *executer, Player *victim)
{

}
void Actions::localBiznesman(Player *executer, Player *victim)
{

}
void Actions::media(Player *executer, Player *victim)
{

}
void Actions::onz(Player *executer, Player *victim)
{

}
void Actions::police(Player *executer, Player *victim)
{

}
void Actions::protest(Player *executer, Player *victim)
{

}
void Actions::russia(Player *executer, Player *victim)
{

}
void Actions::usa(Player *executer, Player *victim)
{

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
