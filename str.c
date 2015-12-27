/* stdio.h 不要なら削除する */
#include <stdio.h>
#include <stdlib.h>
#include "str.h"

/* リソース確保＆初期化（中身を空文字列にする） */
STRING *str_create(){
    //STRING構造体一つのサイズをmallocで割り当てる。
    STRING *s = (STRING *)malloc(sizeof(STRING));
    s->string = (char *)calloc(1, sizeof(char));
    s->count = 0;
    return s;
}

/* 文字列をセット (初期化されていないSTRINGを渡すとSegmentation faultとなる) */
int str_set(STRING *lib_string, const char *string){
    //文字列が空でなければ空にする
    if(lib_string->string[0] != '\0'){
        lib_string->string[0] = '\0';
        lib_string->count = 0;
    }
    //文字数をカウント
    int string_count = 0;
    while(string[string_count] != '\0'){
        string_count++;
    }
    //サイズを追加する
    lib_string->string = (char *)realloc(lib_string->string, (sizeof(char)*string_count)+1);
    //文字をコピーしていく
    for(int i=0; i<=string_count; i++){
        lib_string->string[i] = string[i];
        lib_string->count++;
    }
    //最後にnull文字を加える
    lib_string->string[lib_string->count] = '\0';
    return 1;
}

/* 文字列追加 */
int str_add(STRING *lib_string, const char *str){
    return 0;
}

/* （第二引数）文字目から（第三引数）文字取り出した新しい文字列を返す */
/*  */
STRING *str_extract(const STRING *lib_string, const int start, const int length){
    //start, lengthが負だとエラー
    STRING *ret_string = NULL;
    return ret_string;
}

/* printfで出力できる文字列を返す */
char *str_value(const STRING *lib_strint){
    return "aaaaaaa";
}

/* 文字列の長さを返す */
int str_length(const STRING *s){
    int ret_num = 0;
    return ret_num;
}

/* リソース開放 */
void str_destroy(STRING *s){
}
