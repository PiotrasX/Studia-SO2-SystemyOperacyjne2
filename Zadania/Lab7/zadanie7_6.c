#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_DIGITS 256

int main() {
	char buffer_a[MAX_DIGITS];
	char buffer_b[MAX_DIGITS];

    printf("\n");
    printf("a = ");
    scanf("%s", buffer_a);
    printf("b = ");
    scanf("%s", buffer_b);
    printf("\n");

    int a = atoi(buffer_a);
    int b = atoi(buffer_b);

    if (b > a) {
        int temp = b;
        b = a;
        a = temp;
    }

    int max_ab = fmax(abs(a), abs(b));
    int width_max_ab = max_ab > 0 ? log10(max_ab) + 1 : 1;
	int* carry = (int*)malloc((width_max_ab + 1) * sizeof(int));
	memset(carry, 0, sizeof(carry));

    int result = 0;
    int carry_value = 0;
    int sum = 0;
    int i = 0;
	
    for (i = 0; i < width_max_ab; i++) {
        int digit_a = (a / (int)pow(10, i)) % 10;
        int digit_b = (b / (int)pow(10, i)) % 10;
        
		sum = digit_a + digit_b + carry_value;
		
		if (sum >= 10) {
            carry[i + 1] = 1;
            carry_value = 1;
            sum -= 10;
        } else {
            carry_value = 0;
        }

        result += sum * (int)pow(10, i);
	}

    if (carry_value) {
        result += carry_value * (int)pow(10, i);
    }
		
    printf(" ");
    for (i = width_max_ab; i >= 0; i--) printf("%c", carry[i] == 1 ? '1' : ' ');
    printf("\n");
    printf("%*d", width_max_ab + 2, a);
    printf("\n");
    printf("+%*d", width_max_ab + 1, b);
    printf("\n");
    for (i = 0; i <= width_max_ab + 1; i++) printf("-");
    printf("\n");
    printf("%*d", width_max_ab + 2, a + b);
    printf("\n\n");

    return 0;
}
