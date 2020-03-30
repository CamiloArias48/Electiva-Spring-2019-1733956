#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <time.h>
 
#define MAXVECT 10
#define MAXPROC 5
#define imprimirvector(v,n) printf("Mi vista (%d) del vector, %s\n",myrank, hostname); for (i = 0 ; i < n; i++) printf("[%d: %d] ",myrank,v[i]); printf("\n");

int main(int argc, char *argv[])
{
    int myrank, worldsize;
    int i;
    int a;
    int root;
    int vector[MAXVECT];
    int *rec_vector;
    char hostname[HOST_NAME_MAX + 1];

    gethostname(hostname, HOST_NAME_MAX + 1);
    srand(time(NULL));
    int choosen = (rand()%MAXPROC); 
    root = 0;

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &worldsize);

    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    rec_vector = (int*) malloc(sizeof(int) * MAXVECT/worldsize);
    if (myrank == root) {
     for (i = 0; i < MAXVECT; i++) {
       vector[i] = i;
     }
    }
//    if (myrank == choosen) {
//      imprimirvector(rec_vector,MAXVECT/worldsize);
//	printf("finalizado-1 \n");
//    }

    MPI_Scatter( vector, MAXVECT/worldsize, MPI_INT, rec_vector, MAXVECT/worldsize, MPI_INT, root, MPI_COMM_WORLD);
	for(a=0; a< worldsize; a++) {
	if (myrank == a) {
      		imprimirvector(rec_vector,MAXVECT/worldsize);
        	printf("finalizado-2 \n");
    		}

	}


    MPI_Finalize();
    return 0;
}

