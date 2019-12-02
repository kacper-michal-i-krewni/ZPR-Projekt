#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include "../Mutual/actions/allactions.h"

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
public:
    const USA _usa;
    const LocalBiznesman _localBiznesman;
    const Affair _affair;
    const Russia _russia;
    const Protest _protest;
    const Media _media;
    const ONZ _onz;
    const Police _police;
    const EU _eu;

};

#endif // GAMELOGIC_H
