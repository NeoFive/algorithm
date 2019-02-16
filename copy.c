#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#define MAX_BLOCK_LEN 1024

int main(int argc, char * argv[])
{
    if (argc != 3)
    {    
        printf("argment error\n");
        exit(EXIT_FAILURE);
    }   
    printf("%s%s\n", "The source file is : ", argv[1]);
    printf("%s%s\n", "The object file is : ", argv[2]);
    
    char block[MAX_BLOCK_LEN];
    int in, out;
    in = open(argv[1], O_RDONLY);
    if (in == -1)
    {
        perror("open file failed!");
	exit(EXIT_FAILURE);
    }

    out = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IROTH);
    if (out == -1)
    {
        perror("open file failed!");
	exit(EXIT_FAILURE);
    }

    int nread;
    while ( (nread = read(in, block, MAX_BLOCK_LEN)) > 0)
    {
        write(out, block, nread);
    }
    exit(EXIT_SUCCESS);
}
