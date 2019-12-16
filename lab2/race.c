#define _CRT_SECURE_NO_WARNINGS
 
#include <stdio.h>
#include <string.h>
 
int n;
char country[100000][11], surname[100000][11];
int a[100000], b[100000];
 
int cmp(int x, int y)
{
    int c = strcmp(country[a[x]], country[a[y]]);
    if (c > 0 || c == 0 && a[x] > a[y])
        return 1;
    else
        return 0;
}
 
void swap(int x, int y)
{
    a[x] = a[x] ^ a[y];
    a[y] = a[x] ^ a[y];
    a[x] = a[x] ^ a[y];
}
 
void merge(int x, int m, int y)
{
    int i = x, j = m, k = x;
    while (i <= m - 1 && j <= y) {
        if (cmp(i, j))
            b[k++] = a[j++];
        else
            b[k++] = a[i++];
    }
    while (i <= m - 1) b[k++] = a[i++];
    while (j <= y) b[k++] = a[j++];
    for (i = x; i <= y; i++) a[i] = b[i];
}
 
void sort(int x, int y)
{
    if (x == y) {
        return;
    }
    if (x == y - 1) {
        if (cmp(x, y)) {
            swap(x, y);
        }
        return;
    }
    int m = (x + y + 1) / 2;
    sort(x, m - 1);
    sort(m, y);
    merge(x, m, y);
}
 
void load()
{
    FILE* f;
    f = fopen("race.in", "r");
    fscanf(f, "%d", &n);
    while (getc(f) != '\n');
    for (int i = 0; i < n; i++) {
        fscanf(f, "%s %s", &country[i], &surname[i]);
        a[i] = i;
    }
    fclose(f);
}
 
void save()
{
    FILE* f;
    f = fopen("race.out", "w");
    int j = 0;
    fprintf(f, "=== %s ===\n", country[a[j]]);
    for (int i = 0; i < n; i++) {
        if (strcmp(country[a[j]], country[a[i]])) {
            j = i;
            fprintf(f, "=== %s ===\n", country[a[j]]);
        }
        fprintf(f, "%s\n", surname[a[i]]);
    }
    fclose(f);
}
 
void main()
{
    load();
    sort(0, n - 1);
    save();
}
