#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chatclient.h"
#include "actions.h"
#include "gamelistdialog.h"

#include <QStandardItemModel>
#include <QInputDialog>
#include <QMessageBox>
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_chatClient(new ChatClient(this))
    , m_chatModel(new QStandardItemModel(this))
    , m_actions( new Actions(m_chatClient))
{
    // set up of the .ui file
    ui->setupUi(this);
    // the model for the messages will have 1 column
    m_chatModel->insertColumn(0);
    // set the model as the data source vor the list view
    ui->chatView->setModel(m_chatModel.get());
    // connect the signals from the chat client to the slots in this ui
    connect(m_chatClient.get(), &ChatClient::connected, this, &MainWindow::connectedToServer);
    connect(m_chatClient.get(), &ChatClient::loggedIn, this, &MainWindow::loggedIn);
    connect(m_chatClient.get(), &ChatClient::loginError, this, &MainWindow::loginFailed);
    connect(m_chatClient.get(), &ChatClient::messageReceived, this, &MainWindow::messageReceived);
    connect(m_chatClient.get(), &ChatClient::disconnected, this, &MainWindow::disconnectedFromServer);
    connect(m_chatClient.get(), &ChatClient::error, this, &MainWindow::error);
    connect(m_chatClient.get(), &ChatClient::userJoined, this, &MainWindow::userJoined);
    connect(m_chatClient.get(), &ChatClient::userLeft, this, &MainWindow::userLeft);
    connect(m_chatClient.get(), &ChatClient::actionExecute, this, &MainWindow::actionExecute);
    connect(m_chatClient.get(), &ChatClient::sessionListComplete, this, &MainWindow::displaySessionDialog);
    connect(m_chatClient.get(), &ChatClient::updatePlayerInterface, this, &MainWindow::updatePlayerInterface);
    // connect the create game action to slot that will attempt creating game
    connect(ui->connectToServerAction, &QAction::triggered, this, &MainWindow::connectToServer);
    connect(ui->createGameAction, &QAction::triggered, this, &MainWindow::createGame);
    // connect the connect action to a slot that will attempt the connection
    connect(ui->joinToGameAction, &QAction::triggered, this, &MainWindow::joinToGame);
    // connect the disconnect action to a slot that will make disconnect
    connect(ui->disconnectAction, &QAction::triggered, this, &MainWindow::disconnect);
    // Exiting app
    connect(ui->exitAction, &QAction::triggered, this, &MainWindow::close);
    // connect the click of the "send" button and the press of the enter while typing to the slot that sends the message
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::sendMessage);
    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &MainWindow::sendMessage);
    // connect all actions buttons
    connect(ui->affairButton, &QPushButton::clicked, m_actions.get(), &Actions::affair);
    connect(ui->euButton, &QPushButton::clicked, m_actions.get(), &Actions::eu);
    connect(ui->localBiznesmanButton, &QPushButton::clicked, m_actions.get(), &Actions::localBiznesman);
    connect(ui->mediaButton, &QPushButton::clicked, m_actions.get(), &Actions::media);
    connect(ui->onzButton, &QPushButton::clicked, m_actions.get(), &Actions::onz);
    connect(ui->policeButton, &QPushButton::clicked, m_actions.get(), &Actions::police);
    connect(ui->protestButton, &QPushButton::clicked, m_actions.get(), &Actions::protest);
    connect(ui->russiaButton, &QPushButton::clicked, m_actions.get(), &Actions::russia);
    connect(ui->usaButton, &QPushButton::clicked, m_actions.get(), &Actions::usa);

    ui->sendButton->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    ui->chatView->setEnabled(false);
    ui->disconnectAction->setEnabled(false);
    ui->joinToGameAction->setEnabled(false);
    ui->createGameAction->setEnabled(false);
    tooglePlayerInterface(false);

}

MainWindow::~MainWindow()
{
    // delete the elements created from the .ui file
    delete ui;
}

