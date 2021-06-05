#include <stdio.h>
//#include "max.c"
#include "max.h"
#include "min.h"

int main(){
    int a1 = 20;
    int a2 = 18;
    int maxV = max(a1, a2);
    int minV = min(a1, a2);
    printf("max result is %d\n min result is %d\n", maxV,minV);
    return 0;
}
