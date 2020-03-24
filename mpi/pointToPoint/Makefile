run: compile
	mpirun -np 4 --hostfile machinefile ./SendRecv
compile:
	mpicc SendRecv.c -o SendRecv
clean:
	rm -rf SendRecv
