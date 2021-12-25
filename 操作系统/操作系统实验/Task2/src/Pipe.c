#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/wait.h>

int pid1, pid2;
# define LENGTh 20
int main(){
    int fd[2];
    char OutPipe[40], InPipe[400];
    char c1 = '1', c2 = '2';
    pipe(fd);
    while((pid1 = fork()) == -1);
    if(pid1 == 0){
        lockf(fd[1], 1, 0);
        sprintf(OutPipe,"1");
        for(int i = 0; i < 200; i++){
            write(fd[1], OutPipe, 1);
        }
        sleep(1);
        lockf(fd[1], 0, 0);
        exit(0);

    }

    else{
        while((pid2=fork()) == -1);
        if(pid2 == 0){
            lockf(fd[1], 1, 0);
            sprintf(OutPipe,"2");
            for(int i = 0; i < 200; i++){
                
                write(fd[1], OutPipe, 1);
            }
            lockf(fd[1], 0, 0);
            sleep(1);
            exit(0);
        }
        else{
            wait(0);
            wait(0);
            read(fd[0], InPipe, 400);
            InPipe[400] = '\0';
            printf(InPipe);
            exit(0);
        }
    }
    return 0;
} 