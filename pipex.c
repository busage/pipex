#include <sys/types.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void)
{
	pid_t fd[2] ,pid1 ,pid2;
	if (pipe(fd) == -1)
	{
		return 1;
	}

	pid1 = fork();
	if (pid1 < 0)
	{
		return 1;
	}
	if (pid1 == 0)
	{
		dup2(fd[1],STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("ping","ping","-c","5","google.com",NULL);
	}

	pid2 = fork();

	if (pid2 < 0)
	{
		return 1;
	}
	if (pid2 == 0)
	{
		dup2(fd[0],STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "rtt", NULL);
	}
	
	close(fd[0]);
	close(fd[1]);

	waitpid(pid1,NULL,0);
	waitpid(pid2,NULL,0);


	return 0;
}
