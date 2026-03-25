#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#pragma warning (disable:4996)
int search(char *s, int start, int end, int c) {
	int mid;
	while (*s != '\0') {
		mid = (start + end) / 2;
		if (*s == 'N') {
			end = mid;
		}
		else {
			start = mid + 1;
		}
		s++;
	}
	return start;
}
int main(){
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	char* s = malloc(sizeof(char) * c);
	scanf("%s", s);
	int d = search(s, a, b, c);

	printf("%d", d);
	return 0;
}
