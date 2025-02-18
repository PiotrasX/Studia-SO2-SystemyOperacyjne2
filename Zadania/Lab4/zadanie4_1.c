#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Fraction {
    int num, den;
};

struct Fraction sum(struct Fraction x, struct Fraction y) {
    int a = x.num;
    int b = x.den;
    
    int c = y.num;
    int d = y.den;
    
    struct Fraction z;
    
    z.num = a*d + c*b;
    z.den = b*d;
    
    return z;
}

struct Fraction sub(struct Fraction x, struct Fraction y) {
    int a = x.num;
    int b = x.den;

    int c = y.num;
    int d = y.den;

    struct Fraction z;

    z.num = a*d - c*b;
    z.den = b*d;

    return z;
}

struct Fraction mul(struct Fraction x, struct Fraction y) {
    int a = x.num;
    int b = x.den;

    int c = y.num;
    int d = y.den;

    struct Fraction z;

    z.num = a*c;
    z.den = b*d;

    return z;
}

struct Fraction quo(struct Fraction x, struct Fraction y) {
    int a = x.num;
    int b = x.den;

    int c = y.num;
    int d = y.den;

    struct Fraction z;

    z.num = a*d;
    z.den = b*c;

    return z;
}

void print(struct Fraction x, struct Fraction y, const char op) {
    struct Fraction z;

    if (op == '+') z = sum(x, y);
    else if (op == '-') z = sub(x, y);
    else if (op == '*') z = mul(x, y);
    else if (op == '/' || op == ':') z = quo(x, y);
    else { 
        printf("%c - nieznane dzialanie", op);
        return;
    }

    printf("%d/%d %c %d/%d = %d/%d\n", x.num, x.den, op, y.num, y.den, z.num, z.den); 
}

void printFraction(struct Fraction x) {
    printf("%d/%d = ", x.num, x.den);

    if (x.den == 0) {
        printf("NaN\n");
        return;
    }

    if (x.num == 0) {
        printf("0\n");
        return;
    }

    int isNegative = (x.num < 0 && x.den > 0) || (x.num > 0 && x.den < 0);
    int absNum = abs(x.num);
    int absDen = abs(x.den);

    int totalPart = absNum / absDen;
    int restPart = absNum % absDen;

    if (restPart != 0) {
        if (absDen % restPart == 0) {
            absDen /= restPart;
            restPart = 1;
        }

        int i = 1;
        while (1) {
            if (absDen % i == 0 && restPart % i == 0) {
                absDen /= i;
                restPart /= i;
                i = 1;
            }

            if (i == restPart) break;
            i++;
        }
    }

    if (totalPart > 0 && restPart > 0) {
        printf("%s%d %d/%d\n", isNegative ? "-" : "", totalPart, restPart, absDen);
    } else if (totalPart > 0 && restPart == 0) {
        printf("%s%d\n", isNegative ? "-" : "", totalPart);
    } else {
        printf("%s%d/%d\n", isNegative ? "-" : "", restPart, absDen);
    }
}



// Zadanie 4.1.1

int isNumber(const char *s) {
    if (*s == '-' || *s == '+') s++;
    if (*s == '\0') return 0;

    while (*s != '\0') {
        if (!isdigit(*s)) {
            return 0;
        }
        s++;
    }

    return 1;
}

// Koniec zadania 4.1.1



// Zadanie 4.1.2

char *trim(char *s) {
    while (isspace(*s)) s++;
    char *end = s + strlen(s) - 1;
    while (end > s && isspace(*end)) end--;
    *(end + 1) = '\0';
    return s;
}

// Koniec zadania 4.1.2



// Zadanie 4.1.3

int getOperator(char *op, const char *s) {
    if (strlen(s) != 1) return 0;
    if (*s == '+' || *s == '-' || *s == '*' || *s == '/' || *s == ':') {
        *op = *s;
        return 1;
    }
    return 0;
}

// Koniec zadania 4.1.3



// Zadanie 4.1.4

int getFraction(struct Fraction *x, const char *s) {
    char *slash = strchr(s, '/');

    if (slash == NULL) {
        if (isNumber(s)) {
            x->num = atoi(s);
            x->den = 1;
            return 1;
        }
        return 0;
    } else {
        int length = slash - s;
        
        char *numerator = malloc(length + 1);
        if (numerator == NULL) return 0;

        strncpy(numerator, s, slash - s);
        numerator[slash - s] = '\0';
        char *denominator = slash + 1;

        if (isNumber(numerator) && isNumber(denominator)) {
            x->num = atoi(numerator);
            x->den = atoi(denominator);
            
            free(numerator);
            if (x->den == 0) return 0;         
            return 1;
        }
        free(numerator);
        return 0;
    }
    return 0;
}

// Koniec zadania 4.1.4



int main() {
    const char *test1 = "-12";
    const char *test2 = "123";
    const char *test3 = "-";
    const char *test4 = "abc";
    const char *test5 = "";
    printf("\nCzy '%s' to liczba? %d\n", test1, isNumber(test1));
    printf("Czy '%s' to liczba? %d\n", test2, isNumber(test2));
    printf("Czy '%s' to liczba? %d\n", test3, isNumber(test3));
    printf("Czy '%s' to liczba? %d\n", test4, isNumber(test4));
    printf("Czy '%s' to liczba? %d\n\n", test5, isNumber(test5));

    char test6[] = "   Ala ma kota!   ";
    char test7[] = "     ";
    printf("'%s' -> '%s'\n", test6, trim(test6));
    printf("'%s' -> '%s'\n\n", test7, trim(test7));

    char op;
    const char *test8 = "+";
    const char *test9 = "x";
    const char *test10 = "/";
    const char *test11 = "++";
    printf("Czy '%s' to poprawny operator? %d\n", test8, getOperator(&op, test8));
    printf("Czy '%s' to poprawny operator? %d\n", test9, getOperator(&op, test9));
    printf("Czy '%s' to poprawny operator? %d\n", test10, getOperator(&op, test10));
    printf("Czy '%s' to poprawny operator? %d\n\n", test11, getOperator(&op, test11));

    struct Fraction frac;
    const char *test12 = "37/5";
    const char *test13 = "-5/27";
    const char *test14 = "15";
    const char *test15 = "12/a";
    const char *test16 = "c/13";
    const char *test17 = "x";
    printf("Czy '%s' to poprawny ulamek? %d\n", test12, getFraction(&frac, test12));
    printf("Czy '%s' to poprawny ulamek? %d\n", test13, getFraction(&frac, test13));
    printf("Czy '%s' to poprawny ulamek? %d\n", test14, getFraction(&frac, test14));
    printf("Czy '%s' to poprawny ulamek? %d\n", test15, getFraction(&frac, test15));
    printf("Czy '%s' to poprawny ulamek? %d\n", test16, getFraction(&frac, test16));
    printf("Czy '%s' to poprawny ulamek? %d\n\n", test17, getFraction(&frac, test17));

    return 0;
}
