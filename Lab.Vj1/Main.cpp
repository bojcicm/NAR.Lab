#include <iostream>
#include <thread>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <stdlib.h>     /* srand, rand */

#define N 200000

using namespace std;

chrono::time_point<chrono::steady_clock> getClockTime();
void printTime(chrono::time_point<chrono::steady_clock> t_start, chrono::time_point<chrono::steady_clock> t_end);

void initArrayWithRandomNumbers(int *ArrayToInit, int LastIndex);
long int suma();

void sumaRunnner(int ThreadId);
void paralelThreadRunner(int NumberOfThreads);
void serialThreadRunner(int NumberOfThreads);


int main()
{
	for (auto i = 2; i < 15; i+=4)
	{
		cout << "Serijski " << i << " threadova\n" << endl;
		serialThreadRunner(i);
		cout << "\n============================================================\n" << endl;
		cout << "Paralelno " << i << " threadova\n" << endl;
		paralelThreadRunner(i);

		cout << "\n============================================================" << endl;
		cout << "\n============================================================\n" << endl;
	}
}

chrono::time_point<chrono::steady_clock> getClockTime()
{
	return std::chrono::high_resolution_clock::now();
}

void printTime(chrono::time_point<chrono::steady_clock> t_start, chrono::time_point<chrono::steady_clock> t_end)
{
	cout << "\n==============\n"
		<< "Wall clock time passed: "
		<< chrono::duration<double, std::milli>(t_end - t_start).count()
		<< " ms\n";
}

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

	cout << "Suma[" << ThreadId << "]: " << suma() << endl;

	cout << "thread " << ThreadId << " ended" << endl;
}

void paralelThreadRunner(int NumberOfThreads)
{
	auto* Threads = new thread[NumberOfThreads];
	auto t_start = getClockTime();

	for (int i = 0; i < NumberOfThreads; i++)
	{
		Threads[i] = thread(sumaRunnner, i);
	}
	for (int i = 0; i < NumberOfThreads; i++)
	{
		Threads[i].join();
	}

	auto t_end = getClockTime();
	printTime(t_start, t_end);

	delete[] Threads;

}

void serialThreadRunner(int NumberOfThreads)
{
	auto* Threads = new thread[NumberOfThreads];
	auto t_start = getClockTime();

	for (auto i = 0; i < NumberOfThreads; i++)
	{
		Threads[i] = thread(sumaRunnner, i);
		Threads[i].join();
	}

	auto t_end = getClockTime();
	printTime(t_start, t_end);

	delete[] Threads;
}