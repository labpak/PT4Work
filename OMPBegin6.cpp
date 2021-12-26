#include "pt4.h"
#include "omp.h"

double np_F(double x, int n)
{
	double res = 0.0;
	for (int i = 1; i <= n; i++)
	{
		double z = 0.0;
		for (int j = 1; j <= i + n; j++)
		{
			z += (j + sin(x + j)) / (2 * i * j - 1);
		}
		res += 1 / z;
	}
	return res;
}

double p_F(double x, int n)
{
	double res = 0.0;
	#pragma omp parallel num_threads(4) reduction(+:res)
	{
		int num = omp_get_thread_num();
		int num_threads = omp_get_num_threads();
		int num_procs = omp_get_num_procs();
		int count = 0;
		double time = omp_get_wtime();
		if (num == 0) 
		{
			Show("num_procs: ", num_procs);
			ShowLine();
			Show("num_threads: ", num_threads);
			ShowLine();
		}
		for (int i = 1; i <= n; i += 8) 
		{
			double z = 0.0;
			int i1 = i + num;
			int	i2 = i + 7 - num;
			for (int j = 1; j <= i1 + n; j++) 
			{
				z += (j + sin(x + j)) / (2 * i1 * j - 1);
				count++;
			}
			res += 1 / z;
			z = 0.0;
			for (int j = 1; j <= i2 + n; j++)
			{
				z += (j + sin(x + j)) / (2 * i2 * j - 1);
				count++;
			}
			res += 1 / z;
		}
		Show("thread_num: ", num);
		ShowLine();
		Show("Count: ", count);
		ShowLine();
		Show("Thread time: ", omp_get_wtime() - time);
		ShowLine();
	}
	return res;
}

void Solve()
{
	Task("OMPBegin6");

	//non parallel
	double x = 0.0, res = 0.0, start = omp_get_wtime();;
	int n = 0;
	pt >> x >> n;
	res = np_F(x, n);

	Show("Non-parallel time: ");
	double np_time = omp_get_wtime() - start;
	Show(np_time);
	ShowLine();
	pt << res;

	//parallel
	pt >> x >> n;
	start = omp_get_wtime();
	res = p_F(x, n);

	double p_time = omp_get_wtime() - start;
	Show("Total parallel time: ");
	Show(p_time);
	ShowLine();
	pt << res;
	Show("Rate: ");
	Show(np_time / p_time);
}
