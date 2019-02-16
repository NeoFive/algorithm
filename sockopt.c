#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main()
{
    int fd;
    int type;
    int len = sizeof(type);
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    getsockopt(fd, SOL_SOCKET, SO_TYPE, &type, &len);
    printf("%u:%u:%d\n", SOCK_DGRAM, type, len);
    
    if (type & SOCK_DGRAM)
    {
        printf("sock_dgram\n");
    }
    if (type & SOCK_STREAM)
    {
        printf("sock_stream\n");
    }

    
    


    return 0;
}
