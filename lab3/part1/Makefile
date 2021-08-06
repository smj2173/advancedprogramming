INCLUDES =
CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -g

mylist-test: mylist-test.o libmylist.a

libmylist.a: mylist.o
        ar rcs libmylist.a mylist.o

mylist-test.o: mylist.h

mylist.o: mylist.h

.PHONY: clean
clean:
        rm -f *.o a.out core mylist-test

.PHONY: all
all: clean mylist

.PHONY: vg
vg:
        valgrind --leak-check=yes ./mylist-test
~                                                                                                                                                                       
~                                                          
