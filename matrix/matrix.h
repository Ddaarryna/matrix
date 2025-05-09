#pragma once
struct CSR {
    double* values;
    int* colIndices;
    int* rowPointers;
    int nnz;
};

double** allocateMatrix(int size);
void freeMatrix(double** matrix, int size);
bool readMatrix(double** matrix, int size);

CSR convertToCSR(double** matrix, int size);
void subtractAI(CSR& csr, int size, double a);
void printCSR(const CSR& csr);
void freeCSR(CSR& csr);


