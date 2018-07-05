//for calculating the PI using Mote Carlo Method.
//Lim(n-->inf) pi(n) = pi
#include <stdio.h>
#include <time.h>
#include <mpi.h>

#include <stdlib.h>

using namespace std;

#define INT_MAX_ 1000000000
//the modified code
int main(int argc, char* argv[]){
	MPI_Init(&argc, &argv);

	int myid, size, inside=0, outside=0, points= 10000;
	double x, y, Pi_comp, Pi_real= 3.141592653589793238462643;
	double* rands;
	
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	printf("My Id of Processor is: %d, total number of processor: %d\n", myid, size);
	srand(time(NULL));
	if(myid == 0){
		for(int i=1; i<size; ++i){/*send to slaves*/
			MPI_Send(&points, 1, MPI_INT, i, i, MPI_COMM_WORLD);
		}
	}else{
			MPI_Recv(&points, 1, MPI_INT, 0, myid, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	rands=new double[2*points];
	for(int i=0; i<2*points; ++i){//هنا نقوم بحساب عدد النقاط في كامل القطر، حيث نصف القطر هو
	//points = 10000
		rands[i]=(double)rand()/INT_MAX_ / 1.677;
		if(rands[i] <= INT_MAX_){
			++i;
		}
		
		if(i<=15){
			printf("The Value of rands[%d]: %3.9f\n", i, rands[i]);
		}
	}
			
	for(int i=0;i<points; ++i){
		x=rands[2*i];
		y=rands[2*i+1];
		if((x*x+y*y)<1){//حسب قوانين المثلث القائم ودائرة الوحدة
			++inside;/*points inside unit circle*/
		}
	}
	printf("%d-Number of inside points: %d\n", myid, inside);
	delete[] rands;
	
	if(myid == 0){
		for(int i=1; i<size; ++i){
			int temp;
			MPI_Recv(&temp, 1, MPI_INT, i, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			inside +=temp;
		}/*master sums all*/
	}else{
		MPI_Send(&inside, 1, MPI_INT, 0, myid, MPI_COMM_WORLD);
	}
	
	if(myid == 0){
		Pi_comp = 4*(double)inside/(double)(size*points);//here we use the approximation of Monte carlo pi = points(c)/total_points.
		//total points = number of used processor * number of points in one processor.
		printf("Value obtained: %2.12f\nPi_Real is: %2.12f\n", Pi_comp, Pi_real);
	}
	
	MPI_Finalize();
	return 0;
}
