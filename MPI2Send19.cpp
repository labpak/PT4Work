#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send19");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double x = 0.0;
    pt >> x;
    MPI_Sendrecv_replace(&x, 1, MPI_DOUBLE, size - rank - 1, 0, size - rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    pt << x;
}
