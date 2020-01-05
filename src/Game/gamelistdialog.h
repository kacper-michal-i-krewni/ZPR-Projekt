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
    explicit GameListDialog(QWidget *parent, std::vector<QMap<QString, QString> > &mapVec);
    ~GameListDialog();

private:
    Ui::GameListDialog *ui;
};

#endif // GAMELISTDIALOG_H
