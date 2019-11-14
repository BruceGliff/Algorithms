/* simplest version of calculator */
%{
#include <stdio.h>
#include "../Node.hpp"

 int yylex();
int yyerror(char *); 

Node * currScope = nullptr;

 union yylval
 {
     char name[20];
     int value;
     int op;
 };
%}


/* declare tokens */
%token NUMBER VAR
%token OP SEMMICOLON
%token WHILE IF

%%
%start program

program:
    | exps
    ;
exps: 
    | oper SEMMICOLON
    | WHILE '(' oper ')'
    | IF '(' oper ')'
    | '{' exps '}'
    ;
oper:
    | obj OP obj
    ;
    | oper
    ;
obj:
    | NUMBER { $$ = new Value{$1}; }
    ;
    | VAR { && = new Decl{}; }
    ; 


 




main(int argc, char **argv)
{
 yyparse();
}
yyerror(char *s)
{
 fprintf(stderr, "error: %s\n", s);
}