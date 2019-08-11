#include <iostream>
#define EXIT\
        {\
        if (CurrentLen > maxLen)\
            {maxLen = CurrentLen - 1; p = point;}\
        for (int h = 0; h < maxLen; h++)\
            std::cout << *(p + h);\
        delete String;\
        return 0;}

int main()
{
    const int StringLen = 10;
    char * String = "aaaafgyyg";

    const int k = 5;

    int maxLen = 0;
    char * point = String;
    char * p;

    int CurrentLen = k - 1;
    int Hash[26];


    while(true)
    {
        for (int i = 0; i < 26; i++)
            Hash[i] = 0;

        CurrentLen = k - 1;
        // создать хэш-массив
        // от указателя проверить то что в окне
        // увеличивать окно пока не станет >k
        // запмнить длину сдвинуть указатель
        // чек когда указатель + длина = null

        int diffInWindow = 0;
        while (diffInWindow <= k)
        {
            CurrentLen++;
            diffInWindow = 0;
            for (int i = 0; i < CurrentLen; i++)
            {
                if (*(point + i) == '\0')
                    EXIT

                Hash[*(point + i) - 'a'] = 1;
            }

            for (int i = 0; i < 26; i++)
                diffInWindow += Hash[i];
        }

        if (CurrentLen > maxLen)
        {
            maxLen = CurrentLen - 1;
            p = point;
        }

        point++;
    }


    delete String;
    return 0;
}