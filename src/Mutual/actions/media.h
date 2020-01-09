#ifndef MEDIA_H
#define MEDIA_H

#include "../action.h"

#include <QObject>


/*!
 * \brief The Media class is a specific action in game and has implementation of action slot.
 */
class Media : public Action
{
public:
    /*!
     * \brief Media constructor
     */
    Media();
    /*!
     * \brief ~Media destructor
     */
    virtual ~Media() override;
public slots:
    /*!
     * \brief action is an implementation of action method from Action class
     *
     *  Player look at two cards from the top and decide if he wants to change one or two cards in his hand with those from deck. 
     */
    virtual void action() override;
};


#endif // MEDIA_H
