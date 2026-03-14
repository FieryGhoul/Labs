#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char lexeme[100];
    char type[20];
    int row;
    int col;
} Token;

FILE *fp;
Token currentToken;
int row=1,col=0;

char *keywords[]={"int","char","main",NULL};

/* ----------- Function Declarations ----------- */

Token getNextToken();
void program();
void declarations();
void data_type();
void identifier_list();
void idprime();
void statement_list();
void statement();
void assign_stat();
void expn();
void eprime();
void simple_expn();
void seprime();
void term();
void tprime();
void factor();

void match(char *expected);
void error(char *expected);

/* ----------- Error Function ----------- */

void error(char *expected){
    printf("\nSyntax Error at Row %d Column %d\n",currentToken.row,currentToken.col);
    printf("Expected: %s\n",expected);
    printf("Found: %s\n",currentToken.lexeme);
    exit(1);
}

/* ----------- Match Function ----------- */

void match(char *expected){
    if(strcmp(currentToken.lexeme,expected)==0)
        currentToken=getNextToken();
    else
        error(expected);
}

/* ----------- Keyword Check ----------- */

int isKeyword(char *str){
    for(int i=0;keywords[i]!=NULL;i++)
        if(strcmp(str,keywords[i])==0)
            return 1;
    return 0;
}

/* ----------- Lexical Analyzer ----------- */

Token getNextToken(){
    Token t;
    char ch;
    int i=0;

    ch=fgetc(fp);
    col++;

    while(isspace(ch)){
        if(ch=='\n'){ row++; col=0; }
        ch=fgetc(fp);
        col++;
    }

    t.row=row;
    t.col=col;

    if(isalpha(ch)){
        while(isalnum(ch)){
            t.lexeme[i++]=ch;
            ch=fgetc(fp);
            col++;
        }
        t.lexeme[i]='\0';
        fseek(fp,-1,SEEK_CUR);
        col--;

        if(isKeyword(t.lexeme))
            strcpy(t.type,"KEYWORD");
        else
            strcpy(t.type,"ID");

        return t;
    }

    if(isdigit(ch)){
        while(isdigit(ch)){
            t.lexeme[i++]=ch;
            ch=fgetc(fp);
            col++;
        }
        t.lexeme[i]='\0';
        fseek(fp,-1,SEEK_CUR);
        col--;
        strcpy(t.type,"NUM");
        return t;
    }

    if(ch==EOF){
        strcpy(t.lexeme,"EOF");
        strcpy(t.type,"EOF");
        return t;
    }

    t.lexeme[0]=ch;
    t.lexeme[1]='\0';
    strcpy(t.type,"SYMBOL");
    return t;
}

/* ----------- Grammar Functions ----------- */

void program(){
    match("main");
    match("(");
    match(")");
    match("{");

    declarations();
    statement_list();

    match("}");
    printf("\nParsing Successful!\n");
}

/* declarations → datatype id_list ; declarations | ε */

void declarations(){

    if(strcmp(currentToken.lexeme,"int")==0 ||
       strcmp(currentToken.lexeme,"char")==0){

        data_type();
        identifier_list();
        match(";");
        declarations();
    }
}

/* datatype */

void data_type(){

    if(strcmp(currentToken.lexeme,"int")==0)
        match("int");
    else if(strcmp(currentToken.lexeme,"char")==0)
        match("char");
    else
        error("int or char");
}

/* identifier list with arrays */

void identifier_list(){

    if(strcmp(currentToken.type,"ID")==0){
        match(currentToken.lexeme);
        idprime();
    }
    else
        error("identifier");
}

void idprime(){

    if(strcmp(currentToken.lexeme,"[")==0){

        match("[");
        if(strcmp(currentToken.type,"NUM")==0)
            match(currentToken.lexeme);
        else
            error("number");

        match("]");
    }

    if(strcmp(currentToken.lexeme,",")==0){
        match(",");
        identifier_list();
    }
}

/* statement list */

void statement_list(){

    if(strcmp(currentToken.type,"ID")==0){
        statement();
        statement_list();
    }
}

/* statement */

void statement(){

    assign_stat();
    match(";");
}

/* assignment */

void assign_stat(){

    if(strcmp(currentToken.type,"ID")==0){
        match(currentToken.lexeme);
        match("=");
        expn();
    }
    else
        error("identifier");
}

/* expressions */

void expn(){
    simple_expn();
    eprime();
}

void eprime(){

    if(strcmp(currentToken.lexeme,"<")==0 ||
       strcmp(currentToken.lexeme,">")==0){

        match(currentToken.lexeme);
        simple_expn();
    }
}

void simple_expn(){
    term();
    seprime();
}

void seprime(){

    if(strcmp(currentToken.lexeme,"+")==0 ||
       strcmp(currentToken.lexeme,"-")==0){

        match(currentToken.lexeme);
        term();
        seprime();
    }
}

void term(){
    factor();
    tprime();
}

void tprime(){

    if(strcmp(currentToken.lexeme,"*")==0 ||
       strcmp(currentToken.lexeme,"/")==0 ||
       strcmp(currentToken.lexeme,"%")==0){

        match(currentToken.lexeme);
        factor();
        tprime();
    }
}

void factor(){

    if(strcmp(currentToken.type,"ID")==0)
        match(currentToken.lexeme);

    else if(strcmp(currentToken.type,"NUM")==0)
        match(currentToken.lexeme);

    else
        error("identifier or number");
}

/* ----------- Main ----------- */

int main(){

    fp=fopen("input.txt","r");

    if(fp==NULL){
        printf("File not found\n");
        return 1;
    }

    currentToken=getNextToken();
    program();

    fclose(fp);
}