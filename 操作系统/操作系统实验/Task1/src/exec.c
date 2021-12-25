#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>


int main(int argc, char ** argv){
    pid_t pid, pid1;
    pid = fork();
    if ( pid < 0){
        printf("Fork failed, exiting...");
        return -1;
    }
    else if (pid == 0) {
        pid1 = getpid();
        printf("child：pid = %d", pid);
        printf("child：pid1 = %d", pid1);
    }
    else {
        pid1 = getpid();
        printf("parent：pid = %d", pid);
        printf("parent：pid1 = %d", pid1);
        wait(NULL);
    }

    return 0;
}