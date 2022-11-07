%{
	#include "parser.hpp"

//current node
static char error_text[128];
extern Scope * currentScope;

#define YYERROR_VERBOSE 1
%}

%defines

%token NAME VALUE
%token WHILE IF
%token SM LBR RBR LPAR RPAR LCB RCB ILLEGAL
%token OUTPUT
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
program: 	stms { 
					//printf ("program stms\n");
					currentScope->calc();
				}
			;
scope:		openScope stms closeScope {
					//std::cout << "Scope" << std::endl;
					$$ = $3;
				}
      		;
openScope:	LCB {
					//std::cout << "{" << std::endl;
					currentScope = new Scope{currentScope};
				}
			;
closeScope: RCB {
					//std::cout << "}" << std::endl;
					$$.treeNode = currentScope;
					currentScope = currentScope->resetScope();
				}
			;
stms: 	
			|
			stm { 
					//printf ("stm ");
					currentScope->addBranch($1.treeNode);
					//std::cout << $1.treeNode << '\n';
				}
     		|
			stms stm { 
					//printf ("stms stm ");
					currentScope->addBranch($2.treeNode);
					//std::cout << $2.treeNode << '\n';
				}
			|
			stms scope {
					//printf ("stms scope\n");
					currentScope->addBranch($2.treeNode);
				}
			;
stm:		oper { 
					//printf ("stm oper ");
					$$ = $1;
					//std::cout << $1.treeNode << '\n';
				}
    		;
oper:	 	assign { 
					//printf ("oper assign ");
					$$ = $1;
					//std::cout << $1.treeNode << '\n';
				}
      		|
			if { 
					//printf ("oper if\n");
					currentScope = currentScope->resetScope();
					$$ = $1;
				}
			|
			while { 
					//printf ("oper while\n");
					currentScope = currentScope->resetScope();
					$$ = $1;
				}
			|
			output { 
					//printf ("oper output ");
					$$ = $1;
					//std::cout << $$.treeNode << '\n';
				}
			;
assign:		lval ASG expr SM { 
					//printf ("assign lval ");
					$$.treeNode = new Op{$1.treeNode, Ops::Assign, $3.treeNode};
					//std::cout << $$.treeNode << '\n';
				}
       		;
lval:		NAME { 
					//printf ("laval name ");
					$$.treeNode = (*currentScope)[$1.name];
					//std::cout << $$.treeNode << '\n';
				}
     		;
expr:		expr PLUS expr { 
					//printf ("expr +\n");
					$$.treeNode = new Op{$1.treeNode, Ops::Plus, $3.treeNode};
				}
     		|
			expr MINUS expr { 
					//printf ("expr -\n");
					$$.treeNode = new Op{$1.treeNode, Ops::Minus, $3.treeNode};
				}
			|
			expr MUL expr { 
					//printf ("expt *\n");
					$$.treeNode = new Op{$1.treeNode, Ops::Mul, $3.treeNode};
				}
			|
			expr DIV expr { 
					//printf ("expr /\n");
					$$.treeNode = new Op{$1.treeNode, Ops::Div, $3.treeNode};
				}
			|
			expr MOD expr { 
					//printf ("expr MOD\n");
					$$.treeNode = new Op{$1.treeNode, Ops::Mod, $3.treeNode};
				}
			|
			MINUS expr %prec UMINUS { 
					//printf ("expr u-\n");
					$$.treeNode = new Op{new Value{0}, Ops::Minus, $2.treeNode};
				}
			|
			NAME { 
					//printf ("expr name ");
					// Current scope GET
					//$$.treeNode = (*currentScope)[$1.name];
					$$.treeNode = currentScope->existsLater($1.name);
					if (!$$.treeNode)
					{
						// std::stringstream errOut;
						// errOut << "Undeclared variable: " << $1.name;
						// yyerror(errOut.str().c_str());
					
						YYLTYPE * info = &@1;
						PrintError("Using undeclared variable! %s - Line %d:c%d to %d:c%d", $1.name.c_str(),
                        			info->first_line, info->first_column,
                        			info->last_line, info->last_column);
					}
					
					//std::cout << $$.treeNode << '\n';
				}
			|
			VALUE {
					//printf ("expr value ");
					$$.treeNode = new Value{$1.value};
					//std::cout << $$.treeNode << '\n';
				}
			|
			INPUT { 
					//printf ("expr input\n");
					$$.treeNode = new Op{nullptr, Ops::StdIn, nullptr};
				}
			|
			LPAR expr RPAR { 
					//printf ("(expr)\n");
					$$.treeNode = $2.treeNode;
				}
			;
if:			ifh stm { 
					//printf ("if stm\n");
					currentScope->addBranch($2.treeNode);
					$$.treeNode = new If{$1.treeNode, currentScope};
				}
   			|
			ifh scope { 
					//printf ("if scope\n");
					currentScope->addBranch($2.treeNode);
					$$.treeNode = new If{$1.treeNode, currentScope};
				}
			;
ifh:		IF LPAR lexpr RPAR { 
					//printf ("ifh() newScope: ");
					currentScope = new Scope{currentScope};
					//std::cout << currentScope << std::endl;
					$$ = $3;
				}
    		;
lexpr:		expr {
					//printf("lexpr expr\n");
					$$ = $1;
				}
			|
			expr RELOP expr {
					//printf ("lexpr relop\n");
					$$.treeNode = new Op{$1.treeNode, $2.op, $3.treeNode};
				}
      		|
			lexpr OR lexpr { 
					//printf ("lexpr ||\n");
					$$.treeNode = new Op{$1.treeNode, Ops::Or, $3.treeNode};
				}
			|
			lexpr AND lexpr { 
					//printf ("lexpr &&\n");
					$$.treeNode = new Op{$1.treeNode, Ops::And, $3.treeNode};
				}
			|
			NOT lexpr { 
					//printf ("lexpr !\n");
					$$.treeNode = new Op{nullptr, Ops::Not, $2.treeNode};
				}
			|
			LPAR lexpr RPAR { 
					//printf ("(lexpr)\n");
					$$ = $2;
				}
			;
while:		whileh stm { 
					//printf ("while stm\n");
					currentScope->addBranch($2.treeNode);
					$$.treeNode = new While{$1.treeNode, currentScope};
				}
      		|
			whileh scope { 
					//printf ("while scope\n");
					currentScope->addBranch($2.treeNode);
					$$.treeNode = new While{$1.treeNode, currentScope};
				}
			;
whileh:		WHILE LPAR lexpr RPAR { 
					//printf ("whileh ()\n");
					currentScope = new Scope{currentScope};
					$$ = $3;
				}
			;
output:		OUTPUT expr SM {
					//printf ("output expr ");
					$$.treeNode = new Op{nullptr, Ops::StdOut, $2.treeNode};
					//std::cout << $$.treeNode << std::endl;
				}
       		;
%%
		
int yyerror(const char *s) {
    PrintError(s);
	return 0;
}