# Sparse-mat
To compile use the following command:

g++ SparseMatrix.cpp CSRMatrix.cpp ELLMatrix.cpp helper.cpp -lpthread -std=c++0x -o sparse

#To run use the following pattern

./sparse M N Sparsity option NumRepetitions

where

1. M is the number of rows
2. N is the number of columns
3. Sparsity is the sparsity value of the matrix between 0 to 1
4. Option is 1 for dense, 2 for CSR, 3 for ELL
5. NumReptitions is the number of times you want to repeate the computation
