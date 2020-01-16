#ifndef ACTIONS_H
#define ACTIONS_H


#include <QObject>
#include <map>
#include <QVector>
#include <memory>

class Player;



/*!
 * \brief The Action class that is a base class for each action in game.
 *
 *  This class is inheriting fom QObject, because it needs signals.
 */
class Actions: public QObject
{
    Q_OBJECT
public:
    typedef void (Actions::*functionPointer)(std::shared_ptr<Player>, std::shared_ptr<Player>);
    /*!
     * \brief Actions a constructor
     */
    Actions();
    virtual ~Actions();
    /*!
     * \brief howMuchActionCosts is a function to check actionc cost
     * \param action is a name of an action
     * \return is a cost of action
     */
    int howMuchActionCosts(QString action);
    /*!
     * \brief getMap is a function that return map of a action connected with functions pointers
     * \return map to actions and functions pointers
     */
    std::map<std::string, functionPointer> getMap();
    /*!
     * \brief getCards return all type of cards
     * \return  vector with cards strings
     */
    QVector<std::string> getCards();
    /*!
     * \brief getActionsThatBlock is a function that search for blockers to action pass in parameters
     * \param action is a name of action we want to get blocker
     * \return vector with blockers to action passed in argument
     */
    QVector<QString> getActionsThatBlock(const QString &action);
    /*!
     * \brief AFFAIR_PRICE is a price of affair action
     */
    const static int AFFAIR_PRICE = 7;
    /*!
     * \brief PROTEST_PRICE is a price of protest action
     */
    const static int PROTEST_PRICE = 3;
    /*!
     * \brief affair is an implementation of action affair
     * \param executer is a player who execute action
     * \param victim is a player who is attacked by executer
     */
    void affair(std::shared_ptr<Player> executer,  std::shared_ptr<Player> victim = nullptr); // if action doesnt need viction the pointer will be nullptr
    /*!
     * \brief eu is an implementation of action eu
     * \param executer is a player who execute action
     * \param victim is a player who is attacked by executer
     */
    void eu(std::shared_ptr<Player> executer,  std::shared_ptr<Player> victim = nullptr);
    /*!
     * \brief localBiznesman is an implementation of action localBiznesman
     * \param executer is a player who execute action
     * \param victim is a player who is attacked by executer
     */
    void localBiznesman(std::shared_ptr<Player> executer,  std::shared_ptr<Player> victim = nullptr);
    /*!
     * \brief media is an implementation of action media
     * \param executer is a player who execute action
     * \param victim is a player who is attacked by executer
     */
    void media(std::shared_ptr<Player> executer,  std::shared_ptr<Player> victim = nullptr);
    /*!
     * \brief onz is an implementation of action onz
     * \param executer is a player who execute action
     * \param victim is a player who is attacked by executer
     */
    void onz(std::shared_ptr<Player> executer,  std::shared_ptr<Player> victim = nullptr);
    /*!
     * \brief police is an implementation of action police
     * \param executer is a player who execute action
     * \param victim is a player who is attacked by executer
     */
    void police(std::shared_ptr<Player> executer,  std::shared_ptr<Player> victim = nullptr);
    /*!
     * \brief protest is an implementation of action protest
     * \param executer is a player who execute action
     * \param victim is a player who is attacked by executer
     */
    void protest(std::shared_ptr<Player> executer,  std::shared_ptr<Player> victim = nullptr);
    /*!
     * \brief russia is an implementation of action russia
     * \param executer is a player who execute action
     * \param victim is a player who is attacked by executer
     */
    void russia(std::shared_ptr<Player> executer,  std::shared_ptr<Player> victim = nullptr);
    /*!
     * \brief usa is an implementation of action usa
     * \param executer is a player who execute action
     * \param victim is a player who is attacked by executer
     */
    void usa(std::shared_ptr<Player> executer,  std::shared_ptr<Player> victim = nullptr);
private:
    /*!
     * \brief _cards is a vector of strings that contain actions that has cards
     */
    QVector<std::string> _cards;
    /*!
     * \brief _actionsMap is a map that connects names of actions and function pointers
     */
    std::map<std::string, functionPointer> _actionsMap;
    /*!
     * \brief fillMap is a function that is executed in constructor and fill _actionMap
     */
    void fillMap();
    /*!
     * \brief fillCards ia a function that is executed in constructor and fill _cards
     */
    void fillCards();

};

#endif // ACTIONS_H
