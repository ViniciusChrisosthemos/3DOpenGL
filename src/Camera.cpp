#include "Camera.h"
#include<Vector3.h>

Camera::Camera()
{
    position = new Vector3(0,0,0);
    target = new Vector3(0,0,8);
    direction = new Vector3(0,1,0);
    angle = 0;
}

Camera::~Camera()
{
}
