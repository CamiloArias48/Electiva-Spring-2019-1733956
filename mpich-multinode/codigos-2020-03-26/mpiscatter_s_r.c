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
//    int *vector;
    int vector[MAXVECT];
    char hostname[HOST_NAME_MAX + 1];
    MPI_Status status;


    root = 0;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &worldsize);

    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    int scatter_vector[MAXVECT/worldsize];


    if (myrank == root) {

//	vector = (int*) malloc(sizeof(int)*MAXVECT);


	for (i = 0; i < MAXVECT; i++) {
		vector[i] = i;
	}

	imprimirvector(vector, MAXVECT);

 	for (a = 1; a < worldsize; a++) {

		for (i = 0; i < MAXVECT/worldsize; i++) {
			scatter_vector[i] = vector[(MAXVECT/worldsize)*a +i];
		}

	                MPI_Send (&scatter_vector, MAXVECT/worldsize, MPI_INT, a, tag, MPI_COMM_WORLD);
	}
	for(i = 0; i < MAXVECT/worldsize; i++){
                scatter_vector[i] = vector[(MAXVECT/worldsize)*myrank +i];
        }
        imprimirvector(scatter_vector, MAXVECT/worldsize);
//	free(vector);
//	vector = NULL;

     }

/////////////////////////////////////////////////////////////////////////////////////////

	for (a = 1; a < worldsize; a++) {
	  if (myrank == a) {
		printf("\n antes de recivir: \n");
		imprimirvector(scatter_vector, MAXVECT/worldsize);
		MPI_Recv (&scatter_vector, MAXVECT/worldsize, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
		printf("\n despues de recivir: \n");
		imprimirvector(scatter_vector, MAXVECT/worldsize);
	  }
	}

    MPI_Finalize();
    return 0;
}
