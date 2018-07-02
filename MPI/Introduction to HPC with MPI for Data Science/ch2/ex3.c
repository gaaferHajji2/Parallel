//Test NonBlocking Communication.
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main(argc, argv) int argc; char* argv[];{
	int myid, numprocs;
	int tag, source, destination, count;
	int buffer;
	MPI_Status status;
	MPI_Request request;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	tag = 2312;
	source=0;
	destination=1;
	count=1;
	
	printf("myid is: %d\n*********\n", myid);
	
	if(myid == source){
		buffer=2015;
		MPI_Isend(&buffer, count, MPI_INT, destination, tag, MPI_COMM_WORLD, &request);
	}
	
	if(myid == destination){
		MPI_Irecv(&buffer, count, MPI_INT, source, tag, MPI_COMM_WORLD, &request);
	}
	
	MPI_Wait(&request, &status);
	if(myid == source){
		printf("processor %d Sended %d\n*********\n", myid, buffer);
	}
	
	if(myid == destination){
		printf("processor %d received %d\n*********\n", myid, buffer);
	}
	
	MPI_Finalize();
}
