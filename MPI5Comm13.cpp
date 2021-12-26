#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm13");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    int n = 0;
    if (rank == 0)
        pt >> n;

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Comm comm;
    int dims[2] = { n, size / n };
    int periods[2] = { 0, 0 };
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 0, &comm);


    if (comm != MPI_COMM_NULL) 
    {
        int coords[2];
        MPI_Cart_coords(comm, rank, 2, coords);
        pt << coords[0] << coords[1];
    }
}
