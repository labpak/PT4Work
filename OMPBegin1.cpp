#include "pt4.h"
#include "omp.h"

double np_F(double x, int n) 
{
	double res = 0.0;
	for (int i = 1; i <= n; i++) 
	{
		double z = 0.0;
		for (int j = 1; j <= i; j++) 
		{
			z += (j + pow((x + j), 1 / 3.0)) / (2 * i * j - 1);
		}
		res += 1 / z;
	}
	return res;
}

double p_F(double x, int n)
{
	auto res = 0.0;
#pragma omp parallel num_threads(2) reduction(+:res)
	{
		auto num = omp_get_thread_num();
		auto num_threads = omp_get_num_threads();
		auto num_procs = omp_get_num_procs();
		auto count = 0;
		auto time = omp_get_wtime();
		if (num == 0)
		{
			Show("num_procs: ", num_procs);
			ShowLine();
			Show("num_threads: ", num_threads);
			ShowLine();
		}

		for (int i = num + 1; i <= n; i += 2)
		{
			auto z = 0.0;
			for (int j = 1; j <= i; j++)
			{
				z += (j + pow((x + j), 1 / 3.0)) / (2 * i * j - 1);
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
	Task("OMPBegin1");
	
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
