#ifndef LOCALBIZNESMAN_H
#define LOCALBIZNESMAN_H

#include "action.h"

#include <QObject>

class LocalBiznesman : public Action
{
public:
    LocalBiznesman();
    virtual void action() override;
    ~LocalBiznesman() override;
};

#endif // LOCALBIZNESMAN_H
