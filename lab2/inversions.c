#define _CRT_SECURE_NO_WARNINGS
 
#include <stdio.h>
 
#define MaxN 100000
 
int a[MaxN], b[MaxN];
int n = 0;
long long result = 0;
 
void swap(int x, int y)
{
    a[x] = a[x] ^ a[y];
    a[y] = a[x] ^ a[y];
    a[x] = a[x] ^ a[y];
}
 
long long merge(int x, int m, int y)
{
    int i = x, j = m, k = x;
    long long r = 0, p = 0;
    while (i <= m - 1 && j <= y) {
        if (a[i] <= a[j]) {
            i++;
            r += p;
        }
        else {
            j++;
            p++;
        }
    }
    while (i <= m - 1) {
        r += p;
        i++;
    }
    i = x; j = m; k = x;
    while (i <= m - 1 && j <= y) {
        if (a[i] < a[j])
            b[k++] = a[i++];
        else
            b[k++] = a[j++];
    }
    while (i <= m - 1) b[k++] = a[i++];
    while (j <= y) b[k++] = a[j++];
    for (i = x; i <= y; i++) a[i] = b[i];
    return r;
}
 
long long calc(int x, int y)
{
    if (x == y) {
        return 0;
    }
    if (x == y - 1) {
        if (a[x] > a[y]) {
            swap(x, y);
            return 1;
        }
        return 0;
    }
    int m = (x + y + 1) / 2;
    long long r = calc(x, m - 1) + calc(m, y);
    r += merge(x, m, y);
    return r;
}
 
void save()
{
    FILE* f;
    f = fopen("inversions.out", "w");
    fprintf(f, "%lld", result);
    fclose(f);
}
 
void load()
{
    FILE* f;
    f = fopen("inversions.in", "r");
    fscanf(f, "%d", &n);
    while (getc(f) != '\n');
    for (int i = 0; i < n; i++) {
        fscanf(f, "%d", &a[i]);
    }
    fclose(f);
}
 
void main()
{
    load();
    if (n > 0) {
        result = calc(0, n - 1);
        save();
    }
}
