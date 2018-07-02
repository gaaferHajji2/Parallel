#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]){
	MPI_Init(&argc, &argv);
	
	int rank, size, name_len;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Get_processor_name(processor_name, &name_len);
	
	printf("#procs is: %d, my rank is: %d\n", size, rank);
	printf("The Name of Processor: %s, rank: %d\n", processor_name, rank);
	printf("Salam Alekoum From MPI, rank: %d\n", rank);
	
	
	MPI_Finalize();
}
