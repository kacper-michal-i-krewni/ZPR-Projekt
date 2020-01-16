#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <memory>

/*!
 * \brief The Card class is representation of card
 */
class Card
{
public:
    /*!
     * \brief Card a constructor
     * \param type is a type of card that is saved in _type
     */
    explicit Card(QString type);
    /*!
     * \brief getType returns type of card
     * \return type of card
     */
    QString getType();
    /*!
     * \brief setType is a setter to _type
     * \param type is a name of action that is connected to card
     */
    void setType(QString type);
private:
    /*!
     * \brief _type keep type of action connected with card
     */
    QString _type;
};

#endif // CARD_H
