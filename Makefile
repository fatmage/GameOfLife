CC = g++
CFLAGS = -g
LDFLAGS = -lm

all: funcs.o gol

funcs.o :
	${CC} ${CFLAGS} -c funcs.cpp

main.o :
	${CC} ${CFLAGS} -c main.cpp

gol : funcs.o main.o
	${CC} ${CFLAGS} funcs.o main.o ${LDFLAGS} -o gol
clean:
	rm -rf funcs.o
	rm -rf main.o
	rm -rf gol
