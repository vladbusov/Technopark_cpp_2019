#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "counter.h"


int main() {

    char buffer[128];
    printf("Введите строку символов:\n");
    scanf("%s", buffer);

    char countBuff[128];

    printf("Введите символы для счета:\n");
    scanf("%s", countBuff);

    int* sharedCnt = calloc(strlen(countBuff),sizeof(int));

    interProcessCounter(buffer, countBuff, sharedCnt);
    printResult(sharedCnt, (int) strlen(countBuff));

    free(sharedCnt);
    return 0;
}

