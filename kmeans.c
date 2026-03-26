#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "vec.h"
#include "farfirst.h"

// Finds the nearest cluster to a point
int find_cluster (double* kmeans, double* point, int k, int dim) {
    int cluster = 0;
    double low_dist = DBL_MAX;

    //Find the closest cluster 
    for(int i = 0; i < k; i++){
        double dist = vec_dist_sq(point, kmeans + i*dim, dim);
        if(dist < low_dist){
            low_dist = dist;
            cluster = i;
        }
    }

    return cluster;
}

// calculate the next kmeans
void calc_kmeans_next (double* data, int num_points, int dim, double* kmeans, double* kmeans_next, int k) {
    double cost = 0;
    
    // Array that tracks the cluster assigned to each point
    int* point_clusters = calloc(num_points, sizeof(int));

    // Arrays for accumulating sums and counts
    double* sums = calloc(k * dim, sizeof(double));
    int* counts = calloc(k, sizeof(int));

    // Assigns each point to a cluster & adds to the cost calculation
    for(int i = 0; i < num_points; i++){

        // Variable for the current point for readability
        double* curr_pt = data + i*dim;

        // Finds the nearest cluster
        int cluster = find_cluster(kmeans, curr_pt, k, dim);

        // Records the cluster that was chosen for the ith point & increments
        // the count of points in that cluster
        point_clusters[i] = cluster;
        counts[cluster]++;

        // Adds the to the sum of points for the current cluster
        for (int d = 0; d < dim; d++)

            //Add to the sum for each coordinate 
            sums[cluster*dim + d] += curr_pt[d];

        // Add to the total cost
        cost += vec_dist_sq(curr_pt, kmeans + cluster*dim, dim);
    }

    // Compute new means by iterating through the clusters & finding the mean point
    for(int i = 0; i < k; i++){

        if (counts[i] > 0) {

            // Calculate the average for each coordinate & assign the resulting point as the next mean
            for (int d = 0; d < dim; d++)
                kmeans_next[i*dim + d] = sums[i*dim + d] / counts[i];
        } else {
            // Exit with error if encountering an empty cluster
            fprintf (stderr, "Emtpy cluster found: %d", i);
            exit(1);
        }
    }

    // Frees the memory allocated for the ararys
    free(point_clusters);
    free(sums);
    free(counts);
}

// calculate kmeans using m steps of Lloyd's algorithm
void calc_kmeans (double* data, int num_points, int dim, double* kmeans, int k, int m) {

    // find k centers using the farthest first algorithm
    int centers[k];
    farfirst(data,num_points,dim,centers,k);

    // initialize kmeans using the k centers
    for (int i=0;i<k;i++) {
        vec_copy(kmeans+i*dim,data+centers[i]*dim,dim);
    }

    // update kmeans m times
    double kmeans_next[k*dim];
    for (int i=0;i<m;i++) {
        calc_kmeans_next(data,num_points,dim,kmeans,kmeans_next,k);
        vec_copy(kmeans,kmeans_next,k*dim);
    }
}
