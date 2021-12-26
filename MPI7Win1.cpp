#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI7Win1");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    
    MPI_Win win;
    int* a = new int[size - 1];
    MPI_Win_create(a, (size-1) * sizeof(int) , sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &win);
  
    MPI_Win_fence(0, win);
    if (rank != 0)
    {
        int x = 0;
        pt >> x;
        MPI_Put(&x, 1, MPI_INT, 0, rank-1, 1, MPI_INT, win);
    }

    MPI_Win_fence(0, win);
    if (rank == 0) 
    {
        for (int i = 0; i < size - 1; i++)
            pt << a[i];
    }
    MPI_Win_free(&win);
}
