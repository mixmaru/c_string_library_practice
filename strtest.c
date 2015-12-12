//str_create()でstatic STRING s;としていると、
//s2を作ろうとしてstr_create()を呼ぶたびにs1の内容が消えてしまう。
//static は同じ名前は使えない??

#include <stdio.h>
#include "str.h"

int main(void)
{
    /* 文字列リソースの格納先 */
    STRING *s1, *s2;

    /* リソース確保＆初期化（中身を空文字列にする） */
    s1 = str_create();

    /* "123"を設定 */
    str_set(s1, "123");

    /* “abc"を追加（"123abc"） */
    str_add(s1, "abc");

    /* 2文字目から4文字取り出した新しい文字列を作る（"23ab"） */
    s2 = str_extract(s1, 1, 4);

    /* printfで出力できる文字列を返す */
    printf("%s\n", str_value(s1));  /* "123abc" */
    printf("%s\n", str_value(s2));  /* "23ab" */

    /* 文字列の長さを返す */
    printf("%d\n", str_length(s1)); /* 6 */
    printf("%d\n", str_length(s2)); /* 4 */

    /* リソース解放 */
    str_destroy(s1);
    str_destroy(s2);

    return 0;
}