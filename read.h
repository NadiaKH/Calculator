#ifndef READ_H
#define READ_H
#include "structs.h"
#include "error.h"
#include <stdio.h>

int ReadString(FILE * file, string_t * str, error_t * error);

#endif