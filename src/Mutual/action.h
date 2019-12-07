#ifndef ACTION_H
#define ACTION_H

#include <QObject>
#include <memory>
class Player;
/*!
 * \brief The Action class that is a base class for each action in game.
 *
 *  This class is inheriting fom QObject, because it needs signals.
 */
class Action: public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Action constructor.
     *
     * It does nothing.
     */
    Action();
    /*!
     * \brief Action destructor.
     *
     * It is vitrual, because it needs to destroy lower objects in hierarchy.
     */
    virtual ~Action();
public slots:
    /*!
     * \brief Virtual action method.
     *
     * It is a core of this class. Thanks to virtual mechanism, it execute the right method for action.
     */
    virtual void action() = 0;
private:
    /*!
     * \brief private variavle IndicatePlayer
     *
     * It says if action need to indicate player on board on which action is executed.
     */
    bool IndicatePlayer;

    std::shared_ptr<Player> _player;
};

#endif // ACTION_H
