#ifndef CAMERA_H
#define CAMERA_H
#include<Vector3.h>

class Camera
{
    public:
        Vector3* position;
        Vector3* target;
        Vector3* direction;
        float angle;

        Camera();
        virtual ~Camera();

    protected:

    private:
};

#endif // CAMERA_H
