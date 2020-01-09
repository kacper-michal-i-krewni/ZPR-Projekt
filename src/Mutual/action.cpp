#include "action.h"

Action::Action()
{

}

Action::~Action()
{

}

bool Action::isBlockedBy(QString &name)
{
    return _blockers.contains(name);
}

bool Action::isBlocking(QString &name)
{
    return _blocking.contains(name);
}
