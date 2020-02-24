CC=g++
CFLAGS = -c -O3 -MD -g --coverage 

all : program.out

program.out : main.o
	$(CC) --coverage -o $@ $^

main.o : main.cc
	$(CC) $(CFLAGS) main.cc
-include *.d

clean:
	rm *.o *.d *.out *.gc*
