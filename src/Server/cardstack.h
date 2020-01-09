#ifndef CARDSTACK_H
#define CARDSTACK_H


class Card;
class Player;
#include <memory>
#include <QVector>

class CardStack
{
public:
    CardStack();
    std::shared_ptr<Card> takeCard();
    void putCard(std::shared_ptr<Card> card);
    void dealCards(std::shared_ptr<Player> player);

private:
    QVector<std::shared_ptr<Card>> _stack;
};

#endif // CARDSTACK_H
