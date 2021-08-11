#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
	int rank, nprocs, num, min;
	MPI_Init(&argc, &argv);
	while(1)
	{
		MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);
		
		srand(time(NULL));
		num = rand()%2;
		
		printf("Rank %d process chose = %d \n", rank, num);
		
		MPI_Reduce(&num, &min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
		MPI_Barrier(MPI_COMM_WORLD);

		if (rank == 0)
		{
			if (min ==0)
			{
				printf("Consensus not reached \n");
			}
			else if (min == 1)
			{
				printf("Consensus reached  \n");
				exit(0);
			}
		}
	}
	MPI_Finalize();
	return 0;
}