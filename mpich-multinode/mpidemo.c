#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include "mpi.h"

int main(){

  int rank; 
 
  char hostname[HOST_NAME_MAX + 1];
  gethostname(hostname, HOST_NAME_MAX + 1);
  MPI_Init(NULL, NULL);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);  
 
  printf("Proces %d from host %s!\n", rank, hostname);
 
  MPI_Finalize();

  return(0);
}
