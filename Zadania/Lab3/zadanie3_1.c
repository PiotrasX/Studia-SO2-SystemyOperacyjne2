#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Fraction {
    int num, den;
};

/*
a/b + c/d = (a*d)/(b*d) + (c*b)/(d*b) = (a*d + c*b) / (b*d)
*/

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



// Zadanie 3.1.1

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

// Koniec zadania 3.1.1



// Zadanie 3.1.2

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

// Koniec zadania 3.1.2



int main() {
    struct Fraction x = {2, 3};
    struct Fraction y = {1, 4};
    
    printf("\n");
    print(x, y, '+');
    print(x, y, '-');
    print(x, y, '*');
    print(x, y, '/');
    print(x, y, ':');
    print(x, y, '$');
    printf("\n\n");

    printFraction((struct Fraction) {2, 0});
    printFraction((struct Fraction) {0, 2});
    printFraction((struct Fraction) {2, 4});
    printFraction((struct Fraction) {-1, 2});
    printFraction((struct Fraction) {1, -2});
    printFraction((struct Fraction) {4, -2});
    printFraction((struct Fraction) {5, -2});
    printf("\n");

    return 0;
}
