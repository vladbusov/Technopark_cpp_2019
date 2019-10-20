#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


#define SIZE_OF_CHUNK 2


void charCounter(char* chars, int* cntChars, const char* buffer, int begin, int end) {
    int sizeChars = (int)strlen(chars);

    for (int i = begin; i < end; i++) {
        for (int j = 0; j < sizeChars; j++) {
            if (chars[j] == buffer[i])
                cntChars[j] += 1;
        }
    }
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {

    char buffer[128];
    printf("Введите строку символов:\n");
    scanf("%s", buffer);

    char countBuff[128];

    printf("Введите символы для счета:\n");
    scanf("%s", countBuff);

    int num;
    if (strlen(buffer)%SIZE_OF_CHUNK == 0)
        num = ((int)strlen(buffer))/SIZE_OF_CHUNK;
    else
        num = ((int)strlen(buffer))/SIZE_OF_CHUNK + 1;


    int fd[num][2];
    pid_t pid[num];

    int* sharedCnt = calloc(strlen(countBuff),sizeof(int));


    for (int i = 0; i < num; i ++) {
        pipe(fd[i]);
        pid[i] = fork();

        if (-1 == pid[i]) { /* Error handling ... */ }
        else if (0 == pid[i]) {
            close(fd[i][0]);

            int* cnt = calloc(strlen(countBuff),sizeof(int));
            charCounter(countBuff, cnt, buffer, SIZE_OF_CHUNK*i, min( SIZE_OF_CHUNK*(i+1), (int)strlen(buffer)) );


            write(fd[i][1], cnt, sizeof(int)*strlen(countBuff) );
            free(cnt);
            exit(0);
        }
    }

    for (int i = 0; i < num; i ++) {
        int buf[strlen(countBuff)];
        close(fd[i][1]);

        read(fd[i][0], buf, sizeof(buf));
//        printf("Received %d:\n[", i+1);

        for (int j = 0; j < (int)strlen(countBuff); j++) {
//            printf("%d, ", buf[i]);
            sharedCnt[j] += buf[j];
        }
//        printf("]\n");
    }

    printf("Shared counter :\n[");

    for (int i = 0; i < (int)strlen(countBuff); i++) {
        printf("%d, ", sharedCnt[i]);
    }
    printf("]\n");

    free(sharedCnt);
    return 0;
}

