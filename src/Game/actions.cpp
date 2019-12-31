#include "actions.h"
#include "chatclient.h"

#include <QDataStream>
#include <QJsonDocument>
#include <QJsonObject>
Actions::Actions(ChatClient *chatClient): m_chatClient(chatClient)
{

}

Actions::~Actions()
{

}

void Actions::affair()
{

}
void Actions::eu()
{

}
void Actions::localBiznesman()
{

}
void Actions::media()
{

}
void Actions::onz()
{

}
void Actions::police()
{

}
void Actions::protest()
{

}
void Actions::russia()
{

}
void Actions::usa()
{
    // create a QDataStream operating on the socket
    QDataStream clientStream(m_chatClient->getQTcpSocket());
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;
    message["type"] = QStringLiteral("action");
    message["text"] = "USA";
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
}

