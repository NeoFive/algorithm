#include<stdio.h>
#include<assert.h>

void exchange(int * p_first_num, int * p_second_num)
{
    assert(p_first_num != NULL && p_second_num != NULL);
    int temp = *p_first_num;
    *p_first_num = *p_second_num;
    *p_second_num = temp;
}
int partion(int array[], int begin, int end)
{
    int temp = array[end];
    int r = begin -1;
    for (int i = begin; i < end; i++)
    {
        if (array[i] < temp)
	{
	    r++;
	    exchange(&array[r], &array[i]);
	}
    }
    exchange(&array[r + 1], &array[end]);
    return r + 1;
}

int quick_sort(int array[], int begin, int end)
{
    if (begin < end)
    {
        int k = partion(array, begin, end);
        quick_sort(array, begin, k -1);
        quick_sort(array, k + 1, end);
    }
    return 0;
}

#ifdef DEBUG
int main()
{
    int test_array[10] = {1, 2, 3, 10, 9, 8, 6, 7, 4, 5};
    printf("%s\n","The test_array before quick_sort");
    
    for (int i = 0; i < 10; i++) 
    {
        printf("%d ",test_array[i]);
    }
    
   quick_sort(test_array, 0, 9);
    
    printf("\n");
    
    printf("%s\n","The test_array after quick_sort");
    
    for (int i = 0; i < 10; i++) 
    {
        printf("%d ",test_array[i]);
    }
    printf("\n");

    return 0;
}
#endif
