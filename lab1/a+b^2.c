#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
main() {
	FILE* f;
	long long a, b, c;
	f = fopen("aplusbb.in", "r");
	fscanf(f, "%lld%lld", &a, &b);
	fclose(f);
	c = a + b * b;
	f = fopen("aplusbb.out", "w");
	// printf("%I64d\n", c);
	fprintf(f, "%lld", c);
	fclose(f);
}
