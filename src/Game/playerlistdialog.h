#ifndef PLAYERLISTDIALOG_H
#define PLAYERLISTDIALOG_H

#include <QDialog>

namespace Ui {
class PlayerListDialog;
}

/*!
 * \brief The PlayerListDialog class is a implementation of window to select which player we want to attack with targeted action
 */
class PlayerListDialog : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief PlayerListDialog constructor
     * \param parent is a parent QWidget
     */
    explicit PlayerListDialog(QWidget *parent = nullptr);
    ~PlayerListDialog();
    /*!
     * \brief setList
     * \param action
     * \param playerVec
     */
    void setList(const QString &action, const QVector<QString>  &playerVec);
    /*!
     * \brief setAction sets _action variable
     * \param action is a string identificates action
     */
    void setAction(const QString &action);

private slots:
    /*!
     * \brief onButtonClicked sends info about cliced action and targeted player to mainwindow
     */
    void onButtonClicked();
signals:
    /*!
     * \brief buttonClicked is generated when any button is clicked
     * \param message holds info about action
     */
    void buttonClicked(QJsonObject &message);
private:
    /*!
     * \brief ui is a pointer to whole ui
     */
    Ui::PlayerListDialog *ui;
    /*!
     * \brief _playerVec is vector wit players info
     */
    QVector<QString> _playerVec;
    /*!
     * \brief _action is string with action name that is executed
     */
    QString _action;
};

#endif // PLAYERLISTDIALOG_H
