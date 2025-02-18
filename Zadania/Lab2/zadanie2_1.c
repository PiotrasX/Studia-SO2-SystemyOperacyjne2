#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int f(int n) {
	if (n == 0) return 1;
	if (n == 1) return 1;
	
	return f(n - 1) + f(n - 2);
}

int fibo(int n) {
	static int wywolanie;
	
	wywolanie++;
	
	printf("fibo%u(%u) = %u\n", wywolanie, n, f(n));
	
	if (n == 0) return 1;
	if (n == 1) return 1;
	
	return fibo(n - 1) + fibo(n - 2);
}

int main() {
    int n = 4;
    
    printf("\n");
    fibo(n);
    printf("\n");

    return 0;
}
