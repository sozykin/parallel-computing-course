///
/// Example of computing PI using MPI
///
#include<stdio.h>
#include"mpi.h"

#define N 10000000

int main(int argc, char **argv){
  int myid, numprocs, i;
  double mypi, pi, h, sum, x, time;
  // Start the processes on cluster nodes
  MPI_Init(&argc,&argv);
  // Get the number of processes available for the task
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
  // Get the current process number
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);
  // Only for root
  if (myid == 0) {
    // Start the timer
    time = MPI_Wtime();
  }
  h = 1.0 / (double) N;
  sum = 0.0;
  // Compute the partial sum
  for (i = myid + 1; i <= N; i += numprocs) {
    x = h * ((double)i - 0.5);
    sum += 4.0 / (1.0 + x*x);
  }
  // Compute the local PI value
  mypi = h * sum;
  // Use MPI_Reduce to compute global PI value by summing up local values 
  MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  // Only for root 
  if (myid == 0) {
    // Stop the timer
    time = MPI_Wtime() - time;
    // Print the PI value and required time
    printf("pi is approximately %.16f, Run time is %fs\n", pi, time);
  }
  MPI_Finalize();
}

