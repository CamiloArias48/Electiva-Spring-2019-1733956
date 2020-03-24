run: compile
	mpirun -np 4 --hostfile machinefile ./mpiEx2a
compile:
	mpicc mpiEx2a.c -o mpiEx2a
clean:
	rm -rf mpiEx2a
