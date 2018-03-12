#ifndef SPMVHELPER_H
#define SPMVHELPER_H


#include <vector>
#include <thread>
#include "CSRMatrix.h"
#include "ELLMatrix.h"
#include <chrono>
#include <ctime>

using namespace std;

template <typename OBJECT, typename FUNC>
void Spmv(OBJECT obj, FUNC func, int num_threads, int partition_size,int partition_last_thread, int *Vect, int *result)
{
vector <thread> threads;

 for(int i = 0; i < num_threads-1; i++)
        threads.push_back(thread(func,obj,i,partition_size,partition_size,Vect,result));

 if(partition_last_thread != 0)
        threads.push_back(thread(func,obj,num_threads-1,partition_size,partition_size+partition_last_thread,Vect,result));
 else
        threads.push_back(thread(func,obj,num_threads-1,partition_size,partition_size,Vect,result));

for (vector<thread>::iterator it = threads.begin() ; it != threads.end() ; ++it)
    {
        it->join();
    }
}
void CreateHistogram(int **Mat, int rows, int cols);
void CreateVector(int *Vect, int rows);
void CreateArray(int **Mat, int rows, int cols, float sparsity);
void PrintArray(int **Mat, int rows, int cols);
void PrintVector(int *Vect,int rows);
void SimpleSpMV(int **Mat, int *Vect, int rows, int cols, int *result);
void SpMVThreaded(int **Mat, int *Vect, int rows, int cols, int partition_size, int partition_last_thread, int *result, int num_threads);
void SpMVMultiply(int tid, int partition_size_start, int partition_size_end,int **Mat, int *Vect,int *result,int rows,int cols);
#endif
