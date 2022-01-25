#include <stdio.h>
#include "foo.h"

#ifdef X
#define Y "X DEFINED"
#else
#define Y "X NOT DEFINED"
#endif

int main(void)
{
    printf("Start calling foo() ...\n");
    foo(1);
    foo(2);
    if (0)
    {
        printf("skip this line.");
    }
    return 0;
}
