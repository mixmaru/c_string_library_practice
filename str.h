#define INITIALIZE_BUFFER_SIZE 10
#define ADD_BUFFER_SIZE 10

typedef struct{
    char *string;
    int max_size;
    int count;
} STRING;

/* リソース確保＆初期化（中身を空文字列にする） */
STRING *str_create(void);

/* 文字列をセット */
void str_set(STRING *, char * const);

/* 文字列追加 */
void str_add(STRING *, char * const);

/* （第二引数）文字目から（第三引数）文字取り出した新しい文字列を返す */
STRING *str_extract(STRING *, const int, const int);

/* printfで出力できる文字列を返す */
char *str_value(STRING *);

/* 文字列の長さを返す */
int str_length(STRING *);

/* リソース開放 */
void str_destroy(STRING *);
