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

