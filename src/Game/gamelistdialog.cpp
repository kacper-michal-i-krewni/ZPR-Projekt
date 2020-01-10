#include "gamelistdialog.h"
#include "ui_gamelistdialog.h"

#include <QAction>


GameListDialog::GameListDialog(QWidget *parent):
    QDialog(parent),
    ui(new Ui::GameListDialog)
{
    ui->setupUi(this);
    connect(ui->joinButton, &QPushButton::clicked, this, &GameListDialog::onButtonClicked);
}

void GameListDialog::setList(const QVector<Session> &sessVec)
{
    this->_sessVec = sessVec;
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
    QListWidgetItem* item = ui->listWidget->currentItem();
    int row = ui->listWidget->row(item);
    Session s = _sessVec[row]; //TODO check if indexes are cool

    QJsonObject message;
    message["request"] = QStringLiteral("joinRequest");
    message["type"] = QStringLiteral("session");
    message["id"] = s.getId();

    emit buttonClicked(message);

}


