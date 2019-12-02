#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QWidget>

namespace Ui {
class ServerWindow;
}
class ChatServer;

/*!
 * \brief The ServerWindow class is an UI for server
 */
class ServerWindow : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(ServerWindow)
public:
    /*!
     * \brief ServerWindow
     * \param parent
     */
    explicit ServerWindow(QWidget *parent = nullptr);
    ~ServerWindow();

private:
    /*!
     * \brief ui is pointer on this ui.
     */
    Ui::ServerWindow *ui;
    /*!
     * \brief m_chatServer is a pointer to ChatServer class, because
     *  we want to use its functions like send messaegs and etc.
     */
    ChatServer *m_chatServer;
private slots:
    /*!
     * \brief toggleStartServer is a function that replace 'Server start' with 'Server stop'
     */
    void toggleStartServer();
    /*!
     * \brief logMessage is function thta display messages in log windows in server ui
     * \param msg is a message that is displayed
     */
    void logMessage(const QString &msg);
};

#endif // SERVERWINDOW_H
