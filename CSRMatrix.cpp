#include "CSRMatrix.h"

CSRMatrix::CSRMatrix(int rows, int cols,int num_nnz, int **Mat)
{
        nnz_values = new int[num_nnz];
        col_ind    = new int[num_nnz];
        row_ptr    = new int[rows + 1];
        row_counts = new int[rows];
        num_nnz    = num_nnz;
        rows = rows;
        cols = cols;

        int k = 0;
        int num_elements_in_row = 0;
       
        for(int i = 0 ; i < rows; i ++)
         {
         num_elements_in_row = 0;
         for(int j = 0; j < cols; j++)
           {
             if(Mat[i][j]) {
                 nnz_values[k] = Mat[i][j];
                 col_ind[k]    =  j;
                 k++;
                 num_elements_in_row =  num_elements_in_row + 1;
                }
          }
           row_counts[i] = num_elements_in_row;
         }

       int sum = 0;
       row_ptr[0] = 0;

        for(int i = 1; i < rows; i++)
        {
         sum = 0;
         for(int j = i - 1 ; j >= 0; j--)
         {
           sum = sum + row_counts[j];
         }
           row_ptr[i] = sum;
        }
       row_ptr[rows] = num_nnz;
       delete [] row_counts;
}


void CSRMatrix::MultiplySimple(int rows, int *result, int *Vect)
{
 
 for(int i = 0; i < rows; i++) {
    result[i] = 0;
  for(int j = row_ptr[i]; j < row_ptr[i+1];j++)
	result[i] += nnz_values[j] * Vect[col_ind[j]];
   
  }

  printf("\n\n");
}

void CSRMatrix::MultiplyPthread(int tid,int partition_size_start,int partition_size_end,int *Vect,int *result)
{
 int start = (tid)*partition_size_start;
 int end   = start + partition_size_end;

 for(int i = start; i < end; i++) {
	result[i] = 0;
  for(int j = row_ptr[i]; j < row_ptr[i+1];j++)
	result[i] += nnz_values[j] * Vect[col_ind[j]];
  }

}

void CSRMatrix::PrintMatrix(int rows,int cols,int num_nnz)
{

       printf("---Printing Value Array--- \n");

       for(int i = 0; i < num_nnz; i++)
           printf("%d  ", nnz_values[i]);

       printf("\n---Printing Col index--- \n");

       for(int i = 0; i < num_nnz; i++)
           printf("%d  ", col_ind[i]);

       printf("\n---Printing Row pointer--- \n");

       for(int i = 0; i <= rows ; i++)
          printf("%d ", row_ptr[i]);

       printf("\n\n\n");
}

CSRMatrix::~CSRMatrix(void) {

   }
