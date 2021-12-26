#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI4Type19");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int n = 0, p = 0;
	pt >> n;
	int sz = 4 * n - n - 2;
	if (rank != 0) 
	{
		pt >> p;
		int* B = new int[sz];
		for (int i = 0; i < sz; i++) 		
			pt >> B[i];
		
	MPI_Send(B, sz, MPI_INT, 0, p, MPI_COMM_WORLD);
	}
	else
	{
		int* indices = new int[n];
		for (int i = 0; i < n; i++)
			indices[i] = 0;
		for (int i = 1; i < n; i++) 
			indices[i] = i * n * 3 + (n - i - 1);

		int* blocklens = new int[n];
		for (int i = 0; i < n; i++)
			blocklens[i] = 1;
		blocklens[0] = n;
		blocklens[n - 1] = n;

		MPI_Datatype newtype;
		MPI_Type_indexed(n, blocklens, indices, MPI_INT, &newtype);
		MPI_Type_commit(&newtype);

		int* A = new int[n * ((size - 1) / 3) * 3 * n];
		for (int i = 0; i < n * ((size - 1) / 3) * 3 * n; i++)
			A[i] = 0;

		for (int i = 1; i < size; i++)
		{
			MPI_Status s;
			MPI_Probe(i, MPI_ANY_TAG, MPI_COMM_WORLD, &s);
			MPI_Recv(A + s.MPI_TAG, 1, newtype, i, s.MPI_TAG, MPI_COMM_WORLD, &s);
		}

		for (int i = 0; i < n * ((size - 1) / 3) * 3 * n; i++)
			pt << A[i];
	}
}
