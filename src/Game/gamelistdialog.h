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
    //explicit GameListDialog(QWidget *parent = nullptr);
    explicit GameListDialog(QWidget *parent,const QVector<Session>  &sessVec);
    ~GameListDialog();
private slots:
    void onButtonClicked();
private:
    Ui::GameListDialog *ui;
};

#endif // GAMELISTDIALOG_H
