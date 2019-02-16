#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#define WORK_SIZE 1024

char work_area[WORK_SIZE];
sem_t bin_sem;
void * pthread_result;
void * pthread_function(void * arg)
{
    sem_wait(&bin_sem);
    while (strncmp("end", work_area, 3) != 0)
    {
        printf("you enter %ld characters\n", strlen(work_area) - 1);
	sem_wait(&bin_sem);
    }
    pthread_exit(NULL);
}

int main()
{
    int res;
    pthread_t a_thread;
    
    res = sem_init(&bin_sem, 0, 0);
    if (res != 0)
    {
        perror("semaphore init failure");
	exit(EXIT_FAILURE);
    }

    res = pthread_create(&a_thread, NULL, pthread_function, NULL);
    if (res != 0)
    {
        perror("pthread create failure");
	exit(EXIT_FAILURE);
    }

    printf("please enter some text:\n");

    while (strncmp("end", work_area, 3) != 0)
    {
        fgets(work_area, WORK_SIZE, stdin);
	sem_post(&bin_sem);
    }

    res = pthread_join(a_thread, &pthread_result);
    if (res != 0)
    {
        perror("pthread_join failure");
	exit(EXIT_FAILURE);
    }

    printf("thread finished");
    sem_destroy(&bin_sem);
    exit(EXIT_FAILURE);
}
