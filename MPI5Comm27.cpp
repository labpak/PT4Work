#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm27");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	double x = 0.0;
	pt >> x;

	int dims[3] = { 2, 2, size / 4 };
	int periods[3] = {0, 0, 1};

	MPI_Comm comm_cart;
	MPI_Cart_create(MPI_COMM_WORLD, 3, dims, periods, 0, &comm_cart);

	int rank_source = 0, rank_dest = 0;
	MPI_Cart_shift(comm_cart, 2, -1, &rank_source, &rank_dest);

	MPI_Sendrecv_replace(&x, 1, MPI_DOUBLE, rank_source, 0, rank_dest, 0, comm_cart, MPI_STATUSES_IGNORE);
	pt << x;
}
