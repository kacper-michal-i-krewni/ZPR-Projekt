#include "blockingui.h"
#include "ui_blockingui.h"
#include <QJsonObject>

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
    connect(ui->protest, &QPushButton::clicked, this, &BlockingUi::protest);

}

void BlockingUi::eu()
{
    QJsonObject message;
    message["type"] = QStringLiteral("block");
    message["player"] = client->getNickname();
    message["card"] = QStringLiteral("eu");
    client->sendMessageToServer(message);
    emit this->close();
}
void BlockingUi::russia()
{
    QJsonObject message;
    message["type"] = QStringLiteral("block");
    message["player"] = client->getNickname();
    message["card"] = QStringLiteral("russia");
    client->sendMessageToServer(message);
    emit this->close();
}
void BlockingUi::media()
{
    QJsonObject message;
    message["type"] = QStringLiteral("block");
    message["player"] = client->getNickname();
    message["card"] = QStringLiteral("media");
    client->sendMessageToServer(message);
    emit this->close();
}
void BlockingUi::onz()
{
    QJsonObject message;
    message["type"] = QStringLiteral("block");
    message["player"] = client->getNickname();
    message["card"] = QStringLiteral("onz");
    client->sendMessageToServer(message);
    emit this->close();
}
void BlockingUi::police()
{
    QJsonObject message;
    message["type"] = QStringLiteral("block");
    message["player"] = client->getNickname();
    message["card"] = QStringLiteral("police");
    client->sendMessageToServer(message);
    emit this->close();
}
void BlockingUi::protest()
{
    QJsonObject message;
    message["type"] = QStringLiteral("block");
    message["player"] = client->getNickname();
    message["card"] = QStringLiteral("protest");
    client->sendMessageToServer(message);
    emit this->close();
}

BlockingUi::~BlockingUi()
{
    delete ui;
}
