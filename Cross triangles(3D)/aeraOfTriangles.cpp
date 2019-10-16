#include <iostream>

#include "classes.h"
#include "sphere.h"

int main()
{
    std::vector<Triangle3D> triangles;

    int n = 0;
    std::cin >> n;

    for(int i = 0; i < n; i++)
    {
        Triangle3D t;
        std::cin >> t;

        triangles.push_back(t);
    }

    int ind = 0;
    std::vector<Optimization::OSphere> spheres;
    std::vector<Optimization::OSphere*> spheres_array;

    for (std::vector<Triangle3D>::iterator tr = triangles.begin(); tr < triangles.end(); tr++, ind++)
        spheres.push_back(Optimization::OSphere(tr, ind));

    for (int i = 0; i < spheres.size(); i++)
        spheres_array.push_back(&spheres[i]);

    Optimization::CreateBox(Optimization::Box(Vertex3D(0,0,0), 100.f), spheres_array, spheres.size(), 0);

    return 0;
}