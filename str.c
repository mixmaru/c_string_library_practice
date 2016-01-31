#include <stdlib.h>
#include "str.h"

/*STRING構造体の初期化を行う*/
static void str_init(STRING *s){
    s->string = (char *)calloc(1, sizeof(char));
    s->max_size = 1;
    s->count = 0;
}

/*STRING構造体の文字列サイズを追加する*/
static STRING * add_memsize(STRING * s, const int add_size){
    s->string = (char *)realloc(s->string, s->max_size + add_size);
    s->max_size += add_size;
    return s;
}

/* リソース確保＆初期化（中身を空文字列にする） */
STRING *str_create(){
    //STRING構造体一つのサイズをmallocで割り当てる。
    STRING *s;
    s = (STRING *)malloc(sizeof(STRING));
    str_init(s);
    return s;
}

/* 文字列をセット */
void str_set(STRING *s, const char * str){
    str_init(s);
    str_add(s, str);
}

/* 文字列追加 */
void str_add(STRING *lib_string, const char * str){
    //必要サイズを追加
    int add_size = 0;
    char const *tmp_str = str;          //strの走査用ポインタ
    while(*tmp_str != '\0'){
        add_size++;
        tmp_str++;
    }
    lib_string = add_memsize(lib_string, add_size);

    //それぞれの文字列の走査用ポインタを用意
    tmp_str = str;                                                      //strの走査用ポインタ
    char *tmp_lib_string = lib_string->string + lib_string->count;      //s->stringの走査用ポインタの用意 + 初期位置の設定

    //1文字ずつコピー
    while(*tmp_str != '\0'){
        *tmp_lib_string = *tmp_str;
        lib_string->count++;
        tmp_lib_string++;
        tmp_str++;
    }
    //最後にnull文字を追加
    *tmp_lib_string = '\0';
}

/* （第二引数）文字目から（第三引数）文字取り出した新しい文字列を返す */
STRING *str_extract(STRING * lib_string, const int start, const int chars_num){
    //start, chars_numから文字列コピーの開始位置firstと、コピー文字数copy_numを決定する
    int first       = (start >= 0)     ? start      : lib_string->count + start;
    int copy_num    = (chars_num >= 0) ? chars_num  : (lib_string->count+chars_num)-first+1;

    //返却用構造体の用意
    STRING *ret_string;
    ret_string = str_create();
    //必要分のサイズを用意する。
    ret_string = add_memsize(ret_string, copy_num);

    //それぞれの文字列の走査用ポインタを用意。tmp_lib_stringは開始位置をセット
    char *tmp_ret_string = ret_string->string;
    char *tmp_lib_string = lib_string->string + first;
    //lib_stringのfirst文字目からlast文字までをret_stringにコピーしていく
    for(int i=0; i<copy_num; i++){
        *tmp_ret_string = *tmp_lib_string;
        tmp_ret_string++;
        tmp_lib_string++;
    }
    //最後にnull文字を加える
    *tmp_ret_string = '\0';
    return ret_string;
}

/* printfで出力できる文字列を返す */
char *str_value(STRING *s){
    return s->string;
}

/* 文字列の長さを返す */
int str_length(STRING *s){
    return s->count;
}

/* リソース開放 */
void str_destroy(STRING *s){
    free(s->string);
    free(s);
}
