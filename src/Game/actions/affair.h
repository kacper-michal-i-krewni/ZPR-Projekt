#ifndef AFFAIR_H
#define AFFAIR_H

#include "action.h"

#include <QObject>

/*!
 * \brief The Affair class is a specific action in game and has implementation of action slot.
 */
class Affair : public Action
{
public:
    /*!
     * \brief Affair constructor
     */
    Affair();
    /*!
     * \brief Affair destructor
     */
     virtual ~Affair() override;
public slots:
    /*!
     * \brief action is an implementation of action method
     *
     *  If player has 7 mil or more it is possible for him to make this action. This action make one of the players lose his/her card.
     */
    virtual void action() override;
};

#endif // AFFAIR_H
