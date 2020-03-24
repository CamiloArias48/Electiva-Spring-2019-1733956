run: compile
	mpirun -np 6 --hostfile machinefile ./mpiex
compile:
	mpicc pasoMsg.c -o mpiex
clean:
	rm -rf mpiex
