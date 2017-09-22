#include "common.h"
#include "myerrno.h"
#include "mydef.h"
#include "myhandle_cmd.h"

int handleCmd(char *cmd);
char *trim(char *cmd);
void readLine(char *cmd, int *argc, char (*argv)[64]);
char *toLower(char *str);
void onInit();
void onExit();

Node *head; //data head

int main(int argc, char **argv)
{
	onInit();
	
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

void onInit()
{
	g_my_errno = 0;
	head = NULL;
	atexit(onExit); //register exit function
}

void onExit()
{
	remoteAllElements();
}

int handleCmd(char *cmd)
{
	int argc, i;
	char argv[8][64];
	readLine(cmd, &argc, argv);
	if(argc == 0) return 0; //no content

	if(!strcmp(toLower(argv[0]), "exit"))
	{
		printf("Bye!\n");
		return -1;
	}

	for(i = 0; i < HANDLER_COUNT; i++)
	{
		if(!strcmp(g_HandlerTable[i].name, toLower(argv[0])))
		{
			g_HandlerTable[i].handler(argc, argv);
			break;
		}
	}
	if(i >= HANDLER_COUNT) 
		printf("%s : Unknow command!\n", argv[0]);
	
	return 0;
}

char *trim(char *cmd)
{
	while(*cmd == ' ') cmd++;
	char *end = cmd + strlen(cmd) - 1;
	while(*end == ' ') *end-- = '\0';
	return cmd;
}

void readLine(char *cmd, int *argc, char (*argv)[64])
{
	*argc = 0;
	while(*cmd != '\0')
	{
		int i = 0;
		while(*cmd != ' ' && *cmd != '\0') argv[*argc][i++] = *cmd++;
		argv[(*argc)++][i] = '\0';
		while(*cmd == ' ') cmd++;
	}
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


int addElement(const char *name)
{
	Node *tmp;
	if(head == NULL)
	{
		head = tmp = (Node*)malloc(sizeof(Node));
	}else
	{
		for(tmp = head; ; tmp = tmp -> next)
		{
			if(!strcmp(tmp->name, name))
			{
				g_my_errno = MYERR_ALREADY_HAS_NAME;
				return g_my_errno;
			}
			
			if(tmp->next == NULL) //last element
				break;
		}

		tmp->next = (Node*)malloc(sizeof(Node));
		tmp = tmp -> next;
	}
	tmp->next = NULL;
	strcpy(tmp->name, name);
	tmp->hasValue = 0;
	tmp->value = 0;

	g_my_errno = MYERR_SUCCESS;
	return g_my_errno;
}

int setValue(const char *name, element value)
{
	Node *tmp;
	for(tmp = head; tmp != NULL; tmp = tmp->next)
	{
		if(!strcmp(tmp->name, name))
		{
			tmp->hasValue = 1;
			tmp->value = value;
			break;
		}
	}
	if(tmp == NULL)
	{
		g_my_errno = MYERR_NO_SUCH_NAME;
	}else{
		g_my_errno = MYERR_SUCCESS;
	}
	return g_my_errno;
}

int getValue(const char *name, element *value)
{
	Node *tmp;
	for(tmp = head; tmp != NULL; tmp = tmp->next)
	{
		if(!strcmp(tmp->name, name))
		{
			if(tmp->hasValue)
			{
				*value = tmp->value;
				g_my_errno = MYERR_SUCCESS;
			}else
			{
				g_my_errno = MYERR_NO_VALUE;
			}
			break; 
		}
	}
	if(tmp == NULL)
		g_my_errno = MYERR_NO_SUCH_NAME;
	return g_my_errno;
}

int removeElement(const char *name)
{
	Node *tmp, *pre;
	for(pre = tmp = head; tmp != NULL; tmp = tmp->next)
	{
		if(!strcmp(tmp->name, name))
		{
			if(head == tmp)
				head = tmp->next;
			else
				pre->next = tmp->next;
			free(tmp);
			g_my_errno = MYERR_SUCCESS;
			break;
		}
		pre = tmp;
	}
	if(tmp == NULL)
		g_my_errno = MYERR_NO_SUCH_NAME;
	return g_my_errno;
}

int remoteAllElements()
{
	Node *tmp;
	while(head != NULL){
		tmp = head->next;
		free(head);
		head = tmp;
	}
	head = NULL;
}

