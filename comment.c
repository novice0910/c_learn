/*
 * comment.c
 *
 *  Created on: 2017-12-1
 *      Author: novice
 */

#include "comment.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>


static void err_doit(int, const char *,va_list);

char *pname = NULL;	/* caller can set this from argv[0]*/
/*
 * Nonfatal error related to a system call.
 * Print a message and return.*/

void err_ret(const char *fmt, ...)
{
	va_list ap;
	va_start(ap,fmt);
	err_doit(1,fmt,ap);
	va_end(ap);
	return;
}

/* Fatal error related to a system call.
 * print a message and terminate.*/

void err_sys(const char * fmt,...)
{
	va_list ap;
	va_start(ap,fmt);
	err_doit(1,fmt,ap);
	va_end(ap);
	exit(1);
}

/*Fatal error related to a system call.
 *Print a message, dump core,and terminate. */
void err_dump(const char * fmt,...)
{
	va_list ap;
	va_start(ap,fmt);
	err_doit(1,fmt,ap);
	va_end(ap);
	abort();
	exit(1);
}

/*Nonfatal error unrelated to a system call.
 * Print a message and return*/
void err_msg(const char *fmt,...)
{
	va_list ap;
	va_start(ap,fmt);
	err_doit(0,fmt,ap);
	va_end(ap);
	return;
}

/*Fatal error unrelated to a system call.
 * Print a message and return*/
void err_quit(const char * fmt,...)
{
	va_list ap;
	va_start(ap,fmt);
	err_doit(0,fmt,ap);
	va_end(ap);
	exit(1);
}

/*
 * Print a message and return to caller
 * Caller specifies "erroFlag".*/

static void err_doit(int errnoFlag,const char * fmt,va_list ap)
{
	int erroSave;
	char buf[MAX_LINE];

	erroSave = errno;   /* value caller might want printed*/
	vsprintf(buf, fmt, ap);
	if(errnoFlag)
	{
		sprintf(buf + strlen(buf),": %s", strerror(erroSave));
	}
	printf("%s \n",buf+strlen(buf));
	strcat(buf,"\n");
	fflush(stdout);
	fputs(buf,stderr);
	fflush(NULL);
	return;
}
