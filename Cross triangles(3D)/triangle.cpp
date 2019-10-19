#include "triangle.h"


std::istream& operator>> (std::istream &in, Triangle2D &triangle)
{
    for (auto &v : triangle.vertex)
        in >> v.x >> v.y;

    return in;
}

std::istream& operator>> (std::istream &in, Triangle3D &triangle)
{
    for (auto &v : triangle.vertex)
        in >> v.x >> v.y >> v.z;

    return in;
}

Polygon Triangle2D::commonPolygon(Triangle2D & triangle)
{
    Polygon polygon;
    int out_count = 0;

    // поиск всех точек пересечения 
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            Vertex2D cross(0, 0); // outer vertex
            if (Line(vertex[i], vertex[(i + 1) % 3]).isAcross(Line(triangle[j], triangle[(j + 1) % 3]), cross))
            {
                out_count++;
                polygon.push_back(cross);
            }
        }
    // Добавление всех точек, которые лежат в другом треугольнике
    Internal(triangle, polygon);
 
    return polygon;
}

void Triangle2D::Internal(Triangle2D & triangle, Polygon & polygon)
{
    allInternalVertex2D(triangle, polygon);
    triangle.allInternalVertex2D(*this, polygon);
}

void Triangle2D::allInternalVertex2D(Triangle2D & trianle, Polygon & polygon)
{
    Vertex2D A = vertex[0];
    Vertex2D B = vertex[1];
    Vertex2D C = vertex[2];

    float det = Vector2D(A, B) * Vector2D(A, C);

    for (int j = 0; j < 3; j++)
    {
        float det2 =  Vector2D(A, trianle[j]) * Vector2D(A, C);
        float det1 = Vector2D(A, B) * Vector2D(A, trianle[j]);

        float det3 = det - det1 - det2;
        
        if (!((det2 > 0 && det1 > 0 && det3 > 0) || (det2 < 0 && det1 < 0 && det3 < 0)))
            continue;


        polygon.push_back(trianle[j]);
    }
}

bool Triangle3D::isAcross(const Triangle3D & triangle) const
{
    if (hasInternal(triangle) || triangle.hasInternal(*this))
       return true;

    return intersects(triangle);
}

bool Triangle3D::hasInternal(const Triangle3D & trianle) const
{
    Vertex3D A = vertex[0];
    Vertex3D B = vertex[1];
    Vertex3D C = vertex[2];

    Vector3D crossProd = Vector3D(A, B).cross(Vector3D(A, C));
    float det = sqrtf(crossProd.dot(crossProd));
    if (det == 0) return false;

    for (int j = 0; j < 3; j++)
    {

        crossProd =  Vector3D(A, trianle[j]).cross(Vector3D(A, C));
        float det2 = sqrtf(crossProd.dot(crossProd));

        crossProd = Vector3D(A, B).cross(Vector3D(A, trianle[j]));
        float det1 = sqrtf(crossProd.dot(crossProd));

        crossProd = Vector3D(trianle[j], B).cross(Vector3D(trianle[j], C));
        float det3 = sqrtf(crossProd.dot(crossProd));
        
        if ((det1 + det2 + det3) != det)
            continue;

        return true;
    }

    return false;
}

bool Triangle3D::intersects(const Triangle3D & triangle) const
{
    Vector3D e1 = vertex[1] - vertex[0];
    Vector3D e2 = vertex[2] - vertex[0];

    Vector3D n1 = e1.cross(e2).norm();

    if (n1.length() == 0)
    {
        return false;

        // TODO check if 2 lines intersect!
    }

    Vector3D n2 = e1.cross(n1).norm();

    Triangle2D first = getProection(e1, n2, vertex[0]);
    Triangle2D second = triangle.getProection(e1, n2, vertex[0]);
    if (first.commonPolygon(second).Size() == 0)
        return false;
    
    first = getProection(e1, n1, vertex[0]);
    second = triangle.getProection(e1, n1, vertex[0]);
    if (first.commonPolygon(second).Size() == 0)
        return false;

    first = getProection(n1, n2, vertex[0]);
    second = triangle.getProection(n1, n2, vertex[0]);
    if (first.commonPolygon(second).Size() == 0)
        return false;


    // new point
    e1 = vertex[0] - vertex[1];
    e2 = vertex[2] - vertex[1];

    n1 = e2.cross(e1);
    n2 = n1.cross(e2);

    first = getProection(n1, n2, vertex[1]);
    second = triangle.getProection(n1, n2, vertex[1]);
    if (first.commonPolygon(second).Size() == 0)
        return false;

    return true;
}

Triangle2D Triangle3D::getProection(Vector3D const & e1, Vector3D const & e2, Vertex3D const & center) const
{
    Triangle2D triangle;
    for (int i = 0; i < 3; i++)
        triangle[i] = Vertex2D((vertex[i] - center).dot(e1), (vertex[i] - center).dot(e2));

    return triangle;

}