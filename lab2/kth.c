#define _CRT_SECURE_NO_WARNINGS
 
#include <stdio.h>
 
#define MaxN 30000000
 
int a[MaxN], b[MaxN];
int n = 0, k = 0;
 
void swap(int x, int y)
{
    a[x] = a[x] ^ a[y];
    a[y] = a[x] ^ a[y];
    a[x] = a[x] ^ a[y];
}
 
void save()
{
    FILE* f;
    f = fopen("kth.out", "w");
    fprintf(f, "%d", a[k]);
    fclose(f);
}
 
void load()
{
    FILE* f;
    int aa, bb, cc;
    f = fopen("kth.in", "r");
    fscanf(f, "%d %d", &n, &k);
    k--;
    while (getc(f) != '\n');
    fscanf(f, "%d %d %d %d %d", &aa, &bb, &cc, &a[0], &a[1]);
    fclose(f);
    for (int i = 2; i < n; i++) {
        a[i] = aa * a[i - 2] + bb * a[i - 1] + cc;
    }
}
 
void qsort(int l, int r)
{
    int i, j, key;
    key = a[(l + r) / 2];
    i = l;
    j = r;
    do {
        while (a[i] < key && i <= j) i++;
        while (key < a[j] && i <= j) j--;
        if (i <= j) {
            if(i != j) swap(i, j);
            i++;
            j--;
        }
    } while (i <= j);
    if (k <= j && l < j) qsort(l, j);
    if (k >= i && i < r) qsort(i, r);
}
 
int main()
{
    load();
    if (n > 0) {
        qsort(0, n - 1);
        save();
    }
    return 0;
}
