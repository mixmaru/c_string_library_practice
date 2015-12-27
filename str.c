#include <stdlib.h>
#include "str.h"

/*STRING構造体の文字列サイズを追加する*/
static STRING * add_memsize(STRING *s, const int add_size){
    return s;
}

/* リソース確保＆初期化（中身を空文字列にする） */
STRING *str_create(){
    //STRING構造体一つのサイズをmallocで割り当てる。
    STRING *s;
    return s;
}

/* 文字列をセット */
void str_set(STRING *s, const char *str){
}

/* 文字列追加 */
void str_add(STRING *s, const char *str){
}

/* （第二引数）文字目から（第三引数）文字取り出した新しい文字列を返す */
/*  */
STRING *str_extract(const STRING *string, const int start, const int length){
    //start, lengthが負だとエラー
    STRING *ret_string;
    return ret_string;
}

/* printfで出力できる文字列を返す */
char *str_value(const STRING *s){
    return s;
}

/* 文字列の長さを返す */
int str_length(const STRING *s){
    int ret_num = 0;
    return ret_num;
}

/* リソース開放 */
void str_destroy(STRING *s){
}
