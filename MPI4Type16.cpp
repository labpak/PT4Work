#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI4Type16");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int k = size - 1;
	if (rank != 0)
	{		
		double* A = new double[k];

		for (int i = 0; i < k; i++)
			pt >> A[i];
	
		MPI_Send(A, k, MPI_DOUBLE, 0, k, MPI_COMM_WORLD);		
	}
	else
	{
		double* res = new double[k * k];		
		int d_sz;
		MPI_Datatype newtype, newtype2;
		MPI_Type_size(MPI_DOUBLE, &d_sz);
		MPI_Type_create_resized(MPI_DOUBLE, 0, k * d_sz, &newtype);
		MPI_Type_contiguous(k, newtype, &newtype2);
		MPI_Type_commit(&newtype2);

		for (int i = k; i > 0; i--)
		{
			MPI_Status s;
			MPI_Probe(i, MPI_ANY_TAG, MPI_COMM_WORLD, &s);
			MPI_Recv(res + i - 1, 1, newtype2, i, s.MPI_TAG, MPI_COMM_WORLD, &s);
		}
		for (int i = 0; i < k * k; i++)
			pt << res[i];
	}
}
