#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm18");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n = size / 3, x = 0;
    int* num = new int[n];

    if (rank == 0 || rank == 1 || rank == 2)
        for (int i = 0; i < n; i++)
            pt >> num[i];

    MPI_Comm comm;
    int dims[2] = { n, 3 };
    int periods[2] = { 0, 0 };
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 0, &comm);

    MPI_Comm newcomm;
    int remain_dims[2] = { 1, 0 };
    MPI_Cart_sub(comm, remain_dims, &newcomm);

    MPI_Scatter(num, 1, MPI_INT, &x, 1, MPI_INT, 0, newcomm);
    pt << x;
}
