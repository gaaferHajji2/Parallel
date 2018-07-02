#include <mpi.h>
#include <stdio.h>
//MPICommunicatorRemoveFirstProcess.cpp

//This Example not work only for education purpose. 
int main(int argc, char* argv[]){
	MPI_Comm  comm_world,  comm_worker;
	MPI_Group group_world, group_worker;
	comm_world=MPI_COMM_WORLD;//the default group of commuincation
	
	MPI_Comm_group(comm_world, &group_world);
	MPI_Group_excl(group_world, 1, 0, &group_worker);/*process 0 is removed from the communication group.*/

	MPI_Comm_create(comm_world, group_worker, &comm_worker);
}
