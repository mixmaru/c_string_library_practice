/* stdio.h 不要なら削除する */
#include <stdio.h>
#include <stdlib.h>
#include "str.h"

static int str_add_detail(STRING *, const char *, unsigned int, unsigned int);
static int count_str_length(const char *);

/* リソース確保＆初期化（中身を空文字列にする） */
STRING *str_create(){
    STRING *lib_string = (STRING *)malloc(sizeof(STRING));
    lib_string->string = (char *)calloc(1, sizeof(char));
    lib_string->count = 0;
    return lib_string;
}

/*
文字列をセット (初期化されていないSTRINGの空ポインタを渡すとSegmentation faultとなる)
*/
int str_set(STRING *lib_string, const char *set_string){
    //文字列が空でなければ空にする
    if(lib_string->string[0] != '\0'){
        lib_string->string[0] = '\0';
        lib_string->count = 0;
    }

    //追加
    int success_flag = str_add(lib_string, set_string);
    return success_flag;
}

/*
文字列追加
lib_string->stringのおしりに、add_stringを追加する
*/
int str_add(STRING *lib_string, const char *add_string){
    int success_flag = str_add_detail(lib_string, add_string, 0, count_str_length(add_string));
    return success_flag;
}

/*
STRING->stringから指定番目から指定数の文字を切り出した文字列を保持する新しいSTRING構造体を返す
エラー時はSTRING->stringにNULLポインタをセットする

例:
STRING *string = str_create();
str_set(string, "abcde");
STRING *new_string = str_extract(string, 2,   10 );   この場合 new_string->string == "cde" となる
STRING *new_string = str_extract(string, -2,  1  );   この場合 new_string->string == "e"   となる
STRING *new_string = str_extract(string, 1,   -2 );   この場合 new_string->string == "bc"  となる
STRING *new_string = str_extract(string, 3,   -4 );   この場合 new_string->string == ""    となる
STRING *new_string = str_extract(string, 100, 1  );   この場合 new_string->string == ""    となる

引数：
target          STRING構造体
start           コピー開始位置
chars_num       コピー文字数
*/
STRING *str_extract(const STRING *lib_string, const int start, const int chars_num){

    //start, chars_numから文字列コピーの開始位置startと、停止位置lastを決定する
    int first = (start >= 0)     ? start                 : lib_string->count + start;
    int last  = (chars_num >= 0) ? first + chars_num - 1 : lib_string->count + chars_num - 1;

    STRING *ret_string = str_create();

    //first位置が範囲外である場合と、last位置がfirst位置より手前だった場合は、NULLポインタをセットして返す
    if(first > lib_string->count || first > last){
        ret_string->string = NULL;
        return ret_string;
    }

    int success = str_add_detail(ret_string, lib_string->string, first, last-first+1);
    if(success == STR_LIB_SUCCESS){
        return ret_string;
    }else{
        ret_string->string = NULL;
        return ret_string;
    }
}

/* printfで出力できる文字列を返す */
char *str_value(const STRING *lib_string){
    return lib_string->string;
}

/* 文字列の長さを返す */
int str_length(const STRING *lib_string){
    return lib_string->count;
}

/* リソース開放 */
void str_destroy(STRING *lib_string){
    free(lib_string->string);
    lib_string->string = NULL;
    free(lib_string);
    lib_string = NULL;
}

/*
STRING構造体の文字列へ、
文字列の指定位置から指定の文字数を追加する。

例：
str_set(target, "abcde");
str_add_detail(target, "012", 1, 10); この場合 target->string == "abede12" となる

引数：
target          STRING構造体
string          文字列
start           コピー開始位置
chars_num       コピー文字数
*/
static int str_add_detail(STRING *target, const char *string, unsigned int start, unsigned int chars_num){
    int string_count = count_str_length(string);

    //string文字列のコピー開始位置が、string文字列外ならエラーとする
    if(start >= string_count){
        return STR_LIB_ERROR;
    }

    //コピー文字数にしたがって文字列をコピーするとき、string文字列の範囲を超えてしまう場合は、最大値で収めるようにする
    if(start + chars_num > string_count){
        chars_num = string_count - start;
    }

    //string文字列から指定範囲の文字をtarget->stringに追加していく
    target->string = (char *)realloc(target->string, (sizeof(char)*(target->count + chars_num +1)));
    int last_char_num = target->count;
    for(int i=0; i<chars_num; i++){
        target->string[last_char_num+i] = string[start+i];
        target->count++;
    }
    //最後にnull文字を加える
    target->string[target->count] = '\0';
    return STR_LIB_SUCCESS;
}

/* 文字列のカウント */
static int count_str_length(const char *string){
    int count = 0;
    while(string[count] != '\0'){
        count++;
    }
    return count;
}