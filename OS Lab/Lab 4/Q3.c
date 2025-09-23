#include <stdio.h>

int main() {
    int num = 1234;
    float pi = 3.14159;
    char ch = 'A';
    char str[] = "Hello";

    printf("Integer (%%d) : %d\n", num);         // signed decimal
    printf("Integer (%%i) : %i\n", num);         // signed decimal (same as %d)
    printf("Unsigned (%%u) : %u\n", num);        // unsigned decimal
    printf("Octal (%%o) : %o\n", num);           // octal
    printf("Hex (%%x) : %x\n", num);             // hexadecimal (lowercase)
    printf("Hex (%%X) : %X\n", num);             // hexadecimal (uppercase)

    printf("Character (%%c) : %c\n", ch);        // character
    printf("String (%%s) : %s\n", str);          // string

    printf("Float (%%f) : %f\n", pi);            // decimal notation
    printf("Exponential (%%e) : %e\n", pi);      // scientific notation (lowercase e)
    printf("Exponential (%%E) : %E\n", pi);      // scientific notation (uppercase E)
    printf("Shortest (%%g) : %g\n", pi);         // shortest of %f or %e
    printf("Shortest (%%G) : %G\n", pi);         // shortest of %f or %E

    printf("Pointer (%%p) : %p\n", (void*)&num); // memory address
    printf("Percent sign (%%%%) : %%\n");        // print %

    return 0;
}
