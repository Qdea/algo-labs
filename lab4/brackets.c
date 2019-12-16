#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
 
char a[10005];
int sz = 0;
 
void main()
{
    char cmd;
    FILE *f, *out;
 
    out = fopen("brackets.out", "w");
    f = fopen("brackets.in", "r");
    do {
        int ok = 1;
        int empty = 1;
        sz = 0;
        do {
            cmd = fgetc(f);
            // fscanf(f, "%c", &cmd);
            if (ok) {
                if (cmd == '(' || cmd == '[') {
                    empty = 0;
                    a[sz] = cmd;
                    sz++;
                }
                if (cmd == ')' || cmd == ']') {
                    empty = 0;
                    sz--;
                    if (sz >= 0) {
                        if (cmd == ')' && a[sz] != '(' || cmd == ']' && a[sz] != '[') {
                            ok = 0;
                        }
                    }
                    else {
                        ok = 0;
                    }
                }
            }
        } while (cmd != '\n' && cmd != -1);
        if (empty == 0) {
            fprintf(out, "%s\n", ok && sz == 0 ? "YES" : "NO");
        }
    } while (cmd != -1);
    fclose(f);
    fclose(out);
}
