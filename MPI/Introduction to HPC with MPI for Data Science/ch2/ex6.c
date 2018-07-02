#include <stdio.h>
#include <mpi.h>

void LocalComputation(int rank){
	printf("Here we do some calc with rank: %d\n", rank);
}	

int main(int argc, char* argv[]){
	MPI_Init(&argc, &argv);
	double start[2], end[2];
	int size, rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	printf("#processor is: %d, my rank is: %d\n", size, rank);

	MPI_Barrier(MPI_COMM_WORLD);/*Important*/
	start[rank]=MPI_Wtime();
	/*Some Local Computations here*/
	LocalComputation(rank);
	
	MPI_Barrier(MPI_COMM_WORLD); /*Important*/
	end[rank]=MPI_Wtime();/*measure the worst-case time of a process */
	
	MPI_Finalize();
	if(rank ==0){
		/*use time in master node*/
		printf("Total Time for execution master is: %5.9f\n", (end[rank]*1.0)-start[rank]);
	}else if(rank ==1){
		printf("Total Time for execution slave is : %5.9f\n", end[rank]-start[rank]);
	}
	/*
	 *		We can also use a MPI_Reduce() procedure to compute the minimum, maximum, and overall sum of all the process times. But this eventually 	 *	  requires to add an extra step for perform the global computation with a reduce operation.
	 */
}
