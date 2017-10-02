#include "myhandle_cmd.h"
#include "mylist.h"
#include "myerrno.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

static char *toLower(char *str);

static void cmdDef(int argc, char *argv[]);
static void cmdSet(int argc, char *argv[]);
static void cmdUndef(int argc, char *argv[]);
static void cmdAdd(int argc, char *argv[]);
static void cmdSub(int argc, char *argv[]);
static void cmdMul(int argc, char *argv[]);
static void cmdDiv(int argc, char *argv[]);
static void cmdPrint(int argc, char *argv[]);
static void cmdHelp(int argc, char *argv[]);
static void cmdInit(int argc, char *argv[]);
static void cmdType(int argc, char *argv[]);
static void cmdCD(int argc, char *argv[]);
static void cmdExport(int argc, char *argv[]);
static void cmdEcho(int argc, char *argv[]);
static void cmdEnv(int argc, char *argv[]);

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
	{"end", cmdInit},
	{"type", cmdType},
	{"cd", cmdCD},
	{"export", cmdExport},
	{"echo", cmdEcho},
	{"env", cmdEnv},
};

//counts of commands
#define HANDLER_COUNT (sizeof(g_HandlerTable) / sizeof(HandlerTable))

/**
 * 转换大写到小写
 * @param str 带转换的字符串
 * @return 转换后的结果
 */
char *toLower(char *str)
{
	char *tmp = str;
	while(*tmp != '\0')
	{
		*tmp = tolower(*tmp);
		tmp++;
	}
	return str;
}

int handleCmd(int argc, char *argv[])
{
	int i;
	//Search handler table
	for(i = 0; i < HANDLER_COUNT; i++)
	{
		if(!strcmp(g_HandlerTable[i].name, toLower(argv[0])))
		{
			g_HandlerTable[i].handler(argc, argv);
			return 0;
		}
	}
	return -1;
}

void cmdDef(int argc, char *argv[])
{
	int i;
	for(i = 1; i < argc; i++)
	{
		if(addElement(argv[i]))
			printMyError(argv[i]);
	}
}

void cmdSet(int argc, char *argv[])
{
	if(argc < 3)
	{
		g_my_errno = MYERR_ARGS_FEW;
		printMyError(argv[0]);
		return;
	}
	if(setValue(argv[1], atoi(argv[2])))
		printMyError(argv[1]);
}

void cmdUndef(int argc, char *argv[])
{
	int i;
	for(i = 1; i < argc; i++)
	{
		if(removeElement(argv[i]))
			printMyError(argv[i]);
	}
}

void cmdAdd(int argc, char *argv[])
{
	if(argc < 3)
	{
		g_my_errno = MYERR_ARGS_FEW;
		printMyError(argv[0]);
		return;
	}
	element e1, e2;
	if(getValue(argv[1], &e1))
	{
		printMyError(argv[1]);
		return;
	}
	if(getValue(argv[2], &e2))
	{
		printMyError(argv[2]);
		return;
	}
	setValue(argv[1], e1 + e2);
}

void cmdSub(int argc, char *argv[])
{
	if(argc < 3)
	{
		g_my_errno = MYERR_ARGS_FEW;
		printMyError(argv[0]);
		return;
	}
	element e1, e2;
	if(getValue(argv[1], &e1))
	{
		printMyError(argv[1]);
		return;
	}
	if(getValue(argv[2], &e2))
	{
		printMyError(argv[2]);
		return;
	}
	setValue(argv[1], e1 - e2);
}

void cmdMul(int argc, char *argv[])
{
	if(argc < 3)
	{
		g_my_errno = MYERR_ARGS_FEW;
		printMyError(argv[0]);
		return;
	}
	element e1, e2;
	if(getValue(argv[1], &e1))
	{
		printMyError(argv[1]);
		return;
	}
	if(getValue(argv[2], &e2))
	{
		printMyError(argv[2]);
		return;
	}
	setValue(argv[1], e1 * e2);
}

void cmdDiv(int argc, char *argv[])
{
	if(argc < 3)
	{
		g_my_errno = MYERR_ARGS_FEW;
		printMyError(argv[0]);
		return;
	}
	element e1, e2;
	if(getValue(argv[1], &e1))
	{
		printMyError(argv[1]);
		return;
	}
	if(getValue(argv[2], &e2))
	{
		printMyError(argv[2]);
		return;
	}
	if(e2 == 0)
	{
		g_my_errno = MYERR_ARGS_INVALID;
		printMyError(argv[2]);
		return;
	}
	setValue(argv[1], e1 / e2);
}

void cmdPrint(int argc, char *argv[])
{
	int i;
	element e;
	for(i = 1; i < argc; i++)
	{
		if(getValue(argv[i], &e))
			printMyError(argv[i]);
		else
			printf("%s : %d\n", argv[i], e);
	}
}

void cmdHelp(int argc, char *argv[])
{
	int fd = open("doc/document.txt", O_RDONLY);
	if(fd < 0)
	{
		printSystemError("doc/document.txt");
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

void cmdInit(int argc, char *argv[])
{
	removeAllElements();
}

void cmdType(int argc, char *argv[])
{

}

//TODO ...
void cmdCD(int argc, char *argv[])
{
	static char oldPath[64];
	
	if(argc > 2)
	{
		g_my_errno = MYERR_ARGS_MORE;
		printMyError(argv[0]);
	}
	if(!strcmp(argv[1], "-")) //上个目录
	{
		if(chdir(oldPath))
		{
			printSystemError(argv[0]);
		}else{
			getcwd(oldPath, sizeof(oldPath));
		}
	}
	if(chdir(argv[1]))
	{
		printSystemError(argv[0]);
	}else
	{
		strcpy(oldPath, argv[1]);
	}
}

void cmdExport(int argc, char *argv[])
{
	
}

void cmdEcho(int argc, char *argv[])
{
	
}

void cmdEnv(int argc, char *argv[])
{
	extern char **environ;
	char **tmpEnv = environ;
	while(*tmpEnv)
	{
		printf("%s\n", *tmpEnv++);
		printf("---------------------------------------------\n");
	}
}



