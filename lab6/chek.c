#pragma comment(linker, "/STACK:64000000,64")
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
 
int infinity = 2000000000;
 
struct node {
    int val;
    int left;
    int right;
    int small;
    int big;
};
struct node a[200000];
int n;
int min(a, b) {
    return a > b ? b : a;
}
int max(a, b) {
    return a < b ? b : a;
}
void load() {
    FILE* f = fopen("check.in", "r");
    fscanf(f, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(f, "%d %d %d", &a[i].val, &a[i].left, &a[i].right);
        a[i].small = infinity;
        a[i].big = -infinity;
    }
    fclose(f);
}
int get_small(int i) {
    if (i == 0) {
        return infinity;
    }
    if (a[i - 1].small == infinity) {
        a[i - 1].small = min(a[i - 1].val, min(get_small(a[i - 1].left), get_small(a[i - 1].right)));
    }
    return a[i - 1].small;
}
int get_big(int i) {
    if (i == 0) {
        return -infinity;
    }
    if (a[i - 1].big == -infinity) {
        a[i - 1].big = max(a[i - 1].val, max(get_big(a[i - 1].left), get_big(a[i - 1].right)));
    }
    return a[i - 1].big;
}
void save(char *result) {
    FILE* f = fopen("check.out", "w");
    fprintf(f, "%s", result);
    fclose(f);
}
 
void main() {
    load();
    for (int i = 0; i < n; i++) {
        if (a[i].right > 0 && get_small(a[i].right) <= a[i].val) {
            save("NO");
            return;
        }
        if (a[i].left > 0 && get_big(a[i].left) >= a[i].val) {
            save("NO");
            return;
        }
    }
    save("YES");
}
