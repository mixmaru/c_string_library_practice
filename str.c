/* stdio.h 不要なら削除する */
#include <stdio.h>
#include <stdlib.h>
#include "str.h"

static int str_copy(STRING *, const char *, int, int, int);

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
    if(str_copy(lib_string, string, lib_string->count, 0, string_count)){
        return 1;
    }else{
        return 0;
    }
}

/* （第二引数）文字目から（第三引数）文字取り出した新しい文字列を返す */
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

    //begin位置が範囲外である場合と、end位置がbegin位置より手前だった場合は空文字のまま返す。
    if(begin > lib_string->count || begin > end){
        return ret_string;
    }else{
        //そうでない場合は文字列をコピーする。
        if(str_copy(ret_string, lib_string->string, 0, begin, end - begin + 1)){
            return ret_string;
        }else{
            printf("エラーが発生しました\n");
            return ret_string;
        }
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

/* stringのstring_start番目からlimitまでの文字を、targetのtarget_start番目以降へコピーする */
/*
target          コピー先STRING構造体
string          コピー元文字列
target_start    コピー先のコピー開始位置
string_start    コピー元のコピー開始位置
limit           コピー文字数
*/
static int str_copy(STRING *target, const char *string, int target_start, int string_start, int limit){
    //target_startが存在している文字列(null文字を含む)外を指していればエラー
    if(target_start > target->count){
        return 0;
    }
    //string_startが存在している文字列(null文字を含まない)外を指していればエラー
    int string_count = 0;
    while(string[string_count] != '\0'){
        string_count++;
    }
    if(string_start >= string_count){
        return 0;
    }
    //limitがstringの範囲を超える場合は、最大値で収める
    if(string_start + limit > string_count){
        limit = string_count - string_start;
    }

    //サイズを追加する
    target->string = (char *)realloc(target->string, (sizeof(char)*(target_start + limit +1)));
    //文字をコピーしていく
    for(int i=0; i<limit; i++){
        target->string[target_start+i] = string[string_start+i];
        target->count++;
    }
    //最後にnull文字を加える
    target->string[target->count] = '\0';
    return 1;
}