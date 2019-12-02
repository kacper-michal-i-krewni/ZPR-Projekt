/********************************************************************************
** Form generated from reading UI file 'serverwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERWINDOW_H
#define UI_SERVERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ServerWindow
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QPlainTextEdit *logEditor;
    QSpacerItem *horizontalSpacer;
    QPushButton *startStopButton;

    void setupUi(QWidget *ServerWindow)
    {
        if (ServerWindow->objectName().isEmpty())
            ServerWindow->setObjectName(QStringLiteral("ServerWindow"));
        ServerWindow->resize(400, 300);
        gridLayout = new QGridLayout(ServerWindow);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(ServerWindow);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 2);

        logEditor = new QPlainTextEdit(ServerWindow);
        logEditor->setObjectName(QStringLiteral("logEditor"));
        logEditor->setReadOnly(true);

        gridLayout->addWidget(logEditor, 1, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(298, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        startStopButton = new QPushButton(ServerWindow);
        startStopButton->setObjectName(QStringLiteral("startStopButton"));

        gridLayout->addWidget(startStopButton, 2, 1, 1, 1);


        retranslateUi(ServerWindow);

        QMetaObject::connectSlotsByName(ServerWindow);
    } // setupUi

    void retranslateUi(QWidget *ServerWindow)
    {
        ServerWindow->setWindowTitle(QApplication::translate("ServerWindow", "Qt Simple Chat Server", Q_NULLPTR));
        label->setText(QApplication::translate("ServerWindow", "Server Log", Q_NULLPTR));
        startStopButton->setText(QApplication::translate("ServerWindow", "Start Server", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ServerWindow: public Ui_ServerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERWINDOW_H
