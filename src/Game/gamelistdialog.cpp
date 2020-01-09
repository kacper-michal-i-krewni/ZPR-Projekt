#include "gamelistdialog.h"
#include "ui_gamelistdialog.h"

GameListDialog::GameListDialog(QWidget *parent,const QVector<Session> &sessVec) :
    QDialog(parent),
    ui(new Ui::GameListDialog)
{
    ui->setupUi(this);

    for(auto s: sessVec){
        QString construct ="owner: " + s.getOwner() + "/ number of players: " + (char)s.getNumOfPlayers();
        ui->listWidget->addItem(construct);
    }
}

GameListDialog::~GameListDialog()
{
    delete ui;
}

void GameListDialog::onButtonClicked(){ //TODO implement this method
    ui->listWidget->currentItem();
}


