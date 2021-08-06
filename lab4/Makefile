
CC = gcc
INCLUDES = -I../../lab3/solutions/part1
CFLAGS = -g -Wall $(INCLUDES)
LDFLAGS = -g -L../../lab3/solutions/part1
LDLIBS = -lmylist


#header dependency
mdb-lookup: mdb-lookup.o
mdb-lookup.o: mdb.h

.PHONY: clean
clean:
        rm -f *.o a.out core mdb-lookup


.PHONY: all
all: clean mdb-lookup

.PHONY: vg
vg: 
        valgrind --leak-check=yes ./mdb-lookup my-mdb
