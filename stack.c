#pragma warning(disable : 4996)

//#define _CRTDBG_MAP_ALLOC 
//#include <stdlib.h> 
//#include <crtdbg.h>  

#include "stack.h"
#include <stdlib.h>
#include <math.h>
#define FALSE 0
#define TRUE 1

int dPush(dStack * pS, double d) {
	int extra_capacity = 10;
	double * newData;
	if (pS->size == pS->capacity) {
		newData = (double *)realloc(pS->data, sizeof(double) * (pS->capacity + extra_capacity));
		if (!newData)
			return FALSE;
		pS->data = newData;
		pS->capacity += extra_capacity;
	}
	pS->data[pS->size++] = d;
	return TRUE;
}


double dPop(dStack * pS) {
	if (!pS->size)
		return NAN;
	return pS->data[--(pS->size)];
}

int cPush(cStack * pS, char c) {
	int extra_capacity = 10;
	char * newData = NULL;
	if (pS->size == pS->capacity) {
		newData = (char *)realloc(pS->data, sizeof(char) * (pS->capacity + extra_capacity));
		if (!newData)
			return FALSE;
		pS->data = newData;
		pS->capacity += extra_capacity;
	}
	pS->data[pS->size++] = c;
	return TRUE;
}


char cPop(cStack * pS) {
	return pS->data[--(pS->size)];
}

char cTop(cStack * pS) {
	return pS->data[pS->size - 1];
}
