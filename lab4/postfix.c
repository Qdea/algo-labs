#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
 
int a[105];
int sz = 0;
 
void main()
{
    char cmd;
    FILE* f, * out;
 
    f = fopen("postfix.in", "r");
    do {
        cmd = fgetc(f);
        if (cmd >= '0' && cmd <= '9') {
            a[sz] = cmd - '0';
            sz++;
        }
        if (cmd == '+' || cmd == '-' || cmd == '*') {
            sz--;
            if (cmd == '*') {
                a[sz - 1] = a[sz - 1] * a[sz];
            }
            if (cmd == '+') {
                a[sz - 1] = a[sz - 1] + a[sz];
            }
            if (cmd == '-') {
                a[sz - 1] = a[sz - 1] - a[sz];
            }
        }
    } while (cmd != '\n' && cmd != -1);
    fclose(f);
 
    out = fopen("postfix.out", "w");
    fprintf(out, "%d", a[0]);
    fclose(out);
}
