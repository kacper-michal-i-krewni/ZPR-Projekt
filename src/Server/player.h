#ifndef PLAYER_H
#define PLAYER_H


#include <QUuid>
#include <string>


class Player{
public:
    enum sessionState{
        IN_SESSION, OUT_SESSION
    };
    enum gameState{
      DEAD, INACTIVE, ACTIVE
    };

private:
    std::string userName;
    QUuid id;
    Player::sessionState sState;
    Player::gameState gState;

public:
    void setUsername(const std::string &username){this->userName = username;}
    std::string getUsername(){return this->userName;}
    void setSessionState(const Player::sessionState &state){this->sState = state;}
    sessionState getSessionState(){return this->sState;}
    void setGameState(const Player::gameState state){this->gState = state;}
    gameState getGameState(){return this->gState;}


};

#endif // PLAYER_H
