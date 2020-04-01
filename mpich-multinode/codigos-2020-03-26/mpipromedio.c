#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <time.h>

//#define MAXVECT 10
//#define MAXPROC 5
#define imprimirvector(v,n) printf("Mi vista (%d) del vector\n",myrank); for (i = 0 ; i < n; i++) printf("[%d: %d] ",myrank,v[i]); printf("\n promedio de (%d): \n" ,myrank);for (i = 0; i < n; i++) prom += v[i]; printf("%5.1f \n", prom/(n));

int main(int argc, char *argv[])
{
    int myrank, worldsize;
    int i,a,b,c;
    float prom;
    int N = 10;
    int root;
    int vector[N];
    int *recv_vector;
    float *recv_prom;
    float send_prom;
    float prom_global;
    char hostname[HOST_NAME_MAX + 1];

//    gethostname(hostname, HOST_NAME_MAX + 1);
//    srand(time(NULL));
//    int choosen = (rand()%MAXPROC); 
    root = 0;

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &worldsize);

    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    recv_vector = (int*) malloc(sizeof(int) * N/worldsize);

    if (myrank == root) {
     for (i = 0; i < N ; i++) {
       vector[i] = (rand()%N);
     }
    }

    MPI_Scatter( vector, N/worldsize, MPI_INT, recv_vector, N/worldsize, MPI_INT, root, MPI_COMM_WORLD);
    recv_prom = (float*) malloc(sizeof(float)*worldsize);

	for(a= 0; a < worldsize; a++) {
	  if (myrank == a) {
          imprimirvector(recv_vector, N/worldsize);
            for (b = 0; b < N/worldsize; b++) {
	    send_prom += recv_vector[b];
	    }
	    send_prom = send_prom/(N/worldsize);
	    if (myrank == root) {
	    //puse esto porque no me estaba mostrando los valores reales del vector de la vista (0)
	    //por alguna razon, al poner esto si lo empezo a mostrar correctamente
	    printf("el promedio del proceso: %d es = %5.2f", myrank, send_prom);
            }
	  }
	}

    MPI_Gather(&send_prom, 1, MPI_FLOAT, recv_prom, 1, MPI_FLOAT, root, MPI_COMM_WORLD);

	if (myrank == root) {
	printf("\n Los promedios recibidos por el proceso (%d) son: ", myrank);
	  for (c = 0; c < worldsize; c++) {
		prom_global += recv_prom[c];
		printf(" %5.1f ", recv_prom[c]);
	  }
	  prom_global /= worldsize;
	printf("\n Promedio global: %5.1f \n", prom_global);
	}

  MPI_Finalize();
    return 0;
}

