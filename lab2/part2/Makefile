CC = gcc
INCLUDES =
CFLAGS = -g -Wall $(INCLUDES)
LDFLAGS = -g

twecho: twecho.o

twecho.o: twecho.c

.PHONY: clean
clean:
        rm -f *.o a.out core twecho

.PHONY: all
all: clean twecho
~                                        
