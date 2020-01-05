#include <iostream>
#include <omp.h>
#include <stdio.h>

int main() {
  auto x = 0;
#pragma omp parallel

  std::cout << "x: " << x << std::endl;

  printf("Hello from thread %d, nthreads %d\n", omp_get_thread_num(),
         omp_get_num_threads());
}
