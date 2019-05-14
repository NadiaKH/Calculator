#pragma warning(disable : 4996)

//#define _CRTDBG_MAP_ALLOC 
//#include <stdlib.h> 
//#include <crtdbg.h>  

#include "parse.h"
#include "structs.h"
#include "error.h"
#include "util.h"

#include <string.h>
#define TRUE 1
#define FALSE 0;


int _reallocExprData(expression_t * expr, error_t * error)
{
	int extraCapacity = 10;
	element_t * newData;

	newData = (element_t *)realloc(expr->data, sizeof(element_t) * (expr->capacity + extraCapacity));
	if (!newData)
	{
		error->is = TRUE;
		strcpy(error->message, "ERROR: cannot allocate additional memory\n");
		return FALSE;
	};
	expr->data = newData;
	expr->capacity += extraCapacity;
	return TRUE;
}



int ParseString(char * data, int start, int end, 
	expression_t * expr, 
	userFunctionList_t * userFunList, 
	functionList_t * funList, 
	variableList_t * global, 
	variableList_t * local,
	argsList_t * argList,
	error_t * error) 
{
	//TODO:
	argList = NULL;
	local = NULL;
	userFunList = NULL;
	//

	int pos = start, prev = start, nameLen = 0, unaryNext = TRUE, funID, varID, /*userFunID, argID,*/ numLen;
	/*double res;*/
	

	if (error->is)
		return FALSE;
	expr->size = 0;

	while (pos < end) {
		
		if (expr->capacity == expr->size)
			_reallocExprData(expr, error);
		if (error->is)
			return FALSE;
		prev = pos;

		if ((nameLen = IsCorrectIdentifier(data, pos)) > 0)
		{
			if ((funID = FindFunction(data, pos, nameLen + pos, funList)) >= 0)
			{
				unaryNext = TRUE;
				expr->data[expr->size].type = FUNCTION;
				expr->data[expr->size].field.index = funID;
				++expr->size;
			}
			//TODO
			/*else if ((userFunID = FindUserFunction(data, pos, nameLen + pos, userFunList)) >= 0)
			{
				unaryNext = TRUE;
				expr->data[expr->size].type = USER_FUNCTION;
				expr->data[expr->size].field.index = funID;
				++expr->size;
			}*/
			else if ((varID = FindVariable(data, pos, nameLen + pos, global)) >= 0)
			{
				unaryNext = FALSE;
				expr->data[expr->size].type = NUMBER;
				expr->data[expr->size].field.number = global->list[varID].value;
				++expr->size;

			}
			//TODO
			/*else if (argList && (argID = FindArg(data, pos, nameLen + pos, argList)) >= 0)
			{
				unaryNext = FALSE;
				expr->data[expr->size].type = VARIABLE;
				NameCopy(expr->data[expr->size].field.variable, data, pos, nameLen + pos);
				++expr->size;
			}*/
			else 
			{
				error->is = TRUE;
				strcpy(error->message, "ERROR: Not correct identifier\n");
				return FALSE;
			}
			pos += nameLen;
		}
		
		else if (IsOperation(data[pos]))
		{
			expr->data[expr->size].type = OPERATION;
			expr->data[expr->size].field.operation = (data[pos] == '-' && unaryNext) ? 'u' : data[pos];
			unaryNext = (data[pos] != ')');
			++expr->size;
			++pos;
		}
		else if ((numLen = IsDouble(data, pos)) > 0)
		{
			unaryNext = FALSE;
			expr->data[expr->size].type = NUMBER;
			expr->data[expr->size].field.number = StrToDouble(data, pos, pos + numLen);
			++expr->size;
			pos += numLen;
		}
		//TODO: bin & hex double format
		/*else if (numLen = HexBinToDouble(data, pos, &res))
		{

		}*/
		else if (IsSpaceChar(data[pos]))
		{
			++pos;
		}
		else
		{
			error->is = TRUE;
			strcpy(error->message, "ERROR: Not correct expression\n");
			return FALSE;
		}
	};
	return TRUE;
}
