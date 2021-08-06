CC = gcc

INCLUDES = -I../part1
CFLAGS = -g -Wall $(INCLUDES)
LDFLAGS = -g -L../part1
LDLIBS = -lmylist

revecho: revecho.o
        $(CC) $(LDFLAGS) revecho.o -o revecho $(LDLIBS)

revecho.o: revecho.c

.PHONY: clean
clean: 
        rm -f *.o a.out core revecho

.PHONY: all
all: clean revecho

.PHONY: vg
vg:
        valgrind --leak-check=yes ./revecho hello world dude
~                                                                                                                                                                                              
~                                                                                                                                                                                              
~                                                                          
