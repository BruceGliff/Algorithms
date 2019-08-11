#include <iostream>

int main()
{
    int array[6] = {-10, -5, 2, 3, 7, 11};

    int arrayLen = 6;
    int * lPoint = array;
    int * rPoint = array + arrayLen - 1;

    int SquadArray[6];

    int Step = 0;
    while (lPoint <= rPoint)
    {
        Step++;
        if (*lPoint * *lPoint > *rPoint * *rPoint)
        {
            SquadArray[arrayLen - Step] = *lPoint * *lPoint;
            lPoint++;
        }
        else
        {
            SquadArray[arrayLen - Step] = *rPoint * *rPoint;
            rPoint--;
        }
       
    }

    for (int i = 0; i < arrayLen; i++)
    {
        std::cout << SquadArray[i] << '\n';
    }

    return 0;
}