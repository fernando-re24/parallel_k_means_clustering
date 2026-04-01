#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "vec.h"
#include "ffirst_fast.h"

int main(int argc, char* argv[]){
    if (argc != 2) {
        fprintf(stderr, "Usage: %s k < inputfile\n", argv[0]);
        return 1;
    }

    int k = atoi(argv[1]);
    if (k <= 0) {
        fprintf(stderr, "Error: k must be positive.\n");
        return 1;
    }

    int len, dim;
    if (scanf("%d %d", &len, &dim) != 2) {
        fprintf(stderr, "Error: failed to read len and dim from input.\n");
        return 1;
    }

    double* data = (double*)malloc(sizeof(double)*len*dim);
    if (!data) { printf("malloc failed for data\n"); return 1; }
    vec_read_dataset(data, len, dim);

    int* final_centers = malloc(sizeof(int) * k);
    if (!final_centers){ printf("malloc failed for final_centers\n"); return 1; }

    double final_cost = DBL_MAX;

    // Try every point as the starting center
    for (int i = 0; i < len; i++){
        int* curr_centers = malloc(sizeof(int) * k);
        if (!curr_centers){ printf("malloc failed for curr_centers\n"); return 1; }

        double cost = farthest_first(data, len, dim, k, curr_centers, i);

        if (cost < final_cost){
            final_cost = cost;
            // Copy the centers to final_centers
            for (int j = 0; j < k; j++) {
                final_centers[j] = curr_centers[j];
            }
        }

        free(curr_centers);
    }

    printf("Approximate minimal cost = %lf\n", final_cost);
    printf("Approximate optimal Centers: ");
    for(int i = 0; i < k; i++){
        printf("%d ", final_centers[i]);
    }
    printf("\n");

    free(data);
    free(final_centers);
    return 0;
}
