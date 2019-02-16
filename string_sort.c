#include<stdio.h>
#include<string.h>
#define MAX_STRLEN 64
int main()
{
    int n;
    while (scanf("%d", &n))
    {
        char ** str = new char*[n];
	int i;
	char ch = getchar();
	for (i = 0; i < n; i++)
	{
	    str[i] = new char[MAX_STRLEN + 1];
	    fgets(str[i], MAX_STRLEN, stdin);
	}

	for (i = 0; i < n - 1; i++)
	{
	    int k = i, j;
	    for (j = i + 1; j < n; j++)
	    {
	        if (strcmp(str[j], str[k]) < 0)
		{
	            k = j;
		}
	    }
	    if (k != i)
	    {
	        char temp[MAX_STRLEN + 1];
	        strcpy(temp, str[i]);
	        strcpy(str[i], str[k]);
	        strcpy(str[k], temp);
	    }
	}

	for (i = 0; i < n; i++)
	{
	    fputs(str[i], stdout);
	}

	for (i = 0; i < n; i++)
	{
	    delete str[i];
	}
	delete[] str;
    }


    return 0;
}
