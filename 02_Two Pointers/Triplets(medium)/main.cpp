#include <iostream>
#include <cstdlib>

int compare(const void * x1, const void * x2)
{  
  return ( *(int*)x1 - *(int*)x2 );            
}

int main()
{
    int array[9] = {1, -1, 2, 0, -2, 4, -2, -2, 4};
    int arrayLen = 9;

    // простейший hash с оговоркой, что макс сумма 3-х элементов массива меньше 11 
    int hash[11];
    for (int i = 0; i < 11; i++)
    {
        hash[i] = 0;
    }

    qsort(array, arrayLen, sizeof(int), compare);

    

    for (int i = 0; i < arrayLen - 1; i++)
    {
        int * left =  array + i;
        int * right = array + arrayLen - 1;

        while (left < right)
        {
            int sum = *left + *right + array[i];
            int absSum = abs(*left) + abs(*right) + abs(array[i]);

            if (sum == 0)
            {
                if (!hash[absSum])
                    std::cout << *left << ' ' << *right << ' ' << array[i] << '\n';
                left++;
                right--;

                hash[absSum] = 1;
            }
            
            if (sum < 0)
            {
                left++;
            }

            if (sum > 0)
            {
                right--;
            } 
        }
    }

    return 0;
}