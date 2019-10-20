#pragma once

// Class provides an interface for processing with lines(length, interserts, contains)

#include <algorithm>

#include "vertex.h"
#include "vector.h"

template <typename T>
struct PointParams
{
    T angle1;
    T angle2;

    enum class PointStatus
    {
        DifferentSide,
        OneSide,
        Parallel
    } status;
};

template <typename T>
struct Line
{
    Vertex2D<T> a;
    Vertex2D<T> b;

    Line() = default;
    Line(Vertex2D<T> A, Vertex2D<T> B) : a(A), b(B) {}

    T lengh() const { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); }
    bool isAcross(Line line, Vertex2D<T> & out) const;
    PointParams<T> isSegmentsAcross(const Line & line) const;
    bool lineInLine(Line what, Vertex2D<T> & out) const;
};

#include "line.hpp"