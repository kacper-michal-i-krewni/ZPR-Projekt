#ifndef ACTIONS_H
#define ACTIONS_H

#include <QObject>
/*!
 * \brief The Action class that is a base class for each action in game.
 *
 *  This class is inheriting fom QObject, because it needs signals.
 */
class Actions: public QObject
{
    Q_OBJECT
public:

    Actions();
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
};

#endif // ACTIONS_H
