#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double expression(void);

double vars[26]; // variables

char get(void) { char c = getchar(); return c; } // get one byte
char peek(void) { char c = getchar(); ungetc(c, stdin); return c; } // peek at next byte
double number(void) { double d; scanf("%lf", &d); return d; } // read one double

void expect(char c) { // expect char c from stream
    char d = get();
    if (c != d) {
        fprintf(stderr, "Error: Expected %c but got %c.\n", c, d);
    }
}

double factor(void) { // read a factor
    double f;
    char c = peek();
    if (c == '(') { // an expression inside parentheses?
        expect('(');
        f = expression();
        expect(')');
    } else if (c >= 'A' && c <= 'Z') { // a variable?
        expect(c);
        f = vars[c - 'A'];
    } else { // or, a number?
        f = number();
    }
    return f;
}

double term(void) { // read a term
    double t = factor();
    while (peek() == '*' || peek() == '/') { // * or / more factors
        char c = get();
        if (c == '*') {
            t = t * factor();
        } else {
            t = t / factor();
        }
    }
    return t;
}

double expression(void) { // read an expression
    double e = term();
    while (peek() == '+' || peek() == '-') { // + or - more terms
        char c = get();
        if (c == '+') {
            e = e + term();
        } else {
            e = e - term();
        }
    }
    return e;
}

double statement(void) { // read a statement
    double ret;
    char c = peek();
    if (c >= 'A' && c <= 'Z') { // variable?
        expect(c);
        if (peek() == '=') { // assignment?
            expect('=');
            double val = expression();
            vars[c - 'A'] = val;
            ret = val;
        } else {
            ungetc(c, stdin);
            ret = expression();
        }
    } else {
        ret = expression();
    }
    expect('\n');
    return ret;
}

void execute_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s.\n", filename, "This is probably non function files, or it is invalid.");
        exit(EXIT_FAILURE);
    }
    int c;
    while ((c = fgetc(file)) != EOF) {
        ungetc(c, stdin);
        double v = statement();
        printf(" = %lf\n", v); fflush(stdout);
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            execute_file(argv[i]);
        }
    } else {
        printf("> "); fflush(stdout);
        for (;;) {
            double v = statement();
            printf(" = %lf\n> ", v); fflush(stdout);
        }
    }
    return EXIT_SUCCESS;
}
