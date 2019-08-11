#include <iostream>
#include <limits.h>

int main()
{
    const int arrayLen = 10;

    int * array = new int [arrayLen];

    // GENERATE random array (ordered)
    for (int i = 0; i < arrayLen; i++)
        array[i] = int (array) * (i + int (array)) / 100000; 

    for (int i = 0; i < arrayLen; i++)
        std::cout << array[i] << ' ';

    const int k = 5;

    int maxSum = INT32_MIN;

    int Sum  = 0;
    
    for (int i = 0; i <= arrayLen - k; i++)
    {
        if (i)
            Sum += array[i + k - 1] - array[i - 1];
        else
        {
            for (int j = 0; j < k; j++)
                Sum += array[j];
        }
        if (Sum > maxSum)
            maxSum = Sum;
        
    }

    std::cout << '\n' << maxSum;

    delete array;

    return 0;
}