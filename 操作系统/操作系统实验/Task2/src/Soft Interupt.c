#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
int wait_flag;

void stop()
{
	printf("\n Signal Recieved\n");
	wait_flag = 0;
}

int main()
{
	int pid1, pid2;
	signal(SIGINT, stop);
	while ((pid1 = fork()) == -1);
	if (pid1 > 0)
	{
		while ((pid2 = fork()) == -1);
		if (pid2 > 0)
		{
			wait_flag = 1;
			// sleep(10);
			kill(pid1, 17);
			int kpid1 = wait(0);
			int kpid2 = wait(0);
			printf("\n Child processes have been terminated! \n");
			exit(0);
		}
		else
		{
			printf("\nChild 2,my pid is:%d\n", getpid());
			wait_flag = 1;
			signal(17, stop);
			while (1)
			{
				if (wait_flag == 0)
				{
					printf("\n Child 2 is killed\n");
					exit(0);
				}
			}
		}
	}
	else
	{
		printf("\nChild 1,my pid is:%d\n", getpid());
		wait_flag = 1;
		signal(17, stop);
		while (1)
		{
			if (wait_flag == 0)
			{
				printf("\n Child 1 is killed\n");
				exit(0);
			}
		}
	}
}
