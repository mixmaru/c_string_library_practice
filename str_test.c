#include <stdio.h>
#include <string.h>
#include "str.h"


static int str_create_test(void);
static int str_set_test(void);
static int str_add_test(void);
static int str_extract_test(void);

int main(void){

    //str_create()のテスト
//    str_create_test();
//
//    //str_setのテスト
//    str_set_test();
//
//    //str_addのテスト
//    str_add_test();
//
//    //str_extractのテスト
//    str_extract_test();

    //str_copyのテスト
    //テスト1
    STRING *lib_string;
    lib_string = str_create();
    str_set(lib_string, "abcde");
    if(str_copy(lib_string, "0123456", 2, 3, 3)){
        if(strcmp(lib_string->string, "ab345") == 0){
            printf("test1 ok\n");
        }else{
            printf("test1 ng\n");
        }
    }else{
        printf("test1 ng\n");
    }
    str_destroy(lib_string);

    //テスト2 target_startが外部を指す。
    STRING *lib_string2;
    lib_string2 = str_create();
    str_set(lib_string2, "abcde");
    if(str_copy(lib_string2, "0123456", 6, 1, 1)){
        printf("test2 ng\n");
    }else{
        printf("test2 ok\n");
    }
    str_destroy(lib_string2);

    //テスト3 string_startが外部を指す。
    STRING *lib_string3;
    lib_string3 = str_create();
    str_set(lib_string3, "abcde");
    if(str_copy(lib_string3, "0123456", 2, 7, 1)){
        printf("test3 ng\n");
    }else{
        printf("test3 ok\n");
    }
    str_destroy(lib_string3);

    //テスト4 limitが外部を指す。
    STRING *lib_string4;
    lib_string4 = str_create();
    str_set(lib_string4, "abcde");
    if(str_copy(lib_string4, "0123456", 2, 1, 100)){
        if(strcmp(lib_string4->string, "ab123456") == 0){
            printf("test4 ok\n");
        }else{
            printf("test4 ng\n");
        }
    }else{
        printf("test4 ng\n");
    }
    str_destroy(lib_string4);
}

static int str_create_test(void){
    printf("******** str_create_test start ***********\n");

    //前処理
    int ret_val = 1;
    STRING *s1;

    //テスト1
    s1 = str_create();
    if(sizeof(*s1) == sizeof(STRING) && s1->string[0] == '\0' && s1->count == 0){
        printf("test_1 ok\n");
    }else{
        printf("test_1 ng\n");
        ret_val = 0;
    }

    printf("******** str_create_test end ***********\n\n\n\n");
    return ret_val;
}

static int str_set_test(void){
    printf("******** str_set_test start ***********\n");

    //前処理
    int ret_val = 1;
    STRING *s, *s2, /**s3,*/ *s4, *s5;
    s = str_create();
    s2 = str_create();
//    s3 = NULL;
    s4 = str_create();
    str_set(s4, "abc");
    s5 = str_create();

    //テスト1 通常
    str_set(s, "123");
    if(strcmp(s->string, "123")==0){
        printf("test_1 ok\n");
    }else{
        printf("test_1 ng\n");
        ret_val = 0;
    }

    //テスト2 ものすごい長い
    str_set(s2, "123111111111111111111111111111111111111111111111111111");
    if(strcmp(s2->string, "123111111111111111111111111111111111111111111111111111")==0){
        printf("test_2 ok\n");
    }else{
        printf("test_2 ng\n");
        ret_val = 0;
    }

    //テスト3 初期化されていない
//    if(str_set(s3, "123")){
//        //エラーが出ていないので、正しくない
//        printf("test_3 ng\n");
//        ret_val = 0;
//    }else{
//        printf("test_3 ok\n");
//    }

    //テスト4 すでに文字列が入っている
    str_set(s4, "123");
    if(strcmp(s4->string, "123") == 0){
        printf("test_4 ok\n");
    }else{
        printf("test_4 ng\n");
        ret_val = 0;
    }

    //テスト5 空文字をセット
    str_set(s5, "");
    if(strcmp(s5->string, "") == 0){
        printf("test_5 ok\n");
    }else{
        printf("test_5 ng\n");
        ret_val = 0;
    }

    printf("******** str_set_test end ***********\n\n\n\n");
    return ret_val;

}

static int str_add_test(void){
    printf("******** str_add_test start ***********\n");

    //前処理
    int ret_val = 1;
    STRING *s1, *s2, *s3, *s4;
    s1 = str_create();
    str_set(s1, "abc");

    s2 = str_create();

    s3 = str_create();
    str_set(s3, "abcdefghijklmnopqrstu");

    s4 = str_create();
    str_set(s4, "abc");

    //テスト1 通常
    str_add(s1, "123");
    if(strcmp(s1->string, "abc123") == 0){
        printf("test_1 ok\n");
    }else{
        printf("test_1 ng\n");
        ret_val = 0;
    }

    //テスト2 中身が空
    str_add(s2, "123");
    if(strcmp(s2->string, "123") == 0){
        printf("test_2 ok\n");
    }else{
        printf("test_2 ng\n");
        ret_val = 0;
    }

    //テスト3 長い文字を追加
    str_add(s3, "1234567891234567890123456789012345678901234567890");
    if(strcmp(s3->string, "abcdefghijklmnopqrstu1234567891234567890123456789012345678901234567890") == 0){
        printf("test_3 ok\n");
    }else{
        printf("test_3 ng\n");
        ret_val = 0;
    }

    //テスト4 繰り返し追加
    str_add(s4, "123");
    str_add(s4, "abc");
    str_add(s4, "123");
    str_add(s4, "abc");
    str_add(s4, "123");
    str_add(s4, "abc");
    if(strcmp(s4->string, "abc123abc123abc123abc") == 0){
        printf("test_4 ok\n");
    }else{
        printf("test_4 ng\n");
        ret_val = 0;
    }

    printf("******** str_add_test end ***********\n\n\n\n");
    return ret_val;
}

