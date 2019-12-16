#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
 
int a[100000];
int n = 0;
 
int parent(int i) {
 return (i - 1) / 2;
}
 
int left(int i) {
 return 2 * i + 1;
}
 
int right(int i) {
 return 2 * i + 2;
}
 
void do_swap(int i, int j) {
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}
 
void sift_down(int start, int end) {
    int root = start;
    while (left(root) <= end) {
        int child = left(root); 
        int swap = root;
 
        if (a[swap] < a[child])
            swap = child;
        if (child + 1 <= end && a[swap] < a[child + 1])
            swap = child + 1;
 
        if (swap == root)
            return;
        else {
            do_swap(root, swap);
            root = swap;
        }
    }
}
void heapify(int count)
{
    int start = parent(count - 1);
    while (start >= 0) {
        sift_down(start, count - 1);
        start = start - 1;
    }
}
 
void load()
{
    FILE* f;
 
    f = fopen("sort.in", "r");
    fscanf(f, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(f, "%d", &a[i]);
    }
    fclose(f);
}
 
void save()
{
    FILE* f;
 
    f = fopen("sort.out", "w");
    for (int i = 0; i < n; i++) {
        if (i > 0)
            fprintf(f, " ");
        fprintf(f, "%d", a[i]);
    }
    fclose(f);
}
 
void solve()
{
    heapify(n);
    int j = n - 1;
    for (int i = 0; i < n - 1; i++) {
        do_swap(0, n - 1 - i);
        j--;
        sift_down(0, j);
    }
}
 
void main()
{
    load();
    solve();
    save();
}
