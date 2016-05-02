#ifndef HUFFMANTABLE_H
#define HUFFMANTABLE_H 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** A (size x 2) table of type <char, float>
 *  ASSUME: characters are sizeof(char)
 */
struct HuffmanTable {
   int size;
   char* names;
   float* probs;
};

struct HuffmanTable* HuffmanTable_ctor_filename(char* filename);

int HuffmanTable_check_isValidIndex(struct HuffmanTable* pthis, int i);

int HuffmanTable_swapElements(struct HuffmanTable* pthis, int i, int j);

struct HuffmanTable* HuffmanTable_sort(struct HuffmanTable* pthis, int ascending); 

int HuffmanTable_print(struct HuffmanTable* pthis);

int HuffmanTable_dtor(struct HuffmanTable* pthis); 

#endif /* HUFFMANTABLE_H */
