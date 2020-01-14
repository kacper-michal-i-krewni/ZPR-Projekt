#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <memory>

/*!
 * \brief The Card class
 */
class Card
{
public:
    explicit Card(QString type);
    QString getType();
    void setType(QString type);
private:
    QString _type;
};

#endif // CARD_H
