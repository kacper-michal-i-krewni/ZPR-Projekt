#ifndef SESSION_H
#define SESSION_H

#include "actions.h"
#include "cardstack.h"
#include "serverworker.h"
#include <memory>
#include <QTimer>
#include <QJsonObject>

#include <QObject>
#include <QUuid>

class Player;
/*!
 * \brief The Session class which holds all ifo about session and manage it
 */
class Session: public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Session a constructor of sessiom
     * \param owner is a player who created a session
     * \param playersLimit how many players can join to session
     */
    Session(std::shared_ptr<ServerWorker> owner, int playersLimit);
    /*!
     * \brief ~Session is a destructor
     */
    virtual ~Session();
    /*!
     * \brief getPlayers is a function that returns vector with players
     * \return a vector with serverworkers objects
     */
    QVector<std::shared_ptr<ServerWorker> > getPlayers();
    /*!
     * \brief sendToAllis a function that sends to all players in session a message passed in argument
     * \param message is a message we want to send
     */
    void sendToAll(QJsonObject &message);
    /*!
     * \brief sendToAllExcept is a function similar to sendToAll but we can exclude a player
     * \param player is a pointer to player we want exclude
     * \param message is a meesage we want to send
     */
    void sendToAllExcept(std::shared_ptr<ServerWorker> &player, QJsonObject &message);
    /*!
     * \brief addPlayer adds a player to session
     * \param player is a pointer to player
     */
    void addPlayer(const std::shared_ptr<ServerWorker> player);
    /*!
     * \brief removePlayer
     * \param player
     */
    void removePlayer(const std::shared_ptr<ServerWorker> player);
    /*!
     * \brief getNumOfPlayers returns how many players is in session
     * \return a number of players
     */
    int getNumOfPlayers();
    /*!
     * \brief getPlayersLimit returns how many players can be in session
     * \return limit of players
     */
    int getPlayersLimit();
    /*!
     * \brief getOwner returns owner of this session
     * \return an owner of session
     */
    std::shared_ptr<ServerWorker> getOwner();
    /*!
     * \brief getId returns ID of session
     * \return
     */
    QString getId();
    /*!
     * \brief toJSON is a function that parse a session to JSON sended in message to client
     * \return a complete JSon Object
     */
    QJsonObject toJSON();
    /*!
     * \brief checkIfPlayerIsInSession checks if player is in session
     * \param sender player that is checked
     * \return true or false
     */
    bool checkIfPlayerIsInSession(std::shared_ptr<ServerWorker> sender);
    /*!
     * \brief start is a function that prepare session to start
     */
    void start();
    /*!
     * \brief handleActionMessage read message and check if action can be executed are send messgae about failure or success
     * \param sender is a executer of an action
     * \param docObj is a message we interpert
     */
    void handleActionMessage(std::shared_ptr<ServerWorker> &sender, const QJsonObject &docObj);
    /*!
     * \brief handleCaunterActionMessage read message and checks conditions about counter action
     * \param sender is a player that exectued a messgae
     * \param docObj a message to interpret
     */
    void handleCaunterActionMessage(std::shared_ptr<ServerWorker> &sender, const QJsonObject &docObj);
    /*!
     * \brief searchForPlayer is a function to search player by its nickname
     * \param nickname is a name of player
     * \return a ServerWorker pointer to player
     */
    std::shared_ptr<ServerWorker> searchForPlayer(QString nickname);
    /*!
     * \brief CHECKTIMEOUT is a time to check a action
     */
    const static int CHECKTIMEOUT = 10*1000;
    /*!
     * \brief BLOCKTIMEOUT is a time to block action
     */
    const static int BLOCKTIMEOUT = 15*1000;
    /*!
     * \brief STARTING_MONEY is a money to start
     */
    const static int STARTING_MONEY = 2;

public slots:
    /*!
      * \brief callOnTimeout function that is exectuted after timeout
      */
     void callOnTimeout();
signals:
     /*!
     * \brief checkCard if cards
     */
    void checkCard();
    /*!
     * \brief blockEnable says that block is now enabled
     * \param current says who is know making an action
     */
    void blockEnable(const Player &current);
    /*!
     * \brief blockDisable says that block is now disabled
     */
    void blockDisable();
    /*!
     * \brief checkEnable says that check is now enabled
     * \param current says how is now making an action
     */
    void checkEnable(const Player &current);
    /*!
     * \brief checkDisable says that check is now disabled
     */
    void checkDisable();
    /*!
     * \brief sendUpdate sends update about session
     * \param sess is a session pointer we want to update
     */
    void sendUpdate(std::shared_ptr<Session> sess);
private:
    /*!
     * \brief nextPlayer changes turn of game to new player
     */
    void nextPlayer();
    /*!
     * \brief nextTurn new turn is now
     */
    void nextTurn();
    /*!
     * \brief turnOf sends a info to player whos turn is now
     * \param player who has turn now
     */
    void turnOf(std::shared_ptr<ServerWorker> &player);
    /*!
     * \brief actionCanBeChecked checks if action can be blocked
     * \param action is a name of action
     * \return boolean value
     */
    bool actionCanBeChecked(QString &action);
    /*!
     * \brief startCheckTimer starts checktimer
     */
    void startCheckTimer();
    /*!
     * \brief checkAction
     * \param player
     * \param action
     * \return
     */
    bool checkAction(std::shared_ptr<ServerWorker> &player,const QString &action);
    /*!
     * \brief _cardstack pointer to cardstack
     */
    std::unique_ptr<CardStack> _cardstack;
    /*!
     * \brief _timer pointer to timer
     */
    std::unique_ptr<QTimer> _timer;
    /*!
     * \brief _blockTimer pointer to block timer
     */
    std::unique_ptr<QTimer> _blockTimer;
    /*!
     * \brief _players vector of ServerWorker objects - players
     */
    QVector<std::shared_ptr<ServerWorker> > _players;
    /*!
     * \brief _owner is a pointer to owner
     */
    std::shared_ptr<ServerWorker> _owner;
    /*!
     * \brief _currentPlayer is a poinyer to
     */
    std::shared_ptr<ServerWorker> _currentPlayer;
    /*!
     * \brief _actions is a pointer to Actions object
     */
    std::shared_ptr<Actions> _actions;
    /*!
     * \brief _id is an ID of a session
     */
    QUuid _id;
    /*!
     * \brief _turnId is an ID of a turn
     */
    QUuid _turnId;
    /*!
     * \brief _playersLimit how many players can connject to session
     */
    int _playersLimit;
    /*!
     * \brief _pendingAction
     */
    QString _pendingAction;
};

#endif // SESSION_H
