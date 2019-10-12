#include <iostream>

#include "classes.h"

#define OUT

void Internal(const std::vector<Vertex> & t1, const std::vector<Vertex> & t2, OUT Poligon & poligon);
float square(const std::vector<Vertex> & t1, const std::vector<Vertex> & t2) // arrays of vectors
{
    Poligon poligon;
    int out_count = 0;

    // поиск всех точек пересечения 
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            Vertex cross(0, 0); // outer vertex
            if (Line(t1[i], t1[(i + 1) % 3]).isAcross(Line(t2[j], t2[(j + 1) % 3]), cross))
            {
                out_count++;
                poligon.push_back(cross);
            }
        }
    // Добавление всех точек, которые лежат в другом треугольнике

    Internal(t1, t2, poligon);

    std::cout << poligon.vert_array.size() << '\n';
 
    return poligon.solveSquare();
}

void allInternalVertex(const std::vector<Vertex> & in, const std::vector<Vertex> & what, Poligon & OUT poligon)
{
    Vertex A = in[0];
    Vertex B = in[1];
    Vertex C = in[2];

    float det = Vector(A, B) * Vector(A, C);

    for (int j = 0; j < 3; j++)
    {
        float det2 =  Vector(A, what[j]) * Vector(A, C);
        float det1 = Vector(A, B) * Vector(A, what[j]);

        float det3 = det - det1 - det2;
        
        if (!((det2 > 0 && det1 > 0 && det3 > 0) || (det2 < 0 && det1 < 0 && det3 < 0)))
            continue;


        poligon.push_back(what[j]);
    }

}

void Internal(const std::vector<Vertex> & t1, const std::vector<Vertex> & t2, OUT Poligon & poligon)
{
    allInternalVertex(t1, t2, poligon);
    allInternalVertex(t2, t1, poligon);
}

int main()
{
    std::vector<Vertex> t1;
    std::vector<Vertex> t2;

    for (int i = 0; i < 3; i++)    
    {
        float x = 0;
        float y = 0;
        std::cin >> x >> y;
        t1.push_back(Vertex(x, y));
    }
    
    for (int i = 0; i < 3; i++)
    {
        float x = 0;
        float y = 0;
        std::cin >> x >> y;
        t2.push_back(Vertex(x, y));
    }
    std::cout << square(t1, t2) << '\n';
}