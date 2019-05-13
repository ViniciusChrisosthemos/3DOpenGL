#ifndef EDGE_H
#define EDGE_H
#include <Vector3.h>

class Edge
{
    public:
        Vector3* p1;
        Vector3* p2;
        Vector3* p3;
        Vector3* p4;

        Edge();
        virtual ~Edge();

    protected:

    private:
};

#endif // EDGE_H
