#include <mpi.h>
#include <stdio.h>
//MPIRingBroadcast.c: have alot of changing to the code.
//if we remove commeted section then the program may:
//1--> run wrongly.
//2--> not work.
int main(int argc, char* argv[]){
	int rank, _rank, nproc, value;
	char proc_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Status status;
	value=1;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);
	MPI_Get_processor_name(proc_name, &name_len);
	/*
	if(rank == 0){
		printf("Enter The value: ");
		scanf("%d", &value);
	}
	*/
	printf("The Rank of Processor is: %d, the nproc is: %d\n", rank, nproc);
	do{
	//here the rank 0 send to rank 1 (value)-repeat
		if(rank==0){
			//printf("Enter The value: ");
			//scanf("%d", &value);
			/* Master node sends out the value */
			MPI_Send(&value, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
			//MPI_Send(&rank, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
			printf("1-processor 0 send %d to %d-processor\n", value, rank+1);
			
			MPI_Recv(&value, 1, MPI_INT, nproc-1, 0, MPI_COMM_WORLD, &status);
			
			printf("processor 0 receive %d from %d-processor\n", value, nproc-1);
		}else{
			MPI_Recv(&value, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &status);
			//MPI_Recv(&_rank, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &status);
			if(rank < (nproc - 1)){
				MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
				//MPI_Send(&rank, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
				printf("2-processor %d send %d to %d-processor\n", rank, value, rank+1);
			}
			printf("process %d got %d\n", rank, value);
			printf("***********************\n");
			
			if(rank == nproc -1){
				MPI_Send(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
				printf("processor %d send %d to 0-processor\n", rank, value);
			}
		}
		//printf("The Sender is: %d\n", _rank);
		//here we can do any type of calculations:
		//primitive calculation: product, sum subtract, devision.
		//decision tree.
		//data science operations.
		//...etc.
		value-=1;
	}while(value>=0);
	MPI_Finalize();
	
	return 0;
}
