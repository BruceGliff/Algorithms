#include "classes.h"

namespace Global
{
    Vertex2D center;
}

bool Line::isAcross(Line line, OUT Vertex2D & out)
{
    PointParams params = line.isSegmentsAcross(*this);

    if (isSegmentsAcross(line).status == PointParams::PointStatus::OneSide)
        return false;
    if (params.status == PointParams::PointStatus::OneSide)
        return false;

    // параллельность отрезков
    if (params.status == PointParams::PointStatus::Parallel)
    {

        if (lengh() > line.lengh())
            return lineInLine(line, out);
        else 
            return line.lineInLine(*this, out);
 
        out = a;

        return true;
    }

    out.x = line.a.x + (line.b.x - line.a.x) * fabs(params.angle1) / fabs(params.angle2 - params.angle1);
    out.y = line.a.y + (line.b.y - line.a.y) * fabs(params.angle1) / fabs(params.angle2 - params.angle1);

    return true;
}

PointParams Line::isSegmentsAcross(const Line & line)
{
    PointParams params;

    float angle1 = Vector2D(line.a, a) * Vector2D(line.a, line.b);
    float angle2 = Vector2D(line.a, b) * Vector2D(line.a, line.b); 

    // Если точки одного отрезка лежат по одну сторону от другого отрезка\
    то они не пересекаюся
    if (angle1 * angle2 > 0)
    { 
        params.status = PointParams::PointStatus::OneSide; 
        return params;
    }

    if (angle1 == 0 && angle2 == 0)
    {
        params.status = PointParams::PointStatus::Parallel;
        return params;
    }

    params.status = PointParams::PointStatus::DifferentSide;
    params.angle1 = angle1;
    params.angle2 = angle2;
    return params;
}

bool Line::lineInLine(Line what, OUT Vertex2D & out)
{
    float x1 = std::max(a.x, b.x);
    float x2 = std::min(a.x, b.x);
    if (what.a.x <= x1 && what.a.x >= x2)
    {
        out.x = what.a.x;
        out.y = what.a.y;
        return true;
    }
    if (what.b.x <= x1 && what.b.x >= x2)
    {
        out.x = what.b.x;
        out.y = what.b.y;
        return true;
    }
    return false;
}

Poligon::Poligon(const std::vector<Vertex2D> & vertex_ins)
{
    for (auto x : vertex_ins)
        vert_array.push_back(x);
}

void Poligon::push_back(const Vertex2D & vert_ins)
{
    bool is = false;
    for (auto vert : vert_array)
    {
        if (vert == vert_ins)
        {
            is = true;
            break;
        }
    }
    if (!is)
        vert_array.push_back(vert_ins);
}

float Poligon::solveSquare()
{
    Global::center = calcCenter();

    // Сортировка вершин многоугольника, чтобы можно было совершить их обход против часовой стрелки
    sort(vert_array.begin(), vert_array.end(), compare);

    float square = 0;

    // расчёт площади выпуклого многоугольника s = sum(Xi * Yi+1 - Xi+1 * Yi)
    for (int i = 0; i < vert_array.size(); i++)
    {
        square += vert_array[i].x * vert_array[(i + 1) % vert_array.size()].y - vert_array[(i + 1) % vert_array.size()].x * vert_array[i].y;
    }

    return fabs(square) / 2;
}

bool Poligon::compare(const Vertex2D & a, const Vertex2D & b)
{
    if (getAngle(a) > getAngle(b))
        return 1;
            
    return 0;
}   

float Poligon::getAngle(const Vertex2D & a)
{
    float dx_a = 0, dy_a = 0, r_a = 0, cosA = 0, sinA = 0;
    dx_a = a.x - Global::center.x;
    dy_a = a.y - Global::center.y;

    float b = dx_a * dx_a + dy_a * dy_a;

    r_a = sqrtf(b);

    cosA = dx_a / r_a;
    sinA = dy_a / r_a;

    if (sinA > 0)
        return acosf(cosA);
    else
        return (2 * PI - acosf(cosA));
}

Vertex2D Poligon::calcCenter()
{
    float x = 0;
    float y = 0;
    float kx = 0, ky = 0;

    for (auto vert : vert_array)
    {
        x += vert.x;
        y += vert.y;

        kx += 1; ky += 1;        
    }
    
    return Vertex2D(x / kx, y / ky);
}



std::istream& operator>> (std::istream &in, Triangle2D &triangle)
{
    std::for_each(triangle.vertex.begin(), triangle.vertex.end(),   [&in](Vertex2D & v)
                                                                    { 
                                                                        in >> v.x >> v.y;
                                                                    }
                 );

    return in;
}

std::istream& operator>> (std::istream &in, Triangle3D &triangle)
{
    std::for_each(triangle.vertex.begin(), triangle.vertex.end(),   [&in](Vertex3D & v)
                                                                    { 
                                                                        in >> v.x >> v.y >> v.z;
                                                                    }
                 );

    return in;
}

Poligon Triangle2D::commonPoligon(Triangle2D & triangle)
{
    Poligon poligon;
    int out_count = 0;

    // поиск всех точек пересечения 
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            Vertex2D cross(0, 0); // outer vertex
            if (Line(vertex[i], vertex[(i + 1) % 3]).isAcross(Line(triangle[j], triangle[(j + 1) % 3]), cross))
            {
                out_count++;
                poligon.push_back(cross);
            }
        }
    // Добавление всех точек, которые лежат в другом треугольнике
    Internal(triangle, poligon);
 
    return poligon;
}

void Triangle2D::Internal(Triangle2D & triangle, Poligon & poligon)
{
    allInternalVertex2D(triangle, poligon);
    triangle.allInternalVertex2D(*this, poligon);
}

void Triangle2D::allInternalVertex2D(Triangle2D & trianle, Poligon & poligon)
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


        poligon.push_back(trianle[j]);
    }
}

Triangle2D Triangle3D::getProection(Flat inFlat) const
{
    Triangle2D triangle;
    switch (inFlat)
    {
    case Flat::XY:
        for (int i = 0; i < 3; i++)
            triangle[i] = Vertex2D(vertex[i].x, vertex[i].y);
        break;
    case Flat::YZ:
        for (int i = 0; i < 3; i++)
            triangle[i] = Vertex2D(vertex[i].y, vertex[i].z);
        break;
    case Flat::XZ:
        for (int i = 0; i < 3; i++)
            triangle[i] = Vertex2D(vertex[i].x, vertex[i].z);
        break;
    default:
        break;
    }

    return triangle;
}

bool Triangle3D::isAcross(const Triangle3D & triangle)
{
    if (hasInternal(triangle) || triangle.hasInternal(*this))
        return true;

    // Algorithm Mollers


    return true;
}

bool Triangle3D::hasInternal(const Triangle3D & trianle) const
{
    Vertex3D A = vertex[0];
    Vertex3D B = vertex[1];
    Vertex3D C = vertex[2];

    Vector3D crossProd = Vector3D(A, B).cross(Vector3D(A, C));
    float det = sqrtf(crossProd.dot(crossProd));

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