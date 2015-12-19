#pragma once
#include <stdio.h>

FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

//To resolve the __imp_fprintf thing from SDL, 
//I add legacy_stdio_definitions.lib as an additional linker dependency.
//Remember to do for all platforms and targets!