#pragma once
#ifndef UTIL_H
#define UTIL_H
#include "structs.h"


int IsSpaceChar(char c);
int IsCorrectIdentifier(char * data, int pos);
int FindFunction(char * data, int pos, int end, functionList_t * funList);
int FindVariable(char * data, int pos, int end, variableList_t * varList);
int IsOperation(char c);
int IsDouble(char * str, int pos);
double StrToDouble(char * str, int l, int r);

#endif