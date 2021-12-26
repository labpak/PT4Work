#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI1Proc9");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n;
    double x;
    double sum = 0;
    double mult = 1;
    pt >> n;

    if (rank == 0)
    {
        for (int i = 0; i < n; i++)
        {
            pt >> x;
            mult *= x;
        }
        pt << mult;
    }
    else 
    {
        if (rank % 2 == 0)
        {
            for (int i = 0; i < n; i++)
            {
                pt >> x;
                sum += x;
            }
            pt << sum;
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                pt >> x;
                sum += x;
            }
            pt << sum / (1.0 * n);
        }
    }
}
