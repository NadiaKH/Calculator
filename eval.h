#pragma once
#ifndef EVAL_H
#define EVAL_H
#include "structs.h"
#include "error.h"

//funID ought to be -1 if it is not function call
//recursive function (like dfs, tree nodes is function calls)
//TODO errors in recursive algo

double Evaluate(expression_t * expr, int * pos, functionList_t * funList, userFunctionList_t * userFunList, int funID, error_t * error);

#endif