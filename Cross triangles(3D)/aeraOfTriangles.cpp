#include <iostream>

#include "classes.h"

int main()
{
    Triangle2D t1;
    Triangle2D t2;

    std::cin >> t1 >> t2;

    Poligon common = t1.commonPoligon(t2);

    std::cout << common.solveSquare() << '\n';
}