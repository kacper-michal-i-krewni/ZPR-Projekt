#ifndef RUSSIA_H
#define RUSSIA_H

#include "action.h"

#include <QObject>


/*!
 * \brief The Russia class is a specific action in game and has implementation of action slot.
 */
class Russia : public Action
{
public:
    /*!
     * \brief Russia constructor
     */
    Russia();
    /*!
     * \brief ~Russia destructor
     */
    virtual ~Russia() override;
public slots:
    /*!
     * \brief action is an implementation of action method from Action class
     *
     *   Player gets 3 mil.
     */
    virtual void action() override;
};

#endif // RUSSIA_H
