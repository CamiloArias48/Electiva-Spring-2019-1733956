#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <time.h>

#define MAXVECT 10
#define MAXPROC 5
#define imprimirvector printf("Mi vista (%d) del vector\n",myrank); for (i = 0 ; i < MAXVECT; i++) printf("[%d: %d] ",myrank,vector[i]); printf(" terminado \n");

int main(int argc, char *argv[])
{
    int myrank, worldsize;
    int i, a;
    int tag = 0;
    int vector[MAXVECT];
    MPI_Status status;
    char hostname[HOST_NAME_MAX + 1];

    gethostname(hostname, HOST_NAME_MAX + 1);
    srand(time(NULL));
    //int choosen = (rand()%MAXPROC);

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &worldsize);

    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);


    //if (myrank == choosen) {
      //imprimirvector
    //}
    if (myrank == 0) { // proceso con rango 0 inicializara el vector
      for (i = 1; i < MAXVECT; i++) {
        vector[i] = i;
	}
	for (a = 1; a < worldsize; a++) {
		MPI_Send (&vector, MAXVECT, MPI_INT, a, tag, MPI_COMM_WORLD);
		//imprimirvector
	}
    }
	for (a = 1; a < worldsize; a++) {
		if(myrank == a) {
		MPI_Recv (&vector, MAXVECT, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
		imprimirvector
		}
    	}

    MPI_Finalize();
    return 0;
}

