#ifndef STR_H
#define STR_H

typedef struct{
    char *string;   //文字列ポインタ
    int count;      //文字数(null文字を含まない)
} STRING;


/* リソース確保＆初期化（中身を空文字列にする） */
STRING *str_create(void);

/* 文字列をセット */
int str_set(STRING *, const char *);

/* 文字列追加 */
int str_add(STRING *, const char *);

/* （第二引数）文字目から（第三引数）文字取り出した新しい文字列を返す */
STRING *str_extract(const STRING *, const int, const int);

/* printfで出力できる文字列を返す */
char *str_value(const STRING *);

/* 文字列の長さを返す */
int str_length(const STRING *);

/* リソース開放 */
void str_destroy(STRING *);

int str_copy(STRING *, const char *, unsigned int, unsigned int, unsigned int);

#endif //STR_H
