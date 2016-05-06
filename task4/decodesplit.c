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
        int i = 0;
        char buffer[15];
        for(; i < 14; ++i) {
            buffer[i] = fgetc(filein);
        } buffer[14] = '\0';
        long codebook_size = binStringToInt(buffer, 15);

        /* Rewind to start to file. */
        rewind(filein);

        
        char c;
        i = 0;
        while (c = fgetc(filein)) {
           if (c == EOF && i <= codebook_size) {
                printf("ERROR: File is shorter than projected codebook length.\n");
                break;
           } else if (c == EOF && i > codebook_size) {
                printf("Reached end of file.\n");
                break;
           }
           ++i;
           if (i <= codebook_size) {
                fprintf(file_codebook, "%c", c);
           } else {
                fprintf(file_encoded, "%c", c);
           }
        }

        fclose(file_codebook);
        fclose(file_encoded);

        return 0;

    } else {
        printf("./decodesplit367 <compressed data file> <codebook file> <encoded data file>\n");
    }
}