void MainWindow::connectToServer(){
    const QString hostAddress = QInputDialog::getText(
        this
        , tr("Choose Server")
        , tr("Server Address")
        , QLineEdit::Normal
        , QStringLiteral("127.0.0.1")
    );
    if (hostAddress.isEmpty())
        return; // the user pressed cancel or typed nothing
    // disable the connect button to prevent the user clicking it again

    // tell the client to connect to the host using the port 1967
    m_chatClient->connectToServer(QHostAddress(hostAddress), 1967);
}

void MainWindow::joinToGame()
{
    QJsonObject message;
    message["request"] = QStringLiteral("showSessionsRequest");
    message["type"] = QStringLiteral("session");
    m_chatClient->sendMessageToServer(message);
}

void MainWindow::createGame()
{
    const QString playerNumber = QInputDialog::getText(
        this
        , tr("Number of players")
        , tr("Players:")
        , QLineEdit::Normal
        , QStringLiteral("4")
    );

    QJsonObject message;
    message["playerNumber"] = playerNumber;
    message["request"] = QStringLiteral("createRequest");
    message["type"] = QStringLiteral("session");

    m_chatClient->sendMessageToServer(message);

}


void MainWindow::displaySessionDialog(QVector<QMap<QString, QVariant> > &sessVec){
    GameListDialog* dialog = new GameListDialog(nullptr, sessVec); //TU MA BYĆ SESSMAP);
    dialog->setModal(true);
    dialog->exec();

}

void MainWindow::connectedToServer()
{
    // once we connected to the server we ask the user for what username they would like to use
    const QString newUsername = QInputDialog::getText(this, tr("Chose Username"), tr("Username"));
    if (newUsername.isEmpty()){
        // if the user clicked cancel or typed nothing, we just disconnect from the server
        return m_chatClient->disconnectFromHost();
    }
    // try to login with the given username
    attemptLogin(newUsername);

}

void MainWindow::attemptLogin(const QString &userName)
{
    // use the client to attempt a log in with the given username
    m_chatClient->login(userName);
}

void MainWindow::loggedIn()
{
    // once we successully log in we enable the ui to display and send messages
    ui->sendButton->setEnabled(true);
    ui->lineEdit->setEnabled(true);
    ui->chatView->setEnabled(true);
    ui->usaButton->setEnabled(true);
    ui->connectToServerAction->setEnabled(false);
    ui->createGameAction->setEnabled(true);
    ui->joinToGameAction->setEnabled(true);
    ui->disconnectAction->setEnabled(true);
    // clear the user name record
    m_lastUserName.clear();
}

void MainWindow::loginFailed(const QString &reason)
{
    // the server rejected the login attempt
    // display the reason for the rejection in a message box
    QMessageBox::critical(this, tr("Error"), reason);
    // allow the user to retry, execute the same slot as when just connected
    connectedToServer();
}

