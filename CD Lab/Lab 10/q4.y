%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void yyerror(const char *s);
int yylex(void);
%}

%union {
    int num;
}

%token <num> NUM
%type <num> exp

%%
input:
      input line
    | 
    ;

line:
      '\n'
    | exp '\n' { printf("Result: %d\n", $1); }
    ;

exp:
      NUM              { $$ = $1; }
    | exp exp '+'      { $$ = $1 + $2; }
    | exp exp '-'      { $$ = $1 - $2; }
    | exp exp '*'      { $$ = $1 * $2; }
    | exp exp '/'      { $$ = $1 / $2; }
    | exp exp '^'      { $$ = pow($1, $2); }
    | exp 'n'          { $$ = -$1; }
    ;
%%

void yyerror(const char *s) {
    printf("Error: %s\n", s);
}

int main() {
    printf("Enter postfix expression:\n");
    yyparse();
    return 0;
}