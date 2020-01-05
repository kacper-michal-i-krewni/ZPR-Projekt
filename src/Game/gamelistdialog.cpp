#include "gamelistdialog.h"
#include "ui_gamelistdialog.h"

GameListDialog::GameListDialog(QWidget *parent, std::vector<QMap<QString, QString>> &mapVec) :
    QDialog(parent),
    ui(new Ui::GameListDialog)
{
    ui->setupUi(this);
    for(QMap<QString,QString> map: mapVec){
        QMapIterator<QString, QString> i(map);
        QString construct = "";
        while (i.hasNext()) {
            construct += "/ " + i.key() + ": " + i.value();
            i.next();
        }
        ui->listWidget->addItem(construct);
    }
}

GameListDialog::~GameListDialog()
{
    delete ui;
}
