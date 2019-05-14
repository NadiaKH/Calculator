#pragma once
#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdlib.h>
#define NAME_LEN 32

extern char priority [256];


typedef enum ElementType_t
{
	FUNCTION = 1, USER_FUNCTION,  OPERATION, NUMBER, DELIMITER, VARIABLE
} ElementType_t;


typedef struct element_t
{
	ElementType_t type;
	union {
		double number;
		char operation;
		int index;
		char variable[NAME_LEN];
	} field;
} element_t;


typedef struct function_t
{
	char name[NAME_LEN];
	int argc;
	double(*p)();

} function_t;

typedef struct variable_t
{
	char name[NAME_LEN];
	double value;

} variable_t;


typedef struct functionList_t
{
	int size;
	int capacity;
	function_t * list;

} functionList_t;

typedef struct variableList_t
{
	int size;
	int capacity;
	variable_t * list;
} variableList_t;


typedef struct expression_t
{
	int size;
	int capacity;
	element_t * data;

} expression_t;


typedef struct argsList_t
{
	int size;
	int capacity;
	char(*list)[NAME_LEN];

} argsList_t;


typedef struct userFunction_t
{
	char name[NAME_LEN];
	int argc;
	argsList_t args;
	expression_t body;

} userFunction_t;


typedef struct userFunctionList_t 
{
	int size;
	int capacity;
	userFunction_t * list;

} userFunctionList_t;


typedef struct string_t
{
	int size;
	int capacity;
	char * data;
} string_t;


#endif