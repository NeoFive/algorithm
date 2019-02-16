#include<iostream>

auto f(int i)
{
    if (i > 0)
        return -1;
    else
	return 1;
}

int main()
{
    int i = 5, j = -5;
    int ret1 = f(i);
    int ret2 = f(j);
    printf("ret1 = %d, ret2 = %d\n", ret1, ret2);

    return 0;
}
