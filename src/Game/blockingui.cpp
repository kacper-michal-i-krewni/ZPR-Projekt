#include "blockingui.h"
#include "ui_blockingui.h"
#include <QJsonObject>
#include <QMessageBox>

BlockingUi::BlockingUi(QWidget *parent, std::shared_ptr<ChatClient> c) :
    QWidget(parent),
    ui(new Ui::BlockingUi),
    client(c)
{
    ui->setupUi(this);
    connect(ui->eu, &QPushButton::clicked, this, &BlockingUi::eu);
    connect(ui->russia, &QPushButton::clicked, this, &BlockingUi::russia);
    connect(ui->media, &QPushButton::clicked, this, &BlockingUi::media);
    connect(ui->onz, &QPushButton::clicked, this, &BlockingUi::onz);
    connect(ui->police, &QPushButton::clicked, this, &BlockingUi::police);
   // connect(ui->protest, &QPushButton::clicked, this, &BlockingUi::protest);

}

void BlockingUi::checkAndExecute(const QString &action)
{
    if(client->getCurrentBlockers().isEmpty())
        emit this->close();
    for(QString b: client->getCurrentBlockers())
    {
        if(action.compare(b, Qt::CaseInsensitive) == 0){
            QJsonObject message;
            message["type"] = QStringLiteral("caunterAction");
            message["subtype"] = QStringLiteral("block");
            message["sender"] = client->getNickname();
            message["action"] = action;
            message["turnId"] = client->getTurnId();
            client->sendMessageToServer(message);
            emit disableBlockButton();
            emit this->close();
            return;
        }
    }
    QMessageBox::warning(this, tr("What man"), tr("You can't block with that!"));
}

void BlockingUi::eu()
{
    checkAndExecute("eu");
}
void BlockingUi::russia()
{
    checkAndExecute("russia");
}
void BlockingUi::media()
{
    checkAndExecute("media");
}
void BlockingUi::onz()
{
    checkAndExecute("onz");
}
void BlockingUi::police()
{
   checkAndExecute("police");
}

//void BlockingUi::protest()
//{
//    QJsonObject message;
//    message["type"] = QStringLiteral("block");
//    message["player"] = client->getNickname();
//    message["card"] = QStringLiteral("protest");
//    client->sendMessageToServer(message);
//    emit this->close();
//}

BlockingUi::~BlockingUi()
{
    delete ui;
}
