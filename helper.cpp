#include "helper.h"

void CreateVector(int *Vect, int rows)
{

for(int i = 0; i < rows; i++)
{
 Vect[i] = int((rand()%(10))+1);

}
}


void CreateHistogram(int **Mat, int rows, int cols)
{
 int *nnz_per_row = new int[rows];

 for(int i = 0; i < rows; i++)
 {
  for(int j = 0; j < cols; j++)
  {

   if(Mat[i][j])
	nnz_per_row[i] = nnz_per_row[i] + 1;
  }
 }
 
 for(int i = 0; i < rows; i++)
	printf("%d \n", nnz_per_row[i]);
}

void CreateArray(int **Mat, int rows, int cols, float sparsity)
{
 srand((unsigned)time(0));
 int num_nnz_elements = (1 - sparsity)*rows*cols;

 for(int i = 0; i < rows; i++)
     Mat[i] = new int[cols];

 for (int i = 0; i < rows; i++)
  {
   for(int j = 0; j < cols; j++)
   {
    Mat[i][j] = 0;
   }
  }

  for (int i = 0; i < num_nnz_elements;) {
   int s_rows = rand() % (rows);
   int s_cols = rand() % (cols);

   if(Mat[s_rows][s_cols])
        continue;

   Mat[s_rows][s_cols] =  int((rand()%(10))+1);
   i++;
   }
}

void PrintArray(int **Mat, int rows, int cols)
{
  for(int i = 0; i < rows; i++)
        {
         for(int j = 0; j < cols; j++)
           {
             printf("%6d  ",Mat[i][j]);

           }

       }
   printf("\n \n \n");
}


void PrintVector(int *Vect,int rows)
{
 for(int i = 0; i < rows; i++)
  {
    printf("%d ",Vect[i]);
  }
  printf("\n\n");
}


void SimpleSpMV(int **Mat, int *Vect, int rows, int cols, int *result)
{

for(int i = 0; i < rows; i++)
 {
   for(int j = 0; j < cols; j++)
    {
      result[i] = result[i] + Mat[i][j]*Vect[j];

    }
}
}

void SpMVMultiply(int tid, int partition_size_start, int partition_size_end,int **Mat, int *Vect,int *result,int rows,int cols)
{

 int start = (tid)*partition_size_start;
 int end   = start + partition_size_end;

 for(int i = start; i < end; i++)
 {
   for(int j = 0; j < cols; j++)
    {
      result[i] = result[i] + Mat[i][j]*Vect[j];

    }
}
}

void SpMVThreaded(int **Mat, int *Vect, int rows, int cols, int partition_size, int partition_last_thread, int *result, int num_threads)
{

vector <thread> threads;

for(int i = 0; i < num_threads-1; i++)
        threads.push_back(thread(SpMVMultiply,i,partition_size,partition_size,Mat,Vect,result,rows,cols));

if(partition_last_thread != 0)
        threads.push_back(thread(SpMVMultiply,num_threads-1,partition_size,partition_size+partition_last_thread,Mat,Vect,result,rows,cols));
 else
        threads.push_back(thread(SpMVMultiply,num_threads-1,partition_size,partition_size,Mat,Vect,result,rows,cols));

for (vector<thread>::iterator it = threads.begin() ; it != threads.end() ; ++it)
    {
        it->join();
    }

}
