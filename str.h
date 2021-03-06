#ifndef STR_H
#define STR_H

typedef struct{
    char *string;       //文字列ポインタ
    int max_char_num;   //保持できる最大文字数(null文字を含まない)
    int char_num;       //現在保持している文字数(null文字を含まない)
} STRING;

/* リソース確保＆初期化（中身を空文字列にする） */
STRING *str_create(void);

/* 文字列をセット */
void str_set(STRING *, const char *);

/* 文字列追加 */
void str_add(STRING *, const char *);

/* （第二引数）文字目から（第三引数）文字取り出した新しい文字列を返す */
STRING *str_extract(STRING *, const unsigned int, const unsigned int);

/* printfで出力できる文字列を返す */
char *str_value(STRING *);

/* 文字列の長さを返す */
int str_length(STRING *);

/* リソース開放 */
void str_destroy(STRING *);

#endif //STR_H
