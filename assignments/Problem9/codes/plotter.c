#include <stdio.h>
#include <openssl/rand.h>

// 1 - heads; 0 - tails
void run_sim(int max_tosses, double *points) {
    int count = 0;
    for (int i = 0; i < max_tosses; i++) {  // Iterate up to max_tosses
        unsigned char buffer1[3];
        if (RAND_bytes(buffer1, sizeof(buffer1)) != 1) {
            printf("Error in generating random bytes.\n");
            return;  // Exit the function on failure
        }
        int coin1 = 1 & buffer1[0];
        int coin2 = 1 & buffer1[1];
        int coin3 = 1 & buffer1[2];
        if (!(coin1 && coin2 && coin3)) {
            count++;
        }
        points[2 * i] = (double)(i + 1);
        points[2 * i + 1] = (double)count / (i + 1);
        printf("%d %lf\n", i + 1, points[2 * i + 1]);
    }
    return;
}

int main() {
    int max_tosses;

    // Get the number of tosses from the user
    printf("Enter the maximum number of tosses: ");
    scanf("%d", &max_tosses);

    if (max_tosses <= 0) {
        printf("Error: Number of tosses must be greater than 0.\n");
        return 1;
    }

    // Allocate memory for the points array (2 * max_tosses elements)
    double *points = malloc(2 * max_tosses * sizeof(double));
    if (points == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Run the simulation
    run_sim(max_tosses, points);

    // Print results (optional, for verification)
    printf("\nSimulation Results:\n");
    for (int i = 0; i < max_tosses; i++) {
        printf("Toss: %d, Probability: %.6lf\n", (int)points[2 * i], points[2 * i + 1]);
    }

    // Free allocated memory
    free(points);

    return 0;
}
