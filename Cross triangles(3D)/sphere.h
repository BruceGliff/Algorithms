#pragma once

#include "classes.h"
#include <unistd.h>


namespace Optimization{

struct Box
{
    Vertex3D zero;
    float d;
    Box() = default;
    Box(const Vertex3D & point, float d_ins) : zero(point), d(d_ins) {}
    Box(const Box & box, int iter);

    Vertex3D center() const
    {
        
        return Vertex3D(zero.x + d/2, zero.y + d/2, zero.z + d/2);
    }
};

class OSphere
{
    std::vector<Triangle3D>::iterator triangle;

    std::vector<OSphere *> checkedWith;

    int index;
    Vertex3D center;
    float radius;
    void SetSphere();
    
public:
    OSphere() = default;

    OSphere(std::vector<Triangle3D>::iterator triangle_ins, int index_ins) :
    triangle(triangle_ins),
    index(index_ins),
    radius(0.f)
    {
        SetSphere();
    }

    bool SphereIntersectBox(Box box) const;
    void CheckTriangles(OSphere & sphere)
    {
        for (auto it = checkedWith.begin(); it != checkedWith.end(); it++)
        {
            if(*it == &sphere)
                return;
        }
        
        
        checkedWith.push_back(&sphere); 

        if (triangle->isAcross(*(sphere.triangle)))
            std::cout << index << ' ' << sphere.index << '\n';
    }
};

void CreateBox(const Box & box, std::vector<OSphere*> & array, int last_size = 0, int delta_depth = 0);
}