a.out: strtest.o str.o
	gcc -Wall strtest.o str.o -o a.out

strtest.o: strtest.c
	gcc -Wall -c strtest.c

str.o: str.c
	gcc -Wall -c str.c
