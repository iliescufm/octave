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
# define D 0 // debug messages: 0 - no, 1 -yes
# define CMAX 1234 

int main(void)
{
	int qz = 0, qk = 1, *ql, *qc;//size, capacity, lines vector, columns vector
	int ***q = malloc(qk * sizeof(int **)); //resizable array
	int **a, l, c, k, k1, k2, p;
	ql = malloc(CMAX * sizeof(int));
	qc = malloc(CMAX * sizeof(int));
	char key = '\0';
	while (1) {
		int ok = 0;
		scanf("%c", &key);
		if (key == 'L') {
			ok = 1; scanf("%d%d", &l, &c);
			a = read_matrix(l, c);
			q = add_matrix(q, &qz, &qk, ql, qc, a, l, c);
			free_matrix(a, l);
		}
		if (key == 'D') {
			ok = 1; scanf("%d", &k);
			if (validate_index(k, qz))
				printf("%d %d\n", ql[k], qc[k]);
		}
		if (key == 'P') {
			ok = 1; scanf("%d", &k);
			if (validate_index(k, qz))
				print_matrix(q[k], ql[k], qc[k]);
		}
		if (key == 'C') {
			ok = 1; scanf("%d", &k);
				int lx, cx;
				scanf("%d", &lx); // nr of lines
				int li[lx];
				for (int i = 0; i < lx; i++)
					scanf("%d", &li[i]);
				scanf("%d", &cx); // nr of columns
				int ci[cx];
				for (int i = 0; i < cx; i++)
					scanf("%d", &ci[i]);
			if (validate_index(k, qz))
				q[k] = cut_matrix(q[k], &ql[k], &qc[k], lx, li, cx, ci);
		}
		if (key == 'M') {
			ok = 1; scanf("%d%d", &k1, &k2);
			if (validate_index(k1, qz) && validate_index(k2, qz)) {
				a = mat_multiply(q[k1], ql[k1], qc[k1], q[k2], ql[k2], qc[k2]);
				l = ql[k1]; c = qc[k2];
				if (a) {
					q = add_matrix(q, &qz, &qk, ql, qc, a, l, c);
					free_matrix(a, l);
				}
			}
		}
		if (key == 'O') {
			ok = 1; 
			q = sort_cube(q, qk, qz, ql, qc, qc);
		}
		if (key == 'T') {
			ok = 1; scanf("%d", &k);
			if (validate_index(k, qz))
				q[k] = transpose_matrix(q[k], &ql[k], &qc[k]);
		}
		if (key == 'R') {
			ok = 1; scanf("%d%d", &k, &p);
			if (validate_index(k, qz))
				power_matrix(q[k], ql[k], qc[k], p);
		}
		if (key == 'F') {
			ok = 1; int ki;
			scanf("%d", &ki);
			if (validate_index(ki, qz)) {
				q = del_matrix(q, qk, &qz, ql, qc, ki);
			}
		}
		if (key == 'Q') {
			ok = 1;
			free_collection(q, qz, ql); free(ql); free(qc);
			break;
		}
		if (key == 'S') {
			ok = 1;
			scanf("%d%d", &k1, &k2);
			if (validate_index(k1, qz) && validate_index(k2, qz)) {
				if (validate_size(k1, k2, ql, qc) != 0) {
					l = ql[k2];
					a = init_alloc_matrix(l, l, -1);
					strassen_multiply(q[k1], q[k2], a, l);
					q = add_matrix(q, &qz, &qk, ql, qc, a, l, l); free_matrix(a, l);
				}
			}
		}
		if (ok == 0)
			if (key != '\n' && key != '\r')
				printf("Unrecognized command\n");
	}
	return 0;
}
