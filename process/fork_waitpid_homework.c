#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void print_use_tips(char* arg[])
{
	printf("Use:\n");
	printf("\t%s <n> eg: %s 3\n",arg[0],arg[0]);
	printf("\n");
}

int do_exec(const char* cmd,char* const optarr[])
{
	execvp(cmd,optarr);
	perror(strcat(cmd,"error."));
	exit(1);

	return 0;
}

int main(int argc, char* argv[])
{
	int i,n,k;
	pid_t pid;


	if(argc != 2)
	{
		print_use_tips(argv);
		return -1;
	}

	n = atoi(argv[1]);

	for(i=0;i<n;i++)
	{
		pid = fork();
		if(-1 == pid)
		{
			perror("fork error.");
			exit(-1);
		}
		else if(0 == pid)
		{

			k = i%3;
			sleep(k+1);
			if(0 == k)
			{
				printf("I am child pid = %u.\n",getpid());
				char* const opt[] = {"ls","-a","-h","-l",NULL};
				do_exec("ls",opt);
			}
			else if(1 == k)
			{
				printf("I am child pid = %u.\n",getpid());
				char* const opt[] = {"envTest",NULL};
				do_exec("./envTest",opt);
			}
			else if(2 == k)
			{
				printf("I am child pid = %u.\n",getpid());
				char* const opt[] = {"segmentfault",NULL};
				do_exec("./segmentfualt",opt);
			}
			break;
		}
		else
		{
			int status;
			pid_t wpid;
			while((wpid = waitpid(0,&status,WNOHANG)) != -1)
			{
				if(wpid > 0)
				{
					if(WIFEXITED(status))
						printf("child %u quit with code %d.\n",wpid,WEXITSTATUS(status));
					if(WIFSIGNALED(status))
						printf("child %u out with signal code %d.\n",wpid,WTERMSIG(status));
				}
			}


		}


	}



	return 0;
}


