#include <stdio.h>

void foo4(int num)
{
    if (num >3) {
        printf("when num is equal to 3...\n");
    } else if (num ==1){
        printf("when num is equal to 4...\n");
    } else {
        printf("UT demo\n");
    }
}

void foo(int num)
{
    if (num >3) {
        printf("demo_ok\n");
    } else if (num <1){
        printf("demo_ok\n");
    } else {
        printf("demo_error\n");
    }
}

void foo2(int num)
{
    if (num == 3) {
        printf("when num is equal to 3...\n");
    } else if (num == 4){
        printf("when num is equal to 4...\n");
    } else {
        printf("when num is equal to %d...\n", num);
    }
}

void foo5(int num)
{
    if (num >3) {
        printf("UT demo_ok\n");
    } else if (num <1){
        printf("UT demo_ok\n");
    } else {
        printf("UT demo_error\n");
    }
}

void foo3(int num)
{
    if (num == 3) {
        printf("when num is equal to 3...\n");
    } else if (num == 4){
        printf("when num is equal to 4...\n");
    } else {
        printf("when num is equal to %d...\n", num);
    }
}
