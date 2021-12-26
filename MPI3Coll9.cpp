#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI3Coll9?");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int x = 0;
    int* a = new int[(size * (size + 3) / 2)];
    int* rec_buf = new int[(size * (size + 3) / 2)];
    if (rank == 0)
    for (int i = 0; i < size * (size + 3) / 2; i++)
    {
        pt >> x;
        a[i] = x;
    }
    int* scounts = new int[size];
    int* displs = new int[size];
    x = 0;

    for (int i = 0; i < size; i++)
    {
        scounts[i] = i + 2;
        displs[i] = x;
        x += scounts[i];
    }
    MPI_Scatterv(a, scounts, displs, MPI_INT, rec_buf, 100, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < scounts[rank]; i++) {
        pt << rec_buf[i];
    }
}
