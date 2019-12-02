#ifndef POLICE_H
#define POLICE_H

#include "action.h"

#include <QObject>

class Police : public Action
{
public:
    Police();
    virtual void action() override;
    ~Police() override;
};

#endif // POLICE_H
