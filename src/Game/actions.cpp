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

void Actions::affair()
{
    // create a QDataStream operating on the socket
    QDataStream clientStream(m_chatClient->getQTcpSocket().get());
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;
    message["type"] = QStringLiteral("action");
    message["player"] = m_chatClient->getNickname();
    message["text"] = "affair";
    message["targeted"] = true;
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
}
void Actions::eu()
{
    // create a QDataStream operating on the socket
    QDataStream clientStream(m_chatClient->getQTcpSocket().get());
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;
    message["type"] = QStringLiteral("action");
    message["player"] = m_chatClient->getNickname();
    message["text"] = "eu";
    message["targeted"] = false;
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
}
void Actions::localBiznesman()
{
    // create a QDataStream operating on the socket
    QDataStream clientStream(m_chatClient->getQTcpSocket().get());
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;
    message["type"] = QStringLiteral("action");
    message["player"] = m_chatClient->getNickname();
    message["text"] = "localbiznesman";
    message["targeted"] = false;
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
}
void Actions::media()
{
    // create a QDataStream operating on the socket
    QDataStream clientStream(m_chatClient->getQTcpSocket().get());
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;
    message["type"] = QStringLiteral("action");
    message["player"] = m_chatClient->getNickname();
    message["text"] = "media";
    message["targeted"] = false;
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
}
void Actions::onz()
{
    // create a QDataStream operating on the socket
    QDataStream clientStream(m_chatClient->getQTcpSocket().get());
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;
    message["type"] = QStringLiteral("action");
    message["player"] = m_chatClient->getNickname();
    message["text"] = "onz";
    message["targeted"] = true;
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
}
void Actions::police()
{
    // create a QDataStream operating on the socket
    QDataStream clientStream(m_chatClient->getQTcpSocket().get());
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;
    message["type"] = QStringLiteral("action");
    message["player"] = m_chatClient->getNickname();
    message["text"] = "police";
    message["targeted"] = true;
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
}
void Actions::protest()
{
    // create a QDataStream operating on the socket
    QDataStream clientStream(m_chatClient->getQTcpSocket().get());
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;
    message["type"] = QStringLiteral("action");
    message["player"] = m_chatClient->getNickname();
    message["text"] = "protest";
    message["targeted"] = true;
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
}
void Actions::russia()
{
    // create a QDataStream operating on the socket
    QDataStream clientStream(m_chatClient->getQTcpSocket().get());
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;
    message["type"] = QStringLiteral("action");
    message["player"] = m_chatClient->getNickname();
    message["text"] = "russia";
    message["targeted"] = false;
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
}
void Actions::usa()
{
    // create a QDataStream operating on the socket
    QDataStream clientStream(m_chatClient->getQTcpSocket().get());
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;
    message["type"] = QStringLiteral("action");
    message["player"] = m_chatClient->getNickname();
    message["text"] = "usa";
    message["targeted"] = false;
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
}

