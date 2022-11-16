#pragma once

#include <string>
#include <cstring>
#include <sstream>
#include <cstdarg>
#include "Node.hpp"

struct yyRet
{
	std::string name;
	int value;
	int linePos;
	int inLinePos;
	Node * treeNode;
	Ops op;
};

#define YYSTYPE yyRet

#include "compiler.cpp.h"

extern FILE * yyin;

extern "C" {
int yylex();
int yyerror(char const *);
extern void PrintError(char const * s, ...);
extern void BeginToken(char*, int *);
}
extern int yylineno;
static int yyinlinePos = 0;
