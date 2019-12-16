#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
main() {
	FILE *inputFile, *outputFile;
	int a, b, c;
	inputFile = fopen("aplusb.in", "r");
	fscanf(inputFile,"%d%d", &a, &b);
	fclose(inputFile);
	c = a + b;
	outputFile = fopen("aplusb.out", "w");
//	printf("%d\n", c);
	fprintf(outputFile, "%d\n", c);
	fclose(outputFile);
}
