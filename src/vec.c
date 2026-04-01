#include <stdio.h>

// v = 0
void vec_zero (double* v, int dim) {
    for (int i=0;i<dim;i++) {
        v[i] = 0;
    }
}

// read a vector from stdin
// returns the number of elements read in
int vec_read_stdin (double* v, int dim) {
    for (int i=0;i<dim;i++) {
        if (scanf("%lf",&(v[i])) != 1) { // could also use v+i
            return i;
        }
    }
    return dim;
}

// w = u + v
void vec_add (double* u, double* v, double* w, int dim) {
    for (int i=0;i<dim;i++) {
        w[i] = u[i] + v[i];
    }
}

// w = cv
void vec_scalar_mult (double* v, double c, double* w, int dim) {
    for (int i=0;i<dim;i++) {
        w[i] = c*v[i];
    }
}

// calculate the distance squared between two vectors
double vec_dist_sq (double* u, double* v, int dim) {
    double dist_sq = 0;
    for (int i=0;i<dim;i++) {
        dist_sq += (u[i]-v[i])*(u[i]-v[i]);
    }
    return dist_sq;
}

// performs the copy v->data[i] = w->data[i] for all i
void vec_copy (double* v, double* w, int dim) {
    for (int i=0;i<dim;i++) {
        v[i] = w[i];
    }
}
