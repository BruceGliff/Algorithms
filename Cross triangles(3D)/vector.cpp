#include "vector.h"

Vector3D operator-(const Vertex3D & A, const Vertex3D & B)
{
    return Vector3D(B, A);
}