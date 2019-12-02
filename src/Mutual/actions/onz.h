#ifndef ONZ_H
#define ONZ_H

#include "../action.h"

#include <QObject>

/*!
 * \brief The ONZ class is a specific action in game and has implementation of action slot.
 */
class ONZ : public Action
{
public:
    /*!
     * \brief ONZ constructor
     */
    ONZ();
    /*!
     * \brief ~ONZ destructor
     */
    virtual ~ONZ() override;
public slots:
    /*!
     * \brief action is an implementation of action method from Action class
     *
     *   
     */
    virtual void action() override;
};

#endif // ONZ_H
