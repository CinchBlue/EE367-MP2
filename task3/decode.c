#include <stdio.h>
#include <stdlib.h>

#include "HuffmanTree.h"
#include "HuffmanTable.h"
#include "createcode_impl.h"
#include "encode_impl.h"
#include "decode_impl.h"
#include "util.h"

int main(int argc, char* argv[]) {

    /* Just a generic console input checker. */
    if (main_isConsoleInputGood(argc, argv)) {
        char* filename_codebook = argv[1];
        char* filename_input    = argv[2];
        char* filename_output   = argv[3];

        /* Parse in the codebook. */
        struct HuffmanTree* tree =
            HuffmanTree_ctor_codebook(filename_codebook);

        /* Print out the tree. */
        HuffmanTree_traverse_clr(tree, HuffmanTreeNode_print, NULL);

        struct EncodingTable  e_table;
        struct EncodingBuffer e_buffer;
        EncodingBuffer_ctor(&e_buffer, &e_table);
        
        traverseTreeAndEncode(tree->head, &e_buffer);


        FILE* filein = fopen(filename_input, "r");
        if (filein == NULL) {
            printf("ERROR: Could not open data file.\n");
        }

        FILE* fileout = fopen(filename_output, "w");
        if (fileout == NULL) {
            printf("ERROR: Could not open data file.\n");
        }
       
        decodeFileUsingTree(tree, &e_table, filein, fileout);
        return 0;
    } else {
        printf("./decode367 <codebook file> <compressed data file> <uncompressed data file>\n");
        return 0;
    }
}
