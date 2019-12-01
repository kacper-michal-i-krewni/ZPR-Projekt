#ifndef ONZ_H
#define ONZ_H

#include "action.h"

#include <QObject>

class ONZ : public Action
{
public:
    ONZ();
    virtual void action() = 0;
    virtual ~ONZ(){}
};

#endif // ONZ_H
