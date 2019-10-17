#include "poligon.h"

namespace Global
{
    Vertex2D center;
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