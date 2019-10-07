#include <iostream>
#include <vector>
#include <cmath>
#include <array>
#include <algorithm>

#define OUT
#define PI 3.14159265

struct vertex
{
    float x;
    float y;
    vertex() : x(0), y(0) {}
    vertex(float X, float Y) : x(X), y(Y) {}
};

struct vector
{
    float x;
    float y;
    vector() : x(0), y(0) {}
    vector(float X, float Y) : x(X), y(Y) {}
};

struct line
{
    vertex a;
    vertex b;
    line() {}
    line(vertex A, vertex B) : a(A), b(B) {}
};

enum class PointStatus
{
    DifferentSide,
    OneSide,
    Parallel
};

struct PointParams
{
    PointStatus status;
    float angle1;
    float angle2;
};

bool isAcross(line l1, line l2, OUT vertex & out);
float crossProduct(vector a1, vector a2);
void Internal(const std::vector<vertex> & t1, const std::vector<vertex> & t2, std::vector<vertex> & OUT poligon);
float solveSquare(std::vector<vertex> & poligon);

vertex center(0, 0);

float getAngle(const vertex & a)
{
    float dx_a = 0, dy_a = 0, r_a = 0, cosA = 0, sinA = 0;
    dx_a = a.x - center.x;
    dy_a = a.y - center.y;

    float b = dx_a * dx_a + dy_a * dy_a;

    r_a = sqrtf(b);

    cosA = dx_a / r_a;
    sinA = dy_a / r_a;

    if (sinA > 0)
        return acosf(cosA);
    else
        return (2 * PI - acosf(cosA));
}

// переход в полярную систему координат\
и сравнение углов у разных точек для их сортировки
bool compare(const vertex & a, const vertex & b)
{
    if (getAngle(a) > getAngle(b))
        return 1;
            
    return 0;
}   

float square(const std::vector<vertex> & t1, const std::vector<vertex> & t2) // arrays of vectors
{
    std::vector <vertex> poligon;
    int out_count = 0;
    // поиск всех точек пересечения 
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            vertex cross(0, 0); // outer vertex
            if(isAcross(line(t1[i], t1[(i + 1) % 3]), line(t2[j], t2[(j + 1) % 3]), cross))
            {
                out_count++;
                bool is = false;
                for (auto vert : poligon)
                {
                    if (vert.x == cross.x && vert.y == cross.y)
                    {
                        is = true;
                        break;
                    }
                }
                if (!is)
                    poligon.push_back(cross);
            }
        }
    // Добавление всех точек, которые лежат в другом треугольнике
    Internal(t1, t2, poligon);

    float x = 0;
    float y = 0;
    float kx = 0, ky = 0;

    for (auto vert : poligon)
    {
        x += vert.x;
        y += vert.y;

        kx += 1; ky += 1;        
    }

    if (kx == 0)
        return 0;

    // Центр масс (начало координат полярной системы)
    center = vertex(x / kx, y / ky);
 
    return solveSquare(poligon);
}

float solveSquare(std::vector<vertex> & poligon)
{
    // Сортировка вершин многоугольника, чтобы можно было совершить их обход против часовой стрелки
    sort(poligon.begin(), poligon.end(), compare);

    float square = 0;

    // расчёт площади выпуклого многоугольника s = sum(Xi * Yi+1 - Xi+1 * Yi)
    for (int i = 0; i < poligon.size(); i++)
    {
        square += poligon[i].x * poligon[(i + 1) % poligon.size()].y - poligon[(i + 1) % poligon.size()].x * poligon[i].y;
    }

    return fabs(square) / 2;
}

