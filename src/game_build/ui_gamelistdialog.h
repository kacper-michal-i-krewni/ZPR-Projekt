/********************************************************************************
** Form generated from reading UI file 'gamelistdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMELISTDIALOG_H
#define UI_GAMELISTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_GameListDialog
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QPushButton *pushButton;

    void setupUi(QDialog *GameListDialog)
    {
        if (GameListDialog->objectName().isEmpty())
            GameListDialog->setObjectName(QString::fromUtf8("GameListDialog"));
        GameListDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(GameListDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listWidget = new QListWidget(GameListDialog);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout->addWidget(listWidget);

        pushButton = new QPushButton(GameListDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(GameListDialog);

        QMetaObject::connectSlotsByName(GameListDialog);
    } // setupUi

    void retranslateUi(QDialog *GameListDialog)
    {
        GameListDialog->setWindowTitle(QApplication::translate("GameListDialog", "Dialog", nullptr));
        pushButton->setText(QApplication::translate("GameListDialog", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameListDialog: public Ui_GameListDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMELISTDIALOG_H
