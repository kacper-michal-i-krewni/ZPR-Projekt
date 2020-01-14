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
class Session: public QObject
{
    Q_OBJECT
public:
    Session(std::shared_ptr<ServerWorker> owner, int playersLimit);
    virtual ~Session();
    QVector<std::shared_ptr<ServerWorker> > getPlayers();
    void sendToAll(QJsonObject &message);
    void sendToAllExcept(std::shared_ptr<ServerWorker> &player, QJsonObject &message);
    void addPlayer(const std::shared_ptr<ServerWorker> player);
    void removePlayer(const std::shared_ptr<ServerWorker> player);
    int getNumOfPlayers();
    int getPlayersLimit();
    std::shared_ptr<ServerWorker> getOwner();
    QString getId();
    QJsonObject toJSON();

    void start();

    void handleActionMessage(std::shared_ptr<ServerWorker> &sender, const QJsonObject &docObj);
    void handleCaunterActionMessage(std::shared_ptr<ServerWorker> &sender, const QJsonObject &docObj);

    std::shared_ptr<ServerWorker> searchForPlayer(QString nickname);


    const static int CHECKTIMEOUT = 10*1000;
    const static int BLOCKTIMEOUT = 15*1000;

    const static int STARTING_MONEY = 200;

public slots:
     void callOnTimeout();



signals:

    //TODO: what type should dataRequest return?
//    void dataRequest(const QString &playerId, const PlayerData &pData);
//    void actionPlayed(const Action &a, const Player &p);
//    void targetedActionPlayed(const Action &a, const Player &p, const Player &target);
    void checkCard();
    void blockEnable(const Player &current);
    void blockDisable(); //wysyla do serwera info
    void checkEnable(const Player &current);
    void checkDisable();
    void sendUpdate(std::shared_ptr<Session> sess);


private:
    void nextPlayer();
    void nextTurn();
    void turnOf(std::shared_ptr<ServerWorker> &player);
    bool actionCanBeChecked(QString &action);
    void startCheckTimer();
    bool checkAction(std::shared_ptr<ServerWorker> &player,const QString &action);
    std::shared_ptr<Session> _this;
    std::unique_ptr<CardStack> _cardstack;
    std::unique_ptr<QTimer> _timer;
    std::unique_ptr<QTimer> _blockTimer;
    QVector<std::shared_ptr<ServerWorker> > _players;
    std::shared_ptr<ServerWorker> _owner;
    std::shared_ptr<ServerWorker> _currentPlayer;
    std::shared_ptr<Actions> _actions;
    QUuid _id;
    QUuid _turnId;
    int _playersLimit;
    QString _pendingAction;
    //QTimer _timer;
    //void wait();




};

#endif // SESSION_H
