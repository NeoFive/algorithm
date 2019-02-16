#include<stdio.h>

int exchange(int * p_first, int * p_second)
{
    int temp = *p_first;
    *p_first = *p_second;
    *p_second = temp;
    return 0;
}
int adjust_down(int array[], int k, int len)
{
    array[0] = array[k];
    int i;
    for (i = 2*k; i <= len; i = 2*k)
    {
        if (i < len && array[i + 1] > array[i])//必须确保i + 1 是存在的
	{
	    i = i + 1;
	}
	if (array[i] > array[0])
	{
	    array[k] = array[i];
	    k = i;
	}
	else
	    break;
    
    }
    array[k] = array[0];
    return 0;
}
int build_max_heap(int array[], int len)
{
    int i;
    for (i = len/2; i > 0; i--)
    {
        adjust_down(array, i, len);
    } 
    return 0;
}
int heap_sort(int array[], int len)
{
    build_max_heap(array, len);
    exchange(&array[1], &array[len]);
    int i;
    for (i = len - 1; i > 0; i--)
    {
        adjust_down(array, 1,  i);
	exchange(&array[1], &array[i]);
    }
    return 0;
}

#ifdef DEBUG
int main()
{
    int test_array[9] = {0,  38, 49, 10, 13, 57, 76, 89, 90};//test_array[0]不用
    int i;
    for (i = 1; i < 8; i++)
    {
        printf("%d ", test_array[i]);
    }
    printf("\n");
    heap_sort(test_array, 8);

    for (i = 1; i < 8; i++)
    {
        printf("%d ", test_array[i]);
    }
    printf("\n");

    return 0;
}

#endif
