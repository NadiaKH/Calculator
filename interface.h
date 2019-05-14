#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include "error.h"

void SetInputStream(int argc, char * argv[], FILE ** file, error_t * error);
void WorkLoop(FILE * file, error_t * error);

#endif