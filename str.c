#include <stdlib.h>
#include "str.h"

/*STRING構造体の初期化を行う。最初から10文字(+null文字)のサイズを用意する*/
static void str_init(STRING *lib_string){
    lib_string->string = (char *)malloc(sizeof(char)*11);
    lib_string->string[0] = '\0';
    lib_string->max_char_num = 10;
    lib_string->char_num = 0;
}

/*STRING構造体の文字列サイズを追加する。（必要になる文字数の倍の文字数を保持できるようにメモリを確保する）*/
static void add_memsize(STRING *lib_string, const int new_need_char_num){
    lib_string->max_char_num = (lib_string->char_num + new_need_char_num) * 2;
    lib_string->string = (char *)realloc(lib_string->string, lib_string->max_char_num + 1);
}

//文字列ポインタを渡して、文字数をカウントして返す
static int get_str_length(char const *string){
    int str_num = 0;
    char const *tmp_str = string;          //strの走査用ポインタ
    while(*tmp_str){
        str_num++;
        tmp_str++;
    }
    return str_num;
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
    int str_num = get_str_length(str);

    //メモリサイズが足りるか判定
    //足りなければ、新たにメモリサイズを確保する
    if(lib_string->max_char_num < lib_string->char_num + str_num){
        add_memsize(lib_string, str_num);
    }

    //それぞれの文字列の走査用ポインタを用意
    char const *tmp_str = str;                                                      //strの走査用ポインタ
    char *tmp_lib_string = lib_string->string + lib_string->char_num;      //s->stringの走査用ポインタの用意 + 初期位置の設定

    //構造体のメンバに直接アクセスできるようにポインタを取得しておく
    int *char_num = &lib_string->char_num;

    //1文字ずつコピー
    while(*tmp_str){
        *tmp_lib_string = *tmp_str;
        (*char_num)++;
        tmp_lib_string++;
        tmp_str++;
    }
    //最後にnull文字を追加
    *tmp_lib_string = '\0';
}

/* （第二引数）文字目から（第三引数）文字取り出した新しい文字列を返す */
STRING *str_extract(STRING * lib_string, const unsigned int start, const unsigned int chars_num){
    //返却用構造体の用意
    STRING *ret_string;
    ret_string = str_create();

    //メモリサイズが足りるか判定
    //足りなければ、新たにメモリサイズを確保する
    if(ret_string->max_char_num < chars_num){
        add_memsize(ret_string, chars_num);
    }

    //それぞれの文字列の走査用ポインタを用意。tmp_lib_stringは開始位置をセット
    char *tmp_ret_string = ret_string->string;
    char *tmp_lib_string = lib_string->string + start;
    //構造体のメンバに直接アクセスできるようにポインタを取得しておく
    int *char_num = &ret_string->char_num;
    //lib_stringのstart文字目からlast文字までをret_stringにコピーしていく
    for(int i=0; i<chars_num; i++){
        *tmp_ret_string = *tmp_lib_string;
        (*char_num)++;
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
    return s->char_num;
}

/* リソース開放 */
void str_destroy(STRING *s){
    free(s->string);
    free(s);
}
