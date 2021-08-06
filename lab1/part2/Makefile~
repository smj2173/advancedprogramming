CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -g

convert: main.o convert.o

main.o: main.c convert.h

convert.o: convert.c convert.h

.PHONY: clean
clean:
	rm -f *.o a.out core convert

