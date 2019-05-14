#pragma warning(disable : 4996)

//#define _CRTDBG_MAP_ALLOC 
//#include <stdlib.h> 
//#include <crtdbg.h>  

#include "error.h"
#include <stdio.h>

void ErrorReport(FILE * outputStream, string_t * str, error_t * error)
{
	if (error->is) {
		if (str)
			fprintf(outputStream, "%s == %s", str->data, error->message);
		else
			fprintf(outputStream, "%s", error->message);
	}
}