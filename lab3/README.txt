  - Sophie Johnson
  - smj2173
  - lab 3
  - my solution for each part works.

Valgrind: part 1

==26132== Memcheck, a memory error detector
==26132== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==26132== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==26132== Command: ./mylist-test
==26132==
testing addFront(): 9.0 8.0 7.0 6.0 5.0 4.0 3.0 2.0 1.0
testing flipSignDouble(): -9.0 -8.0 -7.0 -6.0 -5.0 -4.0 -3.0 -2.0 -1.0
testing flipSignDouble() again: 9.0 8.0 7.0 6.0 5.0 4.0 3.0 2.0 1.0
testing findNode(): OK
popped 9.0, the rest is: [ 8.0 7.0 6.0 5.0 4.0 3.0 2.0 1.0 ]
popped 8.0, the rest is: [ 7.0 6.0 5.0 4.0 3.0 2.0 1.0 ]
popped 7.0, the rest is: [ 6.0 5.0 4.0 3.0 2.0 1.0 ]
popped 6.0, the rest is: [ 5.0 4.0 3.0 2.0 1.0 ]
popped 5.0, the rest is: [ 4.0 3.0 2.0 1.0 ]
popped 4.0, the rest is: [ 3.0 2.0 1.0 ]
popped 3.0, the rest is: [ 2.0 1.0 ]
popped 2.0, the rest is: [ 1.0 ]
popped 1.0, the rest is: [ ]
testing addAfter(): 1.0 2.0 3.0 4.0 5.0 6.0 7.0 8.0 9.0
popped 1.0, and reversed the rest: [ 9.0 8.0 7.0 6.0 5.0 4.0 3.0 2.0 ]
popped 9.0, and reversed the rest: [ 2.0 3.0 4.0 5.0 6.0 7.0 8.0 ]
popped 2.0, and reversed the rest: [ 8.0 7.0 6.0 5.0 4.0 3.0 ]
popped 8.0, and reversed the rest: [ 3.0 4.0 5.0 6.0 7.0 ]
popped 3.0, and reversed the rest: [ 7.0 6.0 5.0 4.0 ]
popped 7.0, and reversed the rest: [ 4.0 5.0 6.0 ]
popped 4.0, and reversed the rest: [ 6.0 5.0 ]
popped 6.0, and reversed the rest: [ 5.0 ]
popped 5.0, and reversed the rest: [ ]
==26132==
==26132== HEAP SUMMARY:
==26132==     in use at exit: 0 bytes in 0 blocks
==26132==   total heap usage: 19 allocs, 19 frees, 2,848 bytes allocated
==26132==
==26132== All heap blocks were freed -- no leaks are possible
==26132==
==26132== For counts of detected and suppressed errors, rerun with: -v
==26132== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

part 2 valgrind:

==12682== Memcheck, a memory error detector
==12682== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==12682== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==12682== Command: ./revecho hello world dude
==12682==
dude
world
hello

dude found
==12682==
==12682== HEAP SUMMARY:
==12682==     in use at exit: 0 bytes in 0 blocks
==12682==   total heap usage: 4 allocs, 4 frees, 2,608 bytes allocated
==12682==
==12682== All heap blocks were freed -- no leaks are possible
==12682==
==12682== For counts of detected and suppressed errors, rerun with: -v
==12682== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
                                                                                                                                                      68,1          Bot
                                                                                                                                                     1,1           Top
