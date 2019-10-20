#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "parallelCounter/parallelCounter.h"
#include "trivialCounter/trivialCounter.h"

#define FILESIZE 104857600

int test() {

    FILE* mf=fopen ("test.txt","w");

    srand(time(NULL));

    for (int i = 0; i < FILESIZE; i++) {
        char ch = rand()%255;
        fputc(ch, mf);
    }

    fclose(mf);
}

int main() {

    test();

    FILE* mf=fopen ("test.txt","r");
    char *buffer= (char *) calloc(FILESIZE+10, sizeof(char));
    fgets(buffer, FILESIZE, mf);
    fclose(mf);
//    printf("Введите строку символов:\n");
//    scanf("%s", buffer);

    char countBuff[128] = "qwertyuiop\0";

//    printf("Введите символы для счета:\n");
//    scanf("%s", countBuff);


    int* sharedCnt = calloc(strlen(countBuff),sizeof(int));



    clock_t begin = clock();
    interProcessCounter(buffer, countBuff, sharedCnt);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Время многопроцессного счетчика: %f\n", time_spent);
    printResult(sharedCnt, (int) strlen(countBuff));

    free(sharedCnt);
    sharedCnt = calloc(strlen(countBuff),sizeof(int));

    begin = clock();
    charCount(countBuff, buffer, sharedCnt);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Время тривиального счетчика: %f\n", time_spent);
    printResult(sharedCnt, (int) strlen(countBuff));

    free(sharedCnt);
    free(buffer);
    return 0;
}

