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
    /*!
     * \brief eu slot
     * Implementation of button of action with the same name clicked
     */
    void eu();
    /*!
     * \brief russia slot
     * Implementation of button of action with the same name clicked
     */
    void russia();
    /*!
     * \brief media slot
     * Implementation of button of action with the same name clicked
     */
    void media();
    /*!
     * \brief onz slot
     * Implementation of button of action with the same name clicked
     */
    void onz();
    /*!
     * \brief police slot
     * Implementation of button of action with the same name clicked
     */
    void police();
signals:
    /*!
     * \brief disableBlockButton signal
     * It is used to pass signal to MainWindow to block 'block' button
     */
    void disableBlockButton();
private:
    /*!
     * \brief ui
     * Pointer to blocking ui
     */
    Ui::BlockingUi *ui;
    /*!
     * \brief client pointer
     * Pointer to chatClient used to send messages to server
     */
    std::shared_ptr<ChatClient> client;
    /*!
     * \brief checkAndExecute function
     * \param action's name
     * Function is used to send messgaes to server about blocking
     */
    void checkAndExecute(const QString &action);
};

#endif // BLOCKINGUI_H
