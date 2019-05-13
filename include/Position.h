#ifndef POSITION_H
#define POSITION_H
#include <Vector3.h>

class Position
{
    public:
        Vector3* coord;
        float angle;

        Position();
        Position(Vector3* _coord, float _angle);
        virtual ~Position();

    protected:

    private:
};

#endif // POSITION_H
