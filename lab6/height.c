#pragma comment(linker, "/STACK:64000000,64")
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
 
struct node {
    int val;
    int left;
    int right;
    int height;
};
struct node a[200000];
int n;
int max(a, b) {
    return a < b ? b : a;
}
void load() {
    FILE* f = fopen("height.in", "r");
    fscanf(f, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(f, "%d %d %d", &a[i].val, &a[i].left, &a[i].right);
        a[i].height = -1;
    }
    fclose(f);
}
int tree_height(int i) {
    if (i == 0) {
        return 0;
    }
    if (a[i - 1].height == -1) {
        a[i - 1].height = max(tree_height(a[i - 1].left), tree_height(a[i - 1].right)) + 1;
    }
    return a[i - 1].height;
}
void save(int result) {
    FILE* f = fopen("height.out", "w");
    fprintf(f, "%d", result);
    fclose(f);
}
 
void main() {
    load();
    int result = 0;
    for (int i = 0; i < n; i++) {
        int h = tree_height(i + 1);
        if (h > result)
            result = h;
    }
    save(result);
}
