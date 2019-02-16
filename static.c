#include<stdio.h>

int fun()
{
    static int a = 3;
    a += 2;
    return a;
}

int main()
{
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", fun());
    }
    printf("\n");
    return 0;
}
