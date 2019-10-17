#pragma once

// Forward declaration
struct Vector3D;

// Classes provide an interface for processing with points(vertexes) in 3D and 2D spaces
// Substruction two vertexes gives a Vector

struct Vertex2D
{
    float x = 0.f;
    float y = 0.f;

    Vertex2D() = default;
    Vertex2D(float X, float Y) : x(X), y(Y) {}

    bool operator==(const Vertex2D & A) { return ((x == A.x) && (y == A.y)); }
};

struct Vertex3D
{
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;

    Vertex3D() = default;
    Vertex3D(float X, float Y, float Z) : x(X), y(Y), z(Z) {}

    friend Vector3D operator-(const Vertex3D & A, const Vertex3D & B);
};