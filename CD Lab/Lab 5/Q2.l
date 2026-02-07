%{
#include <stdio.h>
int words = 0, chars = 0, blanks = 0, lines = 0;
%}

%%
\n              { lines++; chars++; }
[ \t]+          { blanks += yyleng; chars += yyleng; }
[^ \t\n]+       { words++; chars += yyleng; }
.               { chars++; }
%%

int main() {
    yylex();
    printf("Words = %d\nCharacters = %d\nBlanks = %d\nLines = %d\n",
            words, chars, blanks, lines);
    return 0;
}

int yywrap() {
    return 1;
}
