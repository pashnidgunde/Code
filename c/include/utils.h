#ifndef __utils_h
#define __utils_h

int compare(double lhs, double rhs) {
  if (lhs < rhs)
    return -1;
  else if (lhs > rhs)
    return 1;
  return 0;
}

/* A utility function to swap two elements */
void swap(double* a, double* b) {
  double t = *a;
  *a = *b;
  *b = t;
}

#endif