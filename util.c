#pragma warning(disable : 4996)

//#define _CRTDBG_MAP_ALLOC 
//#include <stdlib.h> 
//#include <crtdbg.h>  

#include <stdio.h>
#include "util.h"
#include "structs.h"
#define FALSE 0 
#define TRUE 1
#define MAX_PATTERN_SIZE 6


int IsSpaceChar(char c) {
	switch (c) {
	case '\t':
		return 1;
	case '\v':
		return 1;
	case '\b':
		return 1;
	case '\r':
		return 1;
	case '\f':
		return 1;
	case ' ':
		return 1;
	default:
		return 0;
	}
}


int _isEqualNames(char * str, int pos, int end, char * name)
{
	int i;
	for (i = pos; i < end; i++)
	{
		if (str[i] != name[i - pos])
			return FALSE;
	}
	if (name[i - pos] != 0)
		return FALSE;
	return TRUE;
}


int _isDigit(char symbol) {
	return symbol >= '0' && symbol <= '9';
}


int _isLetter(char symbol) {
	return symbol >= 'a' && symbol <= 'z' || symbol >= 'A' && symbol <= 'Z';
}


int _isAvailableSymbol(char symbol)
{
	//Identifier can content only [a-zA-Z] or '_', without digits
	return _isLetter(symbol) || symbol == '_';
}


int IsCorrectIdentifier(char * data, int pos)
{
	int i = 0;
	if (_isDigit(data[pos + i]))
		return i;

	while (_isAvailableSymbol(data[pos + i]))
		++i;

	return i;
}


//if not find function returns -1
int FindFunction(char * data, int pos, int end, functionList_t * funList)
{
	int funID;
	for (funID = 0; funID < funList->size; funID++)
	{
		if (_isEqualNames(data, pos, end, funList->list[funID].name))
			return funID;
	}
	return -1;
}


int FindVariable(char * data, int pos, int end, variableList_t * varList)
{
	int varID;
	for (varID = 0; varID < varList->size; varID++)
		if (_isEqualNames(data, pos, end, varList->list[varID].name))
			return varID;
	return -1;
}


int IsOperation(char c)
{
	switch (c) {
	case '+':
		return TRUE;
	case '-':
		return TRUE;
	case '*':
		return TRUE;
	case '/':
		return TRUE;
	case '^':
		return TRUE;
	case ',':
		return TRUE;
	case '(':
		return TRUE;
	case ')':
		return TRUE;
	default:
		return FALSE;
	}
}


int _doubleLen(char * str, int l)
{
	int r = l;
	if (str[r] == '-')
		++r;

	for (; str[r] != 0; r++) {
		if (str[r] == 'e' || str[r] == 'E') {
			r += (str[r + 1] == '-');
			r += (str[r + 1] == '+');
			continue;
		}

		if (!_isDigit(str[r]) && str[r] != '.')
			break;
	}

	return r - l;
}



int _isMatchDoublePattern(char * s, int l, int r)
{
	char pattern[MAX_PATTERN_SIZE + 1];

	int i = 0, j = 0, prev = 0, exp = MAX_PATTERN_SIZE, dot = -1;

	if (s[l] == '-')
		++l;

	for (; l < r; l++) {
		if (s[l] >= '0' && s[l] <= '9') {
			if (!prev)
				pattern[(i++) % MAX_PATTERN_SIZE] = 'N';
			prev = 1;
		}
		else {
			if (s[l] == '.')
				dot = i;
			if (s[l] == 'E' || s[l] == 'e')
				exp = i;
			pattern[(i++) % MAX_PATTERN_SIZE] = s[l];
			prev = 0;
		}
	}

	if (i > MAX_PATTERN_SIZE)
		return 0;

	exp = min(exp, i);
	if (/*dot == i - 1 ||*/ exp == 0 || exp == i - 1) //точка может быть последней
		return 0;
	for (j = 0; j < dot; j++)
		if (pattern[j] != 'N')
			return 0;
	for (j = dot + 1; j < exp; j++)
		if (pattern[j] != 'N')
			return 0;
	if (exp == i)
		return 1;
	return (pattern[exp + 1] == 'N' || exp + 2 < i && (pattern[exp + 1] == '-' || pattern[exp + 1] == '+') && pattern[exp + 2] == 'N');

}


//returns length of double 
int IsDouble(char * str, int pos)
{
	int len = _doubleLen(str, pos);
	if (_isMatchDoublePattern(str, pos, pos + len))
		return len;
	return 0;
}


int _strToInt(int l, int r, char * str) {
	int sign = 1, res = 0;
	if (l >= r)
		return 0;
	if (str[l] == '-') {
		sign = -1;
		l++;
	}

	if (str[l] == '+')
		l++;

	for (; l < r; l++)
		res = res * 10 + str[l] - '0';
	return  sign * res;
}



double StrToDouble(char * str, int l, int r) {
	int i, exp = 0, sgn = 1;
	double res = 0, factor = 1;

	if (str[l] == '-') 
	{
		sgn = -1;
		++l;
	};

	while (l < r && str[l] == '0') l++;

	for (i = l; i < r && str[i] != 'e' && str[i] != 'E' && str[i] != '.'; i++);
	exp = i - 1 - l;
	for (; i < r && str[i] != 'e' && str[i] != 'E'; i++);
	exp += _strToInt(i + 1, r, str);

	for (; exp > 0; exp--)
		factor *= 10;
	for (; exp < 0; exp++)
		factor /= 10;

	for (; l < i; l++) {
		if (str[l] == '.')
			continue;
		res += factor * (str[l] - '0');
		factor /= 10;
	}
	return sgn * res;
}
