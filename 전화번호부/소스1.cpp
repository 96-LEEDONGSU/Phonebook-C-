#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

struct data {
	char c1;
	short num1;
	int num2;
	char s1[20];
};

int main() {
	struct data d1;
	memset(&d1, 0, sizeof(d1));

	d1.c1 = 'a';
	d1.num1 = 32100;
	d1.num2 = 2100000100;
	strcpy(d1.s1, "hello, world");

	FILE* fp = fopen("data2.bin", "wb");

	fwrite(&d1, sizeof(d1), 1, fp);

	fclose(fp);
	
	FILE* fp2 = fopen("data2.bin", "rb");
	fread(&d1, sizeof(d1), 1, fp2);
	printf("%c %d %d %s", d1.c1, d1.num1, d1.num2, d1.s1);
	fclose(fp2);
	return 0;
}