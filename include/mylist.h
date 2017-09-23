#ifndef __MYLIST_H__
#define __MYLIST_H__

typedef int element;
typedef struct Node
{
	element value;
	char hasValue;
	char name[32];
	struct Node *next;
}Node;

int addElement(const char *name);

int setValue(const char *name, element value);

int getValue(const char *name, element *value);

int removeElement(const char *name);

int removeAllElements();

#endif //__MYLIST_H__

