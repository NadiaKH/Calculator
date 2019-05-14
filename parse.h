#pragma once
#ifndef PARSE_H
#define PARSE_H
#include "error.h"
#include "structs.h"

int ParseString(char * data, int start, int end,
	expression_t * expr,
	userFunctionList_t * userFunList,
	functionList_t * funList,
	variableList_t * global,
	variableList_t * local,
	argsList_t * argList,
	error_t * error);

#endif