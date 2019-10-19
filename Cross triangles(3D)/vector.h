#pragma once
#include <cmath>

#include "vertex.h"

// Classes provide an interface for processing with vectors in 3D and 2D spaces

// Calculation cross and dot products and normalize vectors

struct Vector2D
{
    float x = 0.f;
    float y = 0.f;

    Vector2D() = default;
    Vector2D(float X, float Y) : x(X), y(Y) {}
    Vector2D(const Vertex2D & A, const Vertex2D & B) : x(B.x - A.x), y(B.y - A.y) {}

    float operator*(const Vector2D & A) const { return x * A.y - y * A.x; }
};

struct Vector3D
{
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;

    Vector3D() = default;
    Vector3D(float X, float Y, float Z) : x(X), y(Y), z(Z) {}
    Vector3D(const Vertex3D & A, const Vertex3D & B) : x(B.x - A.x), y(B.y - A.y), z(B.z - A.z) {}

    float length() const { return sqrtf(dot(*this)); }
    void setNorm() { float len = length(); if (len == 0) return; x /= len; y /= len; z /= len; }
    Vector3D norm() const { float len = length(); if (len == 0) return Vector3D();  
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