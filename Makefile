a.out: strtest.o str.o
	gcc -Wall strtest.o str.o -o a.out

strtest.o: strtest.c
	gcc -Wall -c strtest.c

str.o: str.c
	gcc -Wall -c str.c

#str.c用テスト
str_test.out: str_test.o str.o
	gcc -Wall str_test.o str.o -o str_test.out

str_test.o: str_test.c
	gcc -Wall -c str_test.c
