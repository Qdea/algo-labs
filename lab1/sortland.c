#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#define N 10000
float a[N];
int b[N];
bool debug = false;
void main() {
    FILE* f;
    int n = 3, j, i;
    f = fopen("sortland.in", "r");
    fscanf_s(f, "%d", &n);
 
    for (i = 0; i < n; i++) {
        fscanf_s(f, "%f", &a[i]);
        b[i] = i + 1;
    }
    fclose(f);
 
    for (j = 1; j < n; j++) {
        float key = a[j];
        int keyB = b[j];
        if (debug) {
            a[j] = key;
        }
        i = j - 1;
        if (debug) {
            for (int k = 0; k < n; k++)
                printf("%.2f ", a[k]);
            printf(", %.2f < %.2f ? \n", key, a[i]);
        }
        while (i >= 0 && key < a[i]) {
            a[i + 1] = a[i];
            b[i + 1] = b[i];
            if (debug) {
                a[i] = key;
            }
            i = i - 1;
            if (debug) {
                for (int k = 0; k < n; k++)
                    printf("%.2f ", a[k]);
                printf(", key = %.2f \n", key);
            }
        }
        a[i + 1] = key;
        b[i + 1] = keyB;
        if (debug) {
            for (int k = 0; k < n; k++)
                printf("%.2f ", a[k]);
            printf("\n");
        }
    }
    f = fopen("sortland.out", "w");
    fprintf_s(f, "%d %d %d", b[0], b[(n - 1) / 2], b[n - 1]);
    fclose(f);
}
