#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

int main(int argc, char* argv[]){
	MPI_Init(&argc, &argv);
	
	int rank, nprocs, n, i;
	const int root = 0;
	
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	printf("the rank of the processor is: %d, the number of processor is: %d\n", rank, nprocs);
	
	float val[N];
	int myrank, minrank, minindex;
	float minval;
	
	srand(time(NULL));
	for(i=0; i<N; ++i){
		val[i]=drand48();
		/* For Test Only.
		if(i<15){
			printf("The value of val[%d] is: %2.8f\n", i, val[i]);
		}
		*/
	}
	
	//declare c structure
	struct {float value; int index;} in, out;
	
	//First, find the minimum value locally
	in.value = val[0];
	in.index = i;
	
	for(i=1; i<N; ++i){
		if(in.value > val[i]){
			in.value = val[i];
			in.index = i;
		}
	}
	int ii = in.index;
	printf("The First Minimum of %d-processor is: %2.8f\n", rank, in.value);
	
	//and get the global rand index
	in.index = rank * N  + in.index;
	
	// now the compute the global minimum
	// the keyword in MPI for the binary commutative operator is MPI_MINLOC
	MPI_Reduce((void*)&in, (void*)&out, 1, MPI_FLOAT_INT, MPI_MINLOC, root, MPI_COMM_WORLD);
	
	if(rank == root){
		minval 		= out.value;
		minrank 	= out.index / N;
		minindex 	= out.index % N;
		printf("\n\n\t\t****************************\n");
		printf("\n\nminimal value %f on proc. %d at location %d\n\n\t\t****************************\n", minval, minrank, minindex);
	}
	
	MPI_Finalize();
}
