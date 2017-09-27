#ifndef __MYHANDLE_CMD_H__
#define __MYHANDLE_CMD_H__

typedef void(*cmdHandler)(int argc, char *argv[]);
typedef struct 
{
	char *name;
	cmdHandler handler;
}HandlerTable;

int handleCmd(int argc, char *argv[]);

#endif //__MYHANDLE_CMD_H__
