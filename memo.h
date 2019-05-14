#pragma once
#ifndef MEMORY_H
#define MEMORY_H
#include "structs.h"
#include "error.h"


int ReallocVarList(variableList_t * list, error_t * error);
int ReallocExprData(expression_t * expr, error_t * error);
int AddVarList(variableList_t * list, variable_t var, error_t * error);


#endif
