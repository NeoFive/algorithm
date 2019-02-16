#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>

char message[] = "hello world";

void * thread_function(void * arg)
{
    printf("thread_function is running, argument is %s\n", (char *)arg);
    sleep(3);
    strcpy(message, "bye!");
    pthread_exit(reinterpret_cast<void*>(const_cast<char*>("thank you for you cpu time!")));
}

int main()
{
    int res;
    pthread_t a_thread;
    void * thread_result;

    res = pthread_create(&a_thread, NULL, thread_function, (void *)message);

    if (res != 0)
    {
        perror("thread creation failed");
	exit(EXIT_FAILURE);
    }

    printf("waiting for thread to finish...\n");
    res = pthread_join(a_thread, &thread_result);
    if (res != 0)
    {
        perror("pthread failed");
	exit(EXIT_FAILURE);
    }

    printf("thread joined ,it return %s\n", (char*)thread_result);
    printf("message now is %s\n", message);
    while (1)
    {
        printf("loop at here!\n");
	sleep(1);
    }
    exit(EXIT_SUCCESS);


}
