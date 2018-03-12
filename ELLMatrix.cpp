#include "ELLMatrix.h"

ELLMatrix::ELLMatrix(int rows, int cols, int **Mat)
{
      
        int *nnz_row = new int[rows];

        for(int i = 0; i < rows; i++)
                nnz_row[i] = 0;

        for(int i = 0; i < rows; i++)
        {
         for(int j = 0; j < cols; j++)
          {
           if(Mat[i][j])
                nnz_row[i] = nnz_row[i] + 1;
          }

        }

        max_nnz = 0;
        int curr_nnz = 0;

        for(int i = 0; i < rows; i++)
        {
         curr_nnz = nnz_row[i];
         if(curr_nnz > max_nnz)
                max_nnz = curr_nnz;
        }
        
        

        values =  new int*[rows];
        columns = new int*[rows];

        for(int i = 0; i < rows; i++)
         {
            values[i]  = new int[max_nnz];
            columns[i] = new int[max_nnz];
         }

         for(int i = 0; i < rows; i++)
           {
            for(int j = 0; j < max_nnz; j++)
             {
                values[i][j]  = 0;
                columns[i][j] = -1;
             }
           }

        int col_index = 0;
         for(int i = 0; i < rows; i++)
           {
            for(int j = 0; j < cols; j++)
             {
                if(Mat[i][j])
                   {
                        values[i][col_index]  = Mat[i][j];
                        columns[i][col_index] = j;
                        col_index++;
                   }
             }
            col_index = 0;
           }
}

void ELLMatrix::MultiplySimple(int rows,int *result,int *Vect)
{
 int col_val;

 for(int i = 0; i < rows; i++)
  {
   result[i] = 0;
   for(int j = 0; j < max_nnz;j++)
    {
    col_val = columns[i][j];
    if(col_val >= 0)
	result[i] = result[i] + values[i][j] * Vect[col_val];
   }
}

}

void ELLMatrix::MultiplyPthread(int tid,int partition_size_start,int partition_size_end,int *Vect,int *result)
{
 int start = (tid)*partition_size_start;
 int end   = start + partition_size_end;
 int col_val;

 for(int i = start; i < end; i++)
  {
   result[i] = 0;
   for(int j = 0; j < max_nnz;j++)
    {
    col_val = columns[i][j];
    if(col_val >= 0)
        result[i] = result[i] + values[i][j] * Vect[col_val];
   }
}

}

void ELLMatrix::PrintMatrix(int rows)
{
      
    printf("\n----Printing Values Matrix for ELL-----\n");
    for(int i = 0; i < rows; i++)
          {
           for(int j = 0; j < max_nnz; j++)
           {
             printf("%6d ",values[i][j]);
           }
            printf("\n");
         }
        printf("\n\n\n");

    printf("\n-----Printing Columns Matrix for ELL------\n");
    for(int i = 0; i < rows; i++)
          {
           for(int j = 0; j < max_nnz; j++)
           {
             printf("%6d ",columns[i][j]);
           }
            printf("\n");
         }
        printf("\n\n\n");
}
