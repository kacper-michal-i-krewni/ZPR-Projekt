#include "card.h"

Card::Card(QString type): _type(type)
{

}


QString Card::getType()
{
    return _type;
}


void Card::setType(QString type)
{
    _type = type;
}

