#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include "tests.h"


// The strchr function is used to locate a character in a string. 
// More specifically, it returns a pointer to the first occurrence of the character in the string and NULL otherwise. 
// Write a function my_strchr, with the same parametersand return value as strchr.
const char* my_strchr(const char* s, char character)
{
    char* pt = s;
    while (*pt != '\0')
    {
        if (*pt == character)
            return pt;
        pt++;
    }

    return NULL;
}

int main(void)
{
#if ENABLE_TESTS > 0
    run_tests(true);
#endif
    
    const char* rez;
    const char s = '\0';
    char character = '\0';

    rez = my_strchr(&s, character);

    printf("%s", rez);

    return 0;
}
