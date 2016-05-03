#include <stdlib.h>
#include "HuffmanTree.h"
#include "HuffmanTable.h"
#include "encode_impl.h"
#include "util.h"

struct HuffmanTreeNode* setNodeWithString(struct HuffmanTreeNode* node, char c) {
    printf("setNodeWithString "); HuffmanTreeNode_print(node, NULL);
    printf("setNodeWithString IN: %c\n", c);
    if (c == '0') {
        if (node->left != NULL) {
            printf("  went left.\n");
            node = node->left;
        }
    } else if (c == '1') {
        if (node->right != NULL) {
            printf("  went right.\n");
            node = node->right;
        }
    }
    return node;
}

void decodeFileUsingTree(struct HuffmanTree*   tree,
                         struct EncodingTable* e_table,
                         FILE*                 filein,
                         FILE*                 fileout) {

    char c;
    struct HuffmanTreeNode* node = tree->head;
    for (c = fgetc(filein); c != EOF; c = fgetc(filein)) {
       printf("INPUT: %c\n", c);
       node = setNodeWithString(node, c);
       HuffmanTreeNode_print(node, NULL);
       if (node == NULL) {
            printf("ERROR: File encoding does not seem correct.\n");
       } else if (node->code == 0) {
           char found_leaf = node->name;  
           printf("DECODED: %c\n", found_leaf);
           node = tree->head;
           fprintf(fileout, "%c", found_leaf);
       }
    }
}
