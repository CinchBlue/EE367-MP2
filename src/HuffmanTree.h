#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "HuffmanTable.h"

/** The node type used in the HuffmanTree. Simple. */
struct HuffmanTreeNode {
    char                code;
    char                name;
    float               prob;
    struct HuffmanTreeNode*    left;
    struct HuffmanTreeNode*    right;
};

struct HuffmanTreeNode* HuffmanTreeNode_ctor(int code, char name, float prob);
struct HuffmanTreeNode* HuffmanTreeNode_ctor_leaf(char name, float prob);
struct HuffmanTreeNode* HuffmanTreeNode_ctor_internal();

void HuffmanTreeNode_print(struct HuffmanTreeNode* pthis, void* null);

/* LEFT RIGHT CENTER */
void HuffmanTreeNode_traverse_lrc(struct HuffmanTreeNode* pthis,
                                  void (*f) (struct HuffmanTreeNode*, void*),
                                  void* info); 

/* CENTER LEFT RIGHT */
void HuffmanTreeNode_traverse_clr(struct HuffmanTreeNode* pthis,
                                  void (*f) (struct HuffmanTreeNode*, void*),
                                  void* info); 


/*****************************************************************/
/*****************************************************************/
/*****************************************************************/



/** A binary tree that consits of nodes of type <char, float>
 *  that represent the character and probability respectively.
 */
struct HuffmanTree {
    int size;
    int numnames;
    struct HuffmanTreeNode* head; 
};


struct HuffmanTree* HuffmanTree_ctor(struct HuffmanTreeNode* head);
struct HuffmanTree* HuffmanTree_ctor_HuffmanTable(struct HuffmanTable* ptable);
struct HuffmanTree* HuffmanTree_ctor_codebook(char* filename);

struct HuffmanTree* HuffmanTree_insert_left(struct HuffmanTree* root,
                                            struct HuffmanTree* other);

struct HuffmanTree* HuffmanTree_insert_right(struct HuffmanTree* root,
                                             struct HuffmanTree* other);

void HuffmanTreeNode_free_subtree(struct HuffmanTreeNode* head);
void HuffmanTree_traverse_lrc(struct HuffmanTree* pthis,
                              void (*f) (struct HuffmanTreeNode*, void*),
                              void* info);
void HuffmanTree_traverse_clr(struct HuffmanTree* pthis,
                              void (*f) (struct HuffmanTreeNode*, void*),
                              void* info);
struct HuffmanTree* HuffmanTree_merge(struct HuffmanTree* lhs,
                                      struct HuffmanTree* rhs);

/* Sorts the HuffmanTree array. */
struct HuffmanTree** HuffmanTreeArray_sort(struct HuffmanTree** arr, int size);



    

#endif /* HUFFMANTREE_H */
