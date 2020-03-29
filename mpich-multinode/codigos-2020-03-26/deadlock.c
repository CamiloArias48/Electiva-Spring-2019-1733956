#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <time.h>
 

int main(int argc, char *argv[])
{
    int myrank, worldsize;
    char hostname[HOST_NAME_MAX + 1];
    MPI_Status status;
    int recvBuffer, sendBuffer;

    gethostname(hostname, HOST_NAME_MAX + 1);

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &worldsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    // Aqui la logica de su aplicacion
    if(myrank == 0){
     MPI_Send(&sendBuffer, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
     MPI_Recv(&recvBuffer, 1, MPI_INT, 1, 0, MPI_COMM_WORLD,&status);
    } 
    if (myrank == 1) {
     MPI_Send(&sendBuffer, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
     MPI_Recv(&recvBuffer, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,&status);
    }
    MPI_Finalize();
  
    return 0;
}

