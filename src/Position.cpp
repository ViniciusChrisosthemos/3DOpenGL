#include "Position.h"
#include <Vector3.h>

Position::Position()
{
    coord = new Vector3(0,0,0);
    angle = 0;
}

Position::Position(Vector3* _coord, float _angle)
{
    coord = _coord;
    angle = _angle;
}

Position::~Position()
{
    delete coord;
}
