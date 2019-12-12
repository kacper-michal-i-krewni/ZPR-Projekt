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
    typedef void (Actions::*functionPointer)(Player*, Player*);
    Actions();
    virtual ~Actions();
    std::map<std::string, functionPointer> getMap();
    QVector<std::string> getCards();
//public slots:
    void affair(Player *executer, Player *victim = nullptr); // if action doesnt need viction the pointer will be nullptr
    void eu(Player *executer, Player *victim = nullptr);
    void localBiznesman(Player *executer, Player *victim = nullptr);
    void media(Player *executer, Player *victim = nullptr);
    void onz(Player *executer, Player *victim = nullptr);
    void police(Player *executer, Player *victim = nullptr);
    void protest(Player *executer, Player *victim = nullptr);
    void russia(Player *executer, Player *victim = nullptr);
    void usa(Player *executer, Player *victim = nullptr);
private:
    QVector<std::string> _cards;
    std::map<std::string, functionPointer> _actionsMap;
    void fillMap();
    void fillCards();

};

#endif // ACTIONS_H
