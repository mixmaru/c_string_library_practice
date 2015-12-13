#include <stdlib.h>
#include "str.h"

static void _add_more_size(STRING *s);
static int _is_max_size(STRING *);


/* リソース確保＆初期化（中身を空文字列にする） */
STRING *str_create(){
    //STRING構造体一つのサイズをmallocで割り当てる。
    STRING *s;
    s = (STRING *)malloc(sizeof(STRING));

    //sの初期化
    s->string = (char *)calloc(INITIALIZE_BUFFER_SIZE, sizeof(char));
    s->max_size = INITIALIZE_BUFFER_SIZE;
    s->count = 0;
    return s;
}

/* sにstrの文字列をセット */
void str_set(STRING *s, char * const str){
    s->count = 0;
    str_add(s, str);
}

/* 文字列追加 */
void str_add(STRING *s, char * const str){
    int start = s->count;   //文字列追加開始位置
    for(int i=0; str[i]!='\0'; i++){
        //次の文字を入れるサイズがなければ一定サイズを追加する。
        if(_is_max_size(s)){
            _add_more_size(s);
        }
        s->string[start+i] = str[i];
        s->count++;
    }
}

/* （第二引数）文字目から（第三引数）文字取り出した新しい文字列を返す */
STRING *str_extract(STRING * s1, const int num1, const int num2){
    STRING *s2;
    s2 = str_create();

    int i,j;      //i:コピー先文字列用カウンタ, j:コピー元文字列用カウンタ
    for(i=0, j=num1; i<num2; i++,j++){
        //次の文字を入れるサイズがなければ一定サイズを追加する
        if(_is_max_size(s2)){
            _add_more_size(s2);
        }
        s2->string[i] = s1->string[j];
        s2->count++;
    }
    return s2;
}

/* printfで出力できる文字列を返す */
char *str_value(STRING *s){
    return s->string;
}

/* 文字列の長さを返す */
int str_length(STRING *s){
    return s->count;//null文字分は取り除く
}

/* リソース開放 */
void str_destroy(STRING *s){
    free(s->string);
    free(s);
}

//文字列保持用のメモリサイズを追加。追加部分はゼロフィルする。
static void _add_more_size(STRING *s){
    s->string = (char *)realloc(s->string, s->max_size + ADD_BUFFER_SIZE);
    for(int i=0; i<ADD_BUFFER_SIZE; i++){
        printf("add 0 s->string[%d] = 0\n", s->max_size+i);
        s->string[s->max_size + i] = '\0';
    }
    s->max_size += ADD_BUFFER_SIZE;
}

//文字列保持用のメモリサイズが満タンなら1を、そうでなければ0を返す
static int _is_max_size(STRING *s){
    if(s->max_size == s->count+1){//(null文字用サイズのためにs->count+1となる)
        return 1;
    }else{
        return 0;
    }
}