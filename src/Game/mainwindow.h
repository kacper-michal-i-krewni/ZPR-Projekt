#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QJsonObject>
#include <QAbstractSocket>
#include <memory>

class ChatClient;
class QStandardItemModel;
class Actions;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
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
     * \brief m_chatClient - pointer to correlated chat client
     */
    std::shared_ptr<ChatClient> m_chatClient;
    /*!
     * \brief m_chatModel - pointer to chat model - responsible for creating a chat segment
     */
    std::shared_ptr<QStandardItemModel> m_chatModel;

    std::shared_ptr<Actions> m_actions;

    /*!
     * \brief m_lastUserName
     */
    QString m_lastUserName;
private slots:
    /*!
     * \brief attemptConnection - ask user to connect to server.
     * User is asked via pop-up to enter server's ip address
     */
    void connectToGame();
    /*!
     * \brief connectedToServer - evoked when user clicks a button "Connect". Asks for username via input dialog
     */
    void connectedToServer();
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
     * \brief disconnect
     */
    void disconnect();
    /*!
     * \brief createGame - method resposible for creating games.
     * Gets data from input dialog
     */
    void createGame();
    void tooglePlayerInterface(bool b);
    void actionExecute(const QString &sender, const QString &action);
    void updatePlayerInterface(const QString &player, const double money, const double lifes);

};
#endif // MAINWINDOW_H
