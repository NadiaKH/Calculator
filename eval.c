#pragma warning(disable : 4996)

//#define _CRTDBG_MAP_ALLOC 
//#include <stdlib.h> 
//#include <crtdbg.h>  

#include "structs.h"
#include "error.h"
#include "stack.h"
#include <math.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int _canPopTop(char top, char sym)
{
	if (sym == 'u')
		return FALSE;
	if (priority[top] < priority[sym])
		return TRUE;
	if (priority[top] == priority[sym])
	{
		if (sym == '^' || sym == ',')
			return FALSE;
		else return TRUE;
	}
	return FALSE;
}

int _pushSym(cStack * cS, dStack * dS, char sym) {
	//TODO: error(push functions have a return value)
	//TODO: error 
	char top;
	double a, b, basis, exp, res = 0;

	while ((top = cTop(cS)) != '(' && _canPopTop(top, sym)) {
		cPop(cS);
		switch (top) {
		case 'u':
			res = -1 * dPop(dS);
			//dPush(dS, -1 * dPop(dS));
			break;
		case '^':
			exp = dPop(dS);
			basis = dPop(dS);
			res = pow(basis, exp);
			//dPush(dS, pow(basis, exp));
			break;
		case '*':
			a = dPop(dS);
			b = dPop(dS);
			res = a * b;
			//dPush(dS, a * b);
			break;
		case '/':
			a = dPop(dS);
			b = dPop(dS);
			res = (a == 0) ? NAN : b / a;
			//dPush(dS, b / a);
			break;
		case '+':
			a = dPop(dS);
			b = dPop(dS);
			res = a + b;
			//dPush(dS, a + b);
			break;
		case '-':
			a = dPop(dS);
			b = dPop(dS);
			res = b - a;
			//dPush(dS, b - a);
			break;

		case ',':
			break;

		}

		if (top != ',') 
			if (res == res) 
				dPush(dS, res);
			else
				return FALSE;
	}

	if (sym == ')') {
		cPop(cS);
	}
	else {
		cPush(cS, sym);
	}
	return TRUE;
}


double _functionCall(int argc, double(*f)(), double * args)
{
	switch (argc)
	{
	case 0:
		return f();
	case 1:
		return f(*args);
	case 2:
		return f(*args, *(args + 1));
	}
	return 0;
}


double ApplyFunction(functionList_t * funList, userFunctionList_t * userFunList, int funID, dStack * dS, error_t * error)
{
	double args[10];
	int i;
	if (error->is)
		return 0;

	if (funList)
	{
		for (i = funList->list[funID].argc - 1; i >= 0; i--)
		{	
			if (dS->size == 0)
			{
				error->is = TRUE;
				strcpy(error->message, "ERROR: Is not correct expression\n");
			}
			args[i] = dPop(dS);
		}

		return _functionCall(funList->list[funID].argc, funList->list[funID].p, args);
	}
	else if (userFunList)
	{
		//TODO: userFunctions
	}
	else {
		//error
	}
	return 0;
}

double Evaluate(expression_t * expr, int * pos, functionList_t * funList, userFunctionList_t * userFunList, int funID, error_t * error)
{
	double res = 0;
	int balance = 0, isPushed = 1;
	dStack dS = { 0, 0, NULL };
	cStack cS = { 0, 0, NULL };

	if (error->is)
		return 0;

	cPush(&cS, '(');

	for (; *pos < expr->size; (*pos)++) {

		switch (expr->data[*pos].type)
		{
		case FUNCTION:
			*pos += 1;
			dPush(&dS, Evaluate(expr, pos, funList, userFunList, expr->data[*pos - 1].field.index, error));
			break;
			//check if error is
		case USER_FUNCTION:
			//TODO
			break;
		case OPERATION:
			isPushed = _pushSym(&cS, &dS, expr->data[*pos].field.operation);
			balance += (expr->data[*pos].field.operation == '(') - (expr->data[*pos].field.operation == ')');
			break;
		case NUMBER:
			dPush(&dS, expr->data[*pos].field.number);
			break;
		default:
			error->is = TRUE;
			strcpy(error->message, "ERROR: EVAL1: not correct expression\n");
			break;
		};

		if (!isPushed)
			break;
		if (!balance && funID != -1)
			break;
	}

	isPushed = _pushSym(&cS, &dS, ')');


	if (funID == -1)
		res = dPop(&dS);
		//TODO: if stack is not empty 
	else
		res = ApplyFunction(funList, userFunList, funID, &dS, error);
		//TODO: user functions
		//if arg is NaN user function should return NaN
	if (dS.size || cS.size || res != res || !isPushed || res == INFINITY || res == -INFINITY)
	{
		error->is = TRUE;
		strcpy(error->message, "ERROR: EVAL3: not correct expression\n");
	}

	free(dS.data);
	free(cS.data);
	return res;

}