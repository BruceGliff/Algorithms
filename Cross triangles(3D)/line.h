#pragma once

// Class provides an interface for processing with lines

#include <algorithm>

#include "vertex.h"
#include "vector.h"

struct PointParams
{
    float angle1;
    float angle2;

    enum class PointStatus
    {
        DifferentSide,
        OneSide,
        Parallel
    } status;
};

struct Line
{
    Vertex2D a;
    Vertex2D b;

    Line() {}
    Line(Vertex2D A, Vertex2D B) : a(A), b(B) {}

    float lengh() { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); }
    bool isAcross(Line line, Vertex2D & out);
    PointParams isSegmentsAcross(const Line & line);
    bool lineInLine(Line what, Vertex2D & out);
};