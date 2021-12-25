#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int i = 0;
int return_;

int main(int argc, char **argv)
{
    pid_t pid, pid1;
    pid = fork();
    if (pid < 0)
    {
        printf("Fork failed, exiting...");
        return -1;
    }
    else if (pid == 0)
    {
        // return_ = system("echo hello");
    }
    else
    {
        pid1 = getpid();
        return_ = execl("/bin/echo", "echo", "Hello", NULL, (char *)0);

        printf("parent：pid = %d", pid);
        printf("parent：pid1 = %d", pid1);
        wait(NULL);
    }

    return 0;
}