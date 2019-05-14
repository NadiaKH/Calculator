#pragma warning(disable : 4996)

//#define _CRTDBG_MAP_ALLOC 
//#include <stdlib.h> 
//#include <crtdbg.h>  

#include "get.h"
#include "structs.h"
#include "error.h"
#include "parse.h"
#include "util.h"
#include "eval.h"
#include <string.h>

#define FALSE 0
#define TRUE 1




int GetIdentifier(char * data, int pos, char * name, error_t * error)
{
	if (error->is)
		return 0;

	int nameLen = 0, i = 0;

	while (IsSpaceChar(data[pos]))
		++pos;

	if ((nameLen = IsCorrectIdentifier(data, pos)) == TRUE)
	{
		for (i = 0; i < nameLen; i++)
			name[i] = data[pos + i];
		data[i] = 0;
	}
	else
	{
		error->is = TRUE;
		strcpy(error->message, "ERROR: not correct identifier\n");
	}

	return nameLen;
}


int GetVariable(string_t str, expression_t expr, variable_t * var, error_t * error)
{
	(void *)var;
	(void *)error;
	str.size = 1;
	expr.size = 1;

	//TODO
	/*
	char *data = str.data;
	int pos = 0, nameLen = 0, i;

	pos += GetIdentifier(data, pos, var->name, error);
	if (error->is)
		return 0;

	while (IsSpaceChar(data[pos]))
		++pos;

	if (data[pos] == ':' && data[pos + 1] == '=')
		pos += 2;
	else
		return FALSE;

	
	if (ParseExpr(data, pos, str.size, &expr, error))
	{
		var->value = Evaluate(&expr, )
		if (error->is)
			return FALSE;
	}
	else
		return FALSE;
	*/
	return TRUE;
}


int GetFunction(string_t str, userFunction_t * fun, error_t * error)
{
	str.size = 1;
	fun->argc = 1;
	error->is = 0;
	//TODO
	/*char * data = str.data;
	int nameLen = 0, i, pos = 0;

	pos += GetIdentifier(data, pos, fun->name, error);
	if (error->is)
		return 0;

	if (pos = GetList(data, pos, fun->args, error));
	else
		return FALSE;

	while (IsSpaceChar(data[pos]))
		++pos;

	if (data[pos] == ':' && data[pos + 1] == '=')
		pos += 2;
	else
		return FALSE;

	if (ParseExpr(data, pos, str.size, &(fun->body), error));
	else
		return FALSE;
*/
	return TRUE;

}


int _isAssign(char * data, int start, int end)
{
	int i = 0;
	while (start + i < end)
	{
		if (data[start + i] == '=')
			return i;
		++i;
	}
	return 0;
}


int _findDelimiter(char * data, int start, int end)
{
	int i = 0;
	while (start + i < end)
	{
		if (data[start + i] == ';')
			return i;
		++i;
	}
	return i;
}


/*int _isCorrect(expression_t * expr)
{
	
	int i = 0;
		return TRUE;
}*/

int _isCorrect(expression_t * expr) 
{
	int i = 0, balance = 0;
	int prevIsFun = 0, prevIsNumber = 0;
	int prevIs = 0, curIs;
	
	for (i = 0; i < expr->size; i++)
	{
		if (expr->data[i].type == FUNCTION || expr->data[i].type == NUMBER || (expr->data[i].type == OPERATION && expr->data[i].field.operation == '('))
			curIs = 1;
		else
			curIs = 0;

		if (prevIs && curIs)
			return FALSE;

		if (expr->data[i].type == NUMBER || (expr->data[i].type == OPERATION && expr->data[i].field.operation == ')'))
			prevIs = 1;
		else
			prevIs = 0;
	}

	
	
	for (i = 0; i < expr->size; i++)
		if (expr->data[i].type == OPERATION)
		{
			balance += (expr->data[i].field.operation == '(');
			balance -= (expr->data[i].field.operation == ')');
			if (balance < 0)
				return FALSE;
		}

	for (i = 0; i < expr->size; i++)
	{
		if (expr->data[i].type == OPERATION && (expr->data[i].field.operation == '(' || expr->data[i].field.operation == ')' || expr->data[i].field.operation == 'u'))
			continue;

		if (expr->data[i].type == FUNCTION)
		{
			prevIsFun = 1;
			continue;
		}
		if (prevIsFun && expr->data[i].type != NUMBER)
			return FALSE;
		prevIsFun = 0;

		if (expr->data[i].type == NUMBER)
		{
			prevIsNumber = 1;
			continue;
		}
		if (expr->data[i].type == OPERATION && !prevIsNumber)
			return FALSE;
	}
	if (prevIsFun)
		return FALSE;
	return TRUE;
}

double GetRes(string_t str,
	expression_t * expr,
	variableList_t * global,
	functionList_t * funList,
	userFunctionList_t * userFunList,
	error_t * error)
{
	if (error->is)
		return 0;

	variableList_t local = { 0, 0, NULL };
	//variable_t var;
	int strPos = 0, len, assign, exprPos = 0;
	double res = 0;

	while (strPos < str.size)
	{
		len = _findDelimiter(str.data, strPos, str.size);
		if ((assign = _isAssign(str.data, strPos, strPos + len)) == TRUE)
		{
			//TODO
			/*GetIdentifier(str.data, pos, var.name, error);
			ParseString(str.data, pos + assign + 1, pos + len, &expr, error);
			var.value = Evaluate(expr, local, error);
			AddVarList(&local, var, error);*/
		}
		else
		{
			//ParseString(str.data, strPos, strPos + len, expr, userFunList, funList, global, &local, NULL, error);
			ParseString(str.data, 0, str.size, expr, userFunList, funList, global, &local, NULL, error);
//#define DEBUG
#ifdef DEBUG
			{
				int di = 0;
				printf("%i\n", expr->size);
				for (di = 0; di < expr->size; di++)
				{
					if (expr->data[di].type == OPERATION)
					{
						printf("operation: %c\n", expr->data[di].field.operation);
					}
					if (expr->data[di].type == NUMBER)
					{
						printf("number: %g\n", expr->data[di].field.number);
					}
					if (expr->data[di].type == FUNCTION)
					{
						printf("function: %s\n", funList->list[expr->data[di].field.index].name);
					}
				}
			}
#endif
			//exprPos++;
			if (_isCorrect(expr))
				res = Evaluate(expr, &exprPos, funList, NULL, -1, error);
			else
			{
				error->is = TRUE;
				strcpy(error->message, "ERROR: GetRes: not correct expression\n");
			}
		}
		if (error->is)
			return 0;

		strPos += len + 1;
	}

	free(local.list);
	return res;
}