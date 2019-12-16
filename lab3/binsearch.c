#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
 
int a[100000];
int n = 0;
int x;
int p = 0;
int q = 0;
 
void solve()
{
    int left = 0;
    int right = n - 1;
 
    do {
        p = (left + right) / 2;
        // a[left] .. a[p] .. a[right]
        if (x <= a[p]) {
            // a[left] .. x .. a[p] .. a[right]
            // a[left] .. a[p] = x .. a[right]
            // [2] 2 3 4 [4] 4 5 5 [5]
            right = p;
        }
        else {
            // a[left] .. a[p] .. x .. a[right]
            left = p;
        }
    } while (right > left + 1);
 
    if (a[left] != x && a[right] != x) {
        p = -1;
        q = -1;
        return;
    }
    if (a[left] == x) {
        p = left + 1;
    } 
    else if (a[right] == x) {
        p = right + 1;
    }
 
    left = 0;
    right = n - 1;
    do {
        q = (left + right) / 2;
        // a[left] .. a[p] .. a[right]
        if (x >= a[q]) {
            // a[left] .. a[q] .. x .. a[right]
            // a[left] .. a[q] = x .. a[right]
            // [2] 2 3 4 [4] 4 5 5 [5]
            left = q;
        }
        else {
            // a[left] .. x .. a[q] .. a[right]
            right = q;
        }
    } while (right > left + 1);
 
    if (a[right] == x) {
        q = right + 1;
    }
    else if (a[left] == x) {
        q = left + 1;
    }
}
 
void main()
{
    FILE* in;
    FILE* out;
    int m;
 
    out = fopen("binsearch.out", "w");
    in = fopen("binsearch.in", "r");
 
    fscanf(in, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(in, "%d", &a[i]);
    }
 
    fscanf(in, "%d", &m);
    for (int i = 0; i < m; i++) {
        fscanf(in, "%d", &x);
        solve();
        fprintf(out, "%d %d\n", p, q);
    }
 
    fclose(in);
    fclose(out);
}
