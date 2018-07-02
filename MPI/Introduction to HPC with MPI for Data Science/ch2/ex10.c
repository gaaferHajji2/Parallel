#include <stdio.h>
#include <mpi.h>
//linear Algebra: of distributed algorithms on the oriented ring and torus topologies.
//here we reduce the number of communication by 1, because we cam continue the program of myid == 0.

int main(int argc, char* argv[]){
	int A[4][4], b[4], c[4], line[4], temp[4], local_value, myid, nproc;

	MPI_Init(&argc, &argv);
	
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);
	
	printf("My Rank is: %d, The Number of processor is: %d\n", myid, nproc);
	
	if(myid == 0){
		for(int i=0; i<4; ++i){
			b[i]=i;
			for(int j=0; j<4; ++j){
				A[i][j] = i + j;
				printf("A[%d][%d] is: %d\n", i, j, A[i][j]);
			}
		}
		
		//The Value of first line don't sent to reduce the number of communication.
		line[0]=A[0][0];
		line[1]=A[0][1];
		line[2]=A[0][2];
		line[3]=A[0][3];
		
		for(int i=1; i<4; ++i){ //slaves perform multiplication
			temp[0] = A[i][0];
			temp[1] = A[i][1];
			temp[2] = A[i][2];
			temp[3] = A[i][3];
			//every processor sent to itself
			MPI_Send(temp, 	4, MPI_INT, 	i, i, 	MPI_COMM_WORLD);
			MPI_Send(b,			4, MPI_INT, 	i, i, 	MPI_COMM_WORLD);
		}
	}else{
		MPI_Recv(line, 4, MPI_INT, 0, myid, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(b, 4, MPI_INT, 0, myid, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	
	{	//The Master Node
		//This code is common part of all 
		c[myid] = line[0] * b[0] + line[1] * b[1] + line[2] * b[2] + line[3] * b[3];
		if(myid != 0){
			MPI_Send(&c[myid], 1, MPI_INT, 0, myid, MPI_COMM_WORLD);
		}else{
			for(int i=1; i<4; ++i){
				MPI_Recv(&c[i], 1, MPI_INT, i, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			}
		}
		
		if(myid == 0){
			for(int i=0; i<4; ++i){
				printf("The Value of c[%d] is: %d\n", i, c[i]);
			}
		}
	}
	
	MPI_Finalize();
	return 0;
}
