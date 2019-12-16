#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
 
int a[100000];
int bq = 0;
int eq = 0;
 
void main()
{
    char s[100];
    char cmd;
    int m;
    FILE* f, * out;
 
    out = fopen("queue.out", "w");
    f = fopen("queue.in", "r");
    fscanf(f, "%d", &m);
    fgets(s, sizeof(s), f);
    for (int i = 0; i < m; i++) {
        fscanf(f, "%c", &cmd);
        if (cmd == '+') {
            fscanf(f, "%d", &a[eq]);
            eq = (eq + 1) % 100000;
        }
        if (cmd == '-') {
            fprintf(out, "%d\n", a[bq]);
            bq = (bq + 1) % 100000;
        }
        fgets(s, sizeof(s), f);
    }
    fclose(f);
    fclose(out);
}
