//multiplication
#include <stdio.h>
#include <stdlib.h>
#define MAX 100
// Structure to represent a sparse matrix entry
typedef struct {
    int row;
    int col;
    int value;
} SparseEntry;

// Function to convert a normal matrix to sparse matrix representation
void convertToSparse(int rows, int cols, int normalMatrix[rows][cols], SparseEntry sparseMatrix[]) {
    int k = 1; // Index for sparse matrix entries (starting after header)
    sparseMatrix[0].row = rows;
    sparseMatrix[0].col = cols;
    sparseMatrix[0].value = 0; // This will be updated with the total number of non-zero elements

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (normalMatrix[i][j] != 0) {
                sparseMatrix[k].row = i;
                sparseMatrix[k].col = j;
                sparseMatrix[k].value = normalMatrix[i][j];
                k++;
            }
        }
    }
    sparseMatrix[0].value = k - 1; // Total number of non-zero elements
}

// Function to print a sparse matrix
void printSparseMatrix(SparseEntry sparseMatrix[]) {
    int n = sparseMatrix[0].value; // Number of non-zero elements
    printf("\nSparse Matrix Representation:\n");
    printf("Row\tCol\tValue\n");
    for (int i = 0; i <= n; i++) {
        printf("%d\t%d\t%d\n", sparseMatrix[i].row, sparseMatrix[i].col, sparseMatrix[i].value);
    }
}

// Function to multiply two sparse matrices
void multiplySparseMatrices(SparseEntry matA[], SparseEntry matB[], SparseEntry result[]) {
    if (matA[0].col != matB[0].row) {
        printf("Multiplication not possible! Number of columns in Matrix A must be equal to the number of rows in Matrix B.\n");
        result[0].value = 0; // Indicating no valid multiplication
        return;
    }

    int rowsA = matA[0].row, colsB = matB[0].col;
    int tempResult[rowsA][colsB];
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            tempResult[i][j] = 0; // Initialize result matrix as zero
        }
    }

    // Sparse matrix multiplication
    for (int i = 1; i <= matA[0].value; i++) {
        for (int j = 1; j <= matB[0].value; j++) {
            if (matA[i].col == matB[j].row) {
                tempResult[matA[i].row][matB[j].col] += matA[i].value * matB[j].value;
            }
        }
    }

    // Convert the resultant normal matrix to sparse representation
    int k = 1;
    result[0].row = rowsA;
    result[0].col = colsB;
    result[0].value = 0;

    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            if (tempResult[i][j] != 0) {
                result[k].row = i;
                result[k].col = j;
                result[k].value = tempResult[i][j];
                k++;
            }
        }
    }

    result[0].value = k - 1; // Total non-zero values
}

// Main function
int main() {
    int rows1, cols1, rows2, cols2;

    // Input Matrix A
    printf("Enter number of rows and columns for Matrix A: ");
    scanf("%d %d", &rows1, &cols1);

    int matrixA[rows1][cols1];
    printf("Enter elements of Matrix A:\n");
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            scanf("%d", &matrixA[i][j]);
        }
    }

    // Input Matrix B
    printf("Enter number of rows and columns for Matrix B: ");
    scanf("%d %d", &rows2, &cols2);

    int matrixB[rows2][cols2];
    printf("Enter elements of Matrix B:\n");
    for (int i = 0; i < rows2; i++) {
        for (int j = 0; j < cols2; j++) {
            scanf("%d", &matrixB[i][j]);
        }
    }

    // Convert to Sparse Matrix Representations
    SparseEntry sparseA[MAX], sparseB[MAX], sparseResult[MAX];
    convertToSparse(rows1, cols1, matrixA, sparseA);
    convertToSparse(rows2, cols2, matrixB, sparseB);

    printf("\nSparse Matrix A:");
    printSparseMatrix(sparseA);

    printf("\nSparse Matrix B:");
    printSparseMatrix(sparseB);

    // Perform Multiplication
    multiplySparseMatrices(sparseA, sparseB, sparseResult);

    // Print Result
    if (sparseResult[0].value > 0) {
        printf("\nResultant Sparse Matrix (A * B):");
        printSparseMatrix(sparseResult);
    }

    return 0;
}
