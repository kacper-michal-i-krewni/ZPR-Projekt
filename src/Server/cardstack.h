#ifndef CARDSTACK_H
#define CARDSTACK_H


#include <card.h>
class Player;
#include <memory>
#include <QVector>

/*!
 * \brief The CardStack class is a representation of card stack
 */
class CardStack
{
public:
    /*!
     * \brief CardStack is a constructor to card stack
     */
    CardStack();
    /*!
     * \brief takeCard shuffle cards and take first of them
     * \return cards from the top
     */
    std::shared_ptr<Card> takeCard();
    /*!
     * \brief putCard is a function to put back card in stack
     * \param card card we want to put back in stack
     */
    void putCard(std::shared_ptr<Card> card);
    /*!
     * \brief dealCards gives to cards to player
     * \param player is a arg we want to deal cards
     */
    void dealCards(std::shared_ptr<Player> player);

private:
    /*!
     * \brief _stack is a vector with cards
     */
    QVector<std::shared_ptr<Card>> _stack;
};

#endif // CARDSTACK_H
