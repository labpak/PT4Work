#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send5");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double x = 0;
    if (rank == 0)
    {
        for (int i = 1; i < size; i++)
        {
            pt >> x;
            MPI_Send(&x, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
        }
    }
    else
    {              
        MPI_Recv(&x, 1, MPI_DOUBLE,0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        pt << x;      
    }

}
