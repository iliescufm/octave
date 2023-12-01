#include <stdio.h>
#define MODULO 10007
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

int validate_index(int k, int size)
{
	if (k >= size || k < 0) {
		printf("No matrix with the given index\n");
		return 0;
	}
	return 1;
}

int validate_size(int k1, int k2, int *ql, int *qc)
{
	if (qc[k1] == ql[k2]) {
		if (ql[k1] != qc[k2] || ql[k2] != qc[k2]) {
			printf("Cannot perform matrix multiplication\n");
			return 0;
		}
	} else {
		printf("Cannot perform matrix multiplication\n");
		return 0;
	}
	return 1;
}

int modulo_positive(int s)
{
	s = s % MODULO;
	if (s < 0)
		s = s + MODULO;
	return s;
}

int get(int qz, int* k, int *p, int *lx, int *li, int *cx, int *ci)
{
	char key = '\0';
	int ok = 0;
	scanf("%c", &key);
	if (key == 'L') {
		scanf("%d%d", lx, cx); return L;
	}
	if (key == 'D') {
		ok = 1;
		scanf("%d", k);
		if (validate_index(*k, qz)) return D;
	}
	if (key == 'P') {
		ok = 1; 
		scanf("%d", k);
		if (validate_index(*k, qz)) return P;
	}
	if (key == 'C') {
		ok = 1;
		scanf("%d", k);
		scanf("%d", lx); // nr of lines
		for (int i = 0; i < *lx; i++)
			scanf("%d", &li[i]);
		scanf("%d", cx); // nr of columns
		for (int i = 0; i < *cx; i++)
			scanf("%d", &ci[i]);
		if (validate_index(*k, qz)) return C;
		}
	if (key == 'M') {
		ok = 1;
		scanf("%d%d", lx, cx);
		if (validate_index(*lx, qz) && validate_index(*cx, qz)) return M;
		}
	if (key == 'O') return O;
	if (key == 'T') {
		ok = 1;
		scanf("%d", k);
		if (validate_index(*k, qz)) return T;
		}
	if (key == 'R') {
		ok = 1;
		scanf("%d%d", k, p);
		if (validate_index(*k, qz)) return R;
		}
	if (key == 'F') {
		ok = 1;
		scanf("%d", k);
		if (validate_index(*k, qz)) return F;
		}
	if (key == 'Q') return Q;
	if (key == 'S') {
		ok = 1;
		scanf("%d%d", lx, cx);
		if (validate_index(*lx, qz) && validate_index(*cx, qz)) return S;
		}
	if (key != '\n' && key != '\r') {
		if (! ok) printf("Unrecognized command\n");
		}
	return 99;
}