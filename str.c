#include <stdio.h>
#include <stdlib.h>
#include "str.h"

STRING *str_create(void){
    STRING *lib_string = NULL;
    lib_string = (STRING *)calloc(1, sizeof(STRING));
    return lib_string;
}

//lib_stringはstr_create()での返り値を使うこと
int str_set(STRING **lib_string, const char *string){
    if(*lib_string[0] != '\0'){
        *lib_string[0] = '\0';
    }

    //セットする文字用に必要なサイズを追加する
    //セットする文字数をカウント
    int count = 0;
    while(string[count] != '\0'){
        count++;
    }
    //文字数+1(null文字用)のサイズを確保
    *lib_string = (STRING *)realloc(*lib_string, (sizeof(STRING)*count)+1);

    //文字をコピーする。null文字まで含めてコピーする
    int j = 0;
    for(j=0; j<=count; j++){
        (*lib_string)[j] = string[j];
    }
    return 1;
}

int str_add(STRING *lib_string, const char *string){

    return 0;
}

STRING *str_extract(STRING *lib_string, int start, int length){

    return lib_string;
}

char *str_value(STRING *lib_string){

    return lib_string;
}

int str_length(STRING *lib_string){

    return 0;
}

void str_destroy(STRING *lib_string){

}

