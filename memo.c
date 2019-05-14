#pragma warning(disable : 4996)

//#define _CRTDBG_MAP_ALLOC 
//#include <stdlib.h> 
//#include <crtdbg.h>  

#include "memo.h"
#include "error.h"
#include <string.h>
#define TRUE 1
#define FALSE 0




int ReallocVarList(variableList_t * list, error_t * error)
{
	int extraCapacity = 10;
	variable_t * newList;
	
	newList = (variable_t *)realloc(list->list, (list->size + extraCapacity) * sizeof(variable_t));
	if (!newList)
	{
		error->is = TRUE;
		strcpy(error->message, "ERROR: can not reallocate memory\n");
		return FALSE;
	}
	list->list = newList;
	list->size += extraCapacity;
	return TRUE;
}


int AddVarList(variableList_t * list, variable_t var, error_t * error)
{
	int i = 0;
	if (error->is)
		return FALSE;
	if (list->size == list->capacity)
	{
		ReallocVarList(list, error);
		if (error->is)
			return FALSE;
	}
	
	list->list[list->size].value = var.value;
	
	do
	{
		list->list[list->size].name[i] = var.name[i];
	} while (var.name[i++] != 0);

	++list->size;
	return TRUE;
}