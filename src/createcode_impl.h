#ifndef CREATECODE_IMPL_H
#define CREATECODE_IMPL_H 

#include <stdlib.h>
#include <stdio.h>

#include "HuffmanTable.h"
#include "HuffmanTree.h"
#include "util.h"

/** Checks for correct number of arguments. */
int main_validConsoleInput(int argc, char* argv[]) {
   int valid = argc == 3;
   return valid;
}

/** Prints the usage message. */
void main_printConsoleUsageMessage(int argc, char* argv[]) {
    fprintf(stdout, "Usage: ./createcode367 <frequency file> <codebook file>\n");
}


#define BYTE_TO_BIN_PATTERN "%d%d%d%d%d%d%d%d"

#define BYTE_TO_BIN(byte) \
    (byte & 0x80 ? 1 : 0), \
    (byte & 0x40 ? 1 : 0), \
    (byte & 0x20 ? 1 : 0), \
    (byte & 0x10 ? 1 : 0), \
    (byte & 0x08 ? 1 : 0), \
    (byte & 0x04 ? 1 : 0), \
    (byte & 0x02 ? 1 : 0), \
    (byte & 0x01 ? 1 : 0)



/** This is how we print out the codebook encoding.
 *  It's 1 for internal and 0 + 8-bits for leaf.
 */
void main_HuffmanTreeNode_printCodebookEncoding(
    struct HuffmanTreeNode* node,
    void*  vp_file
) {
    FILE* file = (FILE*) vp_file;
    
    if (node->code == 1) {
        fprintf(file, "1");
    } else {
        char buffer[9];
        fprintf(file, "0");
        intToBinString(node->name, buffer, 9);
        fprintf(file, "%s", buffer);
    }
}

#endif /* CREATECODE_IMPL_H */
