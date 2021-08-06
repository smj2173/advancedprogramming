Sophie Johnson
smj2173
lab4
all parts of my lab work as they should
part1 (a) entries into database:

{Sophie Johnson} : {it's sunny today}
{Sophie Johnson} : {i love cs <3}

valgrind for part1:
valgrind --leak-check=yes ./mdb-lookup my-mdb
==10644== Memcheck, a memory error detector
==10644== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==10644== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==10644== Command: ./mdb-lookup my-mdb
==10644==
lookup: 131: {Aditya} said {hey i'm in the AP disco}
132: {Aditya} said {hey class what's up}
133: {Anya Devgan} said {hey}
139: {stan liao} said {hey there demons its me}
147: { christina d} said {heyoooooooo}
171: {They} said {something funny}
293: {hallie} said {hey y'all!}
342: {hey} said {ary o   e [F   [F [B [B}

lookup: ==10644==
==10644== HEAP SUMMARY:
==10644==     in use at exit: 0 bytes in 0 blocks
==10644==   total heap usage: 696 allocs, 696 frees, 29,656 bytes allocated
==10644==
==10644== All heap blocks were freed -- no leaks are possible
==10644==
==10644== For counts of detected and suppressed errors, rerun with: -v
==10644== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
