#include "actions.h"
#include "chatclient.h"

#include <QDataStream>
#include <QJsonDocument>
#include <QJsonObject>


Actions::Actions(std::shared_ptr<ChatClient> chatClient): m_chatClient(chatClient)
{

}

Actions::~Actions()
{

}

void Actions::buildMessage(const QString &name,const bool &targeted)
{
    // create a QDataStream operating on the socket
    QDataStream clientStream(m_chatClient->getQTcpSocket().get());
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;
    message["type"] = QStringLiteral("action");
    message["player"] = m_chatClient->getNickname();
    message["text"] = name;
    message["targeted"] = targeted;
    message["turnId"] = m_chatClient->getTurnId();
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
}

void Actions::affair()
{
    buildMessage("affair", true);
}
void Actions::eu()
{
    buildMessage("eu", false);
}
void Actions::localBiznesman()
{
   buildMessage("localBiznesman", false);
}
void Actions::media()
{
    buildMessage("media", false);
}
void Actions::onz()
{
    buildMessage("onz", true);
}
void Actions::police()
{
    buildMessage("police", true);
}
void Actions::protest()
{
    buildMessage("protest", true);
}
void Actions::russia()
{
    buildMessage("russia", false);
}
void Actions::usa()
{
    buildMessage("usa", false);
}

