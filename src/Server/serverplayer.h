#ifndef SERVERPLAYER_H
#define SERVERPLAYER_H

#include "card.h"
#include <memory>
#include <QObject>
#include <QVector>
//#include <serverworker.h>


/*!
 * \brief The Player class.
 *
 * Player class is a representation of player in game. Holds info about player like money nick etc.
 */
class ServerPlayer:public QObject
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
    ServerPlayer( std::string nick = "", double money = 2, int lifes = 2, bool enabled = false);
    /*!
     * \brief getMoney is a function that returns how much money player has.
     * \return How much money player has.
     */
    double getMoney();
    /*!
     * \brief setMoney is a function that sets player money
     * \param amount is an argument that says how much money player should have after that function
     * \return it returns the amount of money that player have after this method
     */
    double setMoney( double amount );
    /*!
     * \brief getNick is a function that return a player's nickname
     * \return nickname as a string
     */
    const std::string getNick();
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
     * \brief setServerWorker is a function that set _serverWorker if player is connecting to a game
     * \param serverWorker is a pointer to serverworker
     */
//    void setServerWorker( ServerWorker* serverWorker );
    /*!
     * \brief ~Player is a Player destructor
     */
    ~ServerPlayer();
private:
    /*!
     * \brief _nick is a strong with player's nickname
     */
    const std::string _nick;
    /*!
     * \brief _money is an amount of money that player has.
     */
    double _money;
    /*!
     * \brief _lifes says how many lifes player has.
     */
    int _lifes;
    /*!
     * \brief _enabled says if player can make a move.
     */
    bool _enabled;
    /*!
     * \brief _cards is a vector that contains which cards player has.
     */
    QVector<std::shared_ptr<Card>> _cards;
    /*!
     * \brief _serverWorker is a representation of connection in server
     */
//    std::shared_ptr<ServerWorker*> _serverWorker;

};

#endif // SERVERPLAYER_H
