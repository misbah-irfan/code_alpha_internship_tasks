#include <stdio.h>

#define MAX 10

void readMatrix(int m[MAX][MAX], int r, int c, const char *name) {
    printf("Enter elements of matrix %s (%dx%d):\n", name, r, c);
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            scanf("%d", &m[i][j]);
}

void displayMatrix(int m[MAX][MAX], int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)
            printf("%5d", m[i][j]);
        printf("\n");
    }
}

void addMatrices(int a[MAX][MAX], int b[MAX][MAX], int res[MAX][MAX], int r, int c) {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            res[i][j] = a[i][j] + b[i][j];
}

void multiplyMatrices(int a[MAX][MAX], int b[MAX][MAX], int res[MAX][MAX],
                      int r1, int c1, int c2) {
    for (int i = 0; i < r1; i++)
        for (int j = 0; j < c2; j++) {
            res[i][j] = 0;
            for (int k = 0; k < c1; k++)
                res[i][j] += a[i][k] * b[k][j];
        }
}

void transposeMatrix(int a[MAX][MAX], int res[MAX][MAX], int r, int c) {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            res[j][i] = a[i][j];
}

int readDims(int *r, int *c) {
    if (scanf("%d %d", r, c) != 2 || *r < 1 || *c < 1 || *r > MAX || *c > MAX) {
        printf("Invalid size (1 to %d allowed).\n", MAX);
        return 0;
    }
    return 1;
}

int main(void) {
    int a[MAX][MAX], b[MAX][MAX], res[MAX][MAX];
    int r1, c1, r2, c2, choice;

    do {
        printf("\n=== Matrix Operations ===\n");
        printf("1. Addition\n2. Multiplication\n3. Transpose\n4. Exit\n");
        printf("Choose: ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                printf("Enter rows and columns: ");
                if (!readDims(&r1, &c1)) break;
                readMatrix(a, r1, c1, "A");
                readMatrix(b, r1, c1, "B");
                addMatrices(a, b, res, r1, c1);
                printf("A + B =\n");
                displayMatrix(res, r1, c1);
                break;
            case 2:
                printf("Enter rows and columns of A: ");
                if (!readDims(&r1, &c1)) break;
                printf("Enter rows and columns of B: ");
                if (!readDims(&r2, &c2)) break;
                if (c1 != r2) {
                    printf("Error: columns of A must equal rows of B.\n");
                    break;
                }
                readMatrix(a, r1, c1, "A");
                readMatrix(b, r2, c2, "B");
                multiplyMatrices(a, b, res, r1, c1, c2);
                printf("A x B =\n");
                displayMatrix(res, r1, c2);
                break;
            case 3:
                printf("Enter rows and columns: ");
                if (!readDims(&r1, &c1)) break;
                readMatrix(a, r1, c1, "A");
                transposeMatrix(a, res, r1, c1);
                printf("Transpose =\n");
                displayMatrix(res, c1, r1);
                break;
            case 4:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 4);
    return 0;
}
