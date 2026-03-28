%{
#include "q4.tab.h"
#include <stdlib.h>
%}

%%
[0-9]+      { yylval.num = atoi(yytext); return NUM; }
\n          { return '\n'; }
[+\-*/^n]   { return yytext[0]; }
[ \t]       ;
.           { printf("Unexpected character: %s\n", yytext); }
%%

int yywrap(void) {
    return 1;
}