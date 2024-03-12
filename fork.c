#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	int id,wt;
	id = fork();
	if(id == 0)
	{
		printf("hi Iam Child process my process id is %d\n",getpid());
		printf("hi Iam parent process my process id is %d\n",getppid());
		execl("./fib","fib","argv[1]",NULL);
		exit(20);
	}
	else if (id > 0){
		wait(&wt);
		printf("hi Iam Child process my process id is %d\n",getpid());
		printf("hi Iam parent process my process id is %d\n",getppid());
	}
	if (WIFEXITED(wt)){
		printf("the child is terminated normally and its exit status is %d",WEXITSTATUS(wt));
	}
	else if (WIFSIGNALED(wt)){
		printf("the child is terminated abnormally and it is killed by signal %d",WTERMSIG(wt));
	}
}
		
