#include <stdio.h>
#include <stdlib.h>
#include "str.h"

/*STRING構造体の初期化を行う*/
static void str_init(STRING *s){
    s->string = (char *)calloc(1, sizeof(char));
    s->count = 0;
}

/*STRING構造体の文字列サイズを追加する*/
static STRING * add_memsize(STRING * s, const int add_size){
    s->string = (char *)realloc(s->string, s->count + add_size + 1);
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
void str_set(STRING *s, const char *str){
    if(s->count != 0){
        str_init(s);
    }
    str_add(s, str);
}

/* 文字列追加 */
void str_add(STRING *s, const char *str){
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
    s->string[start+i+1] = '\0';
}

/* （第二引数）文字目から（第三引数）文字取り出した新しい文字列を返す */
/*  */
STRING *str_extract(const STRING *string, const int start, const int length){
    //start, lengthが負だとエラー
    if(start < 0 || length < 0){
        printf("str_extractに正しい引数を渡してください\n");
        printf("第二引数、第三引数は正の整数をいれてください\n");
        exit(0);
    }
    //startがstringの文字数を超えていればエラーとする
    if(string->count < start){
        printf("str_extractに正しい引数を渡してください\n");
        exit(0);
    }

    STRING *ret_string;
    ret_string = str_create();
    //length分のサイズを用意する。
    ret_string = add_memsize(ret_string, length);

    //stringをstart位置から一文字ずつコピーする。
    //stringが\0に達したらそこで終了
    int i=0;
    int j=start;      //i:コピー先文字列用カウンタ, j:コピー元文字列用カウンタ
    while(string->string[i] != '\0' && i < length){
        ret_string->string[i] = string->string[j];
        ret_string->count++;
        i++; j++;
    }
    //\0を追加する
    ret_string->string[i+1] = '\0';
    return ret_string;
}

/* printfで出力できる文字列を返す */
char *str_value(const STRING *s){
    return s->string;
}

/* 文字列の長さを返す */
int str_length(const STRING *s){
    return s->count;
}

/* リソース開放 */
void str_destroy(STRING *s){
    free(s->string);
    free(s);
}
