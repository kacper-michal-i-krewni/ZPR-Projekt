#ifndef ACTIONS_H
#define ACTIONS_H

#include <QObject>
#include <memory>
class ChatClient;
/*!
 * \brief The Action class that is a class that send messages about clicked action for each action in game.
 *
 *  This class is inheriting fom QObject, because it needs signals.
 *  It send
 */
class Actions: public QObject
{
    Q_OBJECT
public:
    /*!
     *  A constructor
     * \param is a pointer to ChatClient class, becouse it needs to send messages to server.
     */
    Actions(std::shared_ptr<ChatClient> );
    /*!
     * \brief ~Actions
     * A destructor
     */
    virtual ~Actions();
public slots:
    /*!
     * \brief affair function
     * It sends message that affair action was chosen
     */
    void affair();
    /*!
     * \brief eu function
     * It sends message that eu action was chosen
     */
    void eu();
    /*!
     * \brief localBiznesman function
     * It sends message that localBiznesman action was chosen
     */
    void localBiznesman();
    /*!
     * \brief media function
     * It sends message that media action was chosen
     */
    void media();
    /*!
     * \brief onz function
     * It sends message that onz action was chosen
     */
    void onz();
    /*!
     * \brief police function
     * It sends message that police action was chosen
     */
    void police();
    /*!
     * \brief protest function
     * It sends message that protest action was chosen
     */
    void protest();
    /*!
     * \brief russia function
     * It sends message that russia action was chosen
     */
    void russia();
    /*!
     * \brief usa function
     * It sends message that usa action was chosen
     */
    void usa();
private:
    /*!
     * \brief buildMessage function
     * \param name of the action clicked
     * \param targeted is a arg that says if action need to select another player
     */
    void buildMessage(const QString &name, const bool &targeted);
    /*!
     * \brief m_chatClient a sharedpointer
     * it contains pointer to chatclient to send messages
     */
    std::shared_ptr<ChatClient> m_chatClient;
};

#endif // ACTIONS_H
