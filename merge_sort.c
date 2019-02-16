#include<stdio.h>
#include<stdlib.h>
int merge(int array[], int low, int mid, int high)
{
    int len = high - low + 1;
    int * temp = (int *)malloc(len * sizeof(int));
    int i;
    for (i = 0; i < len; i++)
    {
        temp[i] = array[low + i];
    }
    int j, k;
    for (i = 0, j = mid - low + 1, k = low; i < mid - low + 1 && j < len; k++)
    {
        if (temp[i] > temp[j])
	    array[k] = temp[j++];
	else
	    array[k] = temp[i++];
    }
    while (i < mid -low +1) 
	    array[k++] = temp[i++];
    while (j < len)
	    array[k++] = temp[j++];
    free(temp);
    return 0;
}

int merge_sort(int array[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
	merge_sort(array, low, mid);
	merge_sort(array, mid + 1, high);
        merge(array, low, mid, high);
    }
    return 0;

}
#ifdef DEBUG
int main()
{
    int test_array[10] = {9, 3, 2, 8, 5, 0, 4, 6, 7, 1};
    int i;
    for (i = 0; i < 10; i++)
    {
        printf("%d ", test_array[i]);
    }
    printf("\n");
    merge_sort(test_array, 3, 8);
    for (i = 0; i < 10; i++)
    {
        printf("%d ", test_array[i]);
    }
    printf("\n");

    return 0;
}
#endif
