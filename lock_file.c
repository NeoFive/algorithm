#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>//文件锁头文件
#include<errno.h>

const char * lock_file = "/tmp/lock_file.test";

int main()
{
    int fd;
    int num = 10;
    while (num--)
    {
        fd = open(lock_file, O_CREAT | O_RDWR | O_EXCL, 0444);
	if (fd == -1)
	{
	    printf("%d -lock already present\n", getpid());
	    sleep(1);
	}
	else
	{
	    printf("%d -I have exclusive access\n", getpid());
	    sleep(1);
	    (void)close(fd);
	    (void)unlink(lock_file);
	    sleep(2);
	}
    }
    exit(EXIT_SUCCESS);
}
