#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <memory>

class Action;
/*!
 * \brief The Card class
 */
class Card
{
public:
    explicit Card(std::shared_ptr<Action> type);
    std::shared_ptr<Action> getType();
    void setType(std::shared_ptr<Action> type);
private:
    std::shared_ptr<Action> _type;
};

#endif // CARD_H
