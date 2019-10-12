#include <iostream>

#include "classes.h"

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

    //std::cout << triangles[0].hasInternal(triangles[1]);

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
        {   
            if(triangles[i].isAcross(triangles[j]))
                std::cout << i << ' ' << j << '\n';
        }

    return 0;
}