#include <stdlib.h>
#include <stdio.h>

#include "HuffmanTable.h"
#include "HuffmanTree.h"

int main() {
   
    struct HuffmanTable* table = HuffmanTable_ctor_filename("test.table");

    HuffmanTable_sort(table, 1);
    HuffmanTable_print(table);


    /* 
    struct HuffmanTreeNode* nodel = HuffmanTreeNode_ctor_leaf('A', 0.5);
    struct HuffmanTreeNode* noder = HuffmanTreeNode_ctor_leaf('B', 0.5);
   
    struct HuffmanTree* treel = HuffmanTree_ctor(nodel);
    struct HuffmanTree* treer = HuffmanTree_ctor(noder);

    struct HuffmanTree* tree = HuffmanTree_merge(treel, treer);

    HuffmanTree_traverse(tree, HuffmanTreeNode_print);
    */

    struct HuffmanTree* fromTable = HuffmanTree_ctor_HuffmanTable(table);

    HuffmanTree_traverse_clr(fromTable, HuffmanTreeNode_print);

    return 0;
}
