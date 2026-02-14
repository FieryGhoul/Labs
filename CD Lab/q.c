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


*/
Perfect. Let’s build a universal, reusable framework for solving any Lexical Analyzer + Symbol Table question — this time with clear code snippets for every step.

This is your exam-ready execution blueprint.


---

🔷 COMPLETE STEP-BY-STEP APPROACH (WITH CODE)


---

✅ STEP 1 — Extract Requirements From Question

Before coding, define classification arrays.

Example (based on a typical question):

// KEYWORDS
char *keywords[] = {"let","function","document",NULL};

// PREDEFINED FUNCTIONS
char *predef[] = {"ready","on","val","split",
                  "map","filter","text","join","isNaN",NULL};

// OPERATORS (include multi-character)
char *operators[] = {"==","&&","=>","=","+","-",
                     "*","/","%","!","?",";",":","$",NULL};


---

✅ STEP 2 — Define Token Structure

Every lexical analyzer starts with a token structure.

typedef struct {
    char lexeme[50];
    char type[30];
    int row;
    int col;
} Token;


---

✅ STEP 3 — Helper Functions (Core Decision Engine)

🔹 Keyword Check

int isKeyword(char *str){
    for(int i=0; keywords[i]!=NULL; i++){
        if(strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}


---

🔹 Predefined Function Check

int isPredef(char *str){
    for(int i=0; predef[i]!=NULL; i++){
        if(strcmp(str, predef[i]) == 0)
            return 1;
    }
    return 0;
}


---

🔹 Operator Check

int isOperator(char *str){
    for(int i=0; operators[i]!=NULL; i++){
        if(strcmp(str, operators[i]) == 0)
            return 1;
    }
    return 0;
}


---

✅ STEP 4 — Local Symbol Table Structure

Most questions require storing identifiers and functions.

#define MAX 200

typedef struct {
    char lexeme[50];
    char tokenType[30];
    char argument[100];   // only used for functions
} LocalSymTab;

LocalSymTab LST[MAX];
int lstIndex = 0;


---

🔹 Insert Function

Avoid duplicates.

void insertLocal(char *lex, char *type, char *arg){
    for(int i=0; i<lstIndex; i++){
        if(strcmp(LST[i].lexeme, lex) == 0)
            return;
    }

    strcpy(LST[lstIndex].lexeme, lex);
    strcpy(LST[lstIndex].tokenType, type);
    strcpy(LST[lstIndex].argument, arg);
    lstIndex++;
}


---

✅ STEP 5 — Core Lexical Analyzer Function

This is the heart of every question.


---

🔹 Row & Column Tracking

static int row = 1, col = 0;

Update logic:

if(c == '\n'){
    row++;
    col = 0;
    continue;
}
col++;


---

🔹 Full Token Generator Template

Token getNextToken(FILE *fp){
    Token t;
    char c;
    int i;

    while((c = fgetc(fp)) != EOF){

        col++;

        if(c == '\n'){
            row++;
            col = 0;
            continue;
        }

        if(isspace(c))
            continue;


---

🔹 1. Handle Strings FIRST (Priority Rule)

if(c == '"' || c == '\''){
            char quote = c;
            i = 0;

            while((c = fgetc(fp)) != quote && c != EOF){
                t.lexeme[i++] = c;
            }
            t.lexeme[i] = '\0';

            if(t.lexeme[0] == '#'){
                strcpy(t.type, "IDENTIFIER");
                insertLocal(t.lexeme, "IDENTIFIER", "");
            }
            else{
                strcpy(t.type, "STRING_LITERAL");
            }

            t.row = row;
            t.col = col;
            return t;
        }

Why first?
Because special rules override normal rules.


---

🔹 2. Identifier / Keyword / Function

if(isalpha(c)){
            i = 0;
            t.lexeme[i++] = c;

            while(isalnum(c = fgetc(fp))){
                t.lexeme[i++] = c;
                col++;
            }

            t.lexeme[i] = '\0';
            ungetc(c, fp);

            if(isKeyword(t.lexeme)){
                strcpy(t.type, "KEYWORD");
            }
            else if(isPredef(t.lexeme)){
                strcpy(t.type, "PREDEFINED_FUNCTION");
                insertLocal(t.lexeme, "FUNCTION", "ARGUMENTS_PRESENT");
            }
            else{
                strcpy(t.type, "IDENTIFIER");
                insertLocal(t.lexeme, "IDENTIFIER", "");
            }

            t.row = row;
            t.col = col - strlen(t.lexeme) + 1;
            return t;
        }


---

🔹 3. Numbers

if(isdigit(c)){
            i = 0;
            t.lexeme[i++] = c;

            while(isdigit(c = fgetc(fp))){
                t.lexeme[i++] = c;
                col++;
            }

            t.lexeme[i] = '\0';
            ungetc(c, fp);

            strcpy(t.type, "NUMBER");
            t.row = row;
            t.col = col - strlen(t.lexeme) + 1;
            return t;
        }


---

🔹 4. Multi-Character Operators (Critical Step)

Always check 2-char operator first.

char next = fgetc(fp);
        char temp[3];

        temp[0] = c;
        temp[1] = next;
        temp[2] = '\0';

        if(isOperator(temp)){
            strcpy(t.lexeme, temp);
            strcpy(t.type, "OPERATOR");
            col++;
        }
        else{
            ungetc(next, fp);
            temp[1] = '\0';

            if(isOperator(temp)){
                strcpy(t.lexeme, temp);
                strcpy(t.type, "OPERATOR");
            }
            else{
                strcpy(t.lexeme, temp);
                strcpy(t.type, "SPECIAL_SYMBOL");
            }
        }

        t.row = row;
        t.col = col;
        return t;
    }

    strcpy(t.type,"EOF");
    return t;
}


---

✅ STEP 6 — Main Driver

int main(){
    FILE *fp = fopen("input.js","r");
    Token t;

    if(!fp){
        printf("File not found\n");
        return 0;
    }

    printf("TOKENS:\n");

    while(strcmp((t = getNextToken(fp)).type,"EOF") != 0){
        printf("<%s,%d,%d>\n", t.lexeme, t.row, t.col);
    }

    fclose(fp);

    printf("\nLOCAL SYMBOL TABLE\n");
    printf("Lexeme\t\tType\t\tArgument\n");

    for(int i=0; i<lstIndex; i++){
        printf("%-15s %-15s %-15s\n",
               LST[i].lexeme,
               LST[i].tokenType,
               LST[i].argument);
    }

    return 0;
}


---

🔥 UNIVERSAL EXAM WORKFLOW

Whenever a new lexical question appears:


---

🔹 Step A — Update Arrays

Change:

keywords[]

predef[]

operators[]



---

🔹 Step B — Modify Special Rules

If question says:

Ignore comments → add comment skipping block

Handle floats → modify number logic

Case sensitive → adjust comparison



---

🔹 Step C — Adjust Symbol Table Fields

If question requires:

Only identifiers → remove argument field

Global + Local → add scope tracking

Size calculation → add type-size function



---

🚨 Most Important Rules for Full Marks

1. Check multi-character operator BEFORE single-character


2. Handle string rules before identifier rules


3. Avoid duplicate symbol table entries


4. Track row/column correctly


5. Follow exact token print format




---

🧠 Mental Model

Lexical Analyzer =

Read Character
↓
Match Pattern
↓
Generate Token
↓
Update Symbol Table
↓
Return Token


---

If you want next level mastery, I can now give you:

A harder surprise question to test if you truly understood

A simplified handwritten version (fast exam writing)

A viva defence guide (what examiner may cross-question)


Tell me what maximizes your scoring edge.

*/
