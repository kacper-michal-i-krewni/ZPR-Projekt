#ifndef GAMELISTDIALOG_H
#define GAMELISTDIALOG_H

#include "session.h"

#include <QDialog>

namespace Ui {
class GameListDialog;
}

class GameListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameListDialog(QWidget *parent = nullptr);
    //explicit GameListDialog(QWidget *parent);
    ~GameListDialog();

    void setList(const QVector<Session>  &sessVec);

private slots:
    void onButtonClicked();
signals:
    void buttonClicked(QJsonObject &message);
private:
    Ui::GameListDialog *ui;
    QVector<Session> _sessVec;
};

#endif // GAMELISTDIALOG_H
