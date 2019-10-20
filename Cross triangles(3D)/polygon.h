#pragma once

// Class provides an interface for processing with polygons

// All point in polygon locate counter-clockwise when called solveSquare()

#include <vector>
#include <algorithm>

#define PI 3.14159265

#include "vector.h"
#include "vertex.h"
#include "line.h"

template <typename T>
struct Polygon
{
    std::vector<Vertex2D<T>> vert_array;

    Polygon() = default;
    Polygon(const std::vector<Vertex2D<T>> & vertex_ins);

    void push_back(const Vertex2D<T> & vert_ins);
    T solveSquare();
    static bool compare(const Vertex2D<T> & a, const Vertex2D<T> & b);
    static T getAngle(const Vertex2D<T> & a);
    Vertex2D<T> calcCenter() const;
    int Size() const { return vert_array.size(); }
};

#include "polygon.hpp"