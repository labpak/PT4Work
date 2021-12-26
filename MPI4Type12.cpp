#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI4Type12");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int sz = sizeof(int) * 2 + sizeof(double);
	char* rbuf = new char[sz];
	int pos;
	double d;
	int a[2];
	
	if (rank != 0)
	{
		for (int i = 0; i < 2; i++)
			pt >> a[i];
		pt >> d;

		pos = 0;
		MPI_Pack(a, 2, MPI_INT, rbuf, sz, &pos, MPI_COMM_WORLD);
		MPI_Pack(&d, 1, MPI_DOUBLE, rbuf, sz, &pos, MPI_COMM_WORLD);
	}

	int all_sz = sz * (size - 1);
	char* unpBUF = new char[all_sz];
	MPI_Gather(rbuf, sz, MPI_PACKED, unpBUF, sz, MPI_PACKED, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		pos = sz;
		for (int i = 1; i < size; i++)
		{
			MPI_Unpack(unpBUF, sz, &pos, a, 2, MPI_INT, MPI_COMM_WORLD);
			MPI_Unpack(unpBUF, sz, &pos, &d, 1, MPI_DOUBLE, MPI_COMM_WORLD);
			for (int i = 0; i < 2; i++)
				pt << a[i];
			pt << d;
		}
	}

}


