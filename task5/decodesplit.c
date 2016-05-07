#include <stdio.h>
#include <stdlib.h>

#include "util.h"

int main(int argc, char* argv[]) {
    if (argc == 4) {
        FILE* filein            = fopen(argv[1], "r");
        FILE* file_codebook     = fopen(argv[2], "w");
        FILE* file_encoded      = fopen(argv[3], "w");

        if (!(filein && file_codebook && file_encoded)) {
            printf("ERROR: Could not open files.\n");
            return 1;
        }

        /* Get the file size. */
        long i = 0;
        char buffer[15];
        for(; i < 14; ++i) {
            buffer[i] = fgetc(filein);
        } buffer[14] = '\0';
        long codebook_size = binStringToInt(buffer, 15);
        printf("CODEBOOK SIZE: %ld\n", codebook_size);

        rewind(filein);

        char c;
        i = 0;
        for(; i < codebook_size; ++i) {
            c = fgetc(filein);
            fprintf(file_codebook, "%c", c);
        }

        while (c != EOF) {
            c = fgetc(filein);
            fprintf(file_encoded, "%c", c);
        };

        fclose(file_codebook);
        fclose(file_encoded);

        return 0;

    } else {
        printf("./decodesplit367 <compressed data file> <codebook file> <encoded data file>\n");
    }
}
