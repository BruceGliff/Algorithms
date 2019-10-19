#pragma once
#include <array>
#include <iostream>
#include <algorithm>

#include "vector.h"
#include "vertex.h"
#include "polygon.h"

// Classes provide an interface for processing with triangles in 2D and 3D spaces

struct Triangle2D
{
    std::array<Vertex2D, 3> vertex;

    Vertex2D& operator[](int index) { return vertex[index]; }
	const Vertex2D& operator[](int index) const { return vertex[index]; }
    void operator=(const Triangle2D & triangle_ins)
    {
        std::copy(triangle_ins.vertex.begin(), triangle_ins.vertex.end(), vertex.begin());
    }

    friend std::istream& operator>> (std::istream &in, Triangle2D &triangle);

    Polygon commonPolygon(Triangle2D & triangle);
    void Internal(Triangle2D & triangle, Polygon & polygon);
    void allInternalVertex2D(Triangle2D & trianle, Polygon & polygon);

};

// Triangle in 3D can has a proection to any basis

struct Triangle3D
{
    std::array<Vertex3D, 3> vertex;
    Triangle3D() = default;
    Triangle3D(const Triangle3D & triangle_ins)
    {
        std::copy(triangle_ins.vertex.begin(), triangle_ins.vertex.end(), vertex.begin());
    }
    Triangle3D(Triangle3D && triangle_ins)
    {
        std::swap(vertex, triangle_ins.vertex);
    }

    Vertex3D& operator[](int index) { return vertex[index]; }
	const Vertex3D& operator[](int index) const { return vertex[index]; }

    friend std::istream& operator>> (std::istream &in, Triangle3D &triangle);

    bool isAcross(const Triangle3D & triangle) const;

    bool hasInternal(const Triangle3D & trianle) const;

    bool intersects(const Triangle3D & triangle) const; 

    Triangle2D getProection(Vector3D const & e1, Vector3D const & e2, Vertex3D const & center) const;
};