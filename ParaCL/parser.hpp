#pragma once

#include <string>
#include "Node.hpp"

enum relop
{
	RELOP_EQ,
	RELOP_NE,
	RELOP_GT,
	RELOP_GE,
	RELOP_LT,
	RELOP_LE
};


struct yyRet
{
	std::string name;
	int value;
	Node * treeNode;
};

#define YYSTYPE yyRet

#include "compiler.cpp.h"

extern FILE * yyin;

int yylex();
int yyerror(char const *);

extern int yylineno;
