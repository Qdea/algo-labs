#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define N 70000
 
int a[N];
 
void main() {
    FILE* f;
    int n, i, t;
    f = fopen("antiqs.in", "r");
    fscanf_s(f, "%d", &n);
    fclose(f);
 
    for (i = 0; i < n; i++) {
        a[i] = i + 1;
    }
 
    for (i = 2; i < n; i++) {
        t = a[i];
        a[i] = a[i / 2];
        a[i / 2] = t;
    }
 
    f = fopen("antiqs.out", "w");
    for (i = 0; i < n; i++) {
        fprintf_s(f, "%d ", a[i]);
    }
    fclose(f);
}
