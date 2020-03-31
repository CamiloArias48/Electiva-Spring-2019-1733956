#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <time.h>
 
#define MAXVECT 10
#define MAXPROC 5
#define imprimirvector(v,n) printf("Mi vista (%d) del vector, \n",myrank); for (k = 0 ; k < n; k++) printf("[%d: %d] ",myrank,v[k]); printf("\n");

int main(int argc, char *argv[])
{
    int myrank, worldsize;
    int i,a,k;
    int tag = 0;
    int root;
    int *vector;
    char hostname[HOST_NAME_MAX + 1];
    MPI_Status status;


    root = 0;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &worldsize);

    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    int send_vector[MAXVECT/worldsize];


    if (myrank == root) {

	vector = (int*) malloc(sizeof(int)*MAXVECT);


	for (i = 0; i < MAXVECT; i++) {
		vector[i] = i;
	}

	imprimirvector(vector, MAXVECT);

 	for (a = 1; a < worldsize; a++) {

		for (i = 0; i < MAXVECT/worldsize; i++) {
			send_vector[i] = vector[(MAXVECT/worldsize)*a +i];
		}

	                MPI_Send (send_vector, MAXVECT/worldsize, MPI_INT, a, tag, MPI_COMM_WORLD);
	}
	for(i = 0; i < MAXVECT/worldsize; i++){
                send_vector[i] = vector[(MAXVECT/worldsize)*myrank +i];
        }
        imprimirvector(send_vector, MAXVECT/worldsize);
	free(vector);
	vector = NULL;

     }

/////////////////////////////////////////////////////////////////////////////////////////

	for (a = 1; a < worldsize; a++) {
	  if (myrank == a) {
		MPI_Recv (send_vector, MAXVECT/worldsize, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
		imprimirvector(send_vector, MAXVECT/worldsize);
	  }
	}

    MPI_Finalize();
    return 0;
}
