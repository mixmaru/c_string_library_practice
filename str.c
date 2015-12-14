#include <stdlib.h>
#include "str.h"

static void str_init(STRING *);
static void add_more_size(STRING *);
static int is_max_size(STRING *);


/* リソース確保＆初期化（中身を空文字列にする） */
STRING *str_create(){
    //STRING構造体一つのサイズをmallocで割り当てる。
    STRING *s;
    s = (STRING *)malloc(sizeof(STRING));
    str_init(s);
    return s;
}

/* 文字列をセット */
void str_set(STRING *s, char * const str){
    str_init(s);
    str_add(s, str);
}

/* 文字列追加 */
void str_add(STRING *s, char * const str){
    int start = s->count;   //文字列追加開始位置
    for(int i=0; str[i]!='\0'; i++){
        //次の文字を入れるサイズがなければ一定サイズを追加する。
        if(is_max_size(s)){
            add_more_size(s);
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
        if(is_max_size(s2)){
            add_more_size(s2);
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
    return s->count;
}

/* リソース開放 */
void str_destroy(STRING *s){
    free(s->string);
    free(s);
}

/*STRING構造体の初期化を行う*/
static void str_init(STRING *s){
    s->string = (char *)calloc(INITIALIZE_BUFFER_SIZE, sizeof(char));
    s->max_size = INITIALIZE_BUFFER_SIZE;
    s->count = 0;
}

/*文字列保持用のメモリサイズを追加。追加部分はゼロフィルする。*/
static void add_more_size(STRING *s){
    s->string = (char *)realloc(s->string, s->max_size + ADD_BUFFER_SIZE);
    for(int i=0; i<ADD_BUFFER_SIZE; i++){
        s->string[s->max_size + i] = '\0';
    }
    s->max_size += ADD_BUFFER_SIZE;
}

/*文字列保持用のメモリサイズが満タンなら1を、そうでなければ0を返す*/
static int is_max_size(STRING *s){
    if(s->max_size == s->count+1){//(null文字用サイズのためにs->count+1となる)
        return 1;
    }else{
        return 0;
    }
}