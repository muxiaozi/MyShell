#include "myerrno.h"
#include <stdio.h>

unsigned int g_my_errno;

#define MAXERR_COUNT 7

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

void printInfo(const char *info)
{
	fprintf(stdout, "%s : %s\n", info, getMyError());
}

void printErr(const char *err)
{
	fprintf(stderr, "%s : %s\n", err, getMyError());
}


