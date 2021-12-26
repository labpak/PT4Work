#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm23");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    int m = 0, n = 0, x = 0, y = 0;

    if (rank == 0)
    {   
        pt >> m;
        pt >> n;
    }

    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank < m * n)
    {
        pt >> x;
        pt >> y;
    }
   
    MPI_Comm comm_cart;
    int dims[2] = { m, n };
    int periods[2] = { 1, 0 };
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 0, &comm_cart);

    if (comm_cart != MPI_COMM_NULL)
    {
        int coords[] = { x, y };
        int rank = 0;
        if (MPI_Cart_rank(comm_cart, coords, &rank))
            pt << -1;
        else
            pt << rank;
    }
}
