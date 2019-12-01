#ifndef PROTEST_H
#define PROTEST_H

#include "action.h"

#include <QObject>

class Protest : public Action
{
public:
    Protest();
    virtual void action() = 0;
    virtual ~Protest(){}
};

#endif // PROTEST_H
