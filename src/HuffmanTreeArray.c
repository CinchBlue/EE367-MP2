#include "HuffmanTree.h"
#include "HuffmanTable.h"

/* This implementation assumes this is using an array implementation
 * such that if the parent is [i] using a zero-index
 *      - left = [2*(i+1) - 1]
 *      - right = [2*(i+1)]
 *      - parent = [(i+1)/2]
struct HuffmanTreeNode {
    char code;
    char name; 
    float prob; 
};
