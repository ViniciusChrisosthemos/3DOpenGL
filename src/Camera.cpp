#include "Camera.h"
#include <Vector3.h>
#include <Position.h>
#include <math.h>

#define DEG 0.01745329251

Camera::Camera(Position* _initPos)
{
    position = _initPos;
    target = new Vector3(0,0,8);
    direction = new Vector3(0,1,0);
    speed = 1;
}

Camera::~Camera()
{
}

void Camera::Move(float _dt)
{
    float alfa = 10 * _dt;
    float newX = sin(position->angle*DEG) * alfa;
    float newZ = cos(position->angle*DEG) * alfa;

    position->coord->x += newX;
    position->coord->z += newZ;
    target->x += newX;
    target->z += newZ;
}
