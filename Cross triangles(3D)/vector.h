#pragma once
#include <cmath>

#include "vertex.h"

// Classes provide an interface for processing with vectors in 3D and 2D spaces

// Calculation cross and dot products and normalize vectors

template <typename T>
struct Vector2D
{
    T x;
    T y;

    Vector2D() = default;
    Vector2D(T X, T Y) : x(X), y(Y) {}
    Vector2D(const Vertex2D<T> & A, const Vertex2D<T> & B) : x(B.x - A.x), y(B.y - A.y) {}

    T operator*(const Vector2D & A) const { return x * A.y - y * A.x; }
};

template <typename T>
struct Vector3D
{
    T x;
    T y;
    T z;

    Vector3D() = default;
    Vector3D(T X, T Y, T Z) : x(X), y(Y), z(Z) {}
    Vector3D(const Vertex3D<T> & A, const Vertex3D<T> & B) : x(B.x - A.x), y(B.y - A.y), z(B.z - A.z) {}

    T length() const { return sqrtl(dot(*this)); }
    void setNorm() { T len = length(); if (len == 0) return; x /= len; y /= len; z /= len; }
    Vector3D norm() const { const T len = length(); if (len == 0) return Vector3D();  
        return Vector3D<T>(x / len, y/len, z/len);
    }

    Vector3D cross(const Vector3D & A) const
    {
        return Vector3D(y * A.z - z * A.y, - (x * A.z - z * A.x), x * A.y - y * A.x);
    }
    
    T dot(const Vector3D & A) const
    {
        return x * A.x + y * A.y + z * A.z;
    }
    
};