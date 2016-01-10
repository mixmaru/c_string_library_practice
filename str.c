#include <stdlib.h>
#include "str.h"

/*STRING構造体の初期化を行う*/
static void str_init(STRING *lib_string){
    //lib_string->stringが動的確保されていれば、freeする
    if(lib_string->string != NULL){
        free(lib_string->string);
        lib_string->string = NULL;
    }

    //lib_string->stringポインタを初期化し、空文字をセット。他のプロパティも初期化
    lib_string->string = (char *)malloc(sizeof(char));
    lib_string->string[0] = '\0';
    lib_string->max_size = 1;
    lib_string->count = 0;
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
    STRING *lib_string;
    lib_string = (STRING *)malloc(sizeof(STRING));
    //未定義ポインタにNULLを指定しておく
    lib_string->string = NULL;
    str_init(lib_string);
    return lib_string;
}

/* 文字列をセット */
void str_set(STRING *lib_string, const char * str){
    //すでに文字が入っていれば、文字列・確保サイズを初期化
    if(lib_string->count != 0){
        str_init(lib_string);
    }
    str_add(lib_string, str);
}

/* 文字列追加 */
void str_add(STRING *s, const char * str){
    //必要サイズを追加
    int add_size = 0;
    while(str[add_size]!='\0'){
        add_size++;
    }
    s = add_memsize(s, add_size);

    int start = s->count;   //文字列追加開始位置
    int i;
    for(i=0; str[i]!='\0'; i++){
        s->string[start+i] = str[i];
        s->count++;
    }
    //null文字を追加
    s->string[start+i+1] = '\n';
}

/* （第二引数）文字目から（第三引数）文字取り出した新しい文字列を返す */
STRING *str_extract(STRING * lib_string, const int start, const int chars_num){
    //start, chars_numから文字列コピーの開始位置startと、停止位置lastを決定する
    int first = (start >= 0)     ? start                 : lib_string->count + start;
    int last  = (chars_num >= 0) ? first + chars_num - 1 : lib_string->count + chars_num - 1;

    //返却用構造体の用意
    STRING *ret_string;
    ret_string = str_create();
    //必要分のサイズを用意する。
    ret_string = add_memsize(ret_string, last - first + 1);

    //lib_stringのfirst文字目からlast文字までをret_stringにコピーしていく
    for(int i=0; first+i<=last; i++){
        ret_string->string[i] = lib_string->string[first+i];
        ret_string->count++;
    }
    //最後にnull文字を加える
    ret_string->string[ret_string->count] = '\0';
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
