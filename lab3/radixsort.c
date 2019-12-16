#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
 
unsigned char a[1000][1000];
int id[2][1000];
 
int n;
int m;
int k;
 
int pos[256];
int count[256];
 
void solve()
{
    for (int i = 0; i < n; i++) {
        id[1][i] = i;
    }
    for (int j = 1; j <= k; j++) {
        for (int i = 0; i < 256; i++) {
            pos[i] = 0;
        }
        for (int i = 0; i < 256; i++) {
            count[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            unsigned char c = a[i][m - j];
            if (c < 255) {
                count[c + 1]++;
            }
        }
        for (int i = 0; i < 255; i++) {
            count[i + 1] += count[i];
        }
        for (int i = 0; i < n; i++) {
            char c = a[id[j % 2][i]][m - j];
            int x = count[c] + pos[c];
            id[(j + 1) % 2][x] = id[j % 2][i];
            pos[c]++;
        }
    }
}
 
void load()
{
    FILE* f;
    char s[1005];
 
    f = fopen("radixsort.in", "r");
    fscanf(f, "%d %d %d", &n, &m, &k);
    while (getc(f) != '\n');
    for (int i = 0; i < n; i++) {
        fgets(s, sizeof(s), f);
        for (int j = 0; j < m; j++) {
            a[i][j] = *(s + j);
        }
    }
    fclose(f);
}
 
void save()
{
    FILE* f;
 
    f = fopen("radixsort.out", "w");
    for (int i = 0; i < n; i++) {
        if (i > 0)
            fprintf(f, "\n");
        for (int j = 0; j < m; j++) {
            fprintf(f, "%c", a[id[(k + 1) % 2][i]][j]);
        }
    }
    fclose(f);
}
 
void main()
{
    load();
    solve();
    save();
}
