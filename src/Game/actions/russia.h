#ifndef RUSSIA_H
#define RUSSIA_H

#include "action.h"

#include <QObject>

class Russia : public Action
{
public:
    Russia();
    virtual void action() override;
    ~Russia() override;
};

#endif // RUSSIA_H
