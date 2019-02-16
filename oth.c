#include<stdio.h>

struct Test
{
    unsigned short int a:5;
    unsigned short int b:5;
    unsigned short int c:6;
};
struct a
{
    char f1:3;
    char f2:4;
    char f3:5;
};
int main()
{
    #ifdef DEBUG
    struct Test test;
    test.a = 16;
    test.b = 4;
    test.c = 0;
    int i = *(short*)&test;
    printf("%d\n", i);
    printf("sizeof struct a = %lu\n", sizeof(struct a));
    int a, b, c, d;
    a = 5;
    b = 5;
    c = (a++) + (a++) + (a++);
    d = (++b) + (++b) + (++b);
    printf("a = %d, b = %d, c = %d, d = %d\n", a, b, c, d);

    #endif
    unsigned int a = 0x1FFFFFF7;
    unsigned char b = a;
    char c = a;
    char * p = (char *)&a;
//    printf("%x, %x, %x", b, c, *p);

    return 0;
}
