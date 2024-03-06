#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// Alice forgot her card’s PIN code. She remembers that her PIN code had 4 digits, all the digits were distinct and in decreasing order, 
// and that the sum of these digits was 24. 
// This C program that prints, on different lines, all the PIN codes which fulfill these constraints. 

int main(int argc, char* argv[]) {

	for (int i = 9; i >= 3; i--)
		for (int j = i - 1; j >= 2; j--)
			for (int t = j - 1; t >= 1; t--)
			{
				int s = 24 - (i + j + t);
				if (s < t && s >= 0)
					printf("%d%d%d%d\n", i, j, t, s);
			}
		
	return 0;
}

