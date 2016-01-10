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
STRING *str_extract(STRING * s1, const int num1, const int num2){
    STRING *s2;
    s2 = str_create();
    //num2分のサイズを用意する。
    s2 = add_memsize(s2, num2);

    int i,j;      //i:コピー先文字列用カウンタ, j:コピー元文字列用カウンタ
    for(i=0, j=num1; i<num2; i++,j++){
        s2->string[i] = s1->string[j];
        s2->count++;
    }
    //null文字の追加
    s2->string[i+1] = '\0';
    return s2;
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
