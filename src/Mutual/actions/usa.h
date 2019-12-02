#ifndef USA_H
#define USA_H


#include "../action.h"

#include <QObject>

/*!
 * \brief The USA class is a specific action in game and has implementation of action slot.
 */
class USA : public Action
{
public:
    /*!
     * \brief USA constructor
     */
    USA();
    /*!
     * \brief ~USA destructor
     */
    virtual ~USA() override;
public slots:
    /*!
     * \brief action is an implementation of action method from Action class
     *
     *   Player gets 1 mil.
     */
    virtual void action() override;
};


#endif // USA_H
