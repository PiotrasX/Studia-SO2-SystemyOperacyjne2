#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Fraction {
    int num, den;
};

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

void simplify(struct Fraction *x) {
    int divisor = gcd(abs(x->num), abs(x->den));
    x->num /= divisor;
    x->den /= divisor;
}

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
    simplify(&x);

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

    if (restPart == 0) {
        printf("%s%d", isNegative ? "-" : "", totalPart);
    } else if (totalPart != 0) {
        printf("%s%d %d/%d", isNegative ? "-" : "", totalPart, restPart, absDen);
    } else {
        printf("%s%d/%d", isNegative ? "-" : "", absNum, absDen);
    }
}

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

char *trim(char *s) {
    while (isspace(*s)) s++;
    char *end = s + strlen(s) - 1;
    while (end > s && isspace(*end)) end--;
    *(end + 1) = '\0';
    return s;
}

int getOperator(char *op, const char *s) {
    if (strlen(s) != 1) return 0;
    if (*s == '+' || *s == '-' || *s == '*' || *s == '/' || *s == ':') {
        *op = *s;
        return 1;
    }
    return 0;
}

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

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void safeInput(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        if (buffer[strlen(buffer) - 1] != '\n') {
            clearInputBuffer();
        } else {
            buffer[strlen(buffer) - 1] = '\0';
        }
    } else {
        printf("Blad odczytu danych!\n");
        exit(1);
    }
}

int main() {
    struct Fraction a, b, result;
    char op[2];
    char buffer[100];

    printf("\n");

    do {
        printf("a/b = ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
    } while (!getFraction(&a, buffer));

    do {
        printf("c/d = ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
    } while (!getFraction(&b, buffer));

    printf("\n");

    do {
        printf("op = ");
        fgets(op, sizeof(op), stdin);
        op[strcspn(op, "\n")] = '\0';
        if (!getOperator(op, op)) {
            clearInputBuffer();
        }
    } while (!getOperator(op, op));

    switch (op[0]) {
        case '+':
            result = sum(a, b);
            break;
        case '-':
            result = sub(a, b);
            break;
        case '*':
            result = mul(a, b);
            break;
        case '/':
        case ':':
            result = quo(a, b);
            break;
        default:
            printf("Nieznany operator!\n");
            return 1;
    }

    printf("\n");
    printFraction(a);
    printf(" %s ", op);
    printFraction(b);
    printf(" = ");
    printFraction(result);
    printf("\n\n");

    return 0;
}
