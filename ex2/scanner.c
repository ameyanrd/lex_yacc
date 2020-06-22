#include <stdio.h>
#include "scanner.h"

extern int yylex();  /* Returns the first and successively valid token */
extern int yylineno; /* Returns the line where erro occurs */
extern char* yytext; /* Returns the text of the token */

char *names[] = {NULL, "db_type", "db_name", "db_table-prefix", "db_port"};

int main(void) {
    int ntoken, vtoken;

    ntoken = yylex(); /* Returns the first valid token i.e. the name token a/c to the input file */
    while(ntoken) {
        printf("%d\n", ntoken);
        /* Checks whether the next token is colon or not */
        if (yylex() != COLON) {
            printf("Sntax error in line %d, Expected a ':' but found %s\n", yylineno, yytext);
            return 1;
        }
        vtoken = yylex(); /* Returns the value token after a colon */
        switch(ntoken) {
            case TYPE:
            case NAME:
            case TABLE_PREFIX:
                if (vtoken != IDENTIFIER) {
                    printf("Syntax Error in line %d, Expected an identifier but found %s\n", yylineno, yytext);
                    return 1;
                }
                printf("%s is set to %s\n", names[ntoken], yytext);
                break;
            case PORT:
                if (vtoken != INTEGER) {
                    printf("Syntax Error in line %d, Expected an identifier but found %s\n", yylineno, yytext);
                    return 1;
                }
                printf("%s is set to %s\n", names[ntoken], yytext);
                break;
            default:
                printf("Syntax Error in line %d\n", yylineno);
        }
        ntoken = yylex(); /* Returns the next valid name token after the previous value token */
    }
    return 0;
}
