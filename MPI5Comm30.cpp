#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm30");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int a = 0;
    pt >> a;

    int n = (size - 1) / 3;
    int* index = new int[size], 
        * edges = new int[8 * n];

    index[0] = n;
    int e = n;

    for (int i = 1; i < size; i++)
        if (i % 3 == 0)
            index[i] = index[i - 1] + 3;
        else
            index[i] = index[i - 1] + 2;

    for (int i = 3; i < size; i += 3)
        edges[(i / 3) - 1] = i;

    for (int i = 1; i < size; i++)
    {
        if (i % 3 == 0)
        {
            edges[e] = 0;
            edges[e + 1] = i - 2;
            edges[e + 2] = i - 1;
            e += 3;
        }
        else
        if ((i + 1) % 3 == 0)
        {
            edges[e] = i - 1;
            edges[e + 1] = i + 1;
            e += 2;
        }
        else 
        {
            edges[e] = i + 1;
            edges[e + 1] = i + 2;
            e += 2;
        }
    }

    MPI_Comm g_comm;
    MPI_Graph_create(MPI_COMM_WORLD, size, index, &edges[0], 0, &g_comm);

    int maxneighbors;
    MPI_Graph_neighbors_count(g_comm, rank, &maxneighbors);
    
    int* neighbors = new int[maxneighbors];
    MPI_Graph_neighbors(g_comm, rank, maxneighbors, neighbors);


    int x = 0;
    for (int i = 0; i < maxneighbors; i++)
    {
        MPI_Sendrecv(&a, 1, MPI_INT, neighbors[i], 0, &x, 1, MPI_INT, neighbors[i], 0, g_comm, MPI_STATUSES_IGNORE);
        pt << x;
    }

}
