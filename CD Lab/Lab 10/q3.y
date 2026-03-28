%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror(const char *s);
%}

%token NUM ADD SUB MUL DIV LPAREN RPAREN EOL

%left ADD SUB
%left MUL DIV

%%
input:
     
    | input line
    ;

line:
      EOL
    | exp EOL { printf("Result: %d\n", $1); }
    ;

exp:
      NUM                { $$ = $1; }
    | exp ADD exp        { $$ = $1 + $3; }
    | exp SUB exp        { $$ = $1 - $3; }
    | exp MUL exp        { $$ = $1 * $3; }
    | exp DIV exp {
            if ($3 == 0) {
                yyerror("Division by zero");
                $$ = 0;
            } else {
                $$ = $1 / $3;
            }
        }
    | LPAREN exp RPAREN  { $$ = $2; }
    ;
%%

void yyerror(const char *s) {
    printf("Error: %s\n", s);
}

int main() {
    printf("Enter arithmetic expression:\n");
    yyparse();
    return 0;
}