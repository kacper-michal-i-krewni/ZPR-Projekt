#ifndef ACTION_H
#define ACTION_H

#include <QObject>
#include <memory>
#include <QDataStream>
#include <QJsonDocument>
#include <QJsonObject>
#include "chatclient.h"

#include "gameplayer.h"
/*!
 * \brief The Action class that is a base class for each action in game.
 *
 *  This class is inheriting fom QObject, because it needs signals.
 */
class Actions: public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Action constructor.
     *
     * It does nothing.
     */
    Actions();
    /*!
     * \brief Action destructor.
     *
     * It is vitrual, because it needs to destroy lower objects in hierarchy.
     */
    virtual ~Actions();
public slots:
    void affair();
    void eu();
    void localBiznesman();
    void media();
    void onz();
    void police();
    void protest();
    void russia();
    void usa();

private:
    GamePlayer *_player;
};

#endif // ACTION_H
