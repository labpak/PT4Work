#include "pt4.h"
#include "mpi.h"
#include <vector>
using namespace std;
void Solve()
{
    Task("MPI6File2");
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
    int val = 0, posv = 0;

    MPI_File f;
    MPI_File_open(MPI_COMM_WORLD, name, MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &f);

    if (rank != 0)
    {
        int n = 0;
        pt >> n;
        vector<int> num;
        vector<int> pos;
        for (int i = 0; i < n; i++)
        {
            pt >> posv;
            pt >> val;
            pos.push_back(posv);
            num.push_back(val);
        }

        MPI_Status stat;
        for (int i = 0; i < pos.size(); i++)
        {
            MPI_Offset offset;
            MPI_File_write_at(f, (pos[i] - 1)  * sizeof(int), &num[i], 1, MPI_INT, &stat); 
        }

    }
    MPI_File_close(&f);
}

