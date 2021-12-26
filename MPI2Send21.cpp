#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send21");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double a = 0.0;    
    if (rank > 0)
    {
        int l = 0, n = 0;
        pt >> l;
        for (int i = 0; i < l; i++)
        {
            pt >> a;
            pt >> n;
            MPI_Send(&a, 1, MPI_DOUBLE, 0, n, MPI_COMM_WORLD);
        }
    }
    else
    {
        for (int i = 1; i < 2 * size + 1; i++)
        {
            MPI_Recv(&a, 1, MPI_DOUBLE, MPI_ANY_SOURCE, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            pt << a;
        }
    }
}
