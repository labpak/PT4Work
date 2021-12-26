#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI7Win6");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n = 2 * (size - 1) - 1;
    double* a = new double[n];  
    MPI_Win win;
    double* b = new double[rank];
    MPI_Win_create(a, rank * sizeof(double), sizeof(double), MPI_INFO_NULL, MPI_COMM_WORLD, &win);


    if (rank == 0) 
        for (int i = 0; i < n; i++)
            pt >> a[i];

    MPI_Win_fence(0, win);
    
    if (rank != 0) 
    {
        for (int i = 0; i < rank; i++)
            pt >> b[i];

        for (int i = 0, j = -1; i < rank; i++, j++)
             MPI_Accumulate(&b[i], 1, MPI_DOUBLE, 0, rank + i - 1, 1, MPI_DOUBLE, MPI_SUM, win);
    }

    MPI_Win_fence(0, win);

    if (rank == 0)
        for (int i = 0; i < 2 * (size - 1) - 1; i++)
            pt << a[i];

    MPI_Win_free(&win);
}
