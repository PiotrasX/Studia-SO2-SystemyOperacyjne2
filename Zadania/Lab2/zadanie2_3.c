#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float a(int n) {
	if (n == 0) return 1;
	if (n == 1) return 4;
	
	return 2 * a(n - 1) + 0.5 * a(n - 2);
}

float a_seq(int n) {
	static int wywolanie;
	
	wywolanie++;
	
	printf("a%u(%u) = %f\n", wywolanie, n, a(n));
	
	if (n == 0) return 1;
	if (n == 1) return 4;
	
	return a_seq(n - 1) + a_seq(n - 2);
}

int main() {
    int n = 4;
    
    printf("\n");
    a_seq(4);
    printf("\n");

    return 0;
}
