CC = g++ $(CFLAGS)

CFLAGS = -g -O0 -Wno-unused -Wno-unused-function -Wno-unused-label -Wno-error -Wreturn-type

default: compiler.y scanner.l parser.hpp Node.cpp
	flex -8 scanner.l
	bison -o compiler.cpp --defines=compiler.cpp.h -v compiler.y
	$(CC) $(CFLAGS) -o program compiler.cpp Node.cpp error.cpp lex.yy.c

clean:
	rm lex* program compiler.c* compiler.out*
