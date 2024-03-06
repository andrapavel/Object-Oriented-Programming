#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void generateAllCombinations(int** numbers, char** operators)
{
    double sum;
    double copya;
    double copyb;

    int p = 0;

    for (int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= 9; j++)
        {
            for (int k = 1; k <= 9; k++)
            {
                for (int l = 1; l <= 9; l++)
                {
                    for (int a = 0; a < 4; a++)
                    {
                        sum = 0;

                        if (a == 0)
                        {
                            sum = (double)i + j;
                            copya = sum;
                        }
                        else if (a == 1)
                        {
                            sum = (double)i * j;
                            copya = sum;
                        }
                        else if (a == 2)
                        {
                            sum = (double)i / j;
                            copya = sum;
                        }
                        else if (a == 3)
                        {
                            sum = (double)i - j;
                            copya = sum;
                        }

                        for (int b = 0; b < 4; b++)
                        {
                            sum = copya;

                            if (b == 0)
                            {
                                sum = (double)sum + k;
                                copyb = sum;
                            }
                            else if (b == 1)
                            {
                                sum = (double)sum * k;
                                copyb = sum;
                            }
                            else if (b == 2)
                            {
                                sum = (double)sum / k;
                                copyb = sum;
                            }
                            else if (b == 3)
                            {
                                sum = (double)sum - k;
                                copyb = sum;
                            }

                            for (int c = 0; c < 4; c++)
                            {
                                sum = copyb;

                                if (c == 0)
                                    sum = (double)sum + l;
                                else if (c == 1)
                                    sum = (double)sum * l;
                                else if (c == 2)
                                    sum = (double)sum / l;
                                else if (c == 3)
                                    sum = (double)sum - l;

                                if (fabs(24 - sum) < 0.0001)
                                {
                                    numbers[p][0] = i;
                                    numbers[p][1] = j;
                                    numbers[p][2] = k;
                                    numbers[p][3] = l;

                                    if (a == 0)
                                        operators[p][0] = '+';
                                    if (a == 1)
                                        operators[p][0] = '-';
                                    if (a == 2)
                                        operators[p][0] = '*';
                                    if (a == 3)
                                        operators[p][0] = '/';

                                    if (b == 0)
                                        operators[p][1] = '+';
                                    if (b == 1)
                                        operators[p][1] = '-';
                                    if (b == 2)
                                        operators[p][1] = '*';
                                    if (b == 3)
                                        operators[p][1] = '/';

                                    if (c == 0)
                                        operators[p][2] = '+';
                                    if (c == 1)
                                        operators[p][2] = '-';
                                    if (c == 2)
                                        operators[p][2] = '*';
                                    if (c == 3)
                                        operators[p][2] = '/';

                                    p++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void initEasy(int easy[][4])
{
    easy[0][0] = 1;
    easy[0][1] = 1;
    easy[0][2] = 4;
    easy[0][3] = 6;

    easy[1][0] = 1;
    easy[1][1] = 1;
    easy[1][2] = 3;
    easy[1][3] = 8;

    easy[2][0] = 1;
    easy[2][1] = 2;
    easy[2][2] = 2;
    easy[2][3] = 6;

    easy[3][0] = 1;
    easy[3][1] = 2;
    easy[3][2] = 3;
    easy[3][3] = 4;

    easy[4][0] = 1;
    easy[4][1] = 1;
    easy[4][2] = 3;
    easy[4][3] = 9;

    easy[5][0] = 4;
    easy[5][1] = 4;
    easy[5][2] = 4;
    easy[5][3] = 6;

    easy[6][0] = 1;
    easy[6][1] = 8;
    easy[6][2] = 8;
    easy[6][3] = 8;
}

int main()
{
#if ENABLE_TESTS > 0
    run_tests(true);
#endif

    bool ok = true;
    char var;
    char op1, op2, op3, op4;

    // dynamically allocated memory for the matrix of numbers
    int** numbers = malloc(3188 * sizeof(int*));
    for (int i = 0; i < 3188; i++)
        numbers[i] = malloc(4 * sizeof(int));

    char** operators = malloc(3188 * sizeof(char*));
    for (int i = 0; i < 3188; i++)
        operators[i] = malloc(4 * sizeof(char));

    generateAllCombinations(numbers, operators);

    printf("Welcome to the game of 24.\n");
    printf("Use each of the 4 numbers printed below exectly once,\n");
    printf("combining them somehow with the basic mathematical opperations\n");
    printf("(+,-,*,/) to yeald the value 24.\n\n");
    printf("The numbers are: ");

    while (ok)
    {
        int r = rand() % 3188;
        printf("%d, %d, %d, %d.\n", numbers[r][0], numbers[r][1], numbers[r][2], numbers[r][3]);

        printf("Enter the 3 operations to be used, in order (+,-,*,/): ");
        int t = scanf("%c, %c, %c", &op1, &op2, &op3);
        if (((int)op1 > 47 || (int)op1 < 42) || ((int)op2 > 47 || (int)op2 < 42)
            || ((int)op3 > 47 || (int)op3 < 42))
        {
            printf("Error: You typed an invalid operator. Please retry!");
        }


        int t4 = scanf("%c", &var);
        if (var == 'h')
        {
            printf("RULES:\n");
            printf("The 24 puzzle is a math game and 4 digits are given to the player\n");
            printf("and he / she must figure out a way of combining these digits \n");
            printf("and the addition(+), subtraction(-), multiplication(*), and\n");
            printf("division(/ ) operators such that the result is 24.\n");
            printf("\n MENU: \n");
            printf("-h: display information about how the game is played and exits.\n");
            printf("-s: save all the possible solutions for the game in a text file called 'solution.txt' and then exits.\n");
            printf("-e: play the game in easy mode.\n");
            printf("If no command line arguments are specified, the game is played in the 'full' mode\n");
        }

    }

    //free memory
    for (int i = 0; i < 3188; i++)
    {
        free(numbers[i]);
        free(operators[i]);
    }
    free(numbers);
    free(operators);
    return 0;

}