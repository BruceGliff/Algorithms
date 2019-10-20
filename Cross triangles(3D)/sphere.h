#pragma once

#include <unistd.h>
#include <vector>
#include <set>

#include "vertex.h"
#include "vector.h"
#include "triangle.h"

// Classes provide interfaces for working with optimization \
   using Space splitting and Spheres describing a triangle.

// For optimization Octo-tree used

namespace Optimization{

template <typename T>
struct Box
{
    Vertex3D<T> zero;
    T d;
    Box() = default;
    Box(const Vertex3D<T> & point, T d_ins) : zero(point), d(d_ins) {}
    Box(const Box & box, int iter);

    Vertex3D<T> center() const
    {  
        return Vertex3D<T>(zero.x + d/2, zero.y + d/2, zero.z + d/2);
    }
};

template <typename T>
class Sphere
{
    Triangle3D<T> triangle;

    int index;
    Vertex3D<T> center;
    T radius;
    void SetSphere();
    
public:
    Sphere() = default;

    Sphere(const Triangle3D<T> & triangle_ins, int index_ins) :
        triangle(triangle_ins),
        index(index_ins)
    {
        SetSphere();
    }

    bool SphereIntersectBox(const Box<T> & box) const
    {
        Vertex3D<T> boxCenter = box.center();
        if (center.x - radius <= boxCenter.x || center.x + radius >= boxCenter.x
         || center.y - radius <= boxCenter.y || center.x + radius >= boxCenter.y
         || center.z - radius <= boxCenter.z || center.x + radius >= boxCenter.z)
            return true;

        return false;
    }

    bool CheckTriangles(const Sphere * sphere, std::set<int> & out_result) const
    {
        if (triangle.isAcross(sphere->triangle))
        {
            out_result.insert(index);
            out_result.insert(sphere->index);

            return true;
        }

        return false;
    }

    bool insideBox(const Box<T> & box)
    {
        if (center.x < box.zero.x || center.x > box.zero.x + box.d
         || center.y < box.zero.y || center.y > box.zero.y + box.d
         || center.z < box.zero.z || center.z > box.zero.z + box.d)
            return false;
        
        return true;
    }

};

template <typename T>
void CreateBox(const Box<T> & box, std::vector<Sphere<T>*> & array, int last_size, int delta_depth, std::set<int> & out_result);
}

#include "sphere.hpp"