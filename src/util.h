#ifndef UTIL_H
#define UTIL_H 

#include <stdio.h>
#include <stdlib.h>

char* intToBinString(long i, char* buffer, int size) {
    int j = 0;
    for (j = 0; j < size-1; ++j) {
        char c = '0' + i % 2;
        i = i / 2;
        buffer[j] = c;
    }

    for (j = 0; j < (size-1)/2; ++j) {
        char temp = buffer[j];
        buffer[j] = buffer[size-2-j];
        buffer[size-2-j] = temp;
    }
    buffer[size-1] = '\0';

    return buffer;
}

/** size is the position of offset of the null character from buffer */
long binStringToInt(char* buffer, int size) {
    int sum = 0;

    int j = 0;
    for (j = 0; j < (size-1)/2; ++j) {
        char temp = buffer[j];
        buffer[j] = buffer[size-2-j];
        buffer[size-2-j] = temp;
    }

    buffer[size-1] = '\0';
    int factor = 1;
    for(j = 0; j < size && buffer[j] != '\0'; ++j) {
        sum += factor * (buffer[j]-'0');
        factor *= 2;
    }

    return sum;
}

#endif /* UTIL_H */
