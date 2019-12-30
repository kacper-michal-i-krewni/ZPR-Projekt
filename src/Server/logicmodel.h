#ifndef LOGICMODEL_H
#define LOGICMODEL_H

#include <QObject>
#include <memory>

#include "player.h"

class LogicModel : public QObject
{
    Q_OBJECT
public:
    explicit LogicModel(QObject *parent = nullptr);
    ~LogicModel();

signals:

public slots:

private:
    QVector<std::shared_ptr<Player>> _players;
};

#endif // LOGICMODEL_H
