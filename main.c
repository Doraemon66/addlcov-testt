#include <stdio.h>
#include "foo.h"
#include "fib.h"

int main(void)
{
    printf("Start calling foo() ...\n");
    foo5(5);
    foo(5);
    Fibon3(3);
    Fibon3(4);
    return 0;
}