static int str_extract_test(void){
    printf("******** str_extract_test start ***********\n");

    //前処理
    int ret_val = 1;
    STRING *s1_1 = NULL;
    STRING *s1_2 = NULL;
    s1_1 = str_create();
    str_set(s1_1, "abcdefg");

    STRING *s2_1 = NULL;
    STRING *s2_2 = NULL;
    s2_1 = str_create();
    str_set(s2_1, "abcdefg");

    STRING *s3_1 = NULL;
    STRING *s3_2 = NULL;
    s3_1 = str_create();
    str_set(s3_1, "abcdefg");

    STRING *s4_1 = NULL;
    STRING *s4_2 = NULL;
    s4_1 = str_create();
    str_set(s4_1, "abcdefg");

    STRING *s5_1 = NULL;
    STRING *s5_2 = NULL;
    s5_1 = str_create();
    str_set(s5_1, "abcdefg");

    STRING *s6_1 = NULL;
    STRING *s6_2 = NULL;
    s6_1 = str_create();
    str_set(s6_1, "abcdefg");

    STRING *s7_1 = NULL;
    STRING *s7_2 = NULL;
    s7_1 = str_create();
    str_set(s7_1, "abcdefg");

    STRING *s8_1 = NULL;
    STRING *s8_2 = NULL;
    s8_1 = str_create();
    str_set(s8_1, "abcdefg");

    STRING *s9_1 = NULL;
    STRING *s9_2 = NULL;
    s9_1 = str_create();
    str_set(s9_1, "abcdefg");

    //テスト1 通常
    s1_2 = str_extract(s1_1, 2, 3);
    if(strcmp(s1_2->string, "cde") == 0){
        printf("test_1 ok\n");
    }else{
        printf("test_1 ng\n");
        ret_val = 0;
    }

    //テスト2 startが範囲外を指定(空文字を返す)
    s2_2 = str_extract(s2_1, 100, 3);
    if(strcmp(s2_2->string, "") == 0){
        printf("test_2 ok\n");
    }else{
        printf("test_2 ng\n");
        ret_val = 0;
    }

    //テスト3 lengthが取得できる最大文字数より大きい(startから最後までを切り出して返す)
    s3_2 = str_extract(s3_1, 1, 100);
    if(strcmp(s3_2->string, "bcdefg") == 0){
        printf("test_3 ok\n");
    }else{
        printf("test_3 ng\n");
        ret_val = 0;
    }

    //テスト4 startが負の数(最後から数えて指定番目の文字をstartとする)
    s4_2 = str_extract(s4_1, -5, 2);
    if(strcmp(s4_2->string, "cd") == 0){
        printf("test_4 ok\n");
    }else{
        printf("test_4 ng\n");
        ret_val = 0;
    }

    //テスト5 lengthが負の数(最後の文字から指定の数の文字が省略される)
    s5_2 = str_extract(s5_1, 2, -2);
    if(strcmp(s5_2->string, "cde") == 0){
        printf("test_5 ok\n");
    }else{
        printf("test_5 ng\n");
        ret_val = 0;
    }

    //テスト6 lengthが負の数でstartの位置よりも手前になった場合(空文字を返す)
    s6_2 = str_extract(s6_1, 5, -5);
    if(strcmp(s6_2->string, "") == 0){
        printf("test_6 ok\n");
    }else{
        printf("test_6 ng\n");
        ret_val = 0;
    }

    //しきい値チェック
    //テスト7 startが最後の文字を指定(最後の文字を返す)
    s7_2 = str_extract(s7_1, 6, 100);
    if(strcmp(s7_2->string, "g") == 0){
        printf("test_7 ok\n");
    }else{
        printf("test_7 ng\n");
        ret_val = 0;
    }

    //テスト8 start lengthがどちらも正で、startが最後の文字、lengthが1のとき(最後の文字を返す)
    s8_2 = str_extract(s8_1, 6, 1);
    if(strcmp(s8_2->string, "g") == 0){
        printf("test_8 ok\n");
    }else{
        printf("test_8 ng\n");
        ret_val = 0;
    }

    //テスト9 start lengthがどちらも負で、start指定位置の文字のみ取得できる場合
    s9_2 = str_extract(s9_1, -2, -1);
    if(strcmp(s9_2->string, "f") == 0){
        printf("test_9 ok\n");
    }else{
        printf("test_9 ng\n");
        ret_val = 0;
    }
    printf("******** str_extract_test end ***********\n\n\n\n");
    return ret_val;
}
