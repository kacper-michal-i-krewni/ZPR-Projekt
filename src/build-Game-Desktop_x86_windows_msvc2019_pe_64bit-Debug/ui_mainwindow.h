/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *connectAction;
    QAction *disconnectAction;
    QAction *actionCreate_a_game;
    QAction *exitAction;
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_6;
    QPushButton *pushButton_9;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_5;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *sendButton;
    QGraphicsView *graphicsView;
    QGraphicsView *graphicsView_2;
    QGraphicsView *graphicsView_3;
    QGraphicsView *graphicsView_4;
    QGraphicsView *graphicsView_5;
    QGraphicsView *graphicsView_6;
    QGraphicsView *graphicsView_7;
    QGraphicsView *graphicsView_8;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_3;
    QListView *chatView;
    QMenuBar *menubar;
    QMenu *menuMenu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(951, 653);
        connectAction = new QAction(MainWindow);
        connectAction->setObjectName(QStringLiteral("connectAction"));
        disconnectAction = new QAction(MainWindow);
        disconnectAction->setObjectName(QStringLiteral("disconnectAction"));
        actionCreate_a_game = new QAction(MainWindow);
        actionCreate_a_game->setObjectName(QStringLiteral("actionCreate_a_game"));
        exitAction = new QAction(MainWindow);
        exitAction->setObjectName(QStringLiteral("exitAction"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 500, 691, 83));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_6 = new QPushButton(gridLayoutWidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        gridLayout->addWidget(pushButton_6, 1, 0, 1, 1);

        pushButton_9 = new QPushButton(gridLayoutWidget);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));

        gridLayout->addWidget(pushButton_9, 1, 3, 1, 1);

        pushButton_3 = new QPushButton(gridLayoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 0, 2, 1, 1);

        pushButton_2 = new QPushButton(gridLayoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 0, 1, 1, 1);

        pushButton = new QPushButton(gridLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_7 = new QPushButton(gridLayoutWidget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        gridLayout->addWidget(pushButton_7, 1, 1, 1, 1);

        pushButton_8 = new QPushButton(gridLayoutWidget);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        gridLayout->addWidget(pushButton_8, 1, 2, 1, 1);

        pushButton_5 = new QPushButton(gridLayoutWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        gridLayout->addWidget(pushButton_5, 0, 3, 1, 1);

        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 580, 951, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(horizontalLayoutWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        sendButton = new QPushButton(horizontalLayoutWidget);
        sendButton->setObjectName(QStringLiteral("sendButton"));

        horizontalLayout->addWidget(sendButton);

        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(250, 310, 81, 151));
        graphicsView_2 = new QGraphicsView(centralwidget);
        graphicsView_2->setObjectName(QStringLiteral("graphicsView_2"));
        graphicsView_2->setGeometry(QRect(350, 310, 81, 151));
        graphicsView_3 = new QGraphicsView(centralwidget);
        graphicsView_3->setObjectName(QStringLiteral("graphicsView_3"));
        graphicsView_3->setGeometry(QRect(350, 30, 81, 151));
        graphicsView_4 = new QGraphicsView(centralwidget);
        graphicsView_4->setObjectName(QStringLiteral("graphicsView_4"));
        graphicsView_4->setGeometry(QRect(250, 30, 81, 151));
        graphicsView_5 = new QGraphicsView(centralwidget);
        graphicsView_5->setObjectName(QStringLiteral("graphicsView_5"));
        graphicsView_5->setGeometry(QRect(50, 170, 161, 71));
        graphicsView_6 = new QGraphicsView(centralwidget);
        graphicsView_6->setObjectName(QStringLiteral("graphicsView_6"));
        graphicsView_6->setGeometry(QRect(50, 250, 161, 71));
        graphicsView_7 = new QGraphicsView(centralwidget);
        graphicsView_7->setObjectName(QStringLiteral("graphicsView_7"));
        graphicsView_7->setGeometry(QRect(480, 170, 161, 71));
        graphicsView_8 = new QGraphicsView(centralwidget);
        graphicsView_8->setObjectName(QStringLiteral("graphicsView_8"));
        graphicsView_8->setGeometry(QRect(480, 250, 161, 71));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(250, 460, 181, 31));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(250, 0, 181, 31));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(0, 170, 41, 151));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(650, 170, 41, 151));
        gridLayoutWidget_2 = new QWidget(centralwidget);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(689, 0, 261, 581));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        chatView = new QListView(gridLayoutWidget_2);
        chatView->setObjectName(QStringLiteral("chatView"));

        gridLayout_3->addWidget(chatView, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 951, 21));
        menuMenu = new QMenu(menubar);
        menuMenu->setObjectName(QStringLiteral("menuMenu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuMenu->menuAction());
        menuMenu->addSeparator();
        menuMenu->addAction(actionCreate_a_game);
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        connectAction->setText(QApplication::translate("MainWindow", "Connect", Q_NULLPTR));
        disconnectAction->setText(QApplication::translate("MainWindow", "Disconnect", Q_NULLPTR));
        actionCreate_a_game->setText(QApplication::translate("MainWindow", "Create a game", Q_NULLPTR));
        exitAction->setText(QApplication::translate("MainWindow", "Exit", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
        pushButton_9->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "Akcja2", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Akcja1", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
        pushButton_8->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
        sendButton->setText(QApplication::translate("MainWindow", "Wy\305\233lij", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Kaczmi: 10 mil", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Micha\305\202: 0 kapusty", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        menuMenu->setTitle(QApplication::translate("MainWindow", "Menu", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H