//Copyright Miruna-elena Iliescu 312CAb 2023-2024
#include <stdio.h>
#include <stdlib.h>
#include "Validate.h"
#include "Matrix.h"

#define D 0

// Function to add two matrices
void add(int **A, int **B, int **C, int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			C[i][j] = modulo_positive(A[i][j] + B[i][j]);
}

// Function to subtract two arrays
void sub(int **A, int **B, int **C, int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			C[i][j] = modulo_positive(A[i][j] - B[i][j]);
}

// Function to multiply two matrices using Strassen's algorithm
void mul(int **A, int **B, int **C, int size)
{
	if (size == 1) {
		C[0][0] = modulo_positive(A[0][0] * B[0][0]); return;
	}
	int z = size / 2;
	int **A11 = (int **)malloc(z * sizeof(int *));
	int **A12 = (int **)malloc(z * sizeof(int *));
	int **A21 = (int **)malloc(z * sizeof(int *));
	int **A22 = (int **)malloc(z * sizeof(int *));
	int **B11 = (int **)malloc(z * sizeof(int *));
	int **B12 = (int **)malloc(z * sizeof(int *));
	int **B21 = (int **)malloc(z * sizeof(int *));
	int **B22 = (int **)malloc(z * sizeof(int *));
	int **C11 = (int **)malloc(z * sizeof(int *));
	int **C12 = (int **)malloc(z * sizeof(int *));
	int **C21 = (int **)malloc(z * sizeof(int *));
	int **C22 = (int **)malloc(z * sizeof(int *));
	int **M1 = (int **)malloc(z * sizeof(int *));
	int **M2 = (int **)malloc(z * sizeof(int *));
	int **M3 = (int **)malloc(z * sizeof(int *));
	int **M4 = (int **)malloc(z * sizeof(int *));
	int **M5 = (int **)malloc(z * sizeof(int *));
	int **M6 = (int **)malloc(z * sizeof(int *));
	int **M7 = (int **)malloc(z * sizeof(int *));
	for (int i = 0; i < z; i++) {
		A11[i] = (int *)malloc(z * sizeof(int));
		A12[i] = (int *)malloc(z * sizeof(int));
		A21[i] = (int *)malloc(z * sizeof(int));
		A22[i] = (int *)malloc(z * sizeof(int));
		B11[i] = (int *)malloc(z * sizeof(int));
		B12[i] = (int *)malloc(z * sizeof(int));
		B21[i] = (int *)malloc(z * sizeof(int));
		B22[i] = (int *)malloc(z * sizeof(int));
		C11[i] = (int *)malloc(z * sizeof(int));
		C12[i] = (int *)malloc(z * sizeof(int));
		C21[i] = (int *)malloc(z * sizeof(int));
		C22[i] = (int *)malloc(z * sizeof(int));
		M1[i] = (int *)malloc(z * sizeof(int));
		M2[i] = (int *)malloc(z * sizeof(int));
		M3[i] = (int *)malloc(z * sizeof(int));
		M4[i] = (int *)malloc(z * sizeof(int));
		M5[i] = (int *)malloc(z * sizeof(int));
		M6[i] = (int *)malloc(z * sizeof(int));
		M7[i] = (int *)malloc(z * sizeof(int));
	}
	for (int i = 0; i < z; i++) {
		for (int j = 0; j < z; j++) {
			A11[i][j] = A[i][j]; A12[i][j] = A[i][j + z];
			A21[i][j] = A[i + z][j]; A22[i][j] = A[i + z][j + z];
			B11[i][j] = B[i][j]; B12[i][j] = B[i][j + z];
			B21[i][j] = B[i + z][j]; B22[i][j] = B[i + z][j + z];
		}
	}
	add(A11, A22, C11, z); add(B11, B22, C12, z); mul(C11, C12, M1, z);
	add(A21, A22, C11, z); mul(C11, B11, M2, z); sub(B12, B22, C11, z);
	mul(A11, C11, M3, z); sub(B21, B11, C11, z); mul(A22, C11, M4, z);
	add(A11, A12, C11, z); mul(C11, B22, M5, z); sub(A21, A11, C11, z);
	add(B11, B12, C12, z); mul(C11, C12, M6, z); sub(A12, A22, C11, z);
	add(B21, B22, C12, z); mul(C11, C12, M7, z); add(M1, M4, A11, z);
	sub(A11, M5, A12, z); add(A12, M7, C11, z); add(M3, M5, C12, z);
	add(M2, M4, C21, z); add(M1, M3, A11, z); sub(A11, M2, A12, z);
	add(A12, M6, C22, z); 
	for (int i = 0; i < z; i++) {
		for (int j = 0; j < z; j++) {
			C[i][j] = C11[i][j]; C[i][j + z] = C12[i][j];
			C[i + z][j] = C21[i][j]; C[i + z][j + z] = C22[i][j];
		}
	}
	for (int i = 0; i < z; i++) {
		free(A11[i]); free(A12[i]); free(A21[i]); free(A22[i]); free(B11[i]);
		free(B12[i]); free(B21[i]); free(B22[i]); free(C11[i]); free(C12[i]);
		free(C21[i]); free(C22[i]);	free(M1[i]); free(M2[i]); free(M3[i]);
		free(M4[i]); free(M5[i]); free(M6[i]); free(M7[i]);
	}
	free(A11); free(A12); free(A21); free(A22); free(B11); free(B12);
	free(B21); free(B22); free(C11); free(C12); free(C21); free(C22);
	free(M1); free(M2); free(M3); free(M4); free(M5); free(M6); free(M7);
}

int **strassen_multiply(int **qlx, int **qcx, int l){
	int **a = init_alloc_matrix(l, l, -1);
	mul(qlx, qcx, a, l);
	return a;
}
