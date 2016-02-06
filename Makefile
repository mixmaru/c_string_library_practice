a.out: strtest.o str.o
	gcc -Wall -std=c99 strtest.o str.o -o a.out

strtest.o: strtest.c
	gcc -Wall -std=c99 -c strtest.c

str.o: str.c
	gcc -Wall -std=c99 -c str.c

#str.c用テスト
str_test.out: str_test.o str.o
	gcc -Wall -std=c99 str_test.o str.o -o str_test.out

str_test.o: str_test.c
	gcc -Wall -std=c99 -c str_test.c
