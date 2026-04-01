#ifndef KMEANS_H
#define KMEANS_H

// calculate kmeans using m steps of Lloyd's algorithm
void calc_kmeans (double* data, int num_points, int dim, double* kmeans, int k, int m);

#endif
