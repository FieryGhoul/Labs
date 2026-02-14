#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 200

// TOKEN
typedef struct {
    char lexeme[50];
    char type[30];
    int row, col;
} Token;

// LOCAL SYMBOL TABLE
typedef struct {
    char lexeme[50];
    char tokenType[30];
    char argument[100];   // only for functions
} LocalSymTab;

LocalSymTab LST[MAX];
int lstIndex = 0;

// KEYWORDS
char *keywords[] = {"let","function","document",NULL};

// PREDEFINED FUNCTIONS
char *predef[] = {
    "ready","on","val","split","map",
    "filter","text","join","isNaN",NULL
};

// OPERATORS
char *operators[] = {
    "$","=","+","-","*","/","%","&&","!","?",";",":","==","=>",NULL
};

int isKeyword(char *str){
    for(int i=0;keywords[i];i++)
        if(strcmp(str,keywords[i])==0) return 1;
    return 0;
}

int isPredef(char *str){
    for(int i=0;predef[i];i++)
        if(strcmp(str,predef[i])==0) return 1;
    return 0;
}

int isOperator(char *str){
    for(int i=0;operators[i];i++)
        if(strcmp(str,operators[i])==0) return 1;
    return 0;
}

void insertLocal(char *lex,char *type,char *arg){
    for(int i=0;i<lstIndex;i++)
        if(strcmp(LST[i].lexeme,lex)==0) return;

    strcpy(LST[lstIndex].lexeme,lex);
    strcpy(LST[lstIndex].tokenType,type);
    strcpy(LST[lstIndex].argument,arg);
    lstIndex++;
}

// LEXICAL ANALYZER
Token getNextToken(FILE *fp){
    static int row=1,col=0;
    Token t;
    char c;
    int i;

    while((c=fgetc(fp))!=EOF){
        col++;

        if(c=='\n'){ row++; col=0; continue; }

        if(isspace(c)) continue;

        // STRING OR #IDENTIFIER
        if(c=='"' || c=='\''){
            char quote=c;
            i=0;
            while((c=fgetc(fp))!=quote && c!=EOF){
                t.lexeme[i++]=c;
            }
            t.lexeme[i]='\0';

            if(t.lexeme[0]=='#'){
                strcpy(t.type,"IDENTIFIER");
                insertLocal(t.lexeme,"IDENTIFIER","");
            }
            else strcpy(t.type,"STRING_LITERAL");

            t.row=row;
            t.col=col;
            return t;
        }

        // IDENTIFIER / KEYWORD / FUNCTION
        if(isalpha(c)){
            i=0;
            t.lexeme[i++]=c;
            while(isalnum(c=fgetc(fp))){
                t.lexeme[i++]=c;
                col++;
            }
            t.lexeme[i]='\0';
            ungetc(c,fp);

            if(isKeyword(t.lexeme)){
                strcpy(t.type,"KEYWORD");
            }
            else if(isPredef(t.lexeme)){
                strcpy(t.type,"PREDEFINED_FUNCTION");
                insertLocal(t.lexeme,"FUNCTION","ARGUMENTS_PRESENT");
            }
            else{
                strcpy(t.type,"IDENTIFIER");
                insertLocal(t.lexeme,"IDENTIFIER","");
            }

            t.row=row;
            t.col=col-strlen(t.lexeme)+1;
            return t;
        }

        // NUMBER
        if(isdigit(c)){
            i=0;
            t.lexeme[i++]=c;
            while(isdigit(c=fgetc(fp))){
                t.lexeme[i++]=c;
                col++;
            }
            t.lexeme[i]='\0';
            ungetc(c,fp);

            strcpy(t.type,"NUMBER");
            t.row=row;
            t.col=col-strlen(t.lexeme)+1;
            return t;
        }

        // MULTI CHARACTER OPERATORS
        char next=fgetc(fp);
        char temp[3];
        temp[0]=c;
        temp[1]=next;
        temp[2]='\0';

        if(isOperator(temp)){
            strcpy(t.lexeme,temp);
            strcpy(t.type,"OPERATOR");
            col++;
        }
        else{
            ungetc(next,fp);
            temp[1]='\0';
            if(isOperator(temp)){
                strcpy(t.lexeme,temp);
                strcpy(t.type,"OPERATOR");
            }
            else{
                strcpy(t.lexeme,temp);
                strcpy(t.type,"SPECIAL_SYMBOL");
            }
        }

        t.row=row;
        t.col=col;
        return t;
    }

    strcpy(t.type,"EOF");
    return t;
}

int main(){
    FILE *fp=fopen("input.js","r");
    Token t;

    if(!fp){
        printf("File not found!\n");
        return 0;
    }

    printf("TOKENS:\n");
    while(strcmp((t=getNextToken(fp)).type,"EOF")!=0){
        printf("<%s,%d,%d>\n",t.lexeme,t.row,t.col);
    }

    fclose(fp);

    printf("\nLOCAL SYMBOL TABLE\n");
    printf("Lexeme\t\tTokenType\tArgument\n");
    for(int i=0;i<lstIndex;i++){
        printf("%-15s %-15s %-15s\n",
               LST[i].lexeme,
               LST[i].tokenType,
               LST[i].argument);
    }

    return 0;
}
