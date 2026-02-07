%{
#include <stdio.h>
int pi = 0, ni = 0, pf = 0, nf = 0;
%}

%%
[+]?[0-9]+\.[0-9]+   { pf++; }
-[0-9]+\.[0-9]+     { nf++; }
[+]?[0-9]+           { pi++; }
-[0-9]+              { ni++; }
.|\n                 ;
%%

int main() {
    yylex();
    printf("Positive Integers = %d\nNegative Integers = %d\n", pi, ni);
    printf("Positive Floats = %d\nNegative Floats = %d\n", pf, nf);
    return 0;
}

int yywrap() {
    return 1;
}
