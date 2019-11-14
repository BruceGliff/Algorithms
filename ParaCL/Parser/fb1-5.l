%{
#include "fb1-5.tab.h"
#include "string.h"

// OP
%}
%%
[ \t\n]+

[+-=><]     { yylval.val = yytext[0]; return OP; }

";"         { return SEMICOLON; }

[0-9]+      { yylval.value = atoi(yytext); return NUMBER; }
[a-Az-Z]+   { sscanf(yytext, "%s", yylval.name; return VAR; }

"while"     { return WHILE; }
"if"        { return IF; }
[{}()]      

%%
