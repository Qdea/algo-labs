#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
 
struct node {
    int val;
    int left;
    int right;
    int parent;
};
 
struct node a[100001];
int count = 1;
int root = 0;
 
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
    printf("%d", a[curr].val);
    int prev = 0;
    curr = a[curr].right;
    while (curr > 0) {
        printf(" - %d", a[curr].val);
        prev = curr;
        column++;
        curr = a[curr].right;
    }
    column--;
    printf("\n");
//  printf("prev: %d\n", a[prev].val);
    if (prev == 0 && a[first].left) {
        show(a[first].left, column + 1);
    }
    while (prev > 0 && prev != a[a[prev].parent].left) {
        if (a[prev].left) {
            show(a[prev].left, column+1);
        }
        column--;
        prev = a[prev].parent;
    }
}
void insert(int parent, int *curr, int x)
{
    if (*curr == 0) {
        a[count].val = x;
        a[count].left = 0;
        a[count].right = 0;
        a[count].parent = parent;
        *curr = count;
        count++;
    }
    else if(x < a[*curr].val) {
        insert(*curr, &a[*curr].left, x);
    }
    else if (x > a[*curr].val) {
        insert(*curr, &a[*curr].right, x);
    }
}
 
int find(int curr, int x)
{
    if (x == a[curr].val) {
        return curr;
    }
    else if (x < a[curr].val) {
        return a[curr].left > 0 ? find(a[curr].left, x) : 0;
    }
    else {
        return a[curr].right > 0 ? find(a[curr].right, x) : 0;
    }
}
 
extern void delete(int x);
 
void next(int curr, int x, int* found, int* y)
{
    /*
    if (curr == 0)
        return;
 
    if (*found == 1 && a[curr].val > x && a[curr].val < *y) {
        *y = a[curr].val;
    }
    if (*found == 0 && a[curr].val > x ) {
        *y = a[curr].val;
        *found = 1;
    }
 
    if (x < a[curr].val)
        next(a[curr].left, x, found, y);
 
    next(a[curr].right, x, found, y);
    return;
    */
    int added = 0;
    curr = find(curr, x);
    int parent = a[curr].parent;
    if (curr == 0) {
        insert(0, &root, x);
        curr = find(root, x);
        parent = a[curr].parent;
        added = 1;
    }
    if (a[curr].right > 0) {
        curr = a[curr].right;
        *found = 1;
        *y = a[curr].val;
        while (a[curr].left > 0) {
            curr = a[curr].left;
            *y = a[curr].val;
        }
    }
    else {
        while (a[curr].parent > 0) {
            parent = a[curr].parent;
            if (a[parent].left == curr) {
                *found = 1;
                *y = a[parent].val;
                break;
            }
            curr = parent;
        }
    }
    if (added)
        delete(x);
}
 
void prev(int curr, int x, int* found, int* y)
{
    int added = 0;
    curr = find(curr, x);
    int parent = a[curr].parent;
    if (curr == 0) {
        insert(0, &root, x);
        curr = find(root, x);
        parent = a[curr].parent;
        added = 1;
    }
    if (a[curr].left > 0) {
        curr = a[curr].left;
        *found = 1;
        *y = a[curr].val;
        while (a[curr].right > 0) {
            curr = a[curr].right;
            *y = a[curr].val;
        }
    }
    else {
        while (a[curr].parent > 0) {
            parent = a[curr].parent;
            if (a[parent].right == curr) {
                *found = 1;
                *y = a[parent].val;
                break;
            }
            curr = parent;
        }
    }
    if (added)
        delete(x);
}
 
void delete(int x)
{
    int curr = find(root, x);
    if (curr == 0) {
        return;
    }
    int parent = a[curr].parent;
    if (a[curr].left == 0 && a[curr].right == 0) {
        if (parent == 0) {
            root = 0;
        }
        else if (a[parent].left == curr) {
            a[parent].left = 0;
        }
        else {
            a[parent].right = 0;
        }
    }
    else if (a[curr].left == 0) {
        if (parent == 0) {
            root = a[curr].right;
            a[root].parent = 0;
        }
        else if (a[parent].left == curr) {
            a[parent].left = a[curr].right;
            a[a[parent].left].parent = parent;
        }
        else {
            a[parent].right = a[curr].right;
            a[a[parent].right].parent = parent;
        }
    }
    else if (a[curr].right == 0) {
        if (parent == 0) {
            root = a[curr].left;
            a[root].parent = 0;
        }
        else if (a[parent].left == curr) {
            a[parent].left = a[curr].left;
            a[a[parent].left].parent = parent;
        }
        else {
            a[parent].right = a[curr].left;
            a[a[parent].right].parent = parent;
        }
    }
    else {
        int found = 0;
        int swap = 0;
        next(curr, a[curr].val, &found, &swap);
        swap = find(root, swap);
        int val = a[swap].val;
        delete(val);
        a[curr].val = val;
    }
}
 
void main()
{
    char cmd[10];
    int x;
    FILE* f = fopen("bstsimple.in", "r");
    FILE* out = fopen("bstsimple.out", "w");
    while (!feof(f)) {
        fscanf(f, "%s", &cmd);
        if (strcmp(cmd, "insert") == 0) {
            fscanf(f, "%d", &x);
            if (find(root, x) == 0) {
                insert(0, &root, x);
            }
        }
        else if (strcmp(cmd, "delete") == 0) {
            fscanf(f, "%d", &x);
            delete(x);
        }
        else if (strcmp(cmd, "exists") == 0) {
            fscanf(f, "%d", &x);
            if (find(root, x) > 0) {
                fprintf(out, "true\n");
            }
            else {
                fprintf(out, "false\n");
            }
        }
        else if (strcmp(cmd, "next") == 0) {
            int found = 0;
            int y = 0;
            fscanf(f, "%d", &x);
            next(root, x, &found, &y);
            if (found) {
                fprintf(out, "%d\n", y);
            }
            else {
                fprintf(out, "none\n");
            }
        }
        else if (strcmp(cmd, "prev") == 0) {
            int found = 0;
            int y = 0;
            fscanf(f, "%d", &x);
            prev(root, x, &found, &y);
            if (found) {
                fprintf(out, "%d\n", y);
            }
            else {
                fprintf(out, "none\n");
            }
        }
        *cmd = '\0';
    }
    fclose(out);
    fclose(f);
}
