#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        FILE* file = fopen(argv[1], "r");

        if (file != NULL) {
            fseek(file, 0L, SEEK_END);
            size_t filesize = ftell(file);
            printf("%zu\n", filesize);

            if (argc > 2) {
                if (strcmp(argv[2], "--div8")
                    || strcmp(argv[2], "-8")) {
                    printf("%zu\n", filesize/8);
                }
            }
        } else {
            printf("%s: error - could not open file.\n", argv[0]);
        }
    } else {
        printf("USAGE: size FILENAME [--div8 || -8]\n");
    }
}
