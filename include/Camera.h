#ifndef CAMERA_H
#define CAMERA_H
#include <Vector3.h>
#include <Position.h>

class Camera
{
    public:
        Position* position;
        Vector3* target;
        Vector3* direction;
        float speed;

        Camera(Position* _initPos);
        void Move(float _dt);
        virtual ~Camera();

    protected:

    private:
};

#endif // CAMERA_H
