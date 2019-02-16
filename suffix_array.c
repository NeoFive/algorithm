#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXCHAR 5000//最长处理5000个字符
char c[MAXCHAR], *a[MAXCHAR];

//应用快速排序qsort的比较函数
int pstrcmp(const void * p1, const void * p2)
{
    return strcmp(*(char**)p1, *(char**)p2);
}
int comlen(char * p, char * q)
{
    int i = 0;
    while (*p && (*p++ == *q++)) i++;
    return i;
}
//求字符串中的最长重复子串
int main()
{
    char ch;
    int n = 0;//字符串长度
    printf("Please input your string : \n");
    while ( (ch = getchar()) != '\n')
    {
        a[n] = &c[n];//边输入边创建
	c[n++] = ch;
    }
    c[n] = '\0';
    qsort(a, n, sizeof(char*), pstrcmp);
    int i, temp, maxlen = 0, maxi = 0;
    for (i = 0; i < n - 1; i++)
    {
        temp = comlen(a[i], a[i + 1]);
	if (temp > maxlen)
	{
	    maxlen = temp;
	    maxi = i;
	}
    }
    printf("%.*s\n", maxlen, a[maxi]);

    return 0;
}
