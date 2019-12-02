#ifndef LOCALBIZNESMAN_H
#define LOCALBIZNESMAN_H

#include "../action.h"

#include <QObject>

/*!
 * \brief The LocalBiznesman class is a specific action in game and has implementation of action slot.
 */
class LocalBiznesman : public Action
{
public:
    /*!
     * \brief LocalBiznesman constructor
     */
    LocalBiznesman();
    /*!
     * \brief ~LocalBiznesman destructor
     */
    virtual ~LocalBiznesman() override;
public slots:
    /*!
     * \brief action is an implementation of action method from Action class
     *
     *  Player get 2 mil.
     */
    virtual void action() override;
};
#endif // LOCALBIZNESMAN_H
