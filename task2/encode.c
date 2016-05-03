#include <stdio.h>
#include <stdlib.h>

#include "HuffmanTree.h"
#include "HuffmanTable.h"
#include "createcode_impl.h"
#include "encode_impl.h"
#include "util.h"


int main(int argc, char* argv[]) {

    if (main_isConsoleInputGood(argc, argv)) {
        /* Read in the tree structure from the file. */
        char* filename_codebook = argv[1];
        char* filename_input    = argv[2];
        char* filename_output   = argv[3];

        struct HuffmanTree* tree = HuffmanTree_ctor_codebook(filename_codebook); 

        /* Print out the tree. */
        HuffmanTree_traverse_clr(tree, HuffmanTreeNode_print, NULL); 

        struct EncodingTable e_table;
        /* Create the encoding buffer. */
        struct EncodingBuffer e_buffer;
        /* Clear the buffer and null-terminate it. */
        EncodingBuffer_ctor(&e_buffer, &e_table);

        

        traverseTreeAndEncode(tree->head, &e_buffer);
        /* Now the table has each of the characters and the table. */

        /* Now, open the input file and the output file */
        FILE* filein = fopen(filename_input, "r");
        if (filein == NULL) {
            printf("ERROR: Could not open data file.\n");
        }

        FILE* fileout = fopen(filename_output, "w");
        if (fileout == NULL) {
            printf("ERROR: Could not open compressed data file.\n");
        }

        /* Read in each character, translate to codebook form,
         * write to output file.
         */
        char c;
        do {
            c = fgetc(filein); 
            if (c == EOF) { break; }
            char* encoding = e_table.encoding[(size_t)c];
            fprintf(fileout, "%s", encoding);
        } while (c != EOF);

        fclose(filein);
        fclose(fileout);
        

    } else {
        main_printConsoleUsageEncode();
    }

    

    return 0;
}
