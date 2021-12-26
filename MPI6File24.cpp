#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI6File24");
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

    int d_sz = 0;
    MPI_Type_size(MPI_DOUBLE, &d_sz);
    MPI_Datatype type;
    MPI_Type_vector(2, 2, 2 * (size), MPI_DOUBLE, &type);

    char nat[7] = "native";
    MPI_File_set_view(f, 2*(size - rank - 1) * d_sz, MPI_DOUBLE, type, nat, MPI_INFO_NULL);

    double* num = new double[4];
    pt >> num[0] >> num[1] >> num[2] >> num[3];

    MPI_File_write_all(f, num, 4, MPI_DOUBLE, MPI_STATUS_IGNORE);

    MPI_File_close(&f);
}
