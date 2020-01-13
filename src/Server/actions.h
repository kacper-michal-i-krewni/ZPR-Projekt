#ifndef ACTIONS_H
#define ACTIONS_H


#include <QObject>
#include <map>
#include <QVector>

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
    Actions();
    virtual ~Actions();
    const int howMuchActionCosts(std::string &action);
    std::map<std::string, functionPointer> getMap();
    QVector<std::string> getCards();

    const static int AFFAIR_PRICE = 700;
    const static int PROTEST_PRICE = 300;
//public slots:
    void affair(std::shared_ptr<Player> executer,  std::shared_ptr<Player> victim = nullptr); // if action doesnt need viction the pointer will be nullptr
    void eu(std::shared_ptr<Player> executer,  std::shared_ptr<Player> victim = nullptr);
    void localBiznesman(std::shared_ptr<Player> executer,  std::shared_ptr<Player> victim = nullptr);
    void media(std::shared_ptr<Player> executer,  std::shared_ptr<Player> victim = nullptr);
    void onz(std::shared_ptr<Player> executer,  std::shared_ptr<Player> victim = nullptr);
    void police(std::shared_ptr<Player> executer,  std::shared_ptr<Player> victim = nullptr);
    void protest(std::shared_ptr<Player> executer,  std::shared_ptr<Player> victim = nullptr);
    void russia(std::shared_ptr<Player> executer,  std::shared_ptr<Player> victim = nullptr);
    void usa(std::shared_ptr<Player> executer,  std::shared_ptr<Player> victim = nullptr);
private:
    QVector<std::string> _cards;
    std::map<std::string, functionPointer> _actionsMap;
    void fillMap();
    void fillCards();

};

#endif // ACTIONS_H
