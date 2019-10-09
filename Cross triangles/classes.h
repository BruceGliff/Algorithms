#pragma once
#include <vector>
#include <algorithm>
#include <cmath>

#define PI 3.14159265
#define OUT

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


struct Vertex
{
    float x = 0.f;
    float y = 0.f;

    Vertex();
    Vertex(float X, float Y);

    bool operator==(const Vertex & A);
};

struct Vector
{
    float x = 0.f;
    float y = 0.f;

    Vector();
    Vector(float X, float Y);
    Vector(const Vertex & A, const Vertex & B);

    float operator*(const Vector & A);
};

struct Line
{
    Vertex a;
    Vertex b;

    Line();
    Line(Vertex A, Vertex B);

    float lengh();
    bool isAcross(Line line, OUT Vertex & out);
    PointParams isSegmentsAcross(const Line & line);
    bool lineInLine(Line what, OUT Vertex & out);
};

struct Poligon
{
    std::vector<Vertex> vert_array;

    Poligon();
    Poligon(const std::vector<Vertex> & vertex_ins);

    void push_back(const Vertex & vert_ins);
    float solveSquare();
    static bool compare(const Vertex & a, const Vertex & b);
    static float getAngle(const Vertex & a);
    Vertex calcCenter();
};