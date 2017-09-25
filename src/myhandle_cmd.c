#include "myhandle_cmd.h"
#include "mylist.h"
#include "myerrno.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

static void cmdDef(int argc, char (*argv)[64]);
static void cmdSet(int argc, char (*argv)[64]);
static void cmdUndef(int argc, char (*argv)[64]);
static void cmdAdd(int argc, char (*argv)[64]);
static void cmdSub(int argc, char (*argv)[64]);
static void cmdMul(int argc, char (*argv)[64]);
static void cmdDiv(int argc, char (*argv)[64]);
static void cmdPrint(int argc, char (*argv)[64]);
static void cmdHelp(int argc, char (*argv)[64]);
static void cmdInit(int argc, char (*argv)[64]);

static const HandlerTable g_HandlerTable[] = 
{
	{"start", cmdInit},
	{"def", cmdDef},
	{"set", cmdSet},
	{"undef", cmdUndef},
	{"add", cmdAdd},
	{"sub", cmdSub},
	{"mul", cmdMul},
	{"div", cmdDiv},
	{"print", cmdPrint},
	{"help", cmdHelp},
	{"end", cmdInit}
};

//counts of commands
#define HANDLER_COUNT (sizeof(g_HandlerTable) / sizeof(HandlerTable))

int handleCmd(int argc, char (*argv)[64])
{
	char *toLower(char*);
	int i;
	//Search handler table
	for(i = 0; i < HANDLER_COUNT; i++)
	{
		if(!strcmp(g_HandlerTable[i].name, toLower(argv[0])))
		{
			g_HandlerTable[i].handler(argc, argv);
			break;
		}
	}
	//Unknow command
	if(i >= HANDLER_COUNT) 
	{
		printf("%s : Unknow command!\n", argv[0]);
	}
}

void cmdDef(int argc, char (*argv)[64])
{
	int i;
	for(i = 1; i < argc; i++)
	{
		if(addElement(argv[i]))
			printErr(argv[i]);
	}
	return;
}

void cmdSet(int argc, char (*argv)[64])
{
	if(argc < 3)
	{
		g_my_errno = MYERR_ARGS_FEW;
		printErr(argv[0]);
		return;
	}
	if(setValue(argv[1], atoi(argv[2])))
		printErr(argv[1]);
}

void cmdUndef(int argc, char (*argv)[64])
{
	int i;
	for(i = 1; i < argc; i++)
	{
		if(removeElement(argv[i]))
			printErr(argv[i]);
	}
}

void cmdAdd(int argc, char (*argv)[64])
{
	if(argc < 3)
	{
		g_my_errno = MYERR_ARGS_FEW;
		printErr(argv[0]);
		return;
	}
	element e1, e2;
	if(getValue(argv[1], &e1) || getValue(argv[2], &e2))
	{
		fprintf(stderr, "%s or %s : %s\n", argv[1], argv[2], getMyError());
		return;
	}
	setValue(argv[1], e1 + e2);
}

void cmdSub(int argc, char (*argv)[64])
{
	if(argc < 3)
	{
		g_my_errno = MYERR_ARGS_FEW;
		printErr(argv[0]);
		return;
	}
	element e1, e2;
	if(getValue(argv[1], &e1) || getValue(argv[2], &e2))
	{
		fprintf(stderr, "%s or %s : %s\n", argv[1], argv[2], getMyError());
		return;
	}
	setValue(argv[1], e1 - e2);
}

void cmdMul(int argc, char (*argv)[64])
{
	if(argc < 3)
	{
		g_my_errno = MYERR_ARGS_FEW;
		printErr(argv[0]);
		return;
	}
	element e1, e2;
	if(getValue(argv[1], &e1) || getValue(argv[2], &e2))
	{
		fprintf(stderr, "%s or %s : %s\n", argv[1], argv[2], getMyError());
		return;
	}
	setValue(argv[1], e1 * e2);
}

void cmdDiv(int argc, char (*argv)[64])
{
	if(argc < 3)
	{
		g_my_errno = MYERR_ARGS_FEW;
		printErr(argv[0]);
		return;
	}
	element e1, e2;
	if(getValue(argv[1], &e1) || getValue(argv[2], &e2))
	{
		fprintf(stderr, "%s or %s : %s\n", argv[1], argv[2], getMyError());
		return;
	}
	if(e2 == 0)
	{
		g_my_errno = MYERR_ARGS_INVALID;
		printErr(argv[2]);
		return;
	}
	setValue(argv[1], e1 - e2);
}

void cmdPrint(int argc, char (*argv)[64])
{
	int i;
	element e;
	for(i = 1; i < argc; i++)
	{
		if(getValue(argv[i], &e))
			printErr(argv[i]);
		else
			printf("%s : %d\n", argv[i], e);
	}
}

void cmdHelp(int argc, char (*argv)[64])
{
	int fd = open("doc/document.txt", O_RDONLY);
	if(fd < 0)
	{
		fprintf(stderr, "Can not find doc/document.txt!\n");
		return;
	}
	char buffer[1024];
	int len;
	while((len = read(fd, buffer, 1024)) > 0)
	{
		write(STDOUT_FILENO, buffer, len);
	}
	close(fd);
}

void cmdInit(int argc, char (*argv)[64])
{
	removeAllElements();
}

