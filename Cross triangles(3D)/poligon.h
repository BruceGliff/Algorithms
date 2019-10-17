#pragma once

// Class provides an interface for processing with poligons

#include <vector>
#include <algorithm>

#define PI 3.14159265

#include "vector.h"
#include "vertex.h"
#include "line.h"

struct Poligon
{
    std::vector<Vertex2D> vert_array;

    Poligon() = default;
    Poligon(const std::vector<Vertex2D> & vertex_ins);

    void push_back(const Vertex2D & vert_ins);
    float solveSquare();
    static bool compare(const Vertex2D & a, const Vertex2D & b);
    static float getAngle(const Vertex2D & a);
    Vertex2D calcCenter();
    int Size() { return vert_array.size(); }
};