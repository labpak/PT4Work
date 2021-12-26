#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send9");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    if (rank > 0)
    {       
        int n;
        pt >> n;  
        if (n > 0)
        {
            double x;
            double* bs = new double[n];
            for (int i = 0; i < n; i++)
            {
                pt >> x;
                bs[i] = x;
            }
            MPI_Send(bs, n, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        }      
    }
    else
    {
        MPI_Status s;
        MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &s);
        int count = 0;
        MPI_Get_count(&s, MPI_DOUBLE, &count);
        double* br = new double[count];
        MPI_Recv(br, count, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &s);
        for (int i = 0; i < count; i++)
            pt << br[i];
        
        pt << s.MPI_SOURCE;
    }
   
}
