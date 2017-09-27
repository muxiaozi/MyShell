#include "myhandle_cmd.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int parseCmd(char *cmd);
char *trim(char *cmd);
int formatCmd(char *cmd, char *argv[]);
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
			if(parseCmd(trim(buffer))) break;
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
				parseCmd(trim(buffer));
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

/**
 * 解析命令行
 * @param cmd 命令行
 * @return 如果正常解析，返回0
 */
int parseCmd(char *cmd)
{
	int argc;
	char *argv[64];
	if((argc = formatCmd(cmd, argv)) == 0) //no input
		return 0;

	if(!strcmp(toLower(argv[0]), "exit")) //Exit
	{
		strcpy(cmd, "end");
		parseCmd(cmd);
		printf("Bye!\n");
		return -1;
	}else
	{
		if(handleCmd(argc, argv) == -1)
		{
			pid_t pid = fork();
			if(pid == 0) //子进程执行
			{
				argv[argc] = NULL;
				execvp(argv[0], argv);
				exit(0);
			}else if(pid > 0)
			{
				wait(NULL);
			}
		}
	}
	
	return 0;
}

/**
 * 去除命令行两边的空格
 */
char *trim(char *cmd)
{
	while(*cmd == ' ') cmd++;
	char *end = cmd + strlen(cmd) - 1;
	while(*end == ' ') *end-- = '\0';
	return cmd;
}

/**
 * 格式化字符串
 * @param cmd 命令行
 * @param argv 参数集
 * @return 参数个数
 */
int formatCmd(char *cmd, char *argv[])
{
	int argc = 0;
	while(*cmd != '\0')
	{
		//单词开始
		argv[argc++] = cmd;
		while(*cmd != ' ' && *cmd != '\0') cmd++;
		while(*cmd == ' ') *cmd++ = '\0';
	}
	return argc;
}

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

