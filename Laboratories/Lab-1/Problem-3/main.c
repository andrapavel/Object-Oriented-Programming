#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// This program takes as command line a single integer value which represents a year and then computes and displays the Easter date for that year
// The algorithm for computing the catholic Easter date is the following :
//	A = year mod 19
//	B = year mod 4
//	C = year mod 7
//	D = (19 * A + 24) mod 30
//	E = (2 * B + 4 * C + 6 * D + 5) mod 7 where mod is the remainder of the division of x to y.
// Easter day is then (22 + E + D) March. Note that this formula can give a date from April if 22 + E + D > 31; also take this case into account!
// The program will display the Easter date in the following way "The Easter day is 02 April " (use trailing zeros for the day if it is less than 10)
int main(int argc, char* argv[]) {

	short year;
	int r = scanf("%hu", &year);
	if (r != 1)
		printf("Error!");
	else if (year < 1876)
		printf("Invalid input, the year should be greater or equal to 1876");
	else
	{
		unsigned short A = year % 19;
		unsigned short B = year % 4;
		unsigned short C = year % 7;
		unsigned short D = (19 * A + 24) % 30;
		unsigned short E = (2 * B + 4 * C + 6 * D + 5) % 7;
		unsigned short ED = (22 + E + D);

		char month[6] = "March";
		if (ED > 31)
		{
			strcpy(month, "April");
			ED -= 31;
		}
		
		if (ED < 10)
			printf("In %hu the Easter date is %s 0%d", year, month, ED);
		else 
			printf("In %hu the Easter date is %s %d", year, month, ED);

	}

	return 0;
}

