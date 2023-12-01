#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include "Radix.h"


# define D 0  //debug messages
# define DD 0 //detail debug messages

// print_collection (collection, size, linesvector, columnsvector)
void print_collection(int ***a, int z, int *l, int *c)
{
	if (D)
		printf("print_collection /%d/\n", z);
	int i, j, k;
	for (k = 0; k < z; k++) {
		printf("#%d\n", k);
		for (i = 0; i < l[k]; i++) {
			for (j = 0; j < c[k]; j++)
				printf("%d ", a[k][i][j]);
			printf("\n");
		}
	}
}

// free_collection(collection, size, linesvector)
void free_collection(int ***a, int z, int *l)
{
	if (DD)
		printf("free_collection /%d/\n", z);
	int k;
	for (k = 0; k < z; k++)
		free_matrix(a[k], l[k]);
	free(a);
}

void free_cube(int ***q, int nk, int *ql)
{
	if (D)
		printf("free_cube [%p]\n", (void *)q);

	int k;

	for (k = 0; k < nk ; k++)
		free_matrix(q[k], ql[k]);
}

// int add_matrix(int ***q, int *qz, int *qkp, int *ql, int *qc, int **a, int l, int c)
// {
// 	if (*qz < 0)
// 		return 1;
// 	int i, j;
// 	int nz = *qz + 1;

// 	ql[*qz] = l;
// 	qc[*qz] = c;

// 	q[*qz] = malloc(l * sizeof(int *));
// 	for (i = 0; i < l; i++) {
// 		q[*qz][i] = malloc(c * sizeof(int));
// 		for (j = 0; j < c; j++)
// 			q[*qz][i][j] = a[i][j];
// 	}
// 	*qz = nz;
// 	*qkp = *qkp + 0;
// 	return 0;
// }

int*** add_matrix(int ***q, int *qzp, int *qkp, int *ql, int *qc, int **a, int l, int c)
{
	int qk = *qkp;
	int ***w;	
	int qz = *qzp;

	if (qz == qk) {
		qk = qk * 2;
	}
	*qkp = qk;

	w = malloc(qk * sizeof(int**));

	for (int k = 0; k < qz; k++) {
			w[k] = malloc(ql[k] * sizeof(int *));
			for (int i = 0; i < ql[k]; i++) {
				w[k][i] = malloc(qc[k] * sizeof(int));
				for (int j = 0; j < qc[k]; j++)
					w[k][i][j] = q[k][i][j];
			}
		}

	ql[qz] = l;
	qc[qz] = c;

	w[qz] = malloc(l * sizeof(int *));
	for (int i = 0; i < l; i++) {
		w[qz][i] = malloc(c * sizeof(int));
		for (int j = 0; j < c; j++)
			w[qz][i][j] = a[i][j];
	}
	*qzp = qz+1;

	free_cube(q, qz, ql);
	free(q);
	return w;
}



int ***sort_cube(int ***q, int qk, int z, int *ql, int *qc, int *qcc)
{
	qcc[0]=qcc[0] + 0;
	if (z < 1) return q;
	
	int ***a;
	int i, j, k;

	int *sum = malloc(qk * sizeof(int)); // the sum of each matrix
	int *top = malloc(qk * sizeof(int));// the position of the matrix
	
	for (int i = 0; i < z; i++)
		sum[i] = sum_matrix(q[i], ql[i], qc[i]);
	sort_vector(sum, z, top);

	int *ol = malloc(z * sizeof(int));
	int *oc = malloc(z * sizeof(int));
	for (k = 0; k < z ; k++) {
		ol[k] = ql[k];
		oc[k] = qc[k];
	}
	a = malloc(qk * sizeof(int **));
	for (k = 0; k < z; k++) {
		a[k] = malloc(ql[top[k]] * sizeof(int *));
		for (i = 0; i < ql[top[k]]; i++) {
			a[k][i] = malloc(qc[top[k]] * sizeof(int));
			for (j = 0; j < qc[top[k]]; j++)
				a[k][i][j] = q[top[k]][i][j];
		}
	}
	free_collection(q, z, ql);
	for (k = 0; k < z ; k++) {
		ql[k] = ol[top[k]];
		qc[k] = oc[top[k]];
	}
	free(ol); free(oc);
	free(sum); free(top);
	return a;
}

int ***del_matrix(int ***q, int qk, int *qzp, int *ql, int *qc, int ki)
{

	if (*qzp  == 0) return q;

    int qz = *qzp;
	int *qlo = malloc(qz * sizeof(int));
	for (int i = 0; i < qz; i++) {
		qlo[i] = ql[i];
	}
	int ***w;
	int ka = 0;
	w = malloc((qk) * sizeof(int **));
	for (int k = 0; k < qz; k++) {
		if (k != ki) {
			ql[ka] = ql[k]; qc[ka] = qc[k];
			w[ka] = malloc(ql[k] * sizeof(int *));
			for (int i = 0; i < ql[k]; i++) {
				w[ka][i] = malloc(qc[k] * sizeof(int));
				for (int j = 0; j < qc[k]; j++)
					w[ka][i][j] = q[k][i][j];
			}
			ka++;
		}
	}
	free_cube(q, qz, qlo);
	free(q);
	free(qlo);
	*qzp = qz - 1;
	return w;

}
