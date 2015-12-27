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

/* 文字列をセット */
int str_set(STRING *s, const char *str){
    return 0;
}

/* 文字列追加 */
int str_add(STRING *s, const char *str){
    return 0;
}

/* （第二引数）文字目から（第三引数）文字取り出した新しい文字列を返す */
/*  */
STRING *str_extract(const STRING *string, const int start, const int length){
    //start, lengthが負だとエラー
    STRING *ret_string = NULL;
    return ret_string;
}

/* printfで出力できる文字列を返す */
char *str_value(const STRING *s){
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
