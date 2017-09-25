#ifndef __MYHANDLE_CMD_H__
#define __MYHANDLE_CMD_H__

typedef void(*cmdHandler)(int argc, char (*argv)[64]);
typedef struct 
{
	char *name;
	cmdHandler handler;
}HandlerTable;

int handleCmd(int argc, char (*argv)[64]);

#endif //__MYHANDLE_CMD_H__
