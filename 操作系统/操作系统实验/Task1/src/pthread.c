#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

static g=10;

void *thread(void *arg)
{
    printf("Thread number %d.\n", *(int *)arg);
    g--;
    return arg;
}
int main(int argc, char *argv[])
{
    pthread_t th[3];
    int args[3] = {1, 2, 3};
    for (int i = 0; i < 3; i++)
    {
        if (pthread_create(&th, NULL, thread, &args[i]))
        {
            printf("Error occured!");
        }
    }

    // pthread_exit()

    printf("global = %d",g);
    return 0;
}