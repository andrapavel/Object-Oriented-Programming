#define _CRT_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <stdio.h>
#include <limits.h>
#include "tests.h"
#include <string.h>

// Using the function that you wrote for problem 2, write a function that computes and returns an array with all the positions of the
// occurrences of a character in a string.
void find_all( const char * str, char character, int*  positions, unsigned int cap, unsigned int * l)
{
    for (unsigned int i = 0; i < cap; i++)
        positions[i] = -1;

    *l = 0;
    const char* p;
    p = str;
    while ((p = strchr(p, character)) != NULL && *l < cap)
    {
            positions[*l] = p - str;
            p++;
            (*l)++;

    }
}

int main()
{
#if  ENABLE_TESTS > 0
    run_tests(true);
#endif 

    const char* str = "aabbbcaaabcaaddeeaaaab";
    char character = '\0';
    int positions[10];
    unsigned int cap = 10;
    unsigned int l;
    find_all(str, character, positions, cap, &l);

    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();

    return 0;
}
