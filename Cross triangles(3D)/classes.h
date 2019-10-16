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

enum class Flat
{
    XY,
    XZ,
    YZ
};

struct Vertex2D
{
    float x = 0.f;
    float y = 0.f;

    Vertex2D() {}
    Vertex2D(float X, float Y) : x(X), y(Y) {}

    bool operator==(const Vertex2D & A) { return ((x == A.x) && (y == A.y)); }
};

struct Vertex3D
{
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;

    Vertex3D() {}
    Vertex3D(float X, float Y, float Z) : x(X), y(Y), z(Z) {}

};

struct Vector2D
{
    float x = 0.f;
    float y = 0.f;

    Vector2D() {}
    Vector2D(float X, float Y) : x(X), y(Y) {}
    Vector2D(const Vertex2D & A, const Vertex2D & B) : x(B.x - A.x), y(B.y - A.y) {}

    float operator*(const Vector2D & A) { return x * A.y - y * A.x; }
};

struct Vector3D
{
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;

    Vector3D() {}
    Vector3D(float X, float Y, float Z) : x(X), y(Y), z(Z) {}
    Vector3D(const Vertex3D & A, const Vertex3D & B) : x(B.x - A.x), y(B.y - A.y), z(B.z - A.z) {}

    float length() { return sqrtf(dot(*this)); }
    void setNorm() { float len = length(); if (len == 0) return; x /= len; y /= len; z /= len; }
    Vector3D norm() { float len = length(); if (len == 0) return Vector3D();  
        return Vector3D(x / len, y/len, z/len);
    }

    Vector3D cross(const Vector3D & A) const
    {
        return Vector3D(y * A.z - z * A.y, - (x * A.z - z * A.x), x * A.y - y * A.x);
    }
    float dot(const Vector3D & A) const
    {
        return x * A.x + y * A.y + z * A.z;
    }
};

struct Line
{
    Vertex2D a;
    Vertex2D b;

    Line() {}
    Line(Vertex2D A, Vertex2D B) : a(A), b(B) {}

    float lengh() { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); }
    bool isAcross(Line line, OUT Vertex2D & out);
    PointParams isSegmentsAcross(const Line & line);
    bool lineInLine(Line what, OUT Vertex2D & out);
};

struct Poligon
{
    std::vector<Vertex2D> vert_array;

    Poligon() {}
    Poligon(const std::vector<Vertex2D> & vertex_ins);

    void push_back(const Vertex2D & vert_ins);
    float solveSquare();
    static bool compare(const Vertex2D & a, const Vertex2D & b);
    static float getAngle(const Vertex2D & a);
    Vertex2D calcCenter();
    int Size() { return vert_array.size(); }
};

struct Triangle2D
{
    std::array<Vertex2D, 3> vertex;
    Triangle2D() {};
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
    Triangle3D() {}
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

    Triangle2D getProection(Flat inFlat) const;
    bool isAcross(const Triangle3D & triangle);

    bool hasInternal(const Triangle3D & trianle) const;

    bool intersects(const Triangle3D & triangle) const; 

    Triangle2D getProection(Vector3D const & e1, Vector3D const & e2, Vertex3D const & center) const;
};