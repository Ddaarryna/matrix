#include <iostream>
#include "matrix.h"

using namespace std;

double** allocateMatrix(int size) {
    double** matrix = new double* [size];
    for (int i = 0; i < size; ++i)
        matrix[i] = new double[size];
    return matrix;
}

void freeMatrix(double** matrix, int size) {
    for (int i = 0; i < size; ++i)
        delete[] matrix[i];
    delete[] matrix;
}

bool readMatrix(double** matrix, int size) {
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            if (!(cin >> matrix[i][j])) return false;
    return true;
}

CSR convertToCSR(double** matrix, int size) {
    int capacity = size * size;
    CSR csr;
    csr.values = new double[capacity];
    csr.colIndices = new int[capacity];
    csr.rowPointers = new int[size + 1];

    int idx = 0;
    for (int i = 0; i < size; ++i) {
        csr.rowPointers[i] = idx;
        for (int j = 0; j < size; ++j) {
            if (matrix[i][j] != 0) {
                csr.values[idx] = matrix[i][j];
                csr.colIndices[idx] = j;
                ++idx;
            }
        }
    }
    csr.rowPointers[size] = idx;
    csr.nnz = idx;
    return csr;
}

void subtractAI(CSR& csr, int size, double a) {
    for (int i = 0; i < size; ++i) {
        bool hasDiagonal = false;
        for (int k = csr.rowPointers[i]; k < csr.rowPointers[i + 1]; ++k) {
            if (csr.colIndices[k] == i) {
                csr.values[k] -= a;
                hasDiagonal = true;
                break;
            }
        }

        if (!hasDiagonal && a != 0) {
            int insertAt = csr.rowPointers[i + 1];
            for (int k = csr.rowPointers[i]; k < csr.rowPointers[i + 1]; ++k) {
                if (csr.colIndices[k] > i) {
                    insertAt = k;
                    break;
                }
            }

            double* newVals = new double[csr.nnz + 1];
            int* newCols = new int[csr.nnz + 1];

            for (int k = 0; k < insertAt; ++k) {
                newVals[k] = csr.values[k];
                newCols[k] = csr.colIndices[k];
            }

            newVals[insertAt] = -a;
            newCols[insertAt] = i;

            for (int k = insertAt; k < csr.nnz; ++k) {
                newVals[k + 1] = csr.values[k];
                newCols[k + 1] = csr.colIndices[k];
            }

            delete[] csr.values;
            delete[] csr.colIndices;
            csr.values = newVals;
            csr.colIndices = newCols;
            ++csr.nnz;

            for (int j = i + 1; j <= size; ++j)
                ++csr.rowPointers[j];
        }
    }
}

void printCSR(const CSR& csr) {
    cout << "\nCSR format:\n";
    cout << "values: ";
    for (int i = 0; i < csr.nnz; ++i)
        cout << csr.values[i] << " ";
    cout << "\ncolIndices: ";
    for (int i = 0; i < csr.nnz; ++i)
        cout << csr.colIndices[i] << " ";
    cout << "\nrowPointers: ";
    for (int i = 0; i <= csr.rowPointers[0] + csr.nnz; ++i)
        cout << csr.rowPointers[i] << " ";
    cout << endl;
}

void freeCSR(CSR& csr) {
    delete[] csr.values;
    delete[] csr.colIndices;
    delete[] csr.rowPointers;
}
