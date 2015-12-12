#include <stdlib.h>
#include "str.h"

void _add_more_size(STRING *s);


/* リソース確保＆初期化（中身を空文字列にする） */
STRING *str_create(){
    //STRING構造体一つのサイズをmallocで割り当てる。
    //構造体のプロパティを初期化してアドレスを返す
    static STRING *s;
    s = (STRING *)malloc(sizeof(STRING));
    s->string = (char *)malloc(INITIALIZE_BUFFER_SIZE);
    s->max_size = INITIALIZE_BUFFER_SIZE;
    s->count = 1;
    s->string[0] = '\0';
    return s;
}

///* sにstrの文字列をセット */
void str_set(STRING *s, char * const str){
    str_add(s, str);
}

///* 文字列追加 */
//メモリアドレスを、s->stringをs->count-1の位置(null文字を除くため)と,
//strの先頭位置から勧めながらstrの文字をs->stringにコピーしていく。(null文字までコピーする)
//サイズが足りなければ追加する
//文字をコピーするとき、s->countをインクリメントする
void str_add(STRING *s, char * const str){
    s->count--;//null文字分をデクリメント
    int start = s->count;
    int i=0;
    while(1){
        //次の文字を入れるサイズがなければ一定サイズを追加する。
        if(s->max_size == s->count){
            _add_more_size(s);
        }
        s->string[start+i] = str[i];
        s->count++;
        if(str[i] == '\0') break;
        i++;
    }
}

/* （第二引数）文字目から（第三引数）文字取り出した新しい文字列を返す */
STRING *str_extract(STRING * s1, const int num1, const int num2){
    //s2を初期化する
    STRING *s2;
    s2 = str_create();
    //s1->stringの先頭アドレスのnum1番目からnum2番目までの文字をコピーしていく。
    //最後に'\0'をセットする。
    s2->count = 0;
    int i = 0;
    int j = num1;
    for(i=0, j=num1; i<num2; i++,j++){
        //次の文字を入れるサイズがなければ一定サイズを追加する
        if(s2->max_size == s2->count){
            _add_more_size(s2);
        }
        s2->string[i] = s1->string[j];
        s2->count++;
    }
    if(s2->max_size == s2->count){
        _add_more_size(s2);
    }
    s2->string[++s2->count] = '\0';
    return s2;
}

/* printfで出力できる文字列を返す */
char *str_value(STRING *s){
    return s->string;
}

/* 文字列の長さを返す */
int str_length(STRING *s){
    return s->count - 1;//null文字分は取り除く
}

/* リソース開放 */
void str_destroy(STRING *s){
    free(s->string);
    free(s);
}

//文字列保持用のメモリサイズを追加
void _add_more_size(STRING *s){
    s->string = (char *)realloc(s->string, s->max_size + ADD_BUFFER_SIZE);
    s->max_size += ADD_BUFFER_SIZE;
}