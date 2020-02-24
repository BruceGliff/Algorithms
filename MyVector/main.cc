#include "MyVector.h"

#include <iostream>

int main()
{
    My::Vector<int> ASD(5);
    ASD.push_back(5);
    My::Vector<int> tmp{64};
    tmp = ASD;
    int l = tmp.top();
    tmp[0] = 0;
    l = tmp.top();



    My::Vector<int> a{1};
    a.push_back(6);
    a.resize(2);
    std::cout << l << std::endl;
    l = a[0];
    std::cout << l << std::endl;
    a.push_back(7);
    l = a.top();
    l = a[0];l = a.top();

    a.push_back(10);
    l = a.top();
    std::cout << a.size() << ' ' << a.capacity() << std::endl;

    a.resize(1);
    l = a.top();
    std::cout << a.size() << ' ' << a.capacity() << ' ' << l << std::endl;
    a.push_back(10);
    l = a.top();
    a.resize(100);
    std::cout << a.size() << ' ' << a.capacity() << ' ' << l << std::endl;
}