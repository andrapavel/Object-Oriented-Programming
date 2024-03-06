#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tests.h"

// Substitution cipher or Caesar’s cipher.

// This program which reads a natural number n and a string s. The string s is encoded using Caesar’s cipher with a displacement of
//  n (either positive or negative).
// The program decodes the message and display it on the screen. Punctuation marks and numbers are left as they are.


// DO NOT CHANGE THE SIGNATURE OF THIS METHOD
void encrypt(char s[], int n)
{
	for (int i = 0; i < strlen(s); i++)
	{
		if (isalnum(s[i]))
		{
			// Check if the character is an uppercase letter
			if (isupper(s[i]))
			{
				s[i] = (s[i] - 'A' + n) % 26 + 'A' - 1;
			}
			// Check if the character is a lowercase letter
			else if (islower(s[i]))
			{
				s[i] = (s[i] - 'a' + n) % 26 + 'a' - 1;
			}
			else
			{
				continue;
			}
		}

	}
	printf("%s", s);
}



int main()
{

#if (ENABLE_TESTS > 0)
	run_tests(true);

#endif

	short n;
	char s[1000];
	printf("Type displacement: ");
	int r = scanf("%hi", &n);
	if (r != 1)
	{
		printf("Error");
		return 1;
	}
	// Consume the newline character left in the input buffer
	getchar();

	printf("Type the message to encrypt: ");

	fgets(s, 1000, stdin);

	encrypt(s, &n);

	return 0;
}