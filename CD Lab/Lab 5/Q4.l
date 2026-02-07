%{
#include <stdio.h>

int sc = 0, pr = 0;
FILE *yyin;
%}

%%
scanf      { printf("READ"); sc++; }
printf     { printf("WRITE"); pr++; }
.|\n       { printf("%s", yytext); }
%%

int main() {
    yyin = fopen("input.c", "r");
    if (!yyin) {
        perror("input.c");
        return 1;
    }

    yylex();

    printf("\nScanf count = %d\nPrintf count = %d\n", sc, pr);
    return 0;
}

int yywrap() {
    return 1;
}

