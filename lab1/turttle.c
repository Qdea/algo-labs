#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MaxN 1000
int a[MaxN][MaxN];
long long b[MaxN][MaxN];

void main() {
	FILE* f;
	int h, w, x, y;

	f = fopen("turtle.in", "r");
	fscanf(f, "%d%d", &h, &w);
	for (y = 0; y < h; y++) {
		for (x = 0; x < w; x++) {
			fscanf(f, "%d", &a[x][y]);
			b[x][y] = a[x][y];
		}
	}
	fclose(f);

	for (y = h - 1; y >= 0; y--) {
		for (x = 0; x < w; x++) {
			if (x == 0 && y == h - 1) {
			} 
			else if (x == 0) {
				b[x][y] += b[x][y + 1];
			}
			else if (y == h - 1) {
				b[x][y] += b[x - 1][y];
			}
			else {
				if (b[x][y + 1] > b[x - 1][y]) {
					b[x][y] += b[x][y + 1];
				}
				else {
					b[x][y] += b[x - 1][y];
				}
			}
		}
	}
	
	if (w > 0) {
		f = fopen("turtle.out", "w");
		printf("%I64d\n", b[w - 1][0]);
		fprintf(f, "%I64d", b[w - 1][0]);
		fclose(f);
	}
}
