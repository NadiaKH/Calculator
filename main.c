#pragma warning(disable : 4996)

//#define _CRTDBG_MAP_ALLOC 
//#include <stdlib.h> 
//#include <crtdbg.h>  

#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "error.h"

int main(int argc, char * argv[]) {
	FILE *  file = NULL;
	error_t error = { .is = 0, .returnCode = 0, .message = ""};


	SetInputStream(argc, argv, &file, &error);
	WorkLoop(file, &error);

	ErrorReport(stdout, NULL, &error);

	if (file)
		fclose(file);

	//_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	//_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	//_CrtDumpMemoryLeaks();

	return error.returnCode;
}
