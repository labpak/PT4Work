#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI4Type22");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int k = size - 1;
	double* A = new double[k];
	double* res = new double[k * k];

	int d_sz;
	MPI_Datatype newtype, newtype2;
	MPI_Type_size(MPI_DOUBLE, &d_sz);
	MPI_Type_create_resized(MPI_DOUBLE, 0, k * d_sz, &newtype);
	MPI_Type_contiguous(k, newtype, &newtype2);
	MPI_Type_commit(&newtype2);

	MPI_Datatype* st = new MPI_Datatype[size];
	for (int i = 0; i < size; i++)
		st[i] = MPI_DOUBLE;

	MPI_Datatype* rt = new MPI_Datatype[size];
	for (int i = 0; i < size; i++)
		rt[i] = newtype2;

	if (rank != 0) 
		for (int i = 0; i < k; i++) 
			pt >> A[i];
		
	int* scounts = new int[size * sizeof(int)];
	int* sdispls = new int[size * sizeof(int)];
	int* recvcount = new int[size * sizeof(int)];
	int* rdispls = new int[size * sizeof(int)];

	for (int i = 0; i < size; i++) 
	{
		scounts[i] = k;
		sdispls[i] = 0;

		recvcount[i] = k;
		rdispls[i] = (i - 1) * 8;
	}
	
	MPI_Alltoallw(A, scounts, sdispls, st, res, recvcount, rdispls, rt, MPI_COMM_WORLD);

	if (rank == 0) 
		for (int i = 0; i < k * k; i++) 
			pt << res[i];	
}
