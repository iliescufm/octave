// Copyright Miruna-elena Iliescu 312CAb 2023-2024
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Validate.h"
#include "Matrix.h"
#include "Collection.h"
#include "Radix.h"
#include "PowerMatrix.h"
#include "strassenMultiply.h"
#include "MultiplicateMatrix.h"
# define DD 0 // debug messages: 0 - no, 1 -yes
# define CMAX 1234
# define L 1
# define D 2
# define P 3
# define C 4
# define M 5
# define O 6
# define T 7
# define R 8
# define F 9
# define Q 0
# define S 11

int main(void)
{
	int qz = 0, qk = 1, *ql, *qc;//size, capacity, lines vector, columns vector
	int ***q = malloc(qk * sizeof(int **)); //resizable array
	int **a, l = 0, k = 0, p = 0;
	int lx = 0, cx = 0, cmd = 99;
	int *li = malloc(CMAX * sizeof(int));
	int *ci = malloc(CMAX * sizeof(int));
	ql = malloc(CMAX * sizeof(int));
	qc = malloc(CMAX * sizeof(int));
	while (cmd) {
		cmd = get(qz, &k, &p, &lx, li, &cx, ci);
		if (cmd == L) {
			a = read_matrix(lx, cx);
			q = add_matrix(q, &qz, &qk, ql, qc, a, lx, cx);
			free_matrix(a,lx);
			}
		if (cmd == D) printf("%d %d\n", ql[k], qc[k]);
		if (cmd == P) print_matrix(q[k], ql[k], qc[k]);
		if (cmd == C) q[k] = cut_matrix(q[k], &ql[k], &qc[k], lx, li, cx, ci);
		if (cmd == M) {
			a = mat_multiply(q[lx], ql[lx], qc[lx], q[cx], ql[cx], qc[cx]);
			if (a) { 
				q = add_matrix(q, &qz, &qk, ql, qc, a, ql[lx], qc[cx]);
				free_matrix(a, ql[lx]);
				}
			}
		if (cmd == O) q = sort_cube(q, qk, qz, ql, qc, qc);
		if (cmd == T) q[k] = transpose_matrix(q[k], &ql[k], &qc[k]);
		if (cmd == R) power_matrix(q[k], ql[k], qc[k], p);
		if (cmd == F) q = del_matrix(q, qk, &qz, ql, qc, k);
		if (cmd == S) {
			if (validate_size(lx, cx, ql, qc) != 0) {
					l = ql[cx]; a = init_alloc_matrix(l, l, -1);
					strassen_multiply(q[lx], q[cx], a, l);
					q = add_matrix(q, &qz, &qk, ql, qc, a, l, l); 
					free_matrix(a, l);
				}
		}
	}
	free_cube(q, qz, ql); 
	free(q); free(ql); free(qc);
	free(li); free(ci);
	return 0;
}
