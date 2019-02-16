#include<stdio.h>

int max_sub_array(int A[], int N, int* plow, int* phigh)
{
    int* c = new int[N];
    c[N - 1] = A[N - 1];
    int low, high;
    low = high = N - 1;
    for (int i = N -2; i >= 0; i--)
    {
        if (A[i] < 0)
	    c[i] = c[i + 1];
	else
	{
	    if (low == i + 1)
            {
	        c[i] = c[i + 1] + A[i];
		low = i;
	    }
	    else
	    {
	        int sum = 0;
		int max_temp_sum = 0;
		int max_index;
		for (int j = i; j < low; j++)
		{
		    sum+=A[j];
		    if (sum > max_temp_sum)
		    {
		        max_temp_sum = sum;
			max_index = j;
		    }
		    else if (sum < 0)
		        break;
		}
		if (max_temp_sum > c[i + 1])
		{
		    c[i] = max_temp_sum;
		    low = i;
		    high = max_index;
		}
		else
		    c[i] = c[i + 1];
	    }
	}
    }
    *plow = low;
    *phigh = high;
    int ret = c[0];
    delete[] c;
    return ret;
}
int max_sub_array_red(int A[], int N, int* plow, int* phigh)
{
    int max_sum = 0;
    int sum = 0;
    int low = 0, high = 0;
    for (int i = 0; i < N; i++)
    {
        sum += A[i];
	if (sum > max_sum)
	{
	    max_sum = sum;
	    high = i;
	}
	else if (sum < 0)
	{
	    sum = 0;
	    if (i < N -2)
	    {
	      low = high = i + 1;
	    }
	}
    }
    *plow = low;
    *phigh = high;
    return max_sum;
}
int main()
{
    int A[8] = {-2, 5, 3,9,  6, 4, -8, 6};
    int low, high;
    int ret = max_sub_array_red(A, 8, &low, &high);
    printf("The max sum of sub array is %d\n", ret);
    for (int i = low; i <= high; i++)
        printf("%d ", A[i]);
    printf("\n");
    return 0;
}
