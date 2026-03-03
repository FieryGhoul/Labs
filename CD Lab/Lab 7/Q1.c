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
int row = 1, col = 0;

char *keywords[] = {"int","char","main",NULL};

// ---------- Function Declarations ----------
Token getNextToken();
void program();
void declarations();
void data_type();
void identifier_list();
void assign_stat();
void match(char *expected);
void error(char *expected);

// ---------- Error Function ----------
void error(char *expected) {
    printf("\nSyntax Error at Row %d, Column %d\n",
           currentToken.row, currentToken.col);
    printf("Expected: %s\n", expected);
    printf("Found: %s\n", currentToken.lexeme);
    exit(1);
}

// ---------- Match Function ----------
void match(char *expected) {
    if(strcmp(currentToken.lexeme, expected) == 0)
        currentToken = getNextToken();
    else
        error(expected);
}

// ---------- Keyword Check ----------
int isKeyword(char *str) {
    for(int i=0; keywords[i]!=NULL; i++)
        if(strcmp(str, keywords[i])==0)
            return 1;
    return 0;
}

// ---------- Lexical Analyzer ----------
Token getNextToken() {
    Token t;
    char ch;
    int i = 0;

    ch = fgetc(fp);
    col++;

    // Skip whitespace
    while(isspace(ch)) {
        if(ch=='\n') {
            row++;
            col = 0;
        }
        ch = fgetc(fp);
        col++;
    }

    t.row = row;
    t.col = col;

    // Identifier or Keyword
    if(isalpha(ch)) {
        while(isalnum(ch)) {
            t.lexeme[i++] = ch;
            ch = fgetc(fp);
            col++;
        }
        t.lexeme[i] = '\0';
        fseek(fp,-1,SEEK_CUR);
        col--;

        if(isKeyword(t.lexeme))
            strcpy(t.type,"KEYWORD");
        else
            strcpy(t.type,"ID");

        return t;
    }

    // Number
    if(isdigit(ch)) {
        while(isdigit(ch)) {
            t.lexeme[i++] = ch;
            ch = fgetc(fp);
            col++;
        }
        t.lexeme[i]='\0';
        fseek(fp,-1,SEEK_CUR);
        col--;
        strcpy(t.type,"NUM");
        return t;
    }

    // EOF
    if(ch==EOF) {
        strcpy(t.lexeme,"EOF");
        strcpy(t.type,"EOF");
        return t;
    }

    // Symbols
    t.lexeme[0]=ch;
    t.lexeme[1]='\0';
    strcpy(t.type,"SYMBOL");
    return t;
}

// ---------- Grammar Functions ----------

void program() {
    match("main");
    match("(");
    match(")");
    match("{");
    declarations();
    assign_stat();
    match("}");
    printf("\nParsing Successful!\n");
}

void declarations() {

    // If valid datatype
    if(strcmp(currentToken.lexeme,"int")==0 ||
       strcmp(currentToken.lexeme,"char")==0) {

        data_type();
        identifier_list();
        match(";");
        declarations();
    }

    // If token looks like datatype but invalid
    else if(strcmp(currentToken.type,"ID")==0) {

        // If first identifier appears before assignment,
        // check if it is invalid datatype
        if(strcmp(currentToken.lexeme,"float")==0 ||
           strcmp(currentToken.lexeme,"double")==0 ||
           strcmp(currentToken.lexeme,"long")==0) {

            error("int or char");
        }
    }

    // Otherwise epsilon
}

void data_type() {
    if(strcmp(currentToken.lexeme,"int")==0)
        match("int");
    else if(strcmp(currentToken.lexeme,"char")==0)
        match("char");
    else
        error("int or char");
}

void identifier_list() {
    if(strcmp(currentToken.type,"ID")==0) {
        match(currentToken.lexeme);

        if(strcmp(currentToken.lexeme,",")==0) {
            match(",");
            identifier_list();
        }
    }
    else
        error("identifier");
}

void assign_stat() {
    if(strcmp(currentToken.type,"ID")==0) {
        match(currentToken.lexeme);
        match("=");

        if(strcmp(currentToken.type,"ID")==0)
            match(currentToken.lexeme);
        else if(strcmp(currentToken.type,"NUM")==0)
            match(currentToken.lexeme);
        else
            error("identifier or number");

        match(";");
    }
    else
        error("identifier");
}

// ---------- Main ----------
int main() {

    fp = fopen("input.c","r");
    if(fp==NULL) {
        printf("File not found!\n");
        return 1;
    }

    currentToken = getNextToken();
    program();

    fclose(fp);
    return 0;
}
