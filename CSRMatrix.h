#ifndef CSRMATRIX_H
#define CSRMATRIX_H

#include "common.h"

class CSRMatrix
{
 private:
        int rows;
        int cols;
        int    *nnz_values;
        int    *col_ind;
        int    *row_ptr;
        int    *row_counts;
        int    num_nnz;

 public:
	CSRMatrix(int rows, int cols,int num_nnz, int **Mat);
        void PrintMatrix(int rows,int cols,int num_nnz);
        void MultiplySimple(int rows, int *result, int *Vect);
	void MultiplyPthread(int tid,int partition_size_start,int partition_size_end,int *Vect,int *result);
        ~CSRMatrix(void);
};
#endif
