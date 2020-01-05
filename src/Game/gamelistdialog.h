#ifndef GAMELISTDIALOG_H
#define GAMELISTDIALOG_H

#include <QDialog>

namespace Ui {
class GameListDialog;
}

class GameListDialog : public QDialog
{
    Q_OBJECT

public:
    //explicit GameListDialog(QWidget *parent = nullptr);
    explicit GameListDialog(QWidget *parent,const std::vector<QMap<QString, QVariant>> &mapVec);
    ~GameListDialog();

private:
    Ui::GameListDialog *ui;
};

#endif // GAMELISTDIALOG_H
