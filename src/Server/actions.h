#ifndef ACTIONS_H
#define ACTIONS_H


#include <QObject>
#include <map>
#include <QVector>
#include <memory>
#include <functional>
#include "../../Mutual/action.h"



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
    //typedef void (*functionPointer)(std::shared_ptr<Player>, std::shared_ptr<Player>);
    //typedef std::function<void(std::shared_ptr<Player>, std::shared_ptr<Player>)> functionPointer;
    Actions();
    virtual ~Actions();
    std::map<std::string, functionPointer> getMap();
    QVector<std::string> getCards();
//public slots:
    void affair(std::shared_ptr<Player> executer, std::shared_ptr<Player> victim = nullptr); // if action doesnt need viction the pointer will be nullptr
    void eu(std::shared_ptr<Player> executer, std::shared_ptr<Player> victim = nullptr);
    void localBiznesman(std::shared_ptr<Player> executer, std::shared_ptr<Player> victim = nullptr);
    void media(std::shared_ptr<Player> executer,std::shared_ptr<Player> victim = nullptr);
    void onz(std::shared_ptr<Player> executer, std::shared_ptr<Player> victim = nullptr);
    void police(std::shared_ptr<Player> executer, std::shared_ptr<Player> victim = nullptr);
    void protest(std::shared_ptr<Player> executer, std::shared_ptr<Player> victim = nullptr);
    void russia(std::shared_ptr<Player> executer, std::shared_ptr<Player> victim = nullptr);
    void usa(std::shared_ptr<Player> executer, std::shared_ptr<Player> victim = nullptr);
private:
    QVector<std::string> _cards;
    std::map<std::string, functionPointer> _actionsMap;
    QVector<Action> _actions;
    void fillMap();
    void fillCards();

};

#endif // ACTIONS_H
