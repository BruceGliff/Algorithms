%{
	#include "parser.hpp"

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	void ScanError(char const *, int lineno);
%}
id    [a-zA-Z][a-zA-Z_0-9]*
ws	[ \t\n]+
int   [0-9]+
%option yylineno

%%
{ws}
"if"	{
        	//printf("if\n");
			return IF;
        }   
"while" {
			//printf("while\n");
			return WHILE;
		}
"print"	{
			//printf("print\n");
			return OUTPUT;
		}
"+"		{	return PLUS;	}
"-"		{	return MINUS; 	}
"*"		{	return MUL;	}
"/"		{	return DIV;	}
"%"		{	return MOD;	}
"("		{	return LPAR;	}
")"		{ 	return RPAR;	}
"["		{	return LBR;	}
"]"		{	return RBR;	}
"{"		{	return LCB;	}
"}"		{ 	return RCB;	}
";"		{	return SM;	}
"="		{ 	return ASG;	}
"=="	{	
			yylval.value = RELOP_EQ;
			return RELOP;
		}
"!="	{
			yylval.value = RELOP_NE;
			return RELOP;
		}
"<"		{
			yylval.value = RELOP_LT;
			return RELOP;
		}
">"		{
			yylval.value = RELOP_GT;
			return RELOP;
		}
"<="	{
			yylval.value = RELOP_LE;
			return RELOP;
		}
">="	{
			yylval.value = RELOP_GE;
			return RELOP;
		}
"||"	{	return OR;	}
"&&"	{	return AND;	}
"!"		{	return NOT;	}
"?" 	{	return INPUT; }

{id}	{
			//printf("name %s\n", yytext);
			yylval.name = yytext;
			return NAME;
		}
{int}	{
			yylval.value = atoi(yytext);
			//printf("int %d \n", yylval.value);
			return VALUE;
		}
.		{	
			ScanError("Unexpected smth", yylineno);
			return ILLEGAL;	
		}
%%

int yywrap() 	{ return 1; }
void ScanError(char const * s, int lineno)
{
	fprintf(stderr, 
		"Scanner error: %s in line %d\n", 
		s, lineno
	       );
}