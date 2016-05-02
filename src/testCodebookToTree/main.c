#include <stdio.h>
#include <stdlib.h>

#include "HuffmanTree.h"
#include "HuffmanTable.h"
#include "createcode_impl.h"
#include "encode_impl.h"
#include "util.h"

int main(int argc, char* argv[]) {
    /* Read in the tree structure from the file. */
    struct HuffmanTree* tree = HuffmanTree_ctor_codebook(argv[1]); 

    /* Print out the tree. */
    HuffmanTree_traverse_clr(tree, HuffmanTreeNode_print, NULL); 

    struct EncodingTable e_table;
    /* Create the encoding buffer. */
    struct EncodingBuffer e_buffer;
    /* Clear the buffer and null-terminate it. */
    memset(&e_buffer, -1, sizeof(char)*ENCODING_BUFFER_SIZE);
    e_buffer.buffer[ENCODING_BUFFER_SIZE-1] = '\0'; 
    e_buffer.iterator = ENCODING_BUFFER_SIZE-2;
    printf("buffer iterator: %d\n", e_buffer.iterator);
    /* Attach the EncodingTable into the buffer. */
    e_buffer.table = &e_table;

    HuffmanTree_traverse_clr(tree, printTreeEncodingForChar, (void*)&e_buffer);
    
    


    



    return 0;
}
