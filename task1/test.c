#include <stdio.h>
#include "createcode_impl.h"

int main() {
    printf(""BYTE_TO_BIN_PATTERN, BYTE_TO_BIN(0));
    printf(""BYTE_TO_BIN_PATTERN, BYTE_TO_BIN(1));
    printf(""BYTE_TO_BIN_PATTERN, BYTE_TO_BIN(2));
    printf(""BYTE_TO_BIN_PATTERN, BYTE_TO_BIN(4));
    printf(""BYTE_TO_BIN_PATTERN, BYTE_TO_BIN(8));
    printf(""BYTE_TO_BIN_PATTERN, BYTE_TO_BIN(16));
    printf(""BYTE_TO_BIN_PATTERN, BYTE_TO_BIN(32));
    printf(""BYTE_TO_BIN_PATTERN, BYTE_TO_BIN(64));
    printf(""BYTE_TO_BIN_PATTERN, BYTE_TO_BIN(128));
    printf(""BYTE_TO_BIN_PATTERN, BYTE_TO_BIN(255));
}
