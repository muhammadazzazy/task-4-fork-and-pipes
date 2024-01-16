#include "parallel.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

float add(float a, float b) { return a + b; }

float multiply(float a, float b) { return a * b; }

int main() {
  char filename[200];
  printf("Enter File Path\n");
  scanf("%s", filename);

  int n_proc;
  printf("Enter Number of Process\n");
  scanf("%d", &n_proc);

  float (*fun_ptr)(float, float) = &multiply;

  parallel_compute(filename, n_proc, fun_ptr);

  return 0;
}
