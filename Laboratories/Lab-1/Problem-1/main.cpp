#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Write a simple Hello world program that prompts the user for his / her name and birth year, and you display a greeting message as 
// well as the age of the person.
// You need to check that you have exactly one command line argumentand that this argument is a positive integer.


int main(int argc, char* argv[]) {

	
	char name[32];
	short year;
	printf("Type name: ");
	int n = scanf("%s", name);
	printf("Type birth year: ");
	int r = scanf("%hi", &year);
	if (r != 1)
		printf("Invalid input!");
	else 
		printf("Hello %s, your age is %d", name, 2023 - year);

	return 0;
}

