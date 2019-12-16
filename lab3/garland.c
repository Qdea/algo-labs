#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
 
double eps1 = 10e-12;
double eps2 = 10e-10;
 
int n;
double a;
double b = 0;
 
void load()
{
    FILE* f;
    f = fopen("garland.in", "r");
    fscanf(f, "%d%lf", &n, &a);
    fclose(f);
}
 
void save()
{
    FILE* f;
    f = fopen("garland.out", "w");
    fprintf(f, "%.2lf", fabs(b));
    fclose(f);
}
 
double height(int t, double curr)
{
    double prev = 0.0;
    double next;
    for (int i = 0; i < t; i++) {
        next = (curr + 1.0) * 2.0 - prev;
        prev = curr;
        curr = next;
    }
    return curr;
}
 
void solve()
{
    for (int t = 1; t <= n; t++) {
        double down = 0.0;
        double up = 2.0;
        double y;
        double hA;
        do {
            y = (down + up) / 2.0;
            // down .. y .. up
            hA = height(t - 1, y);
            if (hA > a) {
                up = y; // down .. x
            }
            else {
                down = y; // x .. up
            }
        } while (fabs(up - down) > eps1 && fabs(hA - a) > eps2);
        if (fabs(hA - a) <= eps2 && n - t > 1) {
            b = height(n - t - 2, 2 - y);
            break;
        }
    }
}
 
void main()
{
    load();
    solve();
    save();
}
