#pragma once
#ifndef ERROR_H
#define ERROR_H
#include <stdio.h>
#include "structs.h"

typedef struct error_t 
{
	int is;
	int returnCode;
	char message[128];
}error_t;

void ErrorReport(FILE * outputStream, string_t * str, error_t * error);

#endif