#ifndef ELLMATRIX_H
#define ELLMATRIX_H

#include "common.h"

class ELLMatrix
{
private:
        int **values;
        int **columns;
        int max_nnz;
public:
	ELLMatrix(int rows, int cols, int **Mat);
        void MultiplySimple(int rows, int *result, int *Vect);
        void PrintMatrix(int rows);
        void MultiplyPthread(int tid,int partition_size_start,int partition_size_end,int *Vect,int *result);
};
#endif
