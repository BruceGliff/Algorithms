default:
	clear
	flex -l parcer.l
	bison -dv parcer.y 
	g++ -o test parcer.tab.c lex.yy.c -lfl
