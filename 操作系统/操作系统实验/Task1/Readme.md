# Experiment1
## Basic:
##### Output1:
    parent：pid = 21943
    child：pid = 0
    parent：pid1 = 21938
    child：pid1 = 21943

##### Output2:
    parent：pid = 22264
    parent：pid1 = 22259
    child：pid = 0
    child：pid1 = 22264
##### Illustration
>The diffrences between are caused by context switching of the operating system.

## Global varaible:
##### Situation1:
    else if (pid == 0)  # child
    {
        wait(1);
        printf("child i： = %d\n", i);

    }
    else  # parrent
    {
        wait(0.5);
        i ++;
        printf("parent i： = %d\n", i);
        wait(NULL);
    }

##### Output1:
    child i： = 0
    parent i： = 1

##### Situation2:
    else if (pid == 0)  # child
    {
        wait(0.5);
        i++;
        printf("child i： = %d\n", i);
    }
    else  # parrent
    {
        wait(1);
        printf("parent i： = %d\n", i);
        wait(NULL);
    }
##### Output2:
    child i： = 1
    parent i： = 0

##### Illustration
>When executing fork(), the child program will make a copy on both codes and varialbes of the parent. Thus the operation on i is seperatble.


## Pthread:
    ##### Codes:
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
        printf("global = %d\n",g);
        return 0;
    }
##### Output:
    Thread number 1.
    Thread number 2.
    Thread number 3.
    global = 7
##### Illustration
>Threads shared the global varibale and their operations affect the parent program.