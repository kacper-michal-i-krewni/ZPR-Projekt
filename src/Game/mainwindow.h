#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamelistdialog.h"
#include "playerlistdialog.h"
#include "session.h"

#include <QWidget>
#include <QMainWindow>
#include <QJsonObject>
#include <QAbstractSocket>
#include <memory>
#include "blockingui.h"
#include "ui_blockingui.h"
#include <ui_gamelistdialog.h>
#include <QLabel>

class ChatClient;
class QStandardItemModel;
class Actions;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; class BlockingUi; }
QT_END_NAMESPACE

/*!
 * \brief The MainWindow class - controller class for main view of the game
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_DISABLE_COPY(MainWindow)

public:
    /*!
     * \brief MainWindow - contructor, creates chatClient, viewModel and gameLogic objects, connects all signals to their destinations
     * Disables buttons visible.
     * \param parent
     */
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    /*!
     * \brief ui - pointer to user interface
     */
    Ui::MainWindow *ui;
    /*!
     * \brief m_gameListDialog pointer to game list diaglog that is poping up when you want to connect to session
     */
    std::shared_ptr<GameListDialog> m_gameListDialog;
    /*!
     * \brief m_playerListDialog a pointer to player list dialog when you want to make a action that needs to target a player
     */
    std::shared_ptr<PlayerListDialog> m_playerListDialog;
    /*!
     * \brief m_chatClient - pointer to correlated chat client
     */
    std::shared_ptr<ChatClient> m_chatClient;
    /*!
     * \brief m_chatModel - pointer to chat model - responsible for creating a chat segment
     */
    std::shared_ptr<QStandardItemModel> m_chatModel;
    /*!
     * \brief m_actions is a pointer to actions class
     */
    std::shared_ptr<Actions> m_actions;
    /*!
     * \brief blockingui is a pointer to ui that popup when you want to block a action after clicking block action
     */
    std::shared_ptr<BlockingUi> blockingui;

    /*!
     * \brief m_lastUserName is a string that holds last username displayed in the chat so it dont need to show it when one player sends multiple messages
     */
    QString m_lastUserName;
    /*!
     * \brief setGraphic is a function that sets graphics in interface
     * \param name is name of a file that contains graphic we want to set
     * \param label is a pointer to QLabel we want to change
     */
    void setGraphic(QString name, QLabel *label);
    /*!
     * \brief resetUI resets ui to start state
     */
    void resetUI();
private slots:
    /*!
     * \brief joinToGame is a function is sending message to server about joining game
     */
    void joinToGame();
    /*!
     * \brief createGame is a function is sending message to server about creating game
     */
    void createGame();
    /*!
     * \brief startGame is is a function is sending message to server about starting a game
     */
    void startGame();
    /*!
     * \brief myTurn is setting up ui to enable make an action by an user
     */
    void myTurn();
    /*!
     * \brief turnOf is loggin to chat info about whose turn it is and disable interface
     * \param player
     */
    void turnOf(QString &player);
    /*!
     * \brief sendTargetedAction is a function that sends message about execute targeted action
     * \param message is a object in json that is extended by this function
     */
    void sendTargetedAction(QJsonObject &message);
    /*!
     * \brief displayPlayerList is a action that display ui to target a player if we have targeted action
     * \param action is a name of action
     * \param pVector
     */
    void displayPlayerList(QString &action, QVector<QString> &pVector);
    /*!
     * \brief sessionCreated logs info about creating session and set-up ui
     * \param success is a boolean taht says if session was created or not
     * \param id is an ID of a session
     */
    void sessionCreated(bool &success, QString &id);
    /*!
     * \brief connectToServer is a function that is reposible for connecting to server and pop-ups to write IP and size of session
     */
    void connectToServer();
    /*!
     * \brief connectedToServer - evoked when user clicks a button "Connect". Asks for username via input dialog
     */
    void connectedToServer();
    /*!
     * \brief notEnoughMoney is a waring that displays when you have not enough money to make an action that costs money
     */
    void notEnoughMoney();
    /*!
     * \brief blockActionsInterface is a slot that is connected to all buttons, so it can block an action's interface when any actions button is clicked
     */
    void blockActionsInterface();
    /*!
     * \brief youAreATarget logs info about attack with action and enable block button
     * \param action is a name of axtion that is executed
     * \param sender who is attacking you
     * \param blockers is a info about what blockers are avaliable
     */
    void youAreATarget(QString &action, QString &sender, QVector<QString> &blockers);
    /*!
     * \brief actionCompleted logs info about completed action
     * \param action a name of an action
     * \param sender who is using an action
     */
    void actionCompleted(QString &action, QString &sender);
    /*!
     * \brief actionPending logs ifo about action that can be checked
     * \param action name of action
     * \param sender who wants to use an action
     */
    void actionPending(QString &action, QString &sender);
    /*!
     * \brief disableBlockButton is function that blocks block button
     */
    void disableBlockButton();
    /*!
     * \brief checkResult is a function that logs info about losing life by checker or executer of action
     * \param checked who is checked
     * \param checking who is checking
     * \param result if checked passed
     */
    void checkResult(QString &checked, QString &checking, bool &result);
    /*!
     * \brief attemptLogin - try to log in via chatClient->login()
     * \param userName
     */
    void attemptLogin(const QString &userName);
    /*!
     * \brief loggedIn - enables a set of buttons aviable only for logged users
     */
    void loggedIn();
    /*!
     * \brief loginFailed - pops an alert box, evokes connectedToServer() again
     * \param reason
     */
    void loginFailed(const QString &reason);
    /*!
     * \brief messageReceived - displays username + message in the chat segment
     * \param sender
     * \param text
     */
    void messageReceived(const QString &sender, const QString &text);
    /*!
     * \brief sendMessage - evokes chatClient::sendMessage with text read from the input box
     */
    void sendMessage();
    /*!
     * \brief disconnectedFromServer - evoked when user clicks a button "Disconnect".
     * Blocks buttons aviable for logged users
     */
    void disconnectedFromServer();
    /*!
     * \brief userJoined - updates chat window
     * \param username
     */
    void userJoined(const QString &username);
    /*!
     * \brief userLeft - updates chat window
     * \param username
     */
    void userLeft(const QString &username);
    /*!
     * \brief error - case-structured method to pop error messages
     * \param socketError
     */
    void error(QAbstractSocket::SocketError socketError);
    /*!
     * \brief disconnect is disabling whole ui and resets everything to start state
     */
    void disconnect();
    /*!
     * \brief userReady logs info that user is ready
     * \param username name of user that is ready
     */
    void userReady(const QString &username);
    /*!
     * \brief toggleActionsInterface enable or disable whole actions
     * \param b if we want to switch on or off
     */
    void toggleActionsInterface(bool b);
    /*!
     * \brief displaySessionDialog is displaying dialog to join to session and sets info about it
     * \param sessVec is a Vector with info about sessions
     */
    void displaySessionDialog(QVector<Session> &sessVec);
    /*!
     * \brief sendSessionDialogResponse sends request to join to session by chatclient
     * \param message is a message to send
     */
    void sendSessionDialogResponse(QJsonObject &message);
    /*!
     * \brief joinedSession logs about user joining session
     * \param username name of user
     */
    void joinedSession(const QString &username);
    /*!
     * \brief updatePlayerInterface is a function that changes players money
     * \param player name of a player
     * \param money how much money player has
     * \param lifes how many lifes player has
     */
    void updatePlayerInterface(const QString &player, const double money, const double lifes);
    /*!
     * \brief blockAction is a slot to catch block button clicked
     */
    void blockAction(void);
    /*!
     * \brief checkAction is a slot to catch check button clicked
     */
    void checkAction(void);
    /*!
     * \brief readyAction is a slot to catch ready button clicked
     */
    void readyAction(void);
    /*!
     * \brief cardsDealing is setting interface with cards
     * \param first card
     * \param second card
     */
    void cardsDealing(const QString first, const QString second);
};
#endif // MAINWINDOW_H
