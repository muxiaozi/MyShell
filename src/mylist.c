#include "mylist.h"
#include "myerrno.h"
#include <stdlib.h>
#include <string.h>

static Node *head = NULL;

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

int removeAllElements()
{
	Node *tmp;
	while(head != NULL){
		tmp = head->next;
		free(head);
		head = tmp;
	}
	head = NULL;
	g_my_errno = MYERR_SUCCESS;
	return g_my_errno;
}

