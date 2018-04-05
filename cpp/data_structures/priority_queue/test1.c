
#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL 128000000 /* SAMPLE SIZE */

#include "pri_q.h"
//#include "quick_sort.h"  // TEST implementation to validate result

int main() {
  long i = 0;
  initializeQueue();
  double incoming;

  /* Requirement to use console input */
  for (i = 0; i < TOTAL; i++) {
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
