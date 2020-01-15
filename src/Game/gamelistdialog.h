#ifndef GAMELISTDIALOG_H
#define GAMELISTDIALOG_H

#include "session.h"

#include <QDialog>

namespace Ui {
class GameListDialog;
}
/*!
 * \brief The GameListDialog class is a class that implements window with session list to select and join
 */
class GameListDialog : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief GameListDialog is a constructor of dialog that displays list of sessions
     * \param parent is a pointer to widget that can be parent of this
     */
    explicit GameListDialog(QWidget *parent = nullptr);

    ~GameListDialog();
    /*!
     * \brief setList is a function that puts data about session in dialog window
     * \param sessVec is a Vector with sessions
     */
    void setList(const QVector<Session>  &sessVec);

private slots:
    /*!
     * \brief onButtonClicked is a slot that is executed when button is clicked and session is picked
     */
    void onButtonClicked();
signals:
    /*!
     * \brief buttonClicked is a signal that is emited when user chooses a session
     * \param message
     */
    void buttonClicked(QJsonObject &message);
private:
    /*!
     * \brief ui a pointer to window
     */
    Ui::GameListDialog *ui;
    /*!
     * \brief _sessVec is a vector with sessions
     */
    QVector<Session> _sessVec;
};

#endif // GAMELISTDIALOG_H
