CC = clang
CFLAGS = -g -O2 -fopenmp
LD = clang
LDFLAGS = -g -fopenmp

PROGRAM = 2nd_summ

all:	${PROGRAM}.out

${PROGRAM}.out: ${PROGRAM}.o
	${LD} ${LDFLAGS} $< -o ${PROGRAM}.out
	./${PROGRAM}.out 120 1

${PROGRAM}.o: ${PROGRAM}.c
	${CC} ${CFLAGS} -c $< -o ${PROGRAM}.o

launch:
	./${PROGRAM}.out 120 1

clean:
	rm -f ${PROGRAM}.o ${PROGRAM}.out out.txt
