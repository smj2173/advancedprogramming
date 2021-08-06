Sophie Johnson
smj2173
lab 2

My code works exactly as specified by the descriptions.

part1 valgrind run:

==10213== Memcheck, a memory error detector
==10213== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==10213== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==10213== Command: ./isort
==10213==
original: 83 53 83 6 81
ascending: 6 53 81 83 83
descending: 83 83 81 53 6
==10213==
==10213== HEAP SUMMARY:
==10213==     in use at exit: 0 bytes in 0 blocks
==10213==   total heap usage: 5 allocs, 5 frees, 1,596 bytes allocated
==10213==
==10213== All heap blocks were freed -- no leaks are possible
==10213==
==10213== For counts of detected and suppressed errors, rerun with: -v
==10213== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

valgrind part2

==14579== Memcheck, a memory error detector
==14579== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==14579== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==14579== Command: ./twecho hello world
==14579==
hello HELLO
world WORLD
==14579==
==14579== HEAP SUMMARY:
==14579==     in use at exit: 0 bytes in 0 blocks
==14579==   total heap usage: 5 allocs, 5 frees, 1,589 bytes allocated
==14579==
==14579== All heap blocks were freed -- no leaks are possible
==14579==
==14579== For counts of detected and suppressed errors, rerun with: -v
==14579== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
