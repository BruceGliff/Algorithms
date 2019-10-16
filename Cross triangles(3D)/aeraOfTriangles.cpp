#include <iostream>

#include "classes.h"
#include "sphere.h"
#include "cstring"

int main()
{
    std::vector<Optimization::Sphere*> spheres_array;
    

    int n = 0;
    std::cin >> n;

    bool* triangles = new bool[n];
    memset(triangles, 0, n);

    for(int i = 0; i < n; i++)
    {
        Triangle3D t;
        std::cin >> t;

        spheres_array.push_back(new Optimization::Sphere(t, i));
    }        

    Optimization::CreateBox(Optimization::Box(Vertex3D(0,0,0), 100.f), spheres_array, spheres_array.size(), 0, triangles);

    for (int i = 0; i < n; i++)
        if (triangles[i])
            std::cout << i << '\n';

    delete[] triangles;

    std::for_each(spheres_array.begin(), spheres_array.end(), 
    [](Optimization::Sphere * sp)
    {
        delete sp;
    });

    return 0;
}