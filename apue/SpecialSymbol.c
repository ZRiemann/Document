/**@file SpecialSymbol.c
 */
#include <stdio.h>

extern char __executable_start[];
extern char etext[], _etext[], __etext[];
extern char edata[], _edata[];
extern char end[], _end[];

int main(){
    printf("Executable Start %p\n", __executable_start);
    //...
    return 0;
}