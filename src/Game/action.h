#ifndef ACTION_H
#define ACTION_H

#include <QObject>

class Action
{
public:
    Action();
    virtual void action() = 0;
    virtual ~Action(){}
private:
    bool IndicatePlayer;

};

#endif // ACTION_H
