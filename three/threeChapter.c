/*
 * threeChapter.c
 *
 *  Created on: 2017-12-9
 *      Author: novice
 */


#include "threeChapter.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../comment.h"

#define BUFFSIZE 8192

void program_3_2(void)
{
	char buf1[] = "abcdefghij";
	char buf2[] = "ABCDEFGHIJ";

	int fd;

	if((fd = creat("file.hole",FILE_MODE)) <0 )
	{
		err_sys("create error!");
	}
	if(write(fd,buf1,10) != 10)
	{
		err_sys("buf1 write error");
	}
	if(lseek(fd,40,SEEK_SET) == -1)
	{
		err_sys("lseek error");
	}
	if(write(fd,buf2,10) != 0)
	{
		err_sys("buf2 write error");
	}
	exit(0);
}

void program_3_3(void)
{
	int n;
	char buf[BUFFSIZE];

	while((n = read(STDIN_FILENO,buf,BUFFSIZE)) > 0)
	{
		if(write(STDOUT_FILENO,buf,n) != n)
		{
			err_sys("write error");
		}
	}
	if(n < 0)
	{
		err_sys("read error");
	}
}
