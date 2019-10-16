#pragma once

#include "classes.h"
#include <unistd.h>
#include <set>


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

class Sphere
{
    Triangle3D triangle;

    //std::set<int> checkedWith;
public:
    int index;
    Vertex3D center;
    float radius;
    void SetSphere();
    
public:
    Sphere() = default;

    Sphere(const Triangle3D & triangle_ins, int index_ins) :
    triangle(triangle_ins),
    index(index_ins),
    radius(0.f)
    {
        SetSphere();
    }
    Sphere(Sphere && sp)
    {
        triangle = sp.triangle;
        index = sp.index;
        center = sp.center;
        radius = sp.radius;
    }

    bool SphereIntersectBox(Box box) const
    {
        Vertex3D boxCenter = box.center();
        if (center.x - radius <= boxCenter.x || center.x + radius >= boxCenter.x
         || center.y - radius <= boxCenter.y || center.x + radius >= boxCenter.y
         || center.z - radius <= boxCenter.z || center.x + radius >= boxCenter.z)
            return true;

        return false;
    }

    void CheckTriangles(Sphere * sphere)
    {
        // for (auto it = checkedWith.begin(); it != checkedWith.end(); it++)
        // {
        //     if(*it == &sphere)
        //         return;
        // }
        
        
        // checkedWith.push_back(&sphere); 

        if (triangle.isAcross(sphere->triangle))
            std::cout << index << ' ' << sphere->index << '\n';
    }

    bool insideBox(const Box & box)
    {
        if (center.x < box.zero.x || center.x > box.zero.x + box.d
         || center.y < box.zero.y || center.y > box.zero.y + box.d
         || center.z < box.zero.z || center.z > box.zero.z + box.d)
            return false;
        
        return true;
    }

};

void CreateBox(const Box & box, std::vector<Sphere*> & array, int last_size = 0, int delta_depth = 0);
}