#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI6File22");
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

    int int_sz = 0;
    MPI_Type_size(MPI_INT, &int_sz);
    MPI_Datatype type;
    MPI_Type_vector(3, 1, size, MPI_INT, &type);

    char nat[7] = "native";
    MPI_File_set_view(f, (size-rank-1) * int_sz, MPI_INT, type, nat, MPI_INFO_NULL);

    int* num = new int[3];
    pt >> num[0] >> num[1] >> num[2];

    MPI_File_write_all(f, num, 3, MPI_INT, MPI_STATUS_IGNORE);

    MPI_File_close(&f);
}
