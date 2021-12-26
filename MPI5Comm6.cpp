#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm6");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int k, n;
	if (rank == 0) 
		pt >> k;
	else
		pt >> n;
	
	MPI_Comm comm;
	int color = n == 1 ? 0 : MPI_UNDEFINED;
	MPI_Comm_split(MPI_COMM_WORLD, color, rank, &comm);
	if (comm == MPI_COMM_NULL)
		return;

	double* sbuf = new double[k + 1];
	int* scounts = new int[k + 1];
	int* displs = new int[k + 1];
	double x;

	if (rank == 0) 
	{		
		for (int i = 1; i < k + 1; i++)
			pt >> sbuf[i];
			
		scounts[0] = 0;
		for (int i = 1; i < k + 1; i++)
			scounts[i] = 1;

		for (int i = 0; i < k + 1; i++)
			displs[i] = i;
	}

	MPI_Scatterv(sbuf, scounts, displs, MPI_DOUBLE, &x, 1, MPI_DOUBLE, 0, comm);
	
	if (rank != 0)
		pt << x;
}
