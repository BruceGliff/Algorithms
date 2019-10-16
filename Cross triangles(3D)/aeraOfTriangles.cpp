#include <iostream>

#include "classes.h"
#include "sphere.h"

int main()
{
    std::vector<Optimization::OSphere> spheres;
    std::vector<Optimization::OSphere*> spheres_array;

    int n = 0;
    std::cin >> n;

    for(int i = 0; i < n; i++)
    {
        Triangle3D t;
        std::cin >> t;

        spheres.push_back(Optimization::OSphere(t, i));
        spheres_array.push_back(&(spheres[i]));
    }        

    std::cout << spheres_array[0]->index << '\n';
    Optimization::CreateBox(Optimization::Box(Vertex3D(0,0,0), 100.f), spheres_array, spheres.size(), 0);

    return 0;
}