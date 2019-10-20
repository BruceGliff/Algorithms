#include <iostream>
#include <cstring>
#include <algorithm>
#include <array>

#include "triangle.h"
#include "sphere.h"

int main()
{
    std::vector<Optimization::Sphere<float>*> spheres_array;
    
    int n = 0;
    std::cin >> n;

    std::set<int> out_result;

    for(int i = 0; i < n; i++)
    {
        Triangle3D<float> t;
        std::cin >> t;

        spheres_array.push_back(new Optimization::Sphere<float>(t, i));
    }        

    Optimization::CreateBox(Optimization::Box<float>(Vertex3D<float>(0,0,0), 100.f), spheres_array, spheres_array.size(), 0, out_result);

    for (auto const &i : out_result)
        std::cout << i << '\n';

    for (auto sp : spheres_array)
        delete sp;

    return 0;
}