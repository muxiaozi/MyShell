#ifndef __MYHANDLE_CMD_H__
#define __MYHANDLE_CMD_H__

typedef void(*cmdHandler)(int argc, char (*argv)[64]);
typedef struct 
{
	char *name;
	cmdHandler handler;
}HandlerTable;

extern const HandlerTable g_HandlerTable[];
extern const int HANDLER_COUNT;

#endif //__MYHANDLE_CMD_H__
