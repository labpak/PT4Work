#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm1");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int x = 0, nsize = size / 2;

    size % 2 == 1 ? nsize++ : nsize += 0;

    MPI_Group MPI_GROUP_WORLD;
    MPI_Comm_group(MPI_COMM_WORLD, &MPI_GROUP_WORLD);

    MPI_Group even;
    int* ranks = new int[nsize];
    for (int i = 0; i < nsize; i++)
        ranks[i] = i * 2;

    MPI_Group_incl(MPI_GROUP_WORLD, nsize, ranks, &even);
    for(int i =0; i < nsize; i++)
    ShowLine(ranks[i]);
    MPI_Comm even_comm;
    MPI_Comm_create(MPI_COMM_WORLD, even, &even_comm);

    int* num = new int[nsize];
    if (rank == 0)
        for (int i = 0; i < nsize; i++)
        {        
            pt >> x;
            num[i] = x;
        }
	
	MPI_Scatter(num, 1, MPI_INT, &x, 1, MPI_INT, 0, even_comm);

	if (rank % 2 == 0)
		pt << x;
        
}
