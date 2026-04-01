#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <omp.h>
#include "../include/vec.h"
#include "../include/farfirst.h"

// Farthest-first initialization: greedily picks k centers
// by always choosing the point farthest from any existing center.
void farfirst(double* data, int num_points, int dim, int* centers, int k) {

    // min_dist[i] = distance from point i to its nearest chosen center
    double* min_dist = malloc(num_points * sizeof(double));

    // First center is point 0
    centers[0] = 0;

    // Initialize all distances to distance from point 0
    #pragma omp parallel for
    for (int i = 0; i < num_points; i++) {
        min_dist[i] = vec_dist_sq(data + i*dim, data + centers[0]*dim, dim);
    }

    // Greedily pick k-1 more centers
    for (int c = 1; c < k; c++) {

        // Find the point farthest from any chosen center (parallel reduction)
        int farthest = 0;
        double max_dist = -1.0;

        #pragma omp parallel
        {
            int local_farthest = 0;
            double local_max = -1.0;

            #pragma omp for
            for (int i = 0; i < num_points; i++) {
                if (min_dist[i] > local_max) {
                    local_max = min_dist[i];
                    local_farthest = i;
                }
            }

            #pragma omp critical
            {
                if (local_max > max_dist) {
                    max_dist = local_max;
                    farthest = local_farthest;
                }
            }
        }

        centers[c] = farthest;

        // Update min_dist: for each point, check if the new center is closer
        #pragma omp parallel for
        for (int i = 0; i < num_points; i++) {
            double d = vec_dist_sq(data + i*dim, data + centers[c]*dim, dim);
            if (d < min_dist[i])
                min_dist[i] = d;
        }
    }

    free(min_dist);
}
