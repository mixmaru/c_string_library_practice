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
    str_add(lib_string, string);
    return 1;
}

/* 文字列追加 */
int str_add(STRING *lib_string, const char *string){
    //文字数をカウント
    int string_count = 0;
    while(string[string_count] != '\0'){
        string_count++;
    }
    //サイズを追加する
    lib_string->string = (char *)realloc(lib_string->string, (lib_string->count) + (sizeof(char)*string_count)+1);
    //文字をコピーしていく
    int from = 0;
    int to   = lib_string->count;
    while(from < string_count){
        lib_string->string[to] = string[from];
        lib_string->count++; from++; to++;
    }
    //最後にnull文字を加える
    lib_string->string[lib_string->count] = '\0';
    return 1;
}

/* （第二引数）文字目から（第三引数）文字取り出した新しい文字列を返す */
/*  */
STRING *str_extract(const STRING *lib_string, const int start, const int length){
    //begin位置、end位置を決定する
    int begin = 0;
    int end   = 0;
    if(start >= 0){
        begin = start;
    }else{
        begin = lib_string->count + start;
    }
    if(length >= 0){
        end = begin + length - 1;
    }else{
        end = lib_string->count + length - 1;
    }

    //返却用STRING構造体を用意する
    STRING *ret_string = str_create();

    //begin位置が範囲外である場合と、end位置がbegin位置より手間だった場合は空文字のまま返す。
    if(begin > lib_string->count || begin > end){
        return ret_string;
    }else{
        //そうでない場合は返却用STRING構造体に必要なサイズを追加する。
        ret_string->string = (char *)realloc(ret_string->string, (lib_string->count) + (sizeof(char)*(end - begin + 1))+1);
        //文字列をコピーする
        int from = begin;
        int to   = 0;
        while(from <= end){
            ret_string->string[to] = lib_string->string[from];
            ret_string->count++; from++; to++;
        }
        //最後にnull文字を加える
        ret_string->string[to] = '\0';

        return ret_string;
    }
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
