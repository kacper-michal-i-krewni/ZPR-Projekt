#ifndef PROTEST_H
#define PROTEST_H

#include "action.h"

#include <QObject>

class Protest : public Action
{
public:
    Protest();
    virtual void action() override;
    ~Protest() override;
};

#endif // PROTEST_H
