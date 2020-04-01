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
    int* recv_vector;
    char hostname[HOST_NAME_MAX + 1];
    MPI_Status status;


    root = 0;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &worldsize);

    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    recv_vector = (int*) malloc(sizeof(int)* MAXVECT);
    int vector[MAXVECT/worldsize];


	for (a = 1; a < worldsize; a++) {
	  if (myrank == a) {
		

        	        for (i = 0; i < MAXVECT/worldsize; i++) {
                        vector[i] = (MAXVECT/worldsize)*a +i;
                	}

                        MPI_Send (&vector, MAXVECT/worldsize, MPI_INT, 0, tag, MPI_COMM_WORLD);
			imprimirvector(vector, MAXVECT/worldsize);
			printf("enviando vector al proceso de rango 0 \n");
        	

	  }
	}
///////////////////////////////////////////////////////////////////////////////////////////////////
    if (myrank == root) {

// ya que no puedo enviar mensages desde un proceso hacia el mismo, le paso los valores a las posiciones 0 y 1 de vector manualmente.
	for (i = 0; i < MAXVECT/worldsize; i++) {
                        recv_vector[i] = (MAXVECT/worldsize)*myrank +i;
                        }

        for (a = 1; a < worldsize; a++) {

		MPI_Recv (&vector, MAXVECT/worldsize, MPI_INT, a, tag, MPI_COMM_WORLD, &status);
		recv_vector[a*2] = vector[0];
		recv_vector[(a*2)+1] = vector[1];
        }
	printf("el vector en el proceso de rango 0 ha recibido todos los vectores de los demas procesos \n");
        imprimirvector(recv_vector, MAXVECT);
     }

	free(recv_vector);
	recv_vector = NULL;


    MPI_Finalize();
    return 0;
}

