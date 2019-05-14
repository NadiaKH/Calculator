#pragma once
#ifndef GET_H
#define GET_H
#include "structs.h"
#include "error.h"

int GetIdentifier(char * data, int pos, char * name, error_t * error);
int GetVariable(string_t str, expression_t expr, variable_t * var, error_t * error);
int GetFunction(string_t str, userFunction_t * fun, error_t * error);
double GetRes(string_t str,
	expression_t * expr,
	variableList_t * global,
	functionList_t * funList,
	userFunctionList_t * userFunList,
	error_t * error);



#endif