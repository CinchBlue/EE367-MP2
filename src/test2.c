#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int main() {
    int i = 7;
    char buffer[20];

    intToBinString(i, buffer, 15);
    printf("%s\n", buffer);
    
    long j = binStringToInt(buffer, 15);
    printf("%ld\n", j);

    return 0;
}
