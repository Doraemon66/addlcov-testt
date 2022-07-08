#include <stdio.h>

void foo(int num)
{
    if (num == 1) {
        printf("when num is equal to 1...\n");
    } else if (num == 2){
        printf("when num is equal to 2...\n");
    } else {
	printf("ok\n");
        printf("when num is equal to %d...\n", num);
	    printf("ok\n");
	    printf("ok\n");
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
