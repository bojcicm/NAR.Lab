#include <iostream>
#include <thread>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <stdlib.h>     /* srand, rand */

#define N 200000

using namespace std;

void initArrayWithRandomNumbers(int *ArrayToInit, int LastIndex)
{
	for (int i = 0; i < LastIndex; i++)
	{
		ArrayToInit[i] = rand() % 100 + 1;
	}
}

long int suma()
{
	int nizBrojeva[N];
	long int suma;

	srand(time(NULL));
	initArrayWithRandomNumbers(nizBrojeva, N);

	for (int j = 0; j < 100; j++) {
		suma = 0;
		for (int i = 0; i < N; i++)
			suma += nizBrojeva[i];
	}

	return suma;
}

void sumaRunnner(int ThreadId)
{
	cout << "thread " << ThreadId << " started" << endl;

	cout << "Suma["<< ThreadId <<"]: " << suma() << endl;

	cout << "thread " << ThreadId << " ended" << endl;
}

void paralelThreadRunner(int NumberOfThreads)
{
	thread* Threads = new thread[NumberOfThreads];

	std::clock_t c_start = std::clock();
	auto t_start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < NumberOfThreads; i++)
	{
		Threads[i] = thread(sumaRunnner, i);
	}
	for (int i = 0; i < NumberOfThreads; i++)
	{
		Threads[i].join();
	}

	std::clock_t c_end = std::clock();
	auto t_end = std::chrono::high_resolution_clock::now();

	std::cout << "\n==============\n" << std::fixed << std::setprecision(2) << "CPU time used: "
		<< 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << " ms\n"
		<< "Wall clock time passed: "
		<< std::chrono::duration<double, std::milli>(t_end - t_start).count()
		<< " ms\n";

}

void serialThreadRunner(int NumberOfThreads)
{
	thread* Threads = new thread[NumberOfThreads];

	std::clock_t c_start = std::clock();
	auto t_start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < NumberOfThreads; i++)
	{
		Threads[i] = thread(sumaRunnner, i);
		Threads[i].join();
	}

	std::clock_t c_end = std::clock();
	auto t_end = std::chrono::high_resolution_clock::now();

	std::cout << "\n==============\n" << std::fixed << std::setprecision(2) << "CPU time used: "
		<< 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << " ms\n"
		<< "Wall clock time passed: "
		<< std::chrono::duration<double, std::milli>(t_end - t_start).count()
		<< " ms\n";
}


int main()
{
	cout << "Serijski\n" << endl;
	serialThreadRunner(12);
	cout << "\n============================================================\n" << endl;
	cout << "Paralelno\n" << endl;
	paralelThreadRunner(12);
}