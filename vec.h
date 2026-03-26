#ifndef VEC_H
#define VEC_H

// v = 0
void vec_zero (double* v, int dim);

// read a vector from stdin
// returns the number of elements read in
int vec_read_stdin (double* v, int dim);

// w = u + v
void vec_add (double* u, double* v, double* w, int dim);

// w = cv
void vec_scalar_mult (double* v, double c, double* w, int dim);

// calculate the distance squared between two vectors
double vec_dist_sq (double* u, double* v, int dim);

// performs the copy v->data[i] = w->data[i] for all i
void vec_copy (double* v, double* w, int dim);

#endif
