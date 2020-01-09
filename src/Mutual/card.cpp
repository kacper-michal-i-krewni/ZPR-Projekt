#include "card.h"

Card::Card(std::shared_ptr<Action> type): _type(type)
{

}


std::shared_ptr<Action> Card::getType()
{
    return std::shared_ptr<Action>(_type);
}


void Card::setType(std::shared_ptr<Action> type)
{
    _type = type;
}

