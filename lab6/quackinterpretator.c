#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define BITS 17
#define MASK (1 << 17) - 1
 
FILE* out;
 
struct node {
    char key[21];
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
 
void putlabel(char key[21], int val)
{
    struct node** n;
    unsigned int hash = strhash(key);
    n = &a[hash];
    while (*n != 0) {
        if (strcmp((**n).key, key) == 0) {
            (**n).val = val;
            return;
        }
        n = &((**n).next);
    }
    *n = malloc(sizeof(struct node));
    strcpy((**n).key, key);
    (**n).val = val;
    (**n).next = 0;
}
 
int getlabel(char key[21])
{
    unsigned int hash = strhash(key);
    struct node* n = a[hash];
    while (n != 0) {
        if (strcmp((*n).key, key) == 0) {
            return (*n).val;
        }
        n = (*n).next;
    }
    return -1;
}
 
int reg[30];
int n = 0;
char cmd[200000][21];
FILE* out;
 
int queue[MASK + 1];
int bq = MASK;
int eq = MASK;
int mod = (1 << 16) - 1;
 
void put(int num)
{
    eq = (eq + 1) & MASK;
    queue[eq] = num & mod; // num % (mod + 1)
}
 
int get()
{
    if (bq == eq) return -1;
    bq = (bq + 1) & MASK;
    return queue[bq];
}
 
void save()
{
    out = fopen("quack.out", "w");
    int j = 0;
    for (int i = 0; i < 100000; i++) {
        if (j >= n) {
            break;
        }
        int k = j;
        j++;
        switch (*cmd[k]) {
        case '+': {
            put(get() + get());
            break;
        }
        case '-': {
            put(get() - get());
            break;
        }
        case '*': {
            put(get() * get());
            break;
        }
        case '/': {
            put(get() / get());
            break;
        }
        case '%': {
            put(get() % get());
            break;
        }
        case '>': {
            reg[*(cmd[k] + 1) - 'a'] = get();
            break;
        }
        case '<': {
            put(reg[*(cmd[k] + 1) - 'a']);
            break;
        }
        case 'P': {
            if (*(cmd[k] + 1) == '\0') {
                fprintf(out, "%d%c", get(), 10);
            }
            else {
                fprintf(out, "%d%c", reg[*(cmd[k] + 1) - 'a'], 10);
            }
            break;
        }
        case 'C': {
            if (*(cmd[k] + 1) == '\0') {
                fprintf(out, "%c", get() & 255);
            }
            else {
                fprintf(out, "%c", reg[*(cmd[k] + 1) - 'a'] & 255);
            }
            break;
        }
        case ':': {
            break;
        }
        case 'J': {
            j = getlabel(cmd[k] + 1);
            break;
        }
        case 'Z': {
            if (reg[*(cmd[k] + 1) - 'a'] == 0) {
                j = getlabel(cmd[k] + 2);
            }
            break;
        }
        case 'E': {
            if (reg[*(cmd[k] + 1) - 'a'] == reg[*(cmd[k] + 2) - 'a']) {
                j = getlabel(cmd[k] + 3);
            }
            break;
        }
        case 'G': {
            if (reg[*(cmd[k] + 1) - 'a'] > reg[*(cmd[k] + 2) - 'a']) {
                j = getlabel(cmd[k] + 3);
            }
            break;
        }
        case 'Q': {
            j = n;
            break;
        }
        default: {
            put(atoi(cmd[k]));
        }
        }
    }
    fclose(out);
}
 
void load()
{
    FILE* f;
 
    f = fopen("quack.in", "r");
    while (!feof(f)) {
        fscanf(f, "%s", &cmd[n]);
        if (*(cmd[n]) == ':') {
            putlabel(cmd[n] + 1, n);
        }
        n++;
    }
    fclose(f);
}
 
void main()
{
    load();
    save();
}
