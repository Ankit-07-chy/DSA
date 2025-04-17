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

// Function to convert sparse matrix back to normal matrix
void convertToNormal(SparseEntry sparseMatrix[], int rows, int cols, int normalMatrix[rows][cols]) {
    // Initialize matrix with zeros
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            normalMatrix[i][j] = 0;
        }
    }

    // Fill the non-zero elements from sparse representation
    for (int i = 1; i <= sparseMatrix[0].value; i++) {
        normalMatrix[sparseMatrix[i].row][sparseMatrix[i].col] = sparseMatrix[i].value;
    }
}

// Function to add two sparse matrices
void addSparseMatrices(SparseEntry sparseMatrix1[], SparseEntry sparseMatrix2[], SparseEntry result[]) {
    if (sparseMatrix1[0].row != sparseMatrix2[0].row || sparseMatrix1[0].col != sparseMatrix2[0].col) {
        printf("Addition not possible! Sparse matrices must have the same dimensions.\n");
        return;
    }

    int i = 1, j = 1, k = 1;
    result[0].row = sparseMatrix1[0].row;
    result[0].col = sparseMatrix1[0].col;
    result[0].value = 0;

    while (i <= sparseMatrix1[0].value && j <= sparseMatrix2[0].value) {
        if (sparseMatrix1[i].row < sparseMatrix2[j].row || 
            (sparseMatrix1[i].row == sparseMatrix2[j].row && sparseMatrix1[i].col < sparseMatrix2[j].col)) {
            result[k] = sparseMatrix1[i];
            i++;
        } else if (sparseMatrix2[j].row < sparseMatrix1[i].row || 
            (sparseMatrix1[i].row == sparseMatrix2[j].row && sparseMatrix2[j].col < sparseMatrix1[i].col)) {
            result[k] = sparseMatrix2[j];
            j++;
        } else {
            result[k].row = sparseMatrix1[i].row;
            result[k].col = sparseMatrix1[i].col;
            result[k].value = sparseMatrix1[i].value + sparseMatrix2[j].value;
            i++;
            j++;
        }
        k++;
    }

    while (i <= sparseMatrix1[0].value) {
        result[k++] = sparseMatrix1[i++];
    }
    while (j <= sparseMatrix2[0].value) {
        result[k++] = sparseMatrix2[j++];
    }
    result[0].value = k - 1;
}

// Main function
int main() {
    int rows, cols;

    // Input normal matrix dimensions and elements
    printf("Enter number of rows and columns for the matrix: ");
    scanf("%d %d", &rows, &cols);

    int normalMatrix[rows][cols];
    printf("Enter elements of the matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &normalMatrix[i][j]);
        }
    }

    // Convert to sparse matrix representation
    SparseEntry sparseMatrix[MAX];
    convertToSparse(rows, cols, normalMatrix, sparseMatrix);
    printSparseMatrix(sparseMatrix);

    // Convert sparse matrix back to normal matrix and display
    int convertedMatrix[rows][cols];
    convertToNormal(sparseMatrix, rows, cols, convertedMatrix);
    printf("\nConverted Back to Normal Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", convertedMatrix[i][j]);
        }
        printf("\n");
    }

    // Sparse matrix addition demonstration
    printf("\nEnter elements of another matrix for addition:\n");
    int normalMatrix2[rows][cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &normalMatrix2[i][j]);
        }
    }

    SparseEntry sparseMatrix2[MAX];
    convertToSparse(rows, cols, normalMatrix2, sparseMatrix2);
    printSparseMatrix(sparseMatrix2);

    SparseEntry result[MAX];
    addSparseMatrices(sparseMatrix, sparseMatrix2, result);
    printSparseMatrix(result);

    return 0;
}
