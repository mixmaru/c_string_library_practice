#include <stdlib.h>
#include <stdio.h>

int main(void){
    char *p_str = (char *)malloc(sizeof(char)*17);
    *p_str = '\0';
    p_str = (char *)realloc(p_str, (sizeof(char)*17));
    char *work = p_str;
    *work = 'a';
    work++;
    *work = 'b';
    work++;
    *work = 'c';
    work++;
    *work = 'd';
    work++;
    *work = 'e';
    work++;
    *work = 'f';
    work++;
    *work = 'g';
    work++;
    *work = 'h';
    work++;
    *work = 'i';
    work++;
    *work = 'j';
    work++;
    *work = 'k';
    work++;
    *work = 'l';
    work++;
    *work = 'm';
    work++;
    *work = 'n';
    work++;
    *work = 'o';
    work++;
    *work = 'p';
    work++;
    *work = '\0';

    printf("%s\n", p_str);
}