#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    char filename[10];
    while (1)
    {
        //scanf("%s", filename);
        gets(filename);
	printf("%s\n", filename);
    }


    return 0;
}
