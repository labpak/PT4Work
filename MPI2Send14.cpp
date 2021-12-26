#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send14");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int s_val = 0;
    int r_val = 0;
    int a[2];
    pt >> s_val;
    if (rank > 0)
    {
        MPI_Ssend(&s_val, 1, MPI_INT, (size + rank - 1) % size, 0, MPI_COMM_WORLD);
        MPI_Recv(&r_val, 1, MPI_INT, (size + rank + 1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);      
        a[1] = r_val;
        pt >> s_val;     
        MPI_Ssend(&s_val, 1, MPI_INT, (size + rank + 1) % size, 0, MPI_COMM_WORLD);
        MPI_Recv(&r_val, 1, MPI_INT, (size + rank - 1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        a[0] = r_val;
    }
    else
    {     
        MPI_Recv(&r_val, 1, MPI_INT, (size + rank + 1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Ssend(&s_val, 1, MPI_INT, (size + rank - 1) % size, 0, MPI_COMM_WORLD);
        a[1] = r_val;
        pt >> s_val;        
        MPI_Recv(&r_val, 1, MPI_INT, (size + rank - 1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Ssend(&s_val, 1, MPI_INT, (size + rank + 1) % size, 0, MPI_COMM_WORLD);
        a[0] = r_val;
    }

    pt << a[0] << a[1];
}
