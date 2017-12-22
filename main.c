#include <linux/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/errno.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include "seven/seven.h"
#include "comment.h"
#include "three/threeChapter.h"
#include "four/four.h"
#define BUFF_SIZE 8192

void program_1_3(void);
void program_1_4(void);
void program_1_6(char *);
void program_1_8(void);
void program_8_1(void);
static void sigInit(int);		/*our signal_catching function*/


int glob = 6;
char buf[] = "a write to stdout\n";

int main(int argc,char *argv[])
{
	int var;
	pid_t pid;
	var = 88;
	printf("the dad pid = %d\n",getpid());
	if(write(STDOUT_FILENO,buf,sizeof(buf) -1) != (sizeof(buf)-1))
	{
		err_sys("write error!");
	}
	printf("before fork\n");
	if((pid = fork()) <0)
	{
		err_sys("fork error!");
	}
	else if(pid == 0)
	{
		glob++;
		var ++;
		printf("the pid 2 = %d\n",getpid());
	}
	else
	{
		printf("the pid 3 = %d\n",getpid());
		sleep(2);
	}


	printf("pid = %d,glob= %d,var = %d\n",getpid(),glob,var);
	exit(0);
}

void program_8_1(void)
{

}
void program_1_3(void)
{
	int c;
	while((c = getc(stdin)) != EOF)
	{
		if(putc(c,stdout) == EOF)
		{
			err_sys("output error!");
		}
		if(ferror(stdin)){
			err_sys("input error");
		}
	}
}

void program_1_4(void)
{
	printf("the process ID is %d \n",getpid());
	char buf[MAX_LINE];

	pid_t pid;
	int status;
	printf("%% ");	/* print prompt (printf requires % %to print %)*/
	while( fgets(buf,MAX_LINE,stdin) != NULL)
	{
		buf[strlen(buf) - 1] = 0;	/* replace newline with null*/
	}
	if((pid = fork()) < 0)
	{
		err_sys("fork error1");
	}
	else if(pid ==0) 	/*child*/
	{
		execlp(buf,buf,(char*)0);
		err_ret("couldn't execute: %s",buf);
		exit(127);
	}
	/* parents
	*/
	if((pid = waitpid(pid,&status,0))<0)
	{
		err_sys("waitpid erro!");
	}
	printf("%%");
	exit(0);
}

void program_1_6(char * argv)
{
	fprintf(stderr, "EACCES: %s\n",strerror(EACCES));
	errno = ENOENT;
	perror(argv);
	exit(0);
}

void program_1_8(void)
{
	char buf[MAX_LINE];

	pid_t pid;
	int status;

	if(signal(SIGINT,sigInit) == SIG_ERR)
	{
		err_sys("signal error");
	}


	printf("%% ");	/* print prompt (printf requires % %to print %)*/
	while( fgets(buf,MAX_LINE,stdin) != NULL)
	{
		buf[strlen(buf) - 1] = 0;	/* replace newline with null*/
	}
	if((pid = fork()) < 0)
	{
		err_sys("fork error1");
	}
	else if(pid ==0) 	/*child*/
	{
		execlp(buf,buf,(char*)0);
		err_ret("couldn't execute: %s",buf);
		exit(127);
	}
	/* parents
	*/
	if((pid = waitpid(pid,&status,0))<0)
	{
		err_sys("waitpid erro!");
	}
	printf("%%");
	exit(0);
}

static void sigInit(int signo)
{
	printf("interrupt \n");
}
