#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <chrono>
#include <ctime>

using namespace std;
#define SIZE 10000   // Size by SIZE matrices
int num_thrd;   // number of threads
int A[SIZE][SIZE], B[SIZE];
unsigned int C[SIZE];

void init_matrix(int m[SIZE][SIZE]);
void init_vector(int v[SIZE]);
void print_matrix(int m[SIZE][SIZE]);
void print_vector(int v[SIZE]);
void* multiply(void* slice);
chrono::time_point<chrono::steady_clock> getClockTime();
void printTime(chrono::time_point<chrono::steady_clock> t_start, chrono::time_point<chrono::steady_clock> t_end);


int main()
{
	pthread_t* thread;  // pointer to a group of threads
	int i;

	for(auto trCtr = 2; trCtr < 9; trCtr +=2)
	{
		num_thrd = trCtr;
		init_matrix(A);
		init_vector(B);


		chrono::time_point<chrono::steady_clock> time1 = getClockTime();

		thread = (pthread_t*)malloc(num_thrd * sizeof(pthread_t));

		for (i = 1; i < num_thrd; i++)
		{
			if (pthread_create(&thread[i], NULL, multiply, (void*)i) != 0)
			{
				perror("Can't create thread");
				free(thread);
				exit(-1);
			}
		}
		multiply(0);
		for (i = 1; i < num_thrd; i++)
			pthread_join(thread[i], NULL);

		chrono::time_point<chrono::steady_clock> time2 = getClockTime();
		cout << "\nInit Matrix last element: ";
		print_matrix(A);
		cout << "\nInit Vector last element: ";
		print_vector(B);
		cout << "\nFinal result vector last element: " << C[SIZE - 1] << "\n";
		free(thread);
		cout << "Broj threadova: " << trCtr << endl;
		printTime(time1, time2);
	}
	

	return 0;
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

// thread function: taking "slice" as its argument
void* multiply(void* slice)
{
	int s = int(slice);   // retrive the slice info
	int from = (s * SIZE) / num_thrd; // note that this 'slicing' works fine
	int to = ((s + 1) * SIZE) / num_thrd; // even if SIZE is not divisible by num_thrd
	int i, k;
	cout << "Computing slice" << s << " (from row " << from << " to " << to - 1 << ")." << endl;
	for (i = from; i < to; i++)
	{
		C[i] = 0;
		for (k = 0; k < SIZE; k++)
		{
			C[i] += A[i][k] * B[k];
		}
	}
	cout << "Finished slice " << s << endl;
	return 0;
}

// initialize a matrix
void init_matrix(int m[SIZE][SIZE])
{
	int i, j, val = 0;
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
			m[i][j] = val++;
}

void init_vector(int v[SIZE])
{
	int i, val = 0;
	for (i = 0; i < SIZE; i++)
		v[i] = val++;
}

void print_matrix(int m[SIZE][SIZE])
{
	cout << m[SIZE - 1][SIZE - 1] << endl;
}

void print_vector(int v[SIZE])
{
	cout << v[SIZE - 1] << endl;
}