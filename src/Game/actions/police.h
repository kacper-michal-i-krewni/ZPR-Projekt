#ifndef POLICE_H
#define POLICE_H

#include "action.h"

#include <QObject>

/*!
 * \brief The Police class is a specific action in game and has implementation of action slot.
 */
class Police : public Action
{
public:
    /*!
     * \brief Police constructor
     */
    Police();
    /*!
     * \brief ~Police destructor
     */
    virtual ~Police() override;
public slots:
    /*!
     * \brief action is an implementation of action method from Action class
     *
     *   Player steals 2 mil from one of the players.
     */
    virtual void action() override;
};

#endif // POLICE_H
