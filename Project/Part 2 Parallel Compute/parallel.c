#include "parallel.h"

void parallel_compute(char filename[200], int n_proc, float (*fun_ptr)(float, float)) {
  int  N =0, start, stop;
  float result , data[1000];
  
  // read data

  FILE *infile;
  infile = fopen(filename, "r");
  if (infile == NULL) {
    fprintf(stderr, "\nError opening file\n");
    exit(-1);
  }

  while (!feof(infile)) 
  {
    fscanf(infile, "%f", &data[N]);
     N++;
    if(N>1000)
    {
       printf("Invalid Input ! File is too large\n");
       exit(0);
    }
  }

  fclose(infile);
  

if(n_proc ==0)
{
  printf("Invalid Input ! \n");
  exit(0);
} 
if(n_proc>N)
  n_proc=N+1; //maximum # of process possible 
if(n_proc == 1) //only parent process 
{
  result=data[0];
  for(int i = 1 ; i<N ; i++)
    result=(*fun_ptr)(result,data[i]);
  printf("Final Result = %f \n",result);
  exit(0);
}
  
  
  // divide equally on process
  int numbers_per_process = N/(n_proc -1);
  
  int pipes[n_proc-1][2];
  
  // creating processes
  int ps_id[n_proc-1];
  for (int i = 0; i < (n_proc-1) ; i++) 
  {
    if (pipe(pipes[i]) == -1)
      printf("Failed to create pipe"); //create pipe
      
    ps_id[i] = fork(); //create child

    if (ps_id[i] == 0) // child process
    {
      close(pipes[i][0]); //close reading pipe
      start = i * numbers_per_process;
      if (i != n_proc - 2)
        stop = start + numbers_per_process;
      else
        stop = N;
      float partcial_result =data[start];
      for (int z = start +1; z < stop; z++) {
        partcial_result = (*fun_ptr)(partcial_result, data[z]);
      }
      write(pipes[i][1], &partcial_result, sizeof(int));
      close(pipes[i][1]);
      exit(0); // child won't fork job ends here
    }
  }
 // wait before parent starts 
  for (int i = 0; i < n_proc; i++) {
    wait(NULL);
  }
  
  // parent process
  float total[n_proc-1];
  for (int j = 0; j < n_proc-1; j++) 
  {
      close(pipes[j][1]); // no need to write
      read(pipes[j][0],&total[j],sizeof(int));
    //printf("Read from process %d : %d \n",j,total[j]);
    if(j==0)
      result=total[j];
    else
      result=(*fun_ptr)(result,total[j]);
    //printf("Result after process %d : %d \n",j,result);
    close(pipes[j][0]);
  }
  printf("Final Result : %f \n",result);
}
