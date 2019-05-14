#pragma warning(disable : 4996)

//#define _CRTDBG_MAP_ALLOC 
//#include <stdlib.h> 
//#include <crtdbg.h>  

#include "read.h"
#include "structs.h"
#include "error.h"
#include <string.h>
#include <stdio.h>
#define TRUE 1
#define FALSE 0

int ReadString(FILE * file, string_t * str, error_t * error) 
{
	if (error->is)
		return 0;

	char * newData;
	int extraCapacity = 10;

	if (str->capacity == 0) 
	{
		str->data = (char *)malloc(extraCapacity);
		if (!str->data)
		{
			error->is = TRUE;
			strcpy(error->message, "ERROR: cannot allocate memory\n");
			return 0;
		}
		str->capacity = extraCapacity;
	}

	str->size = 0;

	while ((str->data[str->size++] = (char)fgetc(file)) != '\n')
	{
		if (feof(file) || ferror(file)) {
			str->data[--str->size] = 0;
			return str->size;
		}


		if (str->size == str->capacity) {
			newData = (char *)realloc(str->data, str->capacity + extraCapacity);
			if (newData == NULL) {
				str->data[--str->size] = 0;
				error->is = TRUE;
				strcpy(error->message, "ERROR: cannot allocate additional memory\n");
				return 0;
			}
			str->data = newData;
			str->capacity += extraCapacity;
		}
	
	}

	str->data[--str->size] = 0;
	//return str->size;
	return TRUE;
}
