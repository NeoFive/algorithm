#include<iostream>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string>
using namespace std;

int main()
{
    char c = 'k';
    cout<<c*c<<endl;
    int fd = open("filename", O_WRONLY|O_CREAT, 0666);
    int i = 32;
    write(fd, &i, sizeof(i));
    close(fd);
    string s = "string";
    cout<<s.length()<<endl;
    return 0;
}
