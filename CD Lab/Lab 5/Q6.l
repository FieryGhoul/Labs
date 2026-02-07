%{
#include <stdio.h>
#include <ctype.h>

FILE *yyin;
%}

%%
"/*"([^*]|\*+[^*/])*\*+"/"   { printf("%s", yytext); }   /* multi-line comment */
"//".*                      { printf("%s", yytext); }   /* single-line comment */
[A-Z]                       { putchar(tolower(yytext[0])); }
.|\n                        { printf("%s", yytext); }
%%

int main() {
    yyin = fopen("input.c", "r");
    if (!yyin) {
        perror("input.c");
        return 1;
    }
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}

