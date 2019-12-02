#ifndef EU_H
#define EU_H

#include "action.h"

#include <QObject>

/*!
 * \brief The EU class is a specific action in game and has implementation of action slot.
 */
class EU : public Action
{
public:
    EU();
    ~EU() override;
public slots:
    virtual void action() override;
};

#endif // EU_H
