#include "actions.h"

Actions::Actions()
{

}

void Actions::usa()
{
    // create a QDataStream operating on the socket
    QDataStream clientStream(_player->getChatClient()->getClientSocket());
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;
    message["type"] = QStringLiteral("message");
    message["text"] = "Usa";
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
}

Actions::~Actions()
{

}
