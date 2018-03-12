#include "SparseMatrix.h"


int main(int argc, char *argv[])
{


 int rows = atoi(argv[1]);
 int cols = atoi(argv[2]);
 float sparsity = atof(argv[3]);
 int num_threads = atoi(argv[4]);
 int option =      atoi(argv[5]);
 int repeats   =   atoi(argv[6]); 

 int  ** Mat = new int*[rows];
 int  *Vect  = new int[rows];
 int  *result_simple = new int [rows];
 int  *result_csr = new int[rows];
 int  *result_ell = new int[rows]; 
 int  *result_csr_pthread = new int[rows];
 int  *result_ell_pthread = new int[rows];


 int partition_size = rows / num_threads;
 int partition_last_thread = rows % num_threads;
 
 auto start = std::chrono::system_clock::now();;
 auto end   = std::chrono::system_clock::now();;
 std::chrono::duration<double> elapsed_seconds;
 std::time_t end_time;
 

 CreateArray(Mat, rows, cols, sparsity);
 CreateVector(Vect,rows);
// CreateHistogram(Mat, rows, cols);

 int num_nnz_elements = (1 - sparsity)*rows*cols;
 CSRMatrix csr(rows,cols,num_nnz_elements,Mat);
 ELLMatrix ell(rows, cols, Mat); 

 switch(option) {
	case 1:
		start = std::chrono::system_clock::now();
                for(int i = 0; i < repeats; i++)
			SpMVThreaded(Mat, Vect, rows, cols, partition_size, partition_last_thread, result_simple, num_threads);
                end = std::chrono::system_clock::now(); 
                elapsed_seconds = end-start;
                end_time = std::chrono::system_clock::to_time_t(end);
                std::cout << "Dense format multiply: " << elapsed_seconds.count() << "s\n";
		break; 
         case 2:		
                start = std::chrono::system_clock::now();
                for(int i = 0; i < repeats; i++)
                	Spmv(csr, &CSRMatrix::MultiplyPthread,num_threads,partition_size,partition_last_thread,Vect,result_csr_pthread);
                end = std::chrono::system_clock::now();
                elapsed_seconds = end-start;
                std::cout << "Time for CSR " << elapsed_seconds.count() << "s\n";
                break;
          case 3:
                start = std::chrono::system_clock::now();
                for(int i = 0; i < repeats; i++)
                	Spmv(ell, &ELLMatrix::MultiplyPthread,num_threads,partition_size,partition_last_thread,Vect,result_ell_pthread);
                end = std::chrono::system_clock::now();
                elapsed_seconds = end-start;
                std::cout << "Time for ELL " << elapsed_seconds.count() << "s\n";
                break;
          }

}
