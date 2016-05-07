#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

int main() {
    FILE* file = fopen("4.joint", "r");

    int i = 0;
    char buffer[15];
    for(; i < 14; ++i) {
        buffer[i] = fgetc(file);
    }
    buffer[14] = '\0';

    long codebook_length = binStringToInt(buffer, 15);

    printf("length decoded: %ld\n", codebook_length);
    return 0;
}
