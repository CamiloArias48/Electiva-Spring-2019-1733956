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
//    int vector[MAXVECT];
    char hostname[HOST_NAME_MAX + 1];
    MPI_Status status;


    root = 0;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &worldsize);

    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    int recv_vector[MAXVECT/worldsize];


	for (a = 1; a < worldsize; a++) {
	  if (myrank == a) {
		

        	        for (i = 0; i < MAXVECT/worldsize; i++) {
                        recv_vector[i] = (MAXVECT/worldsize)*a +i;
                	}

                        MPI_Send (recv_vector, MAXVECT/worldsize, MPI_INT, 0, tag, MPI_COMM_WORLD);
			imprimirvector(recv_vector, 2);
			printf("enviando vector al proceso de rango 0 \n");
        	

	  }
	}
///////////////////////////////////////////////////////////////////////////////////////////////////
    if (myrank == root) {

        int      vector[MAXVECT];
// ya que no puedo enviar mensages desde un proceso hacia el mismo, le paso los valores a las posiciones 0 y 1 de vector manualmente.
	for (i = 0; i < MAXVECT/worldsize; i++) {
                        recv_vector[i] = (MAXVECT/worldsize)*myrank +i;
			vector[i]= recv_vector[i];
                        }

        for (a = 1; a < worldsize; a++) {

		MPI_Recv (recv_vector, MAXVECT/worldsize, MPI_INT, a, tag, MPI_COMM_WORLD, &status);
		vector[a*2] = recv_vector[0];
		vector[(a*2)+1] = recv_vector[1];
        }
	printf("el vector en el proceso de rango 0 ha recibido todos los vectores de los demas procesos \n");
        imprimirvector(vector, 10);
     }


    MPI_Finalize();
    return 0;
}

