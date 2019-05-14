#pragma warning(disable : 4996)

//#define _CRTDBG_MAP_ALLOC 
//#include <stdlib.h> 
//#include <crtdbg.h>  

#include "interface.h"
#include "structs.h"
#include "read.h"
#include "get.h"
#include "eval.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

char priority[256] = { ['('] = 0,
					   ['^'] = 1,
					   ['u'] = 2,
					   ['*'] = 3, ['/'] = 3, 
						   ['+'] = 4, ['-'] = 4,  
						   [','] = 5, 
						   [')'] = 6 };

double cotan(double a) 
{
	return cos(a) / sin(a);
}


int _initFunctionList(functionList_t * list)
{
	function_t * newList = (function_t *)malloc(sizeof(function_t) * 12);
	if (!newList)
		return FALSE;
	list->list = newList;
	list->capacity = 12;
	list->size = 12;
	
	list->list[0].argc = 1;
	strcpy(list->list[0].name, "sqrt");
	list->list[0].p = sqrt;

	list->list[1].argc = 1;
	strcpy(list->list[1].name, "sin");
	list->list[1].p = sin;

	list->list[2].argc = 1;
	strcpy(list->list[2].name, "cos");
	list->list[2].p = cos;

	list->list[3].argc = 1;
	strcpy(list->list[3].name, "tg");
	list->list[3].p = tan;

	list->list[4].argc = 1;
	strcpy(list->list[4].name, "ctg");
	list->list[4].p = cotan;

	list->list[5].argc = 1;
	strcpy(list->list[5].name, "arcsin");
	list->list[5].p = asin;

	list->list[6].argc = 1;
	strcpy(list->list[6].name, "arccos");
	list->list[6].p = acos;

	strcpy(list->list[7].name, "arctg");
	list->list[7].argc = 1;
	list->list[7].p = atan;

	strcpy(list->list[8].name, "ln");
	list->list[8].argc = 1;
	list->list[8].p = log;

	//strcpy(list->list[0].name, "log");
	//list->list[10].argc = 1;

	strcpy(list->list[10].name, "floor");
	list->list[10].argc = 1;
	list->list[10].p = floor;

	strcpy(list->list[11].name, "ceil");
	list->list[11].argc = 1;
	list->list[11].p = ceil;
	
	return TRUE;
}

int _initVariableList(variableList_t * list)
{
	variable_t * newList = (variable_t *)malloc(sizeof(variable_t) * 2);
	if (!newList)
		return FALSE;
	list->list = newList;
	list->capacity = 2;
	list->size = 2;
	
	strcpy(list->list[0].name,"pi");
	list->list[0].value = 3.14159265358979323846;

	strcpy(list->list[1].name, "e");
	list->list[1].value = 2.71828182845904523536;

	return TRUE;
}


int _skipLine(char * str) {
	int i = 0;
	while (str[i] && IsSpaceChar(str[i]))
		++i;
	if (!str[i])
		return 1;
	if (str[i + 1] && str[i] == '/' && str[i + 1] == '/')
		return 1;
	return 0;
}


int _isDefenition(char * str)
{
	int i = 0;
	while(str[i] != 0)
	{
		if (str[i] == ':' && str[i + 1] == '=')
			return i;
		++i;
	}
	return 0;
}


void SetInputStream(int argc, char * argv[], FILE ** file, error_t * error) 
{
	if (error->is)
		return;

	switch (argc)
	{
	case 1:
		*file = stdin;
		break;
	case 2:
		*file = fopen(argv[1], "r");
		if (*file == NULL)
		{
			error->is = TRUE;
			strcpy(error->message, "ERROR: cannot open file\n");
		};
		break;
	default:
		error->is = TRUE;
		strcpy(error->message, "ERROR: too many args\n");
	}
}


void WorkLoop(FILE * file, error_t * error) {
	if (error->is)
		return;

	string_t str      = { 0, 0, NULL };
	expression_t expr = { 0, 0, NULL };

	userFunctionList_t userFunList = { 0, 0, NULL };
	functionList_t funList = { 0, 0, NULL };
	variableList_t varList = { 0, 0, NULL };
	
	userFunction_t fun = { .argc = 0 , .args.size = 0, .args.capacity = 0, .args.list = NULL };
	//variable_t var = { .value = 0 };

	_initFunctionList(&funList);
	_initVariableList(&varList);

	while (ReadString(file, &str, error))
	{

		if (_skipLine(str.data))
			printf("%s\n", str.data);

		//TODO
		/*else if (_isDefinition(str.data));
			
			if (GetFunction(str, &fun, error))
				AddFunctionList(&funList, fun, error);
			
			else if (GetVariable(str, &var, error))
				AddVariableList(&varList, var, error);
			
			else if (!error->is)
			{
				error->is = TRUE;
				error->message = "ERROR: not correct definition\n";
			}*/
			
		else
		{
			double value = 0;	
			value = GetRes(str, &expr, &varList, &funList, &userFunList, error);
			if (!error->is)
				printf("%s == %g\n", str.data, value);
		}

		ErrorReport(stdout, &str, error);
		error->is = FALSE;
	}

	//if is reading error (if error is appear in reading function, it returns 0)
	ErrorReport(stdout, NULL, error);
	error->is = FALSE;

	free(expr.data);
	free(str.data);
	free(funList.list);

	free(varList.list);
	free(userFunList.list);
	free(fun.args.list);
	free(fun.body.data);
	
}
