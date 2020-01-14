#ifndef BLOCKINGUI_H
#define BLOCKINGUI_H

#include <QWidget>
#include "chatclient.h"

namespace Ui {
class BlockingUi;
}

class BlockingUi : public QWidget
{
    Q_OBJECT

public:
    explicit BlockingUi(QWidget *parent = nullptr, std::shared_ptr<ChatClient> c = std::shared_ptr<ChatClient>(nullptr));
    ~BlockingUi();

public slots:
    void eu();
    void russia();
    void media();
    void onz();
    void police();
    //void protest();
private:
    Ui::BlockingUi *ui;
    std::shared_ptr<ChatClient> client;

    void checkAndExecute(const QString &action);
};

#endif // BLOCKINGUI_H
