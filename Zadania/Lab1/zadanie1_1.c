#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int a;
    float b;
    char c[10];

    printf("\na = ");
    scanf("%d", &a);
    printf("int value a = %d\n", a);

    printf("\nb = ");
    scanf("%f", &b);
    printf("float value b = %f\n", b);

    printf("\nc = ");
    scanf("%9s", &c);
    printf("string value c = %s\n", c);



    // Zadanie 1.1.1

    fflush(stdin);
    printf("\nd = ");
    fgets(c, 10, stdin);
    printf("string value d = %s\n", c);

    // Koniec zadania 1.1.1



    // Zadanie 1.1.2

    double f;
    printf("e = ");
    scanf("%lf", &f);
    printf("double value e = %.8lf\n", f);

    // Koniec zadania 1.1.2



    // Zadanie 1.1.3

    char i;
    while ((i = getchar()) != '\n' && i != EOF);

    char g[25];
    printf("\nf = ");
    scanf("%[^\n]", &g);
    printf("string value f = %s\n", g);

    // Koniec zadania 1.1.3



    // Zadanie 1.1.4

    while ((i = getchar()) != '\n' && i != EOF);

    fflush(stdin);
    printf("\ng = ");
    fgets(g, sizeof(g), stdin);
    printf("string value g = %s\n", g);

    // Koniec zadania 1.1.4



    return 0;
}
