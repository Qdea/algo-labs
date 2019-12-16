#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
#define BITS 20
 
FILE * out;
 
struct node {
    char key[21];
    char val[21];
    struct node* before;
    struct node* after;
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
 
unsigned int strhash(char key[21])
{
    char* s = key;
    int r = 0;
    int k = 0;
    int m = 0;
    while (*s != '\0') {
        if (*s >= 'a' && *s <= 'z') {
            k = (k << 6) + (*s - 'a');
        }
        else if (*s >= 'A' && *s <= 'Z') {
            k = (k << 6) + 32 + (*s - 'A');
        }
        m++;
        if (m == 4) {
            r = (r << 7) + inthash(k);
            k = 0;
            m = 0;
        }
        s++;
    }
    if (m > 0) {
        r = (r << 7) + inthash(k);
    }
    return inthash(r);
}
 
struct node* before;
 
void put(char key[21], char val[21])
{
    struct node** n;
    unsigned int hash = strhash(key);
    n = &a[hash];
    while (*n != 0) {
        if (strcmp((**n).key, key) == 0) {
            strcpy((**n).val, val);
            return;
        }
        n = &((**n).next);
    }
    *n = malloc(sizeof(struct node));
    strcpy((**n).key, key);
    strcpy((**n).val, val);
    (**n).next = 0;
    (**n).before = before;
    (**n).after = 0;
    if (before) {
        (*before).after = *n;
    }
    before = *n;
}
 
void get(char key[21])
{
    unsigned int hash = strhash(key);
    struct node* n = a[hash];
    while (n != 0) {
        if (strcmp((*n).key, key) == 0) {
            fprintf(out, "%s\n", (*n).val);
            return;
        }
        n = (*n).next;
    }
    fprintf(out, "none\n");
}
 
void prev(char key[21])
{
    unsigned int hash = strhash(key);
    struct node* n = a[hash];
    while (n != 0) {
        if (strcmp((*n).key, key) == 0) {
            if (n->before) {
                fprintf(out, "%s\n", n->before->val);
            }
            else {
                fprintf(out, "none\n");
            }
            return;
        }
        n = (*n).next;
    }
    fprintf(out, "none\n");
}
 
void next(char key[21])
{
    unsigned int hash = strhash(key);
    struct node* n = a[hash];
    while (n != 0) {
        if (strcmp((*n).key, key) == 0) {
            if (n->after) {
                fprintf(out, "%s\n", n->after->val);
            }
            else {
                fprintf(out, "none\n");
            }
            return;
        }
        n = (*n).next;
    }
    fprintf(out, "none\n");
}
 
void delete(char key[21])
{
    struct node* n;
    struct node* p;
    unsigned int hash = strhash(key);
    p = 0;
    n = a[hash];
    while (n != 0) {
        if (strcmp((*n).key, key) == 0) {
            if (p != 0) {
                (*p).next = (*n).next;
            }
            else {
                a[hash] = (*n).next;
            }
            if (n->before) {
                n->before->after = n->after;
            }
            if (n->after) {
                n->after->before = n->before;
            }
            if (before && before == n) {
                before = before->before;
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
    char cmd[10];
    char key[21];
    char val[21];
    int ok;
    FILE* f;
    before = 0;
 
    out = fopen("linkedmap.out", "w");
    f = fopen("linkedmap.in", "r");
 
    for (int i = 0; i < (1 << BITS); i++) {
        a[i] = 0;
    }
 
    do {
        ok = 0;
        fscanf(f, "%s", cmd);
        if (strcmp(cmd, "put") == 0) {
            ok = 1;
            fscanf(f, "%s %s", key, val);
            put(key, val);
        }
        else
            if (strcmp(cmd, "get") == 0) {
                ok = 1;
                fscanf(f, "%s", key);
                get(key);
            }
            else
                if (strcmp(cmd, "delete") == 0) {
                    ok = 1;
                    fscanf(f, "%s", key);
                    delete(key);
                }
                else
                    if (strcmp(cmd, "prev") == 0) {
                        ok = 1;
                        fscanf(f, "%s", key);
                        prev(key);
                    }
                    else
                        if (strcmp(cmd, "next") == 0) {
                            ok = 1;
                            fscanf(f, "%s", key);
                            next(key);
                        }
        cmd[0] = '\0';
    } while (ok);
 
    fclose(f);
    fclose(out);
}
