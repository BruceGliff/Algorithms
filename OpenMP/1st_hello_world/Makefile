CC = clang
CFLAGS = -g -O2 -fopenmp
LD = clang
LDFLAGS = -g -fopenmp

PROGRAM = 1st_hello_world

all:	${PROGRAM}.out

${PROGRAM}.out: ${PROGRAM}.o
	${LD} ${LDFLAGS} $< -o ${PROGRAM}.out
	./${PROGRAM}.out

${PROGRAM}.o: ${PROGRAM}.c
	${CC} ${CFLAGS} -c $< -o ${PROGRAM}.o

launch:
	./${PROGRAM}.out

clean:
	rm -f ${PROGRAM}.o ${PROGRAM}.out
