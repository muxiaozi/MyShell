#include "myerrno.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

unsigned int g_my_errno;

#define MAXERR_COUNT 7

static char buffer[1024];

static const char *ERR_TABLE[] = 
{
	"Success",
	"Already has name",
	"No such name",
	"Unknow error",
	"No value",
	"Arguments too few",
	"Arguments too more",
	"Arguments invalid"
};

const char *getMyError()
{
	if(g_my_errno > MAXERR_COUNT) 
		g_my_errno = MYERR_UNKNOW_ERR;
	return ERR_TABLE[g_my_errno];
}

void printSystemError(const char *msg)
{
	sprintf(buffer, "%s: %s\n", msg, strerror(errno));
	write(STDOUT_FILENO, buffer, strlen(buffer));
}

void printMyError(const char *msg)
{
	sprintf(buffer, "%s: %s\n", msg, getMyError());
	write(STDOUT_FILENO, buffer, strlen(buffer));
}

