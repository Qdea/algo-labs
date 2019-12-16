#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#define N 10000
int a[N];
bool debug = false;
void main() {
    FILE* f;
    int n, j, i;
    f = fopen("smallsort.in", "r");
    fscanf_s(f, "%d", &n);
     
    for (i = 0; i < n; i++) {
        fscanf_s(f, "%d", &a[i]);
    }
    fclose(f);
 
    for (j = 1; j < n; j++) {
        int key = a[j];
        if (debug) {
            a[j] = key;
        }
        i = j - 1;
        if (debug) {
            for (int k = 0; k < n; k++)
                printf("%d ", a[k]);
            printf(", %d < %d ? \n", key, a[i]);
        }
        while (i >= 0 && key < a[i]) {
            a[i + 1] = a[i];
            if (debug) {
                a[i] = key;
            }
            i = i - 1;
            if (debug) {
                for (int k = 0; k < n; k++)
                    printf("%d ", a[k]);
                printf(", key = %d \n", key);
            }
        }
        a[i + 1] = key;
        if (debug) {
            for (int k = 0; k < n; k++)
                printf("%d ", a[k]);
            printf("\n");
        }
    }
    f = fopen("smallsort.out", "w"); 
    for (i = 0; i < n; i++)
        fprintf_s(f, "%d ", a[i]);
    fclose(f);
}