void MainWindow::messageReceived(const QString &sender, const QString &text)
{
    // store the index of the new row to append to the model containing the messages
    int newRow = m_chatModel->rowCount();
    // we display a line containing the username only if it's different from the last username we displayed
    if (m_lastUserName != sender) {
        // store the last displayed username
        m_lastUserName = sender;
        // create a bold default font
        QFont boldFont;
        boldFont.setBold(true);
        // insert 2 row, one for the message and one for the username
        m_chatModel->insertRows(newRow, 2);
        // store the username in the model
        m_chatModel->setData(m_chatModel->index(newRow, 0), sender + ':');
        // set the alignment for the username
        m_chatModel->setData(m_chatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
        // set the for the username
        m_chatModel->setData(m_chatModel->index(newRow, 0), boldFont, Qt::FontRole);
        ++newRow;
    } else {
        // insert a row for the message
        m_chatModel->insertRow(newRow);
    }
    // store the message in the model
    m_chatModel->setData(m_chatModel->index(newRow, 0), text);
    // set the alignment for the message
    m_chatModel->setData(m_chatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
    // scroll the view to display the new message
    ui->chatView->scrollToBottom();
}

void MainWindow::sendMessage()
{
    // we use the client to send the message that the user typed
    m_chatClient->sendChatMessage(ui->lineEdit->text());
    // now we add the message to the list
    // store the index of the new row to append to the model containing the messages
    const int newRow = m_chatModel->rowCount();
    // insert a row for the message
    m_chatModel->insertRow(newRow);
    // Add nickname on the front
    m_chatModel->setData(m_chatModel->index(newRow, 0), m_chatClient->getNickname() + ':');
    // store the message in the model
    m_chatModel->setData(m_chatModel->index(newRow, 0), ui->lineEdit->text());
    // set the alignment for the message
    m_chatModel->setData(m_chatModel->index(newRow, 0), int(Qt::AlignRight | Qt::AlignVCenter), Qt::TextAlignmentRole);
    // clear the content of the message editor
    ui->lineEdit->clear();
    // scroll the view to display the new message
    ui->chatView->scrollToBottom();
    // reset the last printed username
    m_lastUserName.clear();
}

void MainWindow::disconnectedFromServer()
{
    // if the client loses connection to the server
    // comunicate the event to the user via a message box
    QMessageBox::warning(this, tr("Disconnected"), tr("The host terminated the connection"));
    // disable the ui to send and display messages
    ui->sendButton->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    ui->chatView->setEnabled(false);
    // enable the button to connect to the server again
    ui->joinToGameAction->setEnabled(true);

    // store the index of the new row to append to the model containing the messages
    const int newRow = m_chatModel->rowCount();
    // insert a row
    m_chatModel->insertRow(newRow);
    // store in the model the message to comunicate a user joined
    m_chatModel->setData(m_chatModel->index(newRow, 0), tr("%1 left the Chat").arg(m_chatClient->getNickname()));
    // set the alignment for the text
    m_chatModel->setData(m_chatModel->index(newRow, 0), Qt::AlignCenter, Qt::TextAlignmentRole);
    // set the color for the text
    m_chatModel->setData(m_chatModel->index(newRow, 0), QBrush(Qt::blue), Qt::ForegroundRole);

    // reset the last printed username
    m_lastUserName.clear();
}

void MainWindow::userJoined(const QString &username)
{
    // store the index of the new row to append to the model containing the messages
    const int newRow = m_chatModel->rowCount();
    // insert a row
    m_chatModel->insertRow(newRow);
    // store in the model the message to comunicate a user joined
    m_chatModel->setData(m_chatModel->index(newRow, 0), tr("%1 Joined the Chat").arg(username));
    // set the alignment for the text
    m_chatModel->setData(m_chatModel->index(newRow, 0), Qt::AlignCenter, Qt::TextAlignmentRole);
    // set the color for the text
    m_chatModel->setData(m_chatModel->index(newRow, 0), QBrush(Qt::blue), Qt::ForegroundRole);
    // scroll the view to display the new message
    ui->chatView->scrollToBottom();
    // reset the last printed username
    m_lastUserName.clear();
}
void MainWindow::userLeft(const QString &username)
{
    // store the index of the new row to append to the model containing the messages
    const int newRow = m_chatModel->rowCount();
    // insert a row
    m_chatModel->insertRow(newRow);
    // store in the model the message to comunicate a user left
    m_chatModel->setData(m_chatModel->index(newRow, 0), tr("%1 Left the Chat").arg(username));
    // set the alignment for the text
    m_chatModel->setData(m_chatModel->index(newRow, 0), Qt::AlignCenter, Qt::TextAlignmentRole);
    // set the color for the text
    m_chatModel->setData(m_chatModel->index(newRow, 0), QBrush(Qt::red), Qt::ForegroundRole);
    // scroll the view to display the new message
    ui->chatView->scrollToBottom();
    // reset the last printed username
    m_lastUserName.clear();
}

void MainWindow::error(QAbstractSocket::SocketError socketError)
{
    // show a message to the user that informs of what kind of error occurred
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
    case QAbstractSocket::ProxyConnectionClosedError:
        return; // handled by disconnectedFromServer
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::critical(this, tr("Error"), tr("The host refused the connection"));
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        QMessageBox::critical(this, tr("Error"), tr("The proxy refused the connection"));
        break;
    case QAbstractSocket::ProxyNotFoundError:
        QMessageBox::critical(this, tr("Error"), tr("Could not find the proxy"));
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::critical(this, tr("Error"), tr("Could not find the server"));
        break;
    case QAbstractSocket::SocketAccessError:
        QMessageBox::critical(this, tr("Error"), tr("You don't have permissions to execute this operation"));
        break;
    case QAbstractSocket::SocketResourceError:
        QMessageBox::critical(this, tr("Error"), tr("Too many connections opened"));
        break;
    case QAbstractSocket::SocketTimeoutError:
        QMessageBox::warning(this, tr("Error"), tr("Operation timed out"));
        return;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        QMessageBox::critical(this, tr("Error"), tr("Proxy timed out"));
        break;
    case QAbstractSocket::NetworkError:
        QMessageBox::critical(this, tr("Error"), tr("Unable to reach the network"));
        break;
    case QAbstractSocket::UnknownSocketError:
        QMessageBox::critical(this, tr("Error"), tr("An unknown error occured"));
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        QMessageBox::critical(this, tr("Error"), tr("Operation not supported"));
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        QMessageBox::critical(this, tr("Error"), tr("Your proxy requires authentication"));
        break;
    case QAbstractSocket::ProxyProtocolError:
        QMessageBox::critical(this, tr("Error"), tr("Proxy comunication failed"));
        break;
    case QAbstractSocket::TemporaryError:
    case QAbstractSocket::OperationError:
        QMessageBox::warning(this, tr("Error"), tr("Operation failed, please try again"));
        return;
    default:
        Q_UNREACHABLE();
    }
    // enable the button to connect to the server again
    ui->joinToGameAction->setEnabled(true);
    // disable the ui to send and display messages
    ui->sendButton->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    ui->chatView->setEnabled(false);
    // reset the last printed username
    m_lastUserName.clear();
}

void MainWindow::disconnect()
{
    // disconnect player from server
    // for now itd wrong, need to write some more code
    //emit m_chatClient->userLeft(m_chatClient->getNickname());
    m_chatClient->disconnect();
    ui->joinToGameAction->setEnabled(true);
    ui->disconnectAction->setEnabled(false);
}


void MainWindow::tooglePlayerInterface(bool b)
{
    // block all action buttons
    ui->usaButton->setEnabled(b);
    ui->localBiznesmanButton->setEnabled(b);
    ui->affairButton->setEnabled(b);
    ui->russiaButton->setEnabled(b);
    ui->protestButton->setEnabled(b);
    ui->mediaButton->setEnabled(b);
    ui->onzButton->setEnabled(b);
    ui->policeButton->setEnabled(b);
    ui->euButton->setEnabled(b);
    // block user interface
    ui->block1->setEnabled(b);
    ui->check1->setEnabled(b);
    ui->block2->setEnabled(b);
    ui->check2->setEnabled(b);
}

void MainWindow::actionExecute(const QString &sender, const QString &action)
{
    QMessageBox::warning(this, tr(sender.toUtf8().constData()), tr(action.toUtf8().constData()));
}


void MainWindow::updatePlayerInterface(const QString &player, const double money, const double lifes)
{
    if ( ui->nickname1->text().compare(player,Qt::CaseInsensitive ) == 0 ) // if first
    {
        ui->wallet1->setText(QString("%1").arg(money));
    }
    else if ( ui->nickname2->text().compare(player,Qt::CaseInsensitive ) == 0 ) // if first
    {
        ui->wallet2->setText(QString("%1").arg(money));
    }

}
