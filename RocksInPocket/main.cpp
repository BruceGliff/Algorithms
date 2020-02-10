#include <iostream>
#include <fstream>
#include <vector>


struct myData
{
    std::pair<int, int> rock;
    bool isIn = false;
    myData(int x, int y) { rock.first = x; rock.second = y; }
};

void rec(std::vector<myData *> & vec, int x);
int max = 0;
int maxWeight = 0;
int curr = 0;
int currentWeight = 0;
int maxCost = 0;
int main()
{
    std::ifstream file{"input"};

    std::vector<myData *> vec;

    int weight, cost;
    
    int x, y;
    file >> maxWeight;
    while (file >> x >> y)
    {
        ++max;
        vec.push_back(new myData(x,y));
    }

    rec(vec, 0);
    std::cout << maxCost;

}

void rec(std::vector<myData *> & vec, int next)
{
    if(next == max)
    {
        int cost = 0;
        int weight = 0;
        for (auto const & x : vec)
        {
            cost += x->rock.second * x->isIn;
            weight += x->rock.first * x->isIn;
        }
        if ( cost > maxCost && weight <= maxWeight)
            maxCost = cost;
        return;
    }

    vec.at(next)->isIn = true;
    rec(vec, next + 1);
    vec.at(next)->isIn = false;
    rec(vec, next + 1);

    return;
}