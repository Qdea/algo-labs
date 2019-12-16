#define _CRT_SECURE_NO_WARNINGS
 
#include <stdio.h>
#include <string.h>
 
struct queue_node_type {
    int val; // priority value
    int num; // number of string
};
 
struct queue_type {
    struct queue_node_type a[100000];
    int count;
};
 
struct list_node_type {
    int num; // number of string
    int id; // index of element in queue
};
 
struct list_type {
    struct list_node_type a[7000000];
    int count;
};
 
struct queue_type queue;
struct list_type list;
 
FILE* out;
 
int parent(int i)
{
    return (i - 1) / 2;
}
 
int left(int i)
{
    return 2 * i + 1;
}
 
int right(int i)
{
    return 2 * i + 2;
}
 
int find(int num)
{
    int p = 0;
    int q = list.count - 1;
    do {
        int m = (p + q) / 2;
        if (num == list.a[m].num) {
            return m;
        }
        if (num > list.a[m].num) {
            p = m;
        }
        else {
            q = m;
        }
    } while (q > p + 1);
    if (list.a[p].num == num) {
        return p;
    }
    else {
        return q;
    }
}
 
void do_swap(int i, int j)
{
    int xi = find(queue.a[i].num);
    int xj = find(queue.a[j].num);
 
    list.a[xi].id = j;
    list.a[xj].id = i;
 
    struct queue_node_type t = queue.a[i];
    queue.a[i] = queue.a[j];
    queue.a[j] = t;
}
 
void sift_up(int curr)
{
    int swap = parent(curr);
    while (swap >= 0 && queue.a[curr].val < queue.a[swap].val) {
        do_swap(curr, swap);
        curr = swap;
        swap = parent(curr);
    }
}
 
void sift_down(int curr)
{
    while (left(curr) < queue.count) {
        int child = left(curr);
        int swap = curr;
 
        if (queue.a[swap].val > queue.a[child].val)
            swap = child;
 
        if (child + 1 < queue.count && queue.a[swap].val > queue.a[child + 1].val)
            swap = child + 1;
 
        if (swap == curr)
            return;
        else {
            do_swap(curr, swap);
            curr = swap;
        }
    }
}
 
void extract_min()
{
    if (queue.count > 0) {
        fprintf(out, "%d\n", queue.a[0].val);
        do_swap(0, queue.count - 1);
        queue.count--;
        sift_down(0);
    }
    else {
        fprintf(out, "*\n");
    }
}
 
void decrease_key(int new_val, int str_num)
{
    int xi = find(str_num);
    int i = list.a[xi].id;
    queue.a[i].val = new_val;
    sift_up(i);
}
 
void push(int new_val, int str_num) {
 
    queue.a[queue.count].val = new_val;
    queue.a[queue.count].num = str_num;
 
    list.a[list.count].id = queue.count;
    list.a[list.count].num = str_num;
 
    queue.count++;
    list.count++;
 
    sift_up(queue.count - 1);
}
 
void main()
{
    char cmd[100];
    int x;
    int y;
    int z = 0;
    int ok;
    FILE* f;
 
    out = fopen("priorityqueue.out", "w");
    f = fopen("priorityqueue.in", "r");
 
    do {
        ok = 0;
        z++;
        fscanf(f, "%s", cmd);
        if (strcmp(cmd, "push") == 0) {
            ok = 1;
            fscanf(f, "%d", &x);
            push(x, z);
        }
        else if (strcmp(cmd, "extract-min") == 0) {
            ok = 1;
            extract_min();
        }
        else if (strcmp(cmd, "decrease-key") == 0) {
            ok = 1;
            fscanf(f, "%d %d", &y, &x);
            decrease_key(x, y);
        }
        cmd[0] = '\0';
    } while (ok);
 
    fclose(f);
    fclose(out);
}
