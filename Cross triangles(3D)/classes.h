#pragma once
#include <vector>
#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>

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

    Vertex() {}
    Vertex(float X, float Y) : x(X), y(Y) {}

    bool operator==(const Vertex & A) { return ((x == A.x) && (y == A.y)); }
};

struct Vector
{
    float x = 0.f;
    float y = 0.f;

    Vector() {}
    Vector(float X, float Y) : x(X), y(Y) {}
    Vector(const Vertex & A, const Vertex & B) : x(B.x - A.x), y(B.y - A.y) {}

    float operator*(const Vector & A) { return x * A.y - y * A.x; }
};

struct Line
{
    Vertex a;
    Vertex b;

    Line() {}
    Line(Vertex A, Vertex B) : a(A), b(B) {}

    float lengh() { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); }
    bool isAcross(Line line, OUT Vertex & out);
    PointParams isSegmentsAcross(const Line & line);
    bool lineInLine(Line what, OUT Vertex & out);
};

struct Poligon
{
    std::vector<Vertex> vert_array;

    Poligon() {}
    Poligon(const std::vector<Vertex> & vertex_ins);

    void push_back(const Vertex & vert_ins);
    float solveSquare();
    static bool compare(const Vertex & a, const Vertex & b);
    static float getAngle(const Vertex & a);
    Vertex calcCenter();
};

struct  Triangle2D
{
    std::array<Vertex, 3> vertex;
    Triangle2D() {};
    Triangle2D(const Triangle2D & triangle_ins)
    {
        std::copy(triangle_ins.vertex.begin(), triangle_ins.vertex.end(), vertex.begin());
    }
    Triangle2D(Triangle2D && triangle_ins)
    {
        std::swap(vertex, triangle_ins.vertex);
    }

    friend std::istream& operator>> (std::istream &in, Triangle2D &triangle);

};