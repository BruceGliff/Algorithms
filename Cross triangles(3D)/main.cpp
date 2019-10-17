#include <iostream>
#include <cstring>
#include <algorithm>

#include "triangle.h"
#include "sphere.h"

int main()
{
    std::vector<Optimization::Sphere*> spheres_array;
    
    int n = 0;
    std::cin >> n;

    bool* out_result = new bool[n];
    memset(out_result, 0, n);

    for(int i = 0; i < n; i++)
    {
        Triangle3D t;
        std::cin >> t;

        spheres_array.push_back(new Optimization::Sphere(t, i));
    }        

    Optimization::CreateBox(Optimization::Box(Vertex3D(0,0,0), 100.f), spheres_array, spheres_array.size(), 0, out_result);

    for (int i = 0; i < n; i++)
        if (out_result[i])
            std::cout << i << '\n';

    delete[] out_result;

    std::for_each(spheres_array.begin(), spheres_array.end(), 
    [](Optimization::Sphere * sp)
    {
        delete sp;
    });

    return 0;
}