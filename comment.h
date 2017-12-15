/*
 * comment.h
 *
 *  Created on: 2017-12-1
 *      Author: novice
 */

#ifndef COMMENT_H_
#define COMMENT_H_

#include <sys/types.h>		/* required for some of our prototypes*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 4096  /* max line length */
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) /* default file access permission for new files*/

//static void err_doit(int, const char *,va_list);
void err_ret(const char *, ...);
void err_sys(const char *,...);
void err_dump(const char *,...);
void err_msg(const char *,...);
void err_quit(const char *,...);


#endif /* COMMENT_H_ */
