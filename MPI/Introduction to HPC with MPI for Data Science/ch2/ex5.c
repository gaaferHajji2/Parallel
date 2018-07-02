#include <stdio.h>
#include <mpi.h>

#define NPROCS 8
int main(int argc, char* argv[]){
	MPI_Init(&argc, &argv);
	int ranks1[4]={0,1,2,3}, ranks2[4]={4,5,6,7};
	
	MPI_Group origin_group, new_group;
	MPI_Comm new_comm;
	
	int rank, new_rank, size;
	int sendbuff, recvbuff;
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//printf("Rank is: %d, Size is: %d\n******\n", rank, size);
	sendbuff=rank;
	
	//Retrieve The Initial Group
	MPI_Comm_group(MPI_COMM_WORLD, &origin_group);

	if(rank < NPROCS/2){
		MPI_Group_incl(origin_group, NPROCS/2, ranks1, &new_group);
		printf("Include ranks1 in The new group, new group is: %d\n*********\n", new_group);
	}else{
		MPI_Group_incl(origin_group, NPROCS/2, ranks2, &new_group);
		printf("Include ranks2 in The new group, new group is: %d\n*********\n", new_group);
	}
	
	//create new Communicator for calculations
	MPI_Comm_create(MPI_COMM_WORLD, new_group, &new_comm);
	
	//global computation primitive
	MPI_Allreduce(&sendbuff, &recvbuff, 1, MPI_INT, MPI_SUM, new_comm);

	MPI_Group_rank(new_group, &new_rank);
	printf("rank= %d newrank= %d sendbuff= %d recvbuff= %d\n", rank, new_rank, sendbuff, recvbuff);
	printf("The Origin Group: %d, The new Group is: %d\n", origin_group, new_group);
	//printf("******\n");
	MPI_Finalize();
}
