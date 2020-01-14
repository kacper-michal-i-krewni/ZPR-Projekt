#ifndef PLAYER_H
#define PLAYER_H


#include <QObject>
#include <memory>
#include "actions.h"


class Card;

/*!
 * \brief The Player class.
 *
 * Player class is a representation of player in game. Holds info about player like money nick etc.
 */
class Player:public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Player construction.
     * \param nick is a string field that holds nickname of player
     * \param money says how much money in millions has w player. When the game starts every player has 2 mil.
     * \param lifes says how many lifes does player have. When the game starts every player has 2 lifes.
     * \param enabled says if this player has a turn right now. Disable on start of game.
     */
    Player(QString nick = "", int money = 200, int lifes = 2, bool enabled = false);
    /*!
     * \brief getMoney is a function that returns how much money player has.
     * \return How much money player has.
     */
    int getMoney();
    /*!
     * \brief setMoney is a function that sets player money
     * \param amount is an argument that says how much money player should have after that function
     * \return it returns the amount of money that player have after this method
     */
    void setMoney( int amount );
    /*!
     * \brief getNick is a function that return a player's nickname
     * \return nickname as a string
     */
     const QString getNick();
    /*!
     * \brief getLifes is a function that return number of lifes.
     * \return lifes that player has.
     */
    int getLifes();
    /*!
     * \brief DecrementLifes is a function that decrement player's lifes if he losts one.
     * \return value of lifes after decrement.
     */
    int DecrementLifes();
    /*!
     * \brief setLifes is a function that can set value of _lifes if needs.
     * \param amount is a param that say how many life pleyer should have
     * \return value of _lives after decrement
     */
    int setLifes( int amount );
    /*!
     * \brief ~Player is a Player destructor
     */
    void takeCard(std::shared_ptr<Card> card);

    QVector<std::shared_ptr<Card> > getCards

//    bool isGameOwner();

//    void setAsGameOwner(bool &b);

    ~Player();
private:
    /*!
     * \brief _nick is a strong with player's nickname
     */
    const QString _nick;
    /*!
     * \brief _money is an amount of money that player has.
     */
    int _money;
    /*!
     * \brief _lifes says how many lifes player has.
     */
    int _lifes;
    /*!
     * \brief _enabled says if player can make a move.
     */
    bool _enabled;
    //bool _gameOwner;
    QVector<std::shared_ptr<Card> > _cards;
};

#endif // PLAYER_H
