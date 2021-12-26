#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send15");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double a = 0.0;
    int n = 0;
    MPI_Status s;

    pt >> a;
    pt >> n;
    if (n != rank)
    {
        MPI_Send(&a, 1, MPI_DOUBLE, n, 0, MPI_COMM_WORLD);
        MPI_Recv(&a, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &s);
        pt << a << s.MPI_SOURCE;
    }
    else
    pt << a << n;
}
