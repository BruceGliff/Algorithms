#pragma once

#include <string>
#include "Node.hpp"

struct yyRet
{
	std::string name;
	int value;
	Node * treeNode;
	Ops op;
};

#define YYSTYPE yyRet

#include "compiler.cpp.h"

extern FILE * yyin;

int yylex();
int yyerror(char const *);

extern int yylineno;
