#define _CRT_SECURE_NO_WARNINGS
 
#include <stdio.h>
 
#define MaxN 300000
 
long a[MaxN], b[MaxN];
 
void swap1(int x, int y)
{
    a[x] = a[x] ^ a[y];
    a[y] = a[x] ^ a[y];
    a[x] = a[x] ^ a[y];
}
 
void merge1(int x, int m, int y)
{
    int i = x, j = m, k = x;
    while (i <= m - 1 && j <= y) {
        if (a[i] < a[j])
            b[k++] = a[i++];
        else
            b[k++] = a[j++];
    }
    while (i <= m - 1) b[k++] = a[i++];
    while (j <= y) b[k++] = a[j++];
    for (i = x; i <= y; i++) a[i] = b[i];
}
 
void sort1(int x, int y)
{
    if (x == y) {
        return;
    }
    if (x == y - 1) {
        if (a[x] > a[y]) {
            swap1(x, y);
        }
        return;
    }
    int m = (x + y) / 2;
    sort1(x, m - 1);
    sort1(m, y);
    merge1(x, m, y);
}
 
void save1(int n)
{
    FILE* f;
    f = fopen("sort.out", "w");
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            fprintf(f, "%d", a[i]);
        }
        else {
            fprintf(f, " %d", a[i]);
        }
    }
    fclose(f);
}
 
int load1()
{
    FILE* f;
    int n = 0;
    f = fopen("sort.in", "r");
    fscanf(f, "%d", &n);
    while (getc(f) != '\n');
    for (int i = 0; i < n; i++) {
        fscanf(f, "%d", &a[i]);
    }
    fclose(f);
    return n;
}
 
int main()
{
    int n = load1();
    if (n > 0) {
        sort1(0, n - 1);
        save1(n);
    }
    return 0;
}
