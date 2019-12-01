#ifndef EU_H
#define EU_H

#include "action.h"

#include <QObject>

class EU : public Action
{
public:
    EU();
    virtual void action() = 0;
    virtual ~EU(){}
};

#endif // EU_H
