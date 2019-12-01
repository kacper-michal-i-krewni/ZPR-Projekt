#ifndef AFFAIR_H
#define AFFAIR_H

#include "action.h"

#include <QObject>

class Affair : public Action
{
public:
    Affair();
    virtual void action() override;
    virtual ~Affair() override;
};

#endif // AFFAIR_H
