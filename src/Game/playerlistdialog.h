#ifndef PLAYERLISTDIALOG_H
#define PLAYERLISTDIALOG_H

#include <QDialog>

namespace Ui {
class PlayerListDialog;
}

class PlayerListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlayerListDialog(QWidget *parent = nullptr);
    //explicit GameListDialog(QWidget *parent);
    ~PlayerListDialog();

    void setList(const QVector<QString>  &playerVec);
    void setAction(const QString &action)
    {
        this->_action = action;
    }

private slots:
    void onButtonClicked();
signals:
    void buttonClicked(QJsonObject &message);
private:
    Ui::PlayerListDialog *ui;
    QVector<QString> _playerVec;
    QString _action;
};

#endif // PLAYERLISTDIALOG_H
