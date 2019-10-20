#pragma once

// Forward declaration
template <typename T>
struct Vector3D;

// Classes provide an interface for processing with points(vertexes) in 3D and 2D spaces
// Substruction two vertexes gives a Vector

template <typename T>
struct Vertex2D
{
    T x;
    T y;

    Vertex2D() = default;
    Vertex2D(T X, T Y) : x(X), y(Y) {}

    bool operator==(const Vertex2D & A) const { return ((x == A.x) && (y == A.y)); }
};

template <typename T>
struct Vertex3D
{
    T x;
    T y;
    T z;

    Vertex3D() = default;
    Vertex3D(T X, T Y, T Z) : x(X), y(Y), z(Z) {}

    friend Vector3D<T> operator-(const Vertex3D<T> & A, const Vertex3D<T> & B)
    {
        return Vector3D<T>(B, A);
    }
};