#ifndef KMEANS_H
#define KMEANS_H

// calculate kmeans using m steps of Lloyd's algorithm
// num_threads: number of OpenMP threads (0 = system default)
void calc_kmeans (double* data, int num_points, int dim, double* kmeans, int k, int m, int num_threads);

#endif
