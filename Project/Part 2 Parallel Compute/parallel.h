#include<sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <math.h>

void parallel_compute(char filename[200] , int n_proc , float (*fun_ptr)(float , float));