bool lineInLine(line in, line what, OUT vertex & out)
{
    float x1 = std::max(in.a.x, in.b.x);
    float x2 = std::min(in.a.x, in.b.x);
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

PointParams isSegmentsAcross(line & l1, line & l2)
{
    PointParams params;
    float angle1 = crossProduct(vector(l1.a.x - l2.a.x, l1.a.y - l2.a.y),
                                vector(l2.b.x - l2.a.x, l2.b.y - l2.a.y));

    float angle2 = crossProduct(vector(l1.b.x - l2.a.x, l1.b.y - l2.a.y),
                                vector(l2.b.x - l2.a.x, l2.b.y - l2.a.y));  

    // Если точки одного отрезка лежат по одну сторону от другого отрезка\
    то они не пересекаюся
    if (angle1 * angle2 > 0)
    { 
        params.status = PointStatus::OneSide; 
        return params;
    }

    if (angle1 == 0 && angle2 == 0)
    {
        params.status = PointStatus::Parallel;
        return params;
    }

    params.status = PointStatus::DifferentSide;
    params.angle1 = angle1;
    params.angle2 = angle2;
    return params;

}

bool isAcross(line l1, line l2, OUT vertex & out)
{
    PointParams params = isSegmentsAcross(l2,l1);

    if (isSegmentsAcross(l1, l2).status == PointStatus::OneSide)
        return false;
    if (params.status == PointStatus::OneSide)
        return false;

    // параллельность отрезков
    if (params.status == PointStatus::Parallel)
    {
        float len1 = (l1.a.x - l1.b.x) * (l1.a.x - l1.b.x) + (l1.a.y - l1.b.y) * (l1.a.y - l1.b.y);
        float len2 = (l2.a.x - l2.b.x) * (l2.a.x - l2.b.x) + (l2.a.y - l2.b.y) * (l2.a.y - l2.b.y); 

        if (len1 > len2)
            return lineInLine(l1, l2, out);
        else 
            return lineInLine(l2, l1, out);
 

        out.x = l1.a.x;
        out.y = l1.a.y;

        return true;
    }

    out.x = l2.a.x + (l2.b.x - l2.a.x) * fabs(params.angle1) / fabs(params.angle2 - params.angle1);
    out.y = l2.a.y + (l2.b.y - l2.a.y) * fabs(params.angle1) / fabs(params.angle2 - params.angle1);

    return true;
}

void allInternalVertex(const std::vector<vertex> & in, const std::vector<vertex> & what, std::vector<vertex> & OUT poligon)
{
    vertex A = in[0];
    vertex B = in[1];
    vertex C = in[2];

    float det = (B.x - A.x) * (C.y - A.y) - (C.x - A.x) * (B.y - A.y);
    for (int j = 0; j < 3; j++)
    {
        float det2 =  crossProduct(vector(what[j].x - A.x, what[j].y - A.y), 
                                   vector(C.x - A.x, C.y - A.y));

        float det1 =  crossProduct(vector(B.x - A.x, B.y - A.y), 
                                   vector(what[j].x - A.x, what[j].y - A.y));
        float det3 = det - det1 - det2;
        
        if (!((det2 >= 0 && det1 >= 0 && det3 >= 0) || (det2 < 0 && det1 < 0 && det3 < 0)))
            continue;

        bool is = false;
        for (auto x : poligon)
        {
            if (x.x == what[j].x && x.y == what[j].y)
            {
                is = true;
                break;
            }
        }
        if (!is)
            poligon.push_back(what[j]);
    }

}

void Internal(const std::vector<vertex> & t1, const std::vector<vertex> & t2, std::vector<vertex> & OUT poligon)
{
    allInternalVertex(t1, t2, poligon);
    allInternalVertex(t2, t1, poligon);
}


float crossProduct(vector a1, vector a2)
{
    return a1.x * a2.y - a1.y * a2.x;
}


int main()
{
    std::vector<vertex> t1;
    std::vector<vertex> t2;

    for (int i = 0; i < 3; i++)    
    {
        float x = 0;
        float y = 0;
        std::cin >> x >> y;
        t1.push_back(vertex(x, y));
    }
    
    for (int i = 0; i < 3; i++)
    {
        float x = 0;
        float y = 0;
        std::cin >> x >> y;
        t2.push_back(vertex(x, y));
    }

    std::cout << square(t1, t2) << '\n';
}