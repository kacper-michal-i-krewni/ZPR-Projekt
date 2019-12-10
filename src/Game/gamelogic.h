#ifndef GAMELOGIC_H
#define GAMELOGIC_H

class Player;
#include <QObject>

/*!
 * \brief The GameLogic class is a class that is responsible for connecting game ui with backend
 *
 *
 */
class GameLogic: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(GameLogic)
public:
    explicit GameLogic(QObject *parent = nullptr);

private:
    std::shared_ptr<Player> _player;

};

#endif // GAMELOGIC_H
