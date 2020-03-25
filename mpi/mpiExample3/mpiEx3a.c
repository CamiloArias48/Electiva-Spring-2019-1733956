#include <stdio.h>
#include <ctype.h>
#include "mpi.h"
#define MAXVECTOR 20

int main(int argc,char *argv[]){
    	int size, rank, dest, source, count, tag=1;
    	//char inmsg, outmsg='x';
       int outmsg[3]={1,3,4};
       int inmsg[3];
    	MPI_Status Stat;

    	MPI_Init(&argc,&argv);
    	MPI_Comm_size(MPI_COMM_WORLD, &size);
    	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    	if (rank == 0) {
      	dest = 1;
      	source = 1;
      	MPI_Send(&outmsg, 3, MPI_INT, dest, tag, MPI_COMM_WORLD);
      	MPI_Recv(&inmsg, 3, MPI_INT, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &Stat);
      	for (dest = 0; dest < 3; dest++) printf("%d ",inmsg[dest]);
    	}else if (rank == 1) {
      	dest = 0;
      	source = 0;
      	MPI_Recv(&inmsg, 3, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
        for (source = 0; source < 3; source++) outmsg[source] = -1*inmsg[source];
      	MPI_Send(&outmsg, 3, MPI_INT, dest, tag, MPI_COMM_WORLD);
     	}

    	MPI_Get_count(&Stat, MPI_INT, &count);
    	printf("Task %d: Received %d int(s) from task %d with tag %d \n",
               	rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG);

    	MPI_Finalize();
}
