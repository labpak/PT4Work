#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm32");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n = size / 2;
    
    int* sources = new int[n], * degrees = new int[n];

    for (int i = 0; i < n; i++)
        sources[i] = i;

    for (int i = 0; i < n; i++)
    {
        if (i == n - 1 && size % 2 == 0)
            degrees[i] = 1;
        else
        if (i == n - 1 && size % 2 == 1)
            degrees[i] = 2;
        else
            degrees[i] = 2;
    }

    int x = 0;

    for (int i = 0; i < n; i++)
        x += degrees[i];
    
    int* destinations = new int[x];

    for (int i = 0; i < x; i++)
        destinations[i] = i + 1;

   /* for (int i = 0; i < n; i++)
    {
        Show(sources[i]);
    }
    ShowLine();
    for (int i = 0; i < n; i++)
    {
        Show(degrees[i]);
    }
    ShowLine();
    for (int i = 0; i < x; i++)
        Show(destinations[i]);
    ShowLine();*/

    MPI_Comm distcomm;

    if(rank == 0)
        MPI_Dist_graph_create(MPI_COMM_WORLD, n, &sources[0], &degrees[0], &destinations[0], MPI_UNWEIGHTED, MPI_INFO_NULL, 0, &distcomm);
            else
        MPI_Dist_graph_create(MPI_COMM_WORLD, 0, &sources[0], &degrees[0], &destinations[0], MPI_UNWEIGHTED, MPI_INFO_NULL, 0, &distcomm);

    int indegree, outdegree, w;
    MPI_Dist_graph_neighbors_count(distcomm, &indegree, &outdegree, &w);

    int* newsources = new int[indegree];
    int* newdestinations = new int[outdegree];
    MPI_Dist_graph_neighbors(distcomm, indegree, &newsources[0], MPI_UNWEIGHTED, outdegree, &newdestinations[0], MPI_UNWEIGHTED);

    int a = 0, sum = 0;
    pt >> a;
    sum = a;

     for (int i = 0; i < indegree; i++)
     {
         MPI_Status s;
         int x;
         MPI_Recv(&x, 1, MPI_INT, newsources[i], 0, distcomm, &s);
         sum += x;
     }
    
     for (int i = 0; i < outdegree; i++)
     {
         MPI_Send(&sum, 1, MPI_INT, newdestinations[i], 0, distcomm);
     }

    pt << sum;
}