#include "sphere.h"

namespace Optimization
{

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


void OSphere::SetSphere()
{
    Vertex3D A = (*triangle)[0];
    Vertex3D B = (*triangle)[1];
    Vertex3D C = (*triangle)[2];

    center.x = (A.x + B.x + C.x) / 3;
    center.y = (A.y + B.y + C.y) / 3;
    center.z = (A.z + B.z + C.z) / 3;

    radius = 0;
    for(int i = 0; i < 3; i++)
    {
        float f = Vector3D(((*triangle)[i]), center).length();
        if (f > radius)
            radius = f;
    }
}


bool OSphere::SphereIntersectBox(Box box) const
{ 
    
    return (Vector3D(center, box.center()).length() - radius) <= (box.d * sqrtf(3) / 2);
}



void CreateBox(const Box & box, std::vector<OSphere*> & array, int last_size, int delta_depth)
{
    if (last_size == array.size())
        delta_depth++;
    else 
        delta_depth = 0;

    if (array.size() < 2)
        return;
    
    if (array.size() == 2)
    {
       array[0]->CheckTriangles(*array[1]);
       return;
    }

    if (delta_depth == 3)
    {
        for(int i = 0; i < array.size() - 1; i++)
            for (int j = i + 1; j < array.size(); j++)
                array[i]->CheckTriangles(*array[j]);
        return;
    }       

    std::array<std::vector<OSphere*>, 8> mas;
    for (int i = 0; i < array.size(); i++)
    {
        for (int iter = 0; iter < 8; iter++)
            if (array[i]->SphereIntersectBox(Box(box, iter)))
                mas[iter].push_back(array[i]);
    }
    for (int i = 0; i < 8; i++)
        Optimization::CreateBox(Box(box, i), mas[i], array.size(), delta_depth);
}

}