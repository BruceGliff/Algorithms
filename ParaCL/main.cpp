#include <iostream>
#include "Node.hpp"
#include "Parser.hpp"


int main()
{
    Parser p{"main.pcl"};
    p.exec();   
}