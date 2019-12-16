#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
#define BITS 20
 
FILE * out;
 
struct node {
    int val;
    struct node* next;
};
 
struct node* a[1 << BITS];
 
unsigned int inthash(unsigned int key)
{
    key += (key << 12);
    key ^= (key >> 22);
    key += (key << 4);
    key ^= (key >> 9);
    key += (key << 10);
    key ^= (key >> 2);
    key += (key << 7);
    key ^= (key >> 12);
    key = (key & ((1 << BITS) - 1));
    return key;
}
 
void insert(int x)
{
    struct node** n;
    unsigned int hash = inthash(x);
    n = &a[hash];
    while (*n != 0) {
        if ((**n).val == x) return;
        n = &((**n).next);
    }
    *n = malloc(sizeof(struct node));
    (**n).val = x;
    (**n).next = 0;
}
 
void exists(int x)
{
    unsigned int hash = inthash(x);
    struct node* n = a[hash];
    while (n != 0) {
        if ((*n).val == x) {
            fprintf(out, "true\n");
            return;
        }
        n = (*n).next;
    }
    fprintf(out, "false\n");
}
 
void delete(int x)
{
    struct node* n;
    struct node* p;
    unsigned int hash = inthash(x);
    p = 0;
    n = a[hash];
    while (n != 0) {
        if ((*n).val == x) {
            if (p != 0) {
                (*p).next = (*n).next;
            }
            else {
                a[hash] = (*n).next;
            }
            free(n);
            return;
        }
        p = n;
        n = (*n).next;
    }
}
 
void main()
{
    char cmd[100];
    int x;
    int ok;
    FILE* f;
 
    out = fopen("set.out", "w");
    f = fopen("set.in", "r");
 
    for (int i = 0; i < (1 << BITS); i++) {
        a[i] = 0;
    }
 
    do {
        ok = 0;
        fscanf(f, "%s", cmd);
        if (strcmp(cmd, "insert") == 0) {
            ok = 1;
            fscanf(f, "%d", &x);
            insert(x);
        }
        else
            if (strcmp(cmd, "exists") == 0) {
                ok = 1;
                fscanf(f, "%d", &x);
                exists(x);
            }
            else
                if (strcmp(cmd, "delete") == 0) {
                    ok = 1;
                    fscanf(f, "%d", &x);
                    delete(x);
                }
        cmd[0] = '\0';
    } while (ok);
 
    fclose(f);
    fclose(out);
}
