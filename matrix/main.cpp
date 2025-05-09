#include <iostream>
#include "matrix.h"

using namespace std;

int main() {
    int size;
    cout << "Enter the size of the square matrix: ";
    while (!(cin >> size) || size <= 0) {
        cout << "Invalid size. Enter a positive integer: ";
        cin.clear();
        char ch;
        while (cin.get(ch) && ch != '\n'); 
    }

    double** matrix = allocateMatrix(size);
    cout << "Enter " << size * size << " matrix elements:" << endl;
    if (!readMatrix(matrix, size)) {
        cout << "Input error. Exiting.\n";
        freeMatrix(matrix, size);
        return 1;
    }

    CSR csr = convertToCSR(matrix, size);
    freeMatrix(matrix, size);

    double a;
    cout << "Enter the number a: ";
    while (!(cin >> a)) {
        cout << "Invalid input. Enter a number: ";
        cin.clear();
        char ch;
        while (cin.get(ch) && ch != '\n');
    }

    subtractAI(csr, size, a);
    printCSR(csr);

    freeCSR(csr);
    return 0;
}
