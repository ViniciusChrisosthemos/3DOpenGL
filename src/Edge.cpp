#include "Edge.h"
#include <Vector3.h>

Edge::Edge()
{
    p1 = new Vector3(0,0,0);
    p2 = new Vector3(0,0,0);
    p3 = new Vector3(0,0,0);
    p4 = new Vector3(0,0,0);
}

Edge::~Edge()
{
    delete p1;
    delete p2;
    delete p3;
    delete p4;
}
