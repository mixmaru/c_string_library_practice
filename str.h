#ifndef STR_L
#define STR_L

#define STRING char

/* リソース確保＆初期化（中身を空文字列にする） */
STRING *str_create(void);

/* 初期文字列を設定 */
void str_set(STRING *, const char *);

/* 文字列を追記 */
void str_add(STRING *, const char *);

/* 文字列を切り出す */
STRING *str_extract(STRING *, int, int);

/* 文字列ポインタを返す */
char *str_value(STRING *);

/* 文字数を返す */
int str_length(STRING *);

/* リソース開放 */
void str_destroy(STRING *);

#endif //STR_L