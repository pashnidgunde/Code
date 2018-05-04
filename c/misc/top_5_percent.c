
/*
Assumption:
1. Data size is 128000000 ( as in requirement)
2. Input will be from console


Tests:
  Uncomment test code below to test against the randomly generated numbers
  and comment the code to input from console

Algo:

  1. Implement priority queue to keep elements sorted in desc order
  2. Insert numbers as per priority
  3. Any number less than 95% is discarded
  4. Any number number between 95-100% is inserted at its right location in
priority queue
  5. Finally the last number is the number which is greater than 95% of rest

Validation:
  1. Sort all numbers ( by input all numbers in large allocated buffer)
  2. Verify the result with the result from sorting from faster Quick sort

Possible Improvements:
1. Implemenatation of binary search for lookup ( not implemented )
*/

#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL 128000000 /* SAMPLE SIZE */

#include "pri_q.h"
//#include "quick_sort.h"  // TEST implementation to validate result

int main() {
  initializeQueue();
  double incoming;

  /* Requirement to use console input */
  for (long i = 0; i < TOTAL; i++) {
    scanf("%lf", &incoming);
    insertByPriority(incoming);
  }

  /* ============ test code to validate result ================
    double resultUsingFasterQSort = testUsingQSort();
    double *input = getInputArray();
    for (i = 0; i < TOTAL; i++) {
      insertByPriority(input[i]);
    }
    printf("\nUsing faster quick sort :%.*e", DECIMAL_DIG,
           resultUsingFasterQSort);
    free(input);

  ============================================================= */
  printf("\nOutput :: %.*e", DECIMAL_DIG, pri_que[MAX - 1]);
  destroyQueue();
}
