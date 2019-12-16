#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
 
int a[100000];
int sz = 0;
 
void main()
{
    char s[100];
    char cmd;
    int m;
    FILE *f, *out;
 
    out = fopen("stack.out", "w");
    f = fopen("stack.in", "r");
    fscanf(f, "%d", &m);
    fgets(s, sizeof(s), f);
    for (int i = 0; i < m; i++) {
        fscanf(f, "%c", &cmd);
        if (cmd == '+') {
            fscanf(f, "%d", &a[sz]);
            sz++;
        }
        if (cmd == '-') {
            sz--;
            fprintf(out, "%d\n", a[sz]);
        }
        fgets(s, sizeof(s), f);
    }
    fclose(f);
    fclose(out);
}
