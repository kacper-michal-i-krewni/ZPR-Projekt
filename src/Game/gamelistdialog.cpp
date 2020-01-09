#include "gamelistdialog.h"
#include "ui_gamelistdialog.h"

GameListDialog::GameListDialog(QWidget *parent,const QVector<QMap<QString, QVariant> > &mapVec) :
    QDialog(parent),
    ui(new Ui::GameListDialog)
{
    ui->setupUi(this);

    for(auto map: mapVec){
        QMapIterator<QString, QVariant> i(map);
        QString construct = "";
        while (i.hasNext()) {
            construct += "/ " + i.key() + ": " + i.value().toString();
            i.next();
        }
        ui->listWidget->addItem(construct);
    }
}

GameListDialog::~GameListDialog()
{
    delete ui;
}
