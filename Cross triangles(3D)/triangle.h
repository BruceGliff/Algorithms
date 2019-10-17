#pragma once
#include <array>
#include <iostream>
#include <algorithm>

#include "vector.h"
#include "vertex.h"
#include "poligon.h"

// Classes provide an interface for processing with triangles in 2D and 3D spaces

struct Triangle2D
{
    std::array<Vertex2D, 3> vertex;
    Triangle2D() = default;
    Triangle2D(const Triangle2D & triangle_ins)
    {
        std::copy(triangle_ins.vertex.begin(), triangle_ins.vertex.end(), vertex.begin());
    }
    Triangle2D(Triangle2D && triangle_ins)
    {
        std::swap(vertex, triangle_ins.vertex);
    }

    Vertex2D& operator[](int index) { return vertex[index]; }
	const Vertex2D& operator[](int index) const { return vertex[index]; }
    void operator=(const Triangle2D & triangle_ins)
    {
        std::copy(triangle_ins.vertex.begin(), triangle_ins.vertex.end(), vertex.begin());
    }

    friend std::istream& operator>> (std::istream &in, Triangle2D &triangle);

    Poligon commonPoligon(Triangle2D & triangle);
    void Internal(Triangle2D & triangle, Poligon & poligon);
    void allInternalVertex2D(Triangle2D & trianle, Poligon & poligon);

};

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
    Triangle3D operator=(Triangle3D && tr)
    {
        std::swap(vertex, tr.vertex);
        return *this;
    }
    Triangle3D operator=(const Triangle3D & tr)
    {
        std::copy(tr.vertex.begin(), tr.vertex.end(), vertex.begin());
        return *this;
    }

    friend std::istream& operator>> (std::istream &in, Triangle3D &triangle);

    bool isAcross(const Triangle3D & triangle);

    bool hasInternal(const Triangle3D & trianle) const;

    bool intersects(const Triangle3D & triangle) const; 

    Triangle2D getProection(Vector3D const & e1, Vector3D const & e2, Vertex3D const & center) const;
};