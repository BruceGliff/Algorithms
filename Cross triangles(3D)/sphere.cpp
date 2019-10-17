#include "sphere.h"

namespace Optimization{

Box::Box(const Box & box, int iter)
{
    int k = (iter&4) >> 2;
    int j = (iter&2) >> 1;
    int i = iter&1;

    
    zero = Vertex3D(box.zero.x + float(i) * (box.zero.x + box.d) / 2,
                 box.zero.y + float(j) * (box.zero.y + box.d) / 2,
                 box.zero.z + float(k) * (box.zero.z + box.d) / 2);
    d = box.d / 2;
}


void Sphere::SetSphere()
{
    Vertex3D A = triangle[0];
    Vertex3D B = triangle[1];
    Vertex3D C = triangle[2];

    center.x = (A.x + B.x + C.x) / 3;
    center.y = (A.y + B.y + C.y) / 3;
    center.z = (A.z + B.z + C.z) / 3;

    radius = 0;
    for(int i = 0; i < 3; i++)
    {
        float f = Vector3D((triangle[i]), center).length();
        if (f > radius)
            radius = f;
    }
}


void CreateBox(const Box & box, std::vector<Sphere*> & array, int last_size, int delta_depth, bool* status)
{
    if (array.size() < 2)
        return;
    if (array.size() == 2)
    {
       array[0]->CheckTriangles(array[1], status);
       return;
    }

    if (last_size == array.size())
        delta_depth++;
    else 
        delta_depth = 0;

    if (delta_depth == 8)
    {
        for(int i = 0; i < array.size() - 1; i++)
            for (int j = i + 1; j < array.size(); j++)
                array[i]->CheckTriangles(array[j], status);
        return;
    }       

    std::array<std::vector<Sphere*>, 8> mas;
    for (auto i = array.begin(); i < array.end(); i++)
    {
        for (int iter = 0; iter < 8; iter++)
        {   
            Box New = Box(box, iter);

            if (!((*i)->insideBox(New)))
                continue;

            if ((*i)->SphereIntersectBox(New))
            {
                int del2 = 0;
                for (auto j = i; j < array.end(); j++)
                {
                    if (i == j) continue;
                    (*i)->CheckTriangles((*j), status);
                }

                delete (*i);
                array.erase(i);
                i--;
                break;
            }    
                
            mas[iter].push_back(*i);
        }
    }
    for (int i = 0; i < 8; i++)
        Optimization::CreateBox(Box(box, i), mas[i], array.size(), delta_depth, status);
}

}