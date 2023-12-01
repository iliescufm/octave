// print_collection (collection, size, linesvector, columnsvector)
void print_collection(int ***a, int z, int *l, int *c);

// free_collection(collection, size, linesvector)
void free_collection(int ***a, int z, int *l);

void free_cube(int ***q, int nk, int *ql);

// add matrix to collection
int ***add_matrix(int ***q, int *qz, int *qk, int *ql, int *qc, int **a, int l, int c);

// delete matrix form collection
int ***del_matrix(int ***q, int qk, int *qzp, int *ql, int *qc, int ki);


int ***sort_cube(int ***q, int qk, int z, int *ql, int *qc, int *top);
