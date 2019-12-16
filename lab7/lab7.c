#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
 
enum {
    TASK_A = 1,
    TASK_B = 2,
    TASK_C = 3,
    TASK_D = 4,
    TASK_E = 5
};
 
int task = TASK_A;
struct node {
    int num;
    int value;
    int height;
    int link[3];
};
 
int n = 0;
int deleted = 0;
int root = 0;
struct node a[200001];
 
int max(int a, int b)
{
    return a > b ? a : b;
}
 
void show(int curr, int column)
{
    int first = curr;
    for (int i = 0; i < column; i++) {
        printf("|   ");
    }
    printf("\n");
    for (int i = 0; i < column - 1; i++) {
        printf("|   ");
    }
    printf("%d", a[curr].value);
    int prev = 0;
    curr = a[curr].link[2];
    while (curr > 0) {
        printf(" - %d", a[curr].value);
        prev = curr;
        column++;
        curr = a[curr].link[2];
    }
    column--;
    printf("\n");
    if (prev == 0 && a[first].link[1]) {
        show(a[first].link[1], column + 1);
    }
    while (prev > 0 && prev != a[a[prev].link[0]].link[1]) {
        if (a[prev].link[1]) {
            show(a[prev].link[1], column + 1);
        }
        column--;
        prev = a[prev].link[0];
    }
}
 
int find(int value)
{
    int curr = root;
    while (curr > 0) {
        if (value == a[curr].value)
            return 1;
        curr = a[curr].link[value < a[curr].value ? 1 : 2];
    }
    return 0;
}
 
int height(int curr)
{
    if (curr == 0)
        return -1;
 
    if (a[curr].height == -1)
        a[curr].height = max(height(a[curr].link[1]), height(a[curr].link[2])) + 1;
 
    return a[curr].height;
}
 
int balance(int curr)
{
    return height(a[curr].link[2]) - height(a[curr].link[1]);
}
 
void rotation_small(int curr, int p, int q)
{
    int s = curr;
    int w = a[s].link[0];
    int t = a[s].link[q];
    int y = a[t].link[p];
 
    a[t].link[0] = a[s].link[0];
 
    a[y].link[0] = s;
    a[s].link[q] = y;
 
    a[s].link[0] = t;
    a[t].link[p] = s;
 
    a[t].link[0] = w;
    if (root == curr)
        root = t;
    else
        a[w].link[a[t].value < a[w].value ? 1 : 2] = t;
 
    a[s].height = -1;
 
    while (t > 0) {
        a[t].height = -1;
        t = a[t].link[0];
    }
}
 
void rotation_big(int curr, int p, int q)
{
    int s = curr;
    int w = a[s].link[0];
    int t = a[s].link[q];
    int u = a[t].link[p];
    int x = a[u].link[p];
    int y = a[u].link[q];
 
    a[u].link[p] = s;
    a[s].link[0] = u;
 
    a[u].link[q] = t;
    a[t].link[0] = u;
 
    a[s].link[q] = x;
    a[x].link[0] = s;
 
    a[t].link[p] = y;
    a[y].link[0] = t;
 
    a[u].link[0] = w;
    if (root == curr)
        root = u;
    else
        a[w].link[a[u].value < a[w].value ? 1 : 2] = u;
 
    a[s].height = -1;
    a[t].height = -1;
    while (u > 0) {
        a[u].height = -1;
        u = a[u].link[0];
    }
}
 
void rotation(int curr, int p, int q)
{
    int s = curr;
    int t = a[s].link[q];
 
    int diff = p == 1 ? -1 : 1;
    if (balance(t) == diff)
        rotation_big(curr, p, q);
    else
        rotation_small(curr, p, q);
}
 
void update(int curr)
{
    if (curr == 0)
        return;
 
    if (balance(curr) == 2)
        rotation(curr, 1, 2);
 
    if (balance(curr) == -2)
        rotation(curr, 2, 1);
 
    update(a[curr].link[0]);
}
 
void insert(int value)
{
    int curr = root;
    if (curr == 0) {
        n++;
        a[n].value = value;
        a[n].link[0] = 0;
        a[n].link[1] = 0;
        a[n].link[2] = 0;
        a[n].height = -1;
        root = n;
    }
    else {
        int prev = 0;
        while (curr > 0) {
            prev = curr;
            if (value == a[curr].value)
                return;
            curr = a[curr].link[value < a[curr].value ? 1 : 2];
        }
        n++;
        a[n].value = value;
        a[n].link[0] = prev;
        a[n].link[1] = 0;
        a[n].link[2] = 0;
        a[n].height = -1;
        a[prev].link[value < a[prev].value ? 1 : 2] = n;
 
        curr = prev;
        while (curr > 0) {
            a[curr].height = -1;
            curr = a[curr].link[0];
        }
        update(prev);
    }
}
 
void delete(int value)
{
    int curr = root;
    int found = 0;
    while (found == 0 && curr > 0) {
        if (value == a[curr].value)
            found = 1;
        else
            curr = a[curr].link[value < a[curr].value ? 1 : 2];
    }
    if (curr > 0) {
        deleted++;
        if (!a[curr].link[1] && !a[curr].link[2]) {
            int p = a[curr].link[0];
            if (p) {
                a[p].link[value < a[p].value ? 1 : 2] = 0;
                curr = p;
                while (curr > 0) {
                    a[curr].height = -1;
                    curr = a[curr].link[0];
                }
                update(p);
            }
            else {
                root = 0;
            }
        }
        else
            if (!a[curr].link[1]) {
                int temp = curr;
                int p = a[temp].link[0];
                int q = a[temp].link[2];
                if (p) {
                    a[p].link[a[q].value < a[p].value ? 1 : 2] = q;
                    a[q].link[0] = p;
                    curr = p;
                    while (curr > 0) {
                        a[curr].height = -1;
                        curr = a[curr].link[0];
                    }
                    update(p);
                }
                else {
                    root = q;
                    a[q].link[0] = 0;
                }
            }
            else {
                int temp = a[curr].link[1];
                while (a[temp].link[2] > 0)
                    temp = a[temp].link[2];
 
                a[curr].value = a[temp].value;
                int p = a[temp].link[0];
                int q = a[temp].link[1];
                if (p) {
                    a[p].link[p == curr ? 1 : 2] = q;
                    a[q].link[0] = p;
                    curr = p;
                    while (curr > 0) {
                        a[curr].height = -1;
                        curr = a[curr].link[0];
                    }
                    update(p);
                }
                else {
                    root = q;
                    a[q].link[0] = 0;
                }
            }
    }
}
 
void calc_num(int curr, int* num)
{
    if (curr == 0)
        return;
 
    a[curr].num = ++ * num;
    calc_num(a[curr].link[1], num);
    calc_num(a[curr].link[2], num);
}
 
void print_tree(FILE* f, int curr)
{
    if (curr == 0)
        return;
 
    int num = 0;
    if (curr == root)
        calc_num(curr, &num);
 
    fprintf(f, "%d %d %d\n", a[curr].value, a[a[curr].link[1]].num, a[a[curr].link[2]].num);
    print_tree(f, a[curr].link[1]);
    print_tree(f, a[curr].link[2]);
}
 
void solve()
{
    FILE* fr;
    FILE* fw;
 
    switch (task) {
    case TASK_A: {
        fr = fopen("balance.in", "r");
        fw = fopen("balance.out", "w");
        break;
    }
    case TASK_B: {
        fr = fopen("rotation.in", "r");
        fw = fopen("rotation.out", "w");
        break;
    }
    case TASK_C: {
        fr = fopen("addition.in", "r");
        fw = fopen("addition.out", "w");
        break;
    }
    case TASK_D: {
        fr = fopen("deletion.in", "r");
        fw = fopen("deletion.out", "w");
        break;
    }
    case TASK_E: {
        fr = fopen("avlset.in", "r");
        fw = fopen("avlset.out", "w");
        break;
    }
    default: return;
    }
 
    int m;
    fscanf(fr, "%d", &m);
    if (task != TASK_E)
        n = m;
    for (int i = 1; i <= m; i++) {
        if (task == TASK_E) {
            int x;
            char operation[2];
 
            fscanf(fr, "%s %d", operation, &x);
            switch (*operation) {
            case 'A': {
                insert(x);
                fprintf(fw, "%d\n", balance(root));
                break;
            }
            case 'C': {
                if (find(x))
                    fprintf(fw, "Y\n");
                else
                    fprintf(fw, "N\n");
                break;
            }
            case 'D': {
                delete(x);
                fprintf(fw, "%d\n", balance(root));
                break;
            }
            }
            // show(root, 1);
        }
        else {
            fscanf(fr, "%d %d %d", &a[i].value, &a[i].link[1], &a[i].link[2]);
            a[a[i].link[1]].link[0] = i;
            a[a[i].link[2]].link[0] = i;
            a[i].num = i;
            a[i].height = -1;
        }
    }
 
    switch (task) {
    case TASK_B: {
        root = 1;
        a[root].link[0] = 0;
        rotation(root, 1, 2);
        break;
    }
    case TASK_C: {
        int x;
        root = 1;
        a[root].link[0] = 0;
        fscanf(fr, "%d", &x);
        insert(x);
        break;
    }
    case TASK_D: {
        int x;
        root = 1;
        a[root].link[0] = 0;
        fscanf(fr, "%d", &x);
        delete(x);
        break;
    }
    }
 
    switch (task) {
    case TASK_A:
        for (int i = 1; i <= n; i++)
            fprintf(fw, "%d\n", balance(i));
        break;
    case TASK_B:
    case TASK_C:
    case TASK_D:
        fprintf(fw, "%d\n", n - deleted);
        print_tree(fw, root);
        break;
    }
 
    fclose(fr);
    fclose(fw);
}
 
void main()
{
    solve();
}
