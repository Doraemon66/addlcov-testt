#include "fib.h"

int Fibon2(int n)
{
    if (n == 1 || n == 2){
        return 1;
    }
    else
    {
        return 0;
    }
    return -1;
    
}

int Fibon3(int n)
{
    n=n+1;
    if(n==4)
    printf("isOk\n");
    else
    {
        printf("isError\n");
    }
    
    return n;
}
