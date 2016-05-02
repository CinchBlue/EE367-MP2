#include <stdio.h>
#include "createcode_impl.h"

int main() {
    int i = 7;
    char buffer[20];

    toBinString(i, buffer, 20);

    printf("%s\n", buffer);
    return 0;
}
