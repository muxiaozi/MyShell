#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

void err(const char *str)
{
	fprintf(stderr, "%s\n", str);
}

void err_plus(const char *str)
{
	fprintf(stderr, "%s : %s\n", str, strerror(errno));
}

#endif //__COMMON_H__

