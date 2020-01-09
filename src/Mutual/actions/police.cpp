#include "police.h"

Police::Police()
{
    _indicatePlayer = true;
    _name = "police";
    _blocking.push_front("police");
    _blockers.push_front("police");
    _blockers.push_front("media");
    _blockers.push_front("onz");
}


void Police::action()
{


}


Police::~Police()
{

}
