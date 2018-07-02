#include <mpi.h>
#include <stdio.h>
//simplified Code
//MPIFactorialReduce.c
int main(int argc, char* argv[]){
	MPI_Init(&argc, &argv);
	
	int i, me, nproc;
	int number, globalFact=-1, localFact;
	
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);
	MPI_Comm_rank(MPI_COMM_WORLD, &me);
	
	printf("The Rank is: %d, the size of processor: %d\n", me, nproc);
	number= me + 1;
	MPI_Reduce(&number, &globalFact, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);
	
	if(me == 0){
		printf("Computing the factorial in MPI: %d processus = %d\n", nproc, globalFact);
		localFact=1;
		for(i=0; i<nproc; ++i){
			localFact *=(i+1);
		}
		printf("Versus localfactorial: %d\n", localFact);
	}	
	
	MPI_Finalize();
}
