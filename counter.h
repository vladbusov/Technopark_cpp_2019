//
// Created by vlad on 20.10.2019.
//

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#ifndef POTOKI_COUNTER_H
#define POTOKI_COUNTER_H


#define SIZE_OF_CHUNK 2

int min(int a, int b);
void charCounter(char* chars, int* cntChars, const char* buffer, int begin, int end);
void readPipe(int* sharedCnt, int size, int* fd);
void writePipe(char* countBuff, char* buffer, int* fd, int pid, int i);
void interProcessCounter(char* buffer, char* countBuff, int* sharedCnt);
void printResult(int* sharedCnt, int size);

#endif //POTOKI_COUNTER_H
