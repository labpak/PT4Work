#include "pt4.h"
#include "mpi.h"

template<class T>
void send(int t, MPI_Datatype  d)
{
    int n;
    T x;
    pt >> n;
    T* a = new T[n];
    for (int i = 0; i < n; i++)
    {
        pt >> x;
        a[i] = x;
    }
    MPI_Send(a, n, d, 0, t, MPI_COMM_WORLD);
}

template<class T>
void recv(MPI_Datatype d, MPI_Status s)
{   
    int size = 0;
    if (d == MPI_INT)
        size = 4;
    else
        size = 8;
    ShowLine(s.count / size);
    T* a = new T[s.count/size];   
    MPI_Recv(a, s.count / size, d, s.MPI_SOURCE, s.MPI_TAG, MPI_COMM_WORLD, &s);
    for(int i = 0; i < s.count / size; i++)
        pt << a[i];
}

void Solve()
{
    Task("MPI2Send23");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
    if (rank > 0)
    {
        int t;
        pt >> t;
        if (t == 0)
            send<int>(t, MPI_INT);
        else
            send<double>(t, MPI_DOUBLE);
    }
    else
    {
        MPI_Status s;
        for (int i = 1; i < size; i++)
        {
            MPI_Probe(i, MPI_ANY_TAG, MPI_COMM_WORLD, &s);
            if(s.MPI_TAG == 0)
                recv<int>(MPI_INT, s);
            else
                recv<double>(MPI_DOUBLE, s);
        }
    }
}
