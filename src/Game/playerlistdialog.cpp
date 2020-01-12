#include "playerlistdialog.h"
#include "ui_playerlistdialog.h"


#include <QAction>
#include <QJsonObject>
#include <QListWidget>


PlayerListDialog::PlayerListDialog(QWidget *parent):
    QDialog(parent),
    ui(new Ui::PlayerListDialog)
{
    ui->setupUi(this);
    connect(ui->selectButton, &QPushButton::clicked, this, &PlayerListDialog::onButtonClicked);
    connect(ui->selectButton, SIGNAL(clicked()), this, SLOT(close()));
}

void PlayerListDialog::setList(const QString &action, const QVector<QString> &playerVec)
{

    this->_action = action;
    this->_playerVec = playerVec;

    for(auto p: playerVec)
    {
        ui->listWidget->addItem(p);
    }
}

PlayerListDialog::~PlayerListDialog()
{
    delete ui;
}


void PlayerListDialog::onButtonClicked()
{
    if(_playerVec.isEmpty()) return;
    QListWidgetItem* item = ui->listWidget->currentItem();
    int row = ui->listWidget->row(item);
    QString p = _playerVec[row]; //TODO check if indexes are cool

    QJsonObject message;
    message["type"] = QStringLiteral("action");
    message["target"] = p;
    message["text"] = _action;
    message["targeted"] = true;
    _playerVec.clear();
    ui->listWidget->clear();


    emit buttonClicked(message);
}
