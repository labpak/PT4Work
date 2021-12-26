#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI6File9");
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
    MPI_File_open(MPI_COMM_WORLD, name, MPI_MODE_RDONLY, MPI_INFO_NULL, &f);

    MPI_Offset rk = rank * sizeof(int);
    MPI_File_seek(f, rk, MPI_SEEK_SET);
    MPI_Offset offs;
    MPI_File_get_size(f, &offs);

    int file_sz = offs / sizeof(int);
    
    int count = min(rank + 1, file_sz - rank);

    MPI_Status s;
    int* num = new int[count];
    MPI_File_read_all(f, num, count, MPI_INT, &s);

    for (int i = 0; i < count; i++)
        pt << num[i];

    MPI_File_close(&f);
}
