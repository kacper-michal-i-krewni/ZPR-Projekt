/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *connectAction;
    QAction *disconnectAction;
    QAction *createGameAction;
    QAction *exitAction;
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *actionsLayout;
    QPushButton *protestButton;
    QPushButton *russiaButton;
    QPushButton *policeButton;
    QPushButton *onzButton;
    QPushButton *mediaButton;
    QPushButton *euButton;
    QPushButton *usaButton;
    QPushButton *localBiznesmanButton;
    QPushButton *affairButton;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *messageLayout;
    QLineEdit *lineEdit;
    QPushButton *sendButton;
    QWidget *gridLayoutWidget_2;
    QGridLayout *chatViewLayout;
    QListView *chatView;
    QWidget *gridLayoutWidget_3;
    QGridLayout *cardsLayout;
    QGraphicsView *card1;
    QGraphicsView *card2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *playerMenuLayout1;
    QLabel *nickname1;
    QLabel *wallet1;
    QPushButton *block1;
    QPushButton *check1;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *playeMenyLayout2;
    QLabel *nickname2;
    QLabel *wallet2;
    QPushButton *block2;
    QPushButton *check2;
    QWidget *gridLayoutWidget_4;
    QGridLayout *cardsLayout2;
    QGraphicsView *card3;
    QGraphicsView *card4;
    QMenuBar *menubar;
    QMenu *menuMenu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(951, 653);
        connectAction = new QAction(MainWindow);
        connectAction->setObjectName(QString::fromUtf8("connectAction"));
        disconnectAction = new QAction(MainWindow);
        disconnectAction->setObjectName(QString::fromUtf8("disconnectAction"));
        createGameAction = new QAction(MainWindow);
        createGameAction->setObjectName(QString::fromUtf8("createGameAction"));
        exitAction = new QAction(MainWindow);
        exitAction->setObjectName(QString::fromUtf8("exitAction"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 500, 691, 83));
        actionsLayout = new QGridLayout(gridLayoutWidget);
        actionsLayout->setObjectName(QString::fromUtf8("actionsLayout"));
        actionsLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        actionsLayout->setContentsMargins(0, 0, 0, 0);
        protestButton = new QPushButton(gridLayoutWidget);
        protestButton->setObjectName(QString::fromUtf8("protestButton"));

        actionsLayout->addWidget(protestButton, 1, 2, 1, 1);

        russiaButton = new QPushButton(gridLayoutWidget);
        russiaButton->setObjectName(QString::fromUtf8("russiaButton"));

        actionsLayout->addWidget(russiaButton, 1, 1, 1, 1);

        policeButton = new QPushButton(gridLayoutWidget);
        policeButton->setObjectName(QString::fromUtf8("policeButton"));

        actionsLayout->addWidget(policeButton, 2, 2, 1, 1);

        onzButton = new QPushButton(gridLayoutWidget);
        onzButton->setObjectName(QString::fromUtf8("onzButton"));

        actionsLayout->addWidget(onzButton, 2, 1, 1, 1);

        mediaButton = new QPushButton(gridLayoutWidget);
        mediaButton->setObjectName(QString::fromUtf8("mediaButton"));

        actionsLayout->addWidget(mediaButton, 1, 3, 1, 1);

        euButton = new QPushButton(gridLayoutWidget);
        euButton->setObjectName(QString::fromUtf8("euButton"));

        actionsLayout->addWidget(euButton, 2, 3, 1, 1);

        usaButton = new QPushButton(gridLayoutWidget);
        usaButton->setObjectName(QString::fromUtf8("usaButton"));

        actionsLayout->addWidget(usaButton, 0, 1, 1, 1);

        localBiznesmanButton = new QPushButton(gridLayoutWidget);
        localBiznesmanButton->setObjectName(QString::fromUtf8("localBiznesmanButton"));

        actionsLayout->addWidget(localBiznesmanButton, 0, 2, 1, 1);

        affairButton = new QPushButton(gridLayoutWidget);
        affairButton->setObjectName(QString::fromUtf8("affairButton"));

        actionsLayout->addWidget(affairButton, 0, 3, 1, 1);

        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 580, 951, 31));
        messageLayout = new QHBoxLayout(horizontalLayoutWidget);
        messageLayout->setObjectName(QString::fromUtf8("messageLayout"));
        messageLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(horizontalLayoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        messageLayout->addWidget(lineEdit);

        sendButton = new QPushButton(horizontalLayoutWidget);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));

        messageLayout->addWidget(sendButton);

        gridLayoutWidget_2 = new QWidget(centralwidget);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(689, 0, 261, 581));
        chatViewLayout = new QGridLayout(gridLayoutWidget_2);
        chatViewLayout->setObjectName(QString::fromUtf8("chatViewLayout"));
        chatViewLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        chatViewLayout->setContentsMargins(0, 0, 0, 0);
        chatView = new QListView(gridLayoutWidget_2);
        chatView->setObjectName(QString::fromUtf8("chatView"));

        chatViewLayout->addWidget(chatView, 0, 0, 1, 1);

        gridLayoutWidget_3 = new QWidget(centralwidget);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(240, 310, 211, 191));
        cardsLayout = new QGridLayout(gridLayoutWidget_3);
        cardsLayout->setObjectName(QString::fromUtf8("cardsLayout"));
        cardsLayout->setContentsMargins(0, 0, 0, 0);
        card1 = new QGraphicsView(gridLayoutWidget_3);
        card1->setObjectName(QString::fromUtf8("card1"));

        cardsLayout->addWidget(card1, 0, 0, 1, 1);

        card2 = new QGraphicsView(gridLayoutWidget_3);
        card2->setObjectName(QString::fromUtf8("card2"));

        cardsLayout->addWidget(card2, 0, 1, 1, 1);

        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(450, 310, 82, 191));
        playerMenuLayout1 = new QVBoxLayout(verticalLayoutWidget);
        playerMenuLayout1->setObjectName(QString::fromUtf8("playerMenuLayout1"));
        playerMenuLayout1->setContentsMargins(0, 0, 0, 0);
        nickname1 = new QLabel(verticalLayoutWidget);
        nickname1->setObjectName(QString::fromUtf8("nickname1"));

        playerMenuLayout1->addWidget(nickname1);

        wallet1 = new QLabel(verticalLayoutWidget);
        wallet1->setObjectName(QString::fromUtf8("wallet1"));

        playerMenuLayout1->addWidget(wallet1);

        block1 = new QPushButton(verticalLayoutWidget);
        block1->setObjectName(QString::fromUtf8("block1"));

        playerMenuLayout1->addWidget(block1);

        check1 = new QPushButton(verticalLayoutWidget);
        check1->setObjectName(QString::fromUtf8("check1"));

        playerMenuLayout1->addWidget(check1);

        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(450, 0, 82, 191));
        playeMenyLayout2 = new QVBoxLayout(verticalLayoutWidget_2);
        playeMenyLayout2->setObjectName(QString::fromUtf8("playeMenyLayout2"));
        playeMenyLayout2->setContentsMargins(0, 0, 0, 0);
        nickname2 = new QLabel(verticalLayoutWidget_2);
        nickname2->setObjectName(QString::fromUtf8("nickname2"));

        playeMenyLayout2->addWidget(nickname2);

        wallet2 = new QLabel(verticalLayoutWidget_2);
        wallet2->setObjectName(QString::fromUtf8("wallet2"));

        playeMenyLayout2->addWidget(wallet2);

        block2 = new QPushButton(verticalLayoutWidget_2);
        block2->setObjectName(QString::fromUtf8("block2"));

        playeMenyLayout2->addWidget(block2);

        check2 = new QPushButton(verticalLayoutWidget_2);
        check2->setObjectName(QString::fromUtf8("check2"));

        playeMenyLayout2->addWidget(check2);

        gridLayoutWidget_4 = new QWidget(centralwidget);
        gridLayoutWidget_4->setObjectName(QString::fromUtf8("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(240, 0, 211, 191));
        cardsLayout2 = new QGridLayout(gridLayoutWidget_4);
        cardsLayout2->setObjectName(QString::fromUtf8("cardsLayout2"));
        cardsLayout2->setContentsMargins(0, 0, 0, 0);
        card3 = new QGraphicsView(gridLayoutWidget_4);
        card3->setObjectName(QString::fromUtf8("card3"));

        cardsLayout2->addWidget(card3, 0, 0, 1, 1);

        card4 = new QGraphicsView(gridLayoutWidget_4);
        card4->setObjectName(QString::fromUtf8("card4"));

        cardsLayout2->addWidget(card4, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 951, 20));
        menuMenu = new QMenu(menubar);
        menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuMenu->menuAction());
        menuMenu->addSeparator();
        menuMenu->addAction(createGameAction);
        menuMenu->addSeparator();
        menuMenu->addAction(connectAction);
        menuMenu->addSeparator();
        menuMenu->addAction(disconnectAction);
        menuMenu->addSeparator();
        menuMenu->addAction(exitAction);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        connectAction->setText(QApplication::translate("MainWindow", "Connect", nullptr));
        disconnectAction->setText(QApplication::translate("MainWindow", "Disconnect", nullptr));
        createGameAction->setText(QApplication::translate("MainWindow", "Create a game", nullptr));
        exitAction->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        protestButton->setText(QApplication::translate("MainWindow", "Protest", nullptr));
        russiaButton->setText(QApplication::translate("MainWindow", "Rosja", nullptr));
        policeButton->setText(QApplication::translate("MainWindow", "Policja", nullptr));
        onzButton->setText(QApplication::translate("MainWindow", "ONZ", nullptr));
        mediaButton->setText(QApplication::translate("MainWindow", "Media", nullptr));
        euButton->setText(QApplication::translate("MainWindow", "UE", nullptr));
        usaButton->setText(QApplication::translate("MainWindow", "USA", nullptr));
        localBiznesmanButton->setText(QApplication::translate("MainWindow", "Lokalni Biznesmani", nullptr));
        affairButton->setText(QApplication::translate("MainWindow", "Afera!", nullptr));
        sendButton->setText(QApplication::translate("MainWindow", "Wy\305\233lij", nullptr));
        nickname1->setText(QApplication::translate("MainWindow", "Kaczmii", nullptr));
        wallet1->setText(QApplication::translate("MainWindow", "3 mil", nullptr));
        block1->setText(QApplication::translate("MainWindow", "Zablokuj", nullptr));
        check1->setText(QApplication::translate("MainWindow", "Sprawdz", nullptr));
        nickname2->setText(QApplication::translate("MainWindow", "Kaczmii", nullptr));
        wallet2->setText(QApplication::translate("MainWindow", "3 mil", nullptr));
        block2->setText(QApplication::translate("MainWindow", "Zablokuj", nullptr));
        check2->setText(QApplication::translate("MainWindow", "Sprawdz", nullptr));
        menuMenu->setTitle(QApplication::translate("MainWindow", "Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H