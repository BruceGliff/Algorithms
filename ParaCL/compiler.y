%{
	#include "parser.hpp"

//current node
static char error_text[128];
Scope * currentScope = nullptr;
%}

%term NAME VALUE
%term WHILE IF
%term SM LBR RBR LPAR RPAR LCB RCB ILLEGAL
%term OUTPUT
%right ASG
%nonassoc RELOP
%left INPUT
%left OR
%left AND
%left NOT
%left PLUS MINUS
%left MUL DIV MOD
%nonassoc UMINUS

%%
program : 	stms { 
					printf ("program stms\n");
					currentScope->calc();
				}
			;
scope	:	LCB stms RCB { printf ("{scope}\n");}
      		;
stms	: 	
			|
			stm { 
					printf ("stm ");
					currentScope->addBranch($1.treeNode);
					std::cout << $1.treeNode << '\n';
				}
     		|
			stms stm { 
					printf ("stms stm ");
					currentScope->addBranch($2.treeNode);
					std::cout << $2.treeNode << '\n';
				}
			|
			stms scope {printf ("stms scope\n");}
			;
stm		:	oper { 
					printf ("stm oper ");
					$$ = $1;
					std::cout << $1.treeNode << '\n';
				}
    		;
oper 	: 	assign { 
					printf ("oper assign ");
					$$ = $1;
					std::cout << $1.treeNode << '\n';
				}
      		|
			if { printf ("oper if\n");}
			|
			while { printf ("oper while\n");}
			|
			output { 
					printf ("oper output ");
					$$ = $1;
					std::cout << $$.treeNode << '\n';
				}
			;
assign	:	lval ASG expr SM { 
					printf ("assign lval ");
					$$.treeNode = new Op{$1.treeNode, Ops::Assign, $3.treeNode};
					std::cout << $$.treeNode << '\n';
				}
       		;
lval	:	NAME { 
					printf ("laval name ");
					$$.treeNode = (*currentScope)[$1.name];
					std::cout << $$.treeNode << '\n';
				}
     		;
expr	:	expr PLUS expr { printf ("expr +\n");}
     		|
			expr MINUS expr { 
					printf ("expr -\n");
					$$.treeNode = new Op{$1.treeNode, Ops::Minus, $3.treeNode};
				}
			|
			expr MUL expr { 
					printf ("expt *\n");
					$$.treeNode = new Op{$1.treeNode, Ops::Mul, $3.treeNode};
				}
			|
			expr DIV expr { 
					printf ("expr /\n");
					$$.treeNode = new Op{$1.treeNode, Ops::Div, $3.treeNode};
				}
			|
			expr MOD expr { 
					printf ("expr MOD\n");
					$$.treeNode = new Op{$1.treeNode, Ops::Mod, $3.treeNode};
				}
			|
			MINUS expr %prec UMINUS { 
					printf ("expr u-\n");
					$$.treeNode = new Op{new Value{0}, Ops::Minus, $2.treeNode};
				}
			|
			NAME { 
					printf ("expr name ");
					$$.treeNode = (*currentScope)[$1.name];
					std::cout << $$.treeNode << '\n';
				}
			|
			VALUE {
					printf ("expr value ");
					$$.treeNode = new Value{$1.value};
					std::cout << $$.treeNode << '\n';
				}
			|
			INPUT { printf ("expr input\n");}
			|
			LPAR expr RPAR { printf ("(expr)\n");}
			;
if	:		ifh stms { printf ("if stm\n");}
   			|
			ifh scope { printf ("is scope\n");}
			;
ifh	:		IF LPAR lexpr RPAR { printf ("ifh()\n");}
    		;
lexpr	:	expr {printf("lexpr expr\n");}
			|
			expr RELOP expr { printf ("lexpr relop\n");}
      		|
			lexpr OR lexpr { printf ("lexpr ||\n");}
			|
			lexpr AND lexpr { printf ("lexpr &&\n");}
			|
			NOT lexpr { printf ("lexpr !\n");}
			|
			LPAR lexpr RPAR { printf ("(lexpr)\n");}
			;
while	:	whileh stm { printf ("while stm\n");}
      		|
			whileh scope { printf ("while scope\n");}
			;
whileh 	:	WHILE LPAR lexpr RPAR { printf ("whileh ()\n");}
			;
output	:	OUTPUT expr SM {
					printf ("output expr ");
					$$.treeNode = new Op{nullptr, Ops::StdOut, $2.treeNode};
					std::cout << $$.treeNode << std::endl;
				}
       		;
%%

int main(int argc, char * argv[])
{
	FILE * f = fopen(argv[1], "r");
	if (f <= 0)
	{
		perror("Cannot open file");
		return 1;
	}
	yyin = f;
	currentScope = new Scope{nullptr};
	yyparse();
	fclose(f);

	return 0;
}
		
int yyerror(const char *s) {
    printf("%s in line %d\n", s, yylineno);
    return 0;
}