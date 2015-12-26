#include <stdio.h>
#include <string.h>
#include "str.h"


static int str_create_test(void);
static int str_set_test(void);

int main(void){

    //str_create()のテスト
    str_create_test();

    //str_setのテスト
    str_set_test();
}

static int str_create_test(void){
    printf("******** str_create_test start ***********\n");

    //前処理
    int ret_val = 1;
    STRING *s1;

    //テスト1
    s1 = str_create();
    if(sizeof(*s1) == sizeof(STRING)){
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
    STRING *s, *s2, *s3, *s4;
    s = str_create();
    s2 = str_create();
    s3 = NULL;
    s4 = str_create();
//    str_set(s4, "abc");

    //テスト1 通常
//    str_set(s, "123");
//    if(strcmp(s, "123")==0){
//        printf("test_1 ok\n");
//    }else{
//        printf("test_1 ng\n");
//        ret_val = 0;
//    }

    //テスト2 ものすごい長い
    str_set(s2, "abcdefghijklmnop");
        printf("a %s\n", s2);
    if(strcmp(s2, "abcdefghijklmnop")==0){
        printf("test_2 ok\n");
    }else{
        printf("test_2 ng\n");
        printf("a %s\n", s2);
        printf("b %s\n", "abcdefghijklmnop");
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
//    str_set(s4, "123");
//    if(strcmp(s4, "123") == 0){
//        printf("test_4 ok\n");
//    }else{
//        printf("test_4 ng\n");
//        ret_val = 0;
//    }

    printf("******** str_set_test end ***********\n\n\n\n");
    return ret_val;

}
