#ifndef USA_H
#define USA_H


#include "action.h"
#include <QObject>

class USA : public Action
{
public:
    USA();
    virtual void action() override;
    virtual ~USA() override;
};

#endif // USA_H
