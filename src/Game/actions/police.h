#ifndef POLICE_H
#define POLICE_H

#include "action.h"

#include <QObject>

class Police : public Action
{
public:
    Police();
    virtual void action() = 0;
    virtual ~Police(){}
};

#endif // POLICE_H
