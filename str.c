#include <stdio.h>
#include <stdlib.h>
#include "str.h"

/*STRING構造体の文字列サイズを追加する*/
static STRING * add_memsize(STRING *s, const int add_size){
    s = (char *)realloc(s, str_length(s) + add_size + 1);
    return s;
}

/* リソース確保＆初期化（中身を空文字列にする） */
STRING *str_create(){
    //STRING構造体一つのサイズをmallocで割り当てる。
    STRING *s;
    s = (STRING *)malloc(sizeof(STRING));
    s[0] = '\0';
    return s;
}

/* 文字列をセット */
void str_set(STRING *s, const char *str){
    if(str_length(s) != 0){
        s[0] = '\0';
    }
    str_add(s, str);
}

/* 文字列追加 */
void str_add(STRING *s, const char *str){
    //必要サイズを追加
    int str_count = str_length(str);
    s = add_memsize(s, str_count);

    int start = str_length(s);   //文字列追加開始位置
    int i;
    for(i=0; i<=str_count; i++){
        s[start+i] = str[i];
    }
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
    if(str_length(string) < start){
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
    while(i < length){
        ret_string[i] = string[j];
        if(string[j] == '\0') break;
        i++; j++;
    }
    return ret_string;
}

/* printfで出力できる文字列を返す */
char *str_value(const STRING *s){
    return s;
}

/* 文字列の長さを返す */
int str_length(const STRING *s){
    int ret_num = 0;
    while(s[ret_num]!='\0'){
        ret_num++;
    }
    return ret_num;
}

/* リソース開放 */
void str_destroy(STRING *s){
    free(s);
}
