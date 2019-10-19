#pragma once

// Class provides an interface for processing with polygons

// All point in polygon locate counter-clockwise when called solveSquare()

#include <vector>
#include <algorithm>

#define PI 3.14159265

#include "vector.h"
#include "vertex.h"
#include "line.h"

struct Polygon
{
    std::vector<Vertex2D> vert_array;

    Polygon() = default;
    Polygon(const std::vector<Vertex2D> & vertex_ins);

    void push_back(const Vertex2D & vert_ins);
    float solveSquare();
    static bool compare(const Vertex2D & a, const Vertex2D & b);
    static float getAngle(const Vertex2D & a);
    Vertex2D calcCenter() const;
    int Size() const { return vert_array.size(); }
};