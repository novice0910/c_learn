/*
 * four.c
 *
 *  Created on: 2017-12-15
 *      Author: novice
 */


#include "four.h"
#include <sys/stat.h>
#include <fcntl.h>
#include "../comment.h"


void my_stat(char * pathName)
{
	struct stat fileStat;
	int ret = stat(pathName,&fileStat);
	if(ret == -1)
	{
		err_sys("no %s existence",pathName);
	}
	else{
		printf("the size of %s is %d !\n",pathName,fileStat.st_size);
	}
}

void program_4_1(int argc,char* argv[])
{
	int i = 0;
	char * ptr = NULL;
	struct stat fileStat;
	for(i = 1;i < argc;i++)
	{
		printf("%s: ",argv[i]);
		if(lstat(argv[i],&fileStat) < 0)
		{
			err_sys("lstat erro");
			continue;
		}
		if   	(S_ISREG(fileStat.st_mode)) ptr = "regular";
		else if (S_ISDIR(fileStat.st_mode)) ptr = "directory";
		else if (S_ISCHR(fileStat.st_mode)) ptr = "character special";
		else if (S_ISBLK(fileStat.st_mode)) ptr = "block special";
		else if (S_ISFIFO(fileStat.st_mode)) ptr = "fifo";
#ifdef S_ISLNK
		else if (S_ISLNK(fileStat.st_mode)) ptr = "symbolic link";
#endif
#ifdef S_ISSOCK
		else if (S_ISSOCK(fileStat.st_mode)) ptr = "socket";
#endif
		else ptr= "unknown mode";
		printf(" %s\n",ptr);
	}
	exit(0);
}

void program_4_2(int argc,char* argv[])
{
	if(argc != 2)
	{
		err_quit("usage a.out <pathname>");
	}
	if(access(argv[1],R_OK) < 0)
	{
		err_ret("access error for %s",argv[1]);
	}
	else{
		printf("read access ok!\n");
	}
	if(open(argv[1],O_RDONLY) <0)
	{
		err_ret("open error for %s ",argv[1]);
	}
	else{
		printf("open for reading success!!\n");
	}
	exit(0);
}
