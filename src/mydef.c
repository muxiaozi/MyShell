#include "myhandle_cmd.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

//Handle command
int handleCmd(char *cmd);
//earse space before cmd and after cmd
char *trim(char *cmd);
//parse command to argv
int readLine(char *cmd, int *argc, char (*argv)[64]);
//change A-Z to a-z
char *toLower(char *str);

int main(int argc, char **argv)
{
	char buffer[1024];
	if(argc < 2) //read terminal
	{
		while(1)
		{
			write(STDOUT_FILENO, "myshell> ", 9);
			int len = read(STDIN_FILENO, buffer, sizeof(buffer));
			buffer[len - 1] = '\0';
			if(handleCmd(trim(buffer))) break;
		}
	}else //read file
	{
		int fd = open(argv[1], O_RDONLY);	
		if(fd < 0)
		{
			fprintf(stderr, "%s : %s\n", argv[1], strerror(errno));
			return -1;
		}
		int index = 0;
		char ch;
		while(read(fd, &ch, 1) > 0)
		{
			if(ch == '\n')	
			{
				buffer[index] = '\0';
				handleCmd(trim(buffer));
				index = 0;
			}else
			{
				buffer[index++] = ch;
			}
		}
		close(fd);
	}
		
	return 0;
}

int handleCmd(char *cmd)
{
	int argc, i;
	char argv[8][64];
	if(readLine(cmd, &argc, argv))
	{
		//no input
		return;
	}

	//Exit
	if(!strcmp(toLower(argv[0]), "exit"))
	{
		handleCmd("end");
		printf("Bye!\n");
		return -1;
	}
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
	
	return 0;
}

char *trim(char *cmd)
{
	while(*cmd == ' ') cmd++;
	char *end = cmd + strlen(cmd) - 1;
	while(*end == ' ') *end-- = '\0';
	return cmd;
}

int readLine(char *cmd, int *argc, char (*argv)[64])
{
	*argc = 0;
	while(*cmd != '\0')
	{
		int i = 0;
		while(*cmd != ' ' && *cmd != '\0') argv[*argc][i++] = *cmd++;
		argv[(*argc)++][i] = '\0';
		while(*cmd == ' ') cmd++;
	}
	return *argc == 0;
}

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

