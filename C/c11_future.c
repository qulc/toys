_Static_assert(__STDC_VERSION__ >= 201112L, "C11 support required");

#include <stdio.h>

static void __attribute__((overloadable)) MyFunc(float x)
{
    puts("This is a float function");
}
 
static int __attribute__((overloadable)) MyFunc(int x)
{
    puts(u8"This is an integer function");
    return x;
}
 
int main(int argc, char *argv[])
{

    printf("The alignment of char is %zd.\n", _Alignof (char));
    MyFunc(1.0f);
    MyFunc(1);
}
