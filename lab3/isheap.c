#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
 
int a[100000];
int n;
int k = 1;
 
void load() {
    FILE* In;
     
    In = fopen("isheap.in", "r");
    fscanf(In, "%d", &n);
    for (int i = 0; i < n; i++)
        fscanf(In, "%d", &a[i]);
    fclose(In);
}
 
void save() {
    FILE* Out;
    Out = fopen("isheap.out", "w");
    for (int i = 1; i < n; i++)
        if (a[i] >= a[(i - 1) / 2])
            k = k + 1;
    if (k == n)
        fprintf(Out, "YES");
    else
        fprintf(Out, "NO");
    fclose(Out);
}
 
void main()
{
    load();
    save();
}
