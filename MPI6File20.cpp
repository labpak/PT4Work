#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI6File20");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char name[12];
    if (rank == 0)
        pt >> name;
    MPI_Bcast(name, 12, MPI_CHAR, 0, MPI_COMM_WORLD);

    MPI_File f;
    MPI_File_open(MPI_COMM_WORLD, name, MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &f);

    //MPI_Offset disp = (size + rank + 1) / 2 * (size - rank - 1) * sizeof(double);
    char nat[7] = "native";
    //(size - rank - 1)*size - 
    MPI_File_set_view(f, (size * (size - rank - 1) - (size - rank - 1) * (size - rank - 2) / 2 ) * sizeof(double), MPI_DOUBLE, MPI_DOUBLE, nat, MPI_INFO_NULL);
    //Show(size * (size - rank - 1) - (size - rank - 1) * (size - rank - 2) / 2);
    double* num = new double[rank + 1];
    for (int i = rank; i >= 0; i--)
        pt >> num[i];

    MPI_File_write_all(f, num, rank + 1, MPI_DOUBLE, MPI_STATUSES_IGNORE);

    MPI_File_close(&f);
}
