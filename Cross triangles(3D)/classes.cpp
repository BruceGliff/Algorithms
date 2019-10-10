#include "classes.h"

namespace Global
{
    Vertex center;
}

bool Line::isAcross(Line line, OUT Vertex & out)
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

    float angle1 = Vector(line.a, a) * Vector(line.a, line.b);
    float angle2 = Vector(line.a, b) * Vector(line.a, line.b); 

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

bool Line::lineInLine(Line what, OUT Vertex & out)
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

Poligon::Poligon(const std::vector<Vertex> & vertex_ins)
{
    for (auto x : vertex_ins)
        vert_array.push_back(x);
}

void Poligon::push_back(const Vertex & vert_ins)
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

bool Poligon::compare(const Vertex & a, const Vertex & b)
{
    if (getAngle(a) > getAngle(b))
        return 1;
            
    return 0;
}   

float Poligon::getAngle(const Vertex & a)
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

Vertex Poligon::calcCenter()
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
    
    return Vertex(x / kx, y / ky);
}



std::istream& operator>> (std::istream &in, Triangle2D &triangle)
{
    std::for_each(triangle.vertex.begin(), triangle.vertex.end(),   [&in](Vertex & v)
                                                                    { 
                                                                        in >> v.x >> v.y;
                                                                    }
                 );

    return in;
}
