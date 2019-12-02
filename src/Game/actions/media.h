#ifndef MEDIA_H
#define MEDIA_H

#include "action.h"

#include <QObject>

class Media : public Action
{
public:
    Media();
    virtual void action() override;
    ~Media() override;
};

#endif // MEDIA_H
