#pragma once
#ifndef STACK_H
#define STACK_H
#include <stdlib.h>


typedef struct {
	int size;
	int capacity;
	double * data;
}dStack;


typedef struct {
	int size;
	int capacity;
	char * data;
}cStack;


int dPush(dStack * pS, double d);
int cPush(cStack * pS, char c);
double dPop(dStack * pS);
char cPop(cStack * pS);
char cTop(cStack * pS);


#endif
