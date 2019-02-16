#include<stdio.h>

int package(int weight[], int value[], int N, int V)
{
    int** c = new int*[N + 1];
    for (int i = 0; i < N + 1; i++)
    {
        c[i] = new int[V + 1];
    }

    for (int i = 0; i <= N; i++)
        c[i][0] = 0;
    for (int j = 0; j <= V; j++)
	c[N][j] = 0;
    for (int i = N -1; i >= 0; i--)
    {
        for (int j = 1; j<= V; j++)
	{
	    if (j < weight[i])
	        c[i][j] = c[i + 1][j];
	    else
	    {
	        int p = c[i + 1][j];
                int q = c[i + 1][j - weight[i]] + value[i];
		c[i][j] = p > q ? p : q;
	    }
	}
    }

    int ret = c[0][V];
    for (int i = 0; i< N + 1; i++)
    {
        delete[] c[i];
    }
    delete[] c;

    return ret;
}

int main()
{
    int weight[3] = {1 ,2, 3};
    int value[3] = {60, 100, 120};
    int N = 3, V = 5;
    int ret = package(weight, value, N, V);
    printf("the max value is %d\n", ret);

    return 0;
}
