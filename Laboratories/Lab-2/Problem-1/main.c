#include <stdio.h>
#include <limits.h>
#include "tests.h"

// Write a function that takes as an input an array of integer numbers (both positive and negative numbers and returns the value of 
// the triplet with the maximum product, as well as the elements that form this triplet (in increasing order). 
// Use pass by pointer/address to return the elements that form that triplet. 
// Think about the appropriate data type for the result. If the size of the array is less than 3, you should return the minimum
// representable value of the data type and the elements that form the triplet should be set to 0.

long long computeMaxTriplet(int arr[], unsigned int sz, int *t1, int* t2, int* t3)
{
    long long max1 = LLONG_MIN, max2 = LLONG_MIN, max3 = LLONG_MIN, min1 = LLONG_MAX, min2 = LLONG_MAX;
    long long prodl = 0;
    long long prods = 0;
    long long prod = 0;

    if (sz < 3)
    {
        *t1 = *t2 = *t3 = 0;
        prod = LLONG_MIN;

        return prod;
    }

    for (unsigned int i = 0; i < sz; i++)
    {
        if (arr[i] < min1)
        {
            min2 = min1;
            min1 = arr[i];
        }
        else if (arr[i] <= min2)
            min2 = arr[i];
        if (arr[i] > max1)
        {
            max3 = max2;
            max2 = max1;
            max1 = arr[i];
        }
        else if (arr[i] > max2)
        {
            max3 = max2;
            max2 = arr[i];
        }
        else if (arr[i] > max3)
            max3 = arr[i];
         
    }
    
    prodl = (long long) max1 * max2 * max3;
    prods = (long long) min1 * min2 * max1;

    if (prodl >= prods)
    {
        *t1 = max3;
        *t2 = max2;
        *t3 = max1;

        return prodl;
    }
    else
    {
        *t1 = min1;
        *t2 = min2;
        *t3 = max1;

        return prods;
    }
    
}

int main()
{
#if ENABLE_TESTS > 0
    run_tests(true);
#endif
    
    int arr[100];
    unsigned int sz = sizeof(arr) / sizeof(arr[0]);
    int t1, t2, t3;
    long long p;
    unsigned int n = scanf_s("%u", &sz);
    for (unsigned int j = 0; j < sz; j++)
        scanf_s("%d", &arr[j]);
    
    p = computeMaxTriplet(arr, sz, &t1, &t2, &t3);

    if (sz < 3)
        printf("%lld", p);
    else
        printf("The triplet with the maximum product %lld is (%d, %d, %d)", p, t1, t2, t3);

    return 0;
}
