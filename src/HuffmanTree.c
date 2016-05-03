#include "HuffmanTree.h"
#include "HuffmanTable.h"

/** Easy ctor for HuffmanTreeNode */
struct HuffmanTreeNode* HuffmanTreeNode_ctor(int code, char name, float prob) {

    struct HuffmanTreeNode* pnode =
        (struct HuffmanTreeNode*) malloc(sizeof(struct HuffmanTreeNode));
    pnode->code     = code;
    pnode->name     = name;
    pnode->prob     = prob;
    pnode->left     = NULL;
    pnode->right    = NULL;
    return pnode;
}

struct HuffmanTreeNode* HuffmanTreeNode_ctor_leaf(char name, float prob) {
    return HuffmanTreeNode_ctor(0, name, prob);
}

struct HuffmanTreeNode* HuffmanTreeNode_ctor_internal() {
    return HuffmanTreeNode_ctor(1, -1, 0.0);
}

void HuffmanTreeNode_print(struct HuffmanTreeNode* pthis, void* null) {

    fprintf(stdout, "Node: {%2d, %3d, %f}",
        pthis->code,
        pthis->name,
        pthis->prob);

    if (pthis->left != NULL || pthis->right != NULL) {
        fprintf(stdout, " ->");
    }
    
    if (pthis->left != NULL) {
        fprintf(stdout, " L(%3d)", pthis->left->name);
    }

    if (pthis->right != NULL) {
        fprintf(stdout, " R(%3d)", pthis->right->name);
    }

    fprintf(stdout, "\n");
}

void HuffmanTreeNode_traverse_lrc(struct HuffmanTreeNode* pthis,
                                  void (*f) (struct HuffmanTreeNode*, void*),
                                  void* info) {
    /* iterator pointer */
    typedef struct HuffmanTreeNode Node;
    Node* it = pthis;

    /* ENSURE: All children are called before parents. */

    /* Return if I am NULL. */
    if (pthis == NULL) {
        return;
    }     

    /* Else, call left, right, self, back to parent */
    if (pthis->left != NULL) {
        HuffmanTreeNode_traverse_lrc(it->left, f, info);
    } 
    if (pthis->right != NULL) {
        HuffmanTreeNode_traverse_lrc(it->right, f, info);
    } 
   
    f(it, info);

}


void HuffmanTreeNode_traverse_clr(struct HuffmanTreeNode* pthis,
                                  void (*f) (struct HuffmanTreeNode*, void*),
                                  void* info) {
    /* iterator pointer */
    typedef struct HuffmanTreeNode Node;
    Node* it = pthis;

    /* ENSURE: All children are called before parents. */

    /* Return if I am NULL. */
    if (pthis == NULL) {
        return;
    }     
    f(it, info);

    /* Else, call left, right, self, back to parent */
    if (pthis->left != NULL) {
        HuffmanTreeNode_traverse_clr(it->left, f, info);
    } 
    if (pthis->right != NULL) {
        HuffmanTreeNode_traverse_clr(it->right, f, info);
    } 
   

}



/*****************************************************************/
/*****************************************************************/
/*****************************************************************/



/** Constructs a tree from a HuffmanTreeNode.
 *  - It's left open whether we want a 0 or 1 as the root.
 */
struct HuffmanTree* HuffmanTree_ctor(struct HuffmanTreeNode* head) {
    /* Dyanmic allocation */
    struct HuffmanTree* ptree = 
        (struct HuffmanTree*) malloc(sizeof(struct HuffmanTree)); 

    /* Returns NULL on failed allocation. */
    if (ptree == NULL) {
        return NULL;
    } else {

        ptree->size = 1;
        ptree->numnames = 1;
        ptree->head = head;
        return ptree;
   }
}


/** Destroy all child nodes using depth-first iteration (left, right, current)
 */
void HuffmanTreeNode_free_subtree(struct HuffmanTreeNode* head) {
    /* iterator pointer */
    typedef struct HuffmanTreeNode Node;
    Node* it = head;

    /* If we are NULL, we are nothing, return. */
    if (it == NULL) {
        return;
    }

    /* If we have no children, free ourselves. */
    if (it->left == NULL && it->right == NULL) {
        free(it);
        it = NULL;
        return;
    }

    /* If we do, free them first. */
    HuffmanTreeNode_free_subtree(it->left);
    it->left = NULL;
    HuffmanTreeNode_free_subtree(it->right);
    it->right = NULL;

    /* Now that we have no children, free ourselves. */
    free(it);
    it = NULL;
    return;
}


void HuffmanTree_parse_codebook(
    struct HuffmanTreeNode** it,
    FILE* file,
    long* file_it,
    const long filesize
) {

    /* Determine if 0 or 1.
     * If 1, create a new internal node on the specified node slot iterator.
       Then, insert into the left and right slots recursively.
     * If 0, read the next 8 characters, translate to int, then create a new
       leaf node, and return.
     */
    printf("CURRENT ITERATOR: %ld\n", *file_it);
     
    char c = fgetc(file);
    (*file_it)++;
    printf("CURRENT ITERATOR: %ld\n", *file_it);
    struct HuffmanTreeNode* temp;
    if (c != EOF && *file_it <= filesize) {
        if (c == '1') {
            *it = HuffmanTreeNode_ctor_internal();
            HuffmanTree_parse_codebook(&(*it)->left, file, file_it, filesize);
            HuffmanTree_parse_codebook(&(*it)->right, file, file_it, filesize);
            return;
        } else if (c == '0') {
            char buffer[9];
            int i = 0;
            for (; i < 8; ++i) {
                char c2 = fgetc(file);
                (*file_it)++;
                if (c2 == EOF || *file_it > filesize) {
                    break;
                } else { 
                    buffer[i] = c2;
                }
            }
            int char_value = binStringToInt(buffer, 9);
            *it = HuffmanTreeNode_ctor_leaf(char_value, 0.0f);
            return;
        } 
    } else {
        printf("Reached max file size. Stopping parse of codebook.\n");
    }
}

struct HuffmanTree* HuffmanTree_ctor_codebook(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stdout, "HuffmanTree_ctor_codebook: could not open file.\n");
    }

    int i = 0;
    char buffer[15]; 
    for(; i < 14; ++i) {
        buffer[i] = fgetc(file);
    } buffer[14] = '\0';
    
    long filesize = binStringToInt(buffer, 15) - 14;
    printf("CODEBOOK FILESIZE: %ld\n", filesize);

    /* Determine if 0 or 1.
     * If 1, create a new internal node.
     * If 0, read the next 8 characters, translate to int, then create a new
       leaf node.
     */
    char c = fgetc(file);
    long file_it = 1;
    struct HuffmanTreeNode* temp;
    if (c != EOF) { 
        if (c == '1') {
            temp = HuffmanTreeNode_ctor_internal();
        } else if (c == '0') {
            char buffer[9];
            int i = 0;
            for (; i < 8; ++i) {
                char c2 = fgetc(file);
                file_it++;
                if (c2 == EOF) {
                    break;
                } else { 
                    buffer[0] = c2;
                }
            }
            int char_value = binStringToInt(buffer, 9);
            temp = HuffmanTreeNode_ctor_leaf(char_value, 0.0f);
        }
    }
    printf("CURRENT ITERATOR: %ld\n", file_it);

    /* If we are an internal node, we have already inserted the root.
     * Now, parse left and right and insert into their subtrees.
     * Go into the recursive algorithm. */
    if (temp->code != 0) {
       HuffmanTree_parse_codebook(&temp->left, file, &file_it, filesize);
       HuffmanTree_parse_codebook(&temp->right, file, &file_it, filesize);
    } 

    return HuffmanTree_ctor(temp);
}


struct HuffmanTree* HuffmanTree_insert_left(struct HuffmanTree* root,
                                            struct HuffmanTree* other) {
   root->head->left =  other->head;
   root->numnames   += other->numnames;
   root->size       += other->size;
   free(other);
}

struct HuffmanTree* HuffmanTree_insert_right(struct HuffmanTree* root,
                                             struct HuffmanTree* other) {
   root->head->right = other->head;
   root->numnames   += other->numnames;
   root->size       += other->size;
   free(other);
}

/** Traverses the tree in left-right-current order */
void HuffmanTree_traverse_lrc(struct HuffmanTree* pthis,
                              void (*f) (struct HuffmanTreeNode*, void*),
                              void* info) { 
    /* iterator pointer */
    typedef struct HuffmanTreeNode Node;
    Node* it = pthis->head;

    /* If we are NULL, we are nothing, return. */
    if (it == NULL) {
        return;
    }

    /* Iterate left, right, current, return */
    if (it->left != NULL) {        
        HuffmanTreeNode_traverse_lrc(it->left, f, info);
    }
    if (it->right != NULL) {
        HuffmanTreeNode_traverse_lrc(it->right, f, info);
    } 
    f(it, info); 
    return;
}


/** CENTER LEFT RIGHT */
void HuffmanTree_traverse_clr(struct HuffmanTree* pthis,
                              void (*f) (struct HuffmanTreeNode*, void*),
                              void* info) { 
    /* iterator pointer */
    typedef struct HuffmanTreeNode Node;
    Node* it = pthis->head;

    /* If we are NULL, we are nothing, return. */
    if (it == NULL) {
        return;
    }

    f(it, info);
    /* Iterate center left right return */
    if (it->left != NULL) { 
        HuffmanTreeNode_traverse_clr(it->left, f, info);
    }
    if (it->right != NULL) {
        HuffmanTreeNode_traverse_clr(it->right, f, info);
    } 
    return;
}


/** Constructs a new tree by merging the two trees to a new internal head
 *  HuffmanTreeNode.
 */
struct HuffmanTree* HuffmanTree_merge(struct HuffmanTree* lhs,
                                      struct HuffmanTree* rhs) {
    struct HuffmanTreeNode* newhead = HuffmanTreeNode_ctor_internal();
    newhead->left = lhs->head;
    newhead->right = rhs->head;
    newhead->prob = lhs->head->prob + rhs->head->prob;

    struct HuffmanTree* newtree = HuffmanTree_ctor(newhead);
    newtree->size = lhs->size + rhs->size + 1;
    newtree->numnames = lhs->numnames + rhs->numnames;

    free(lhs);
    free(rhs);

    return newtree;
}

/** Constructs a HuffmanTree from a HuffmanTable as required by the
 *  assignment.
 */
struct HuffmanTree* HuffmanTree_ctor_HuffmanTable(struct HuffmanTable* ptable) {
    /* ERROR: Cannot construct from NULL table. */
    if (ptable == NULL) {
        fprintf(stderr, "HuffmanTable_ctor_HuffmanTable: ptable is NULL\n");
        return NULL;
    }
    
    /* First, sort by ascending order. */
    ptable = HuffmanTable_sort(ptable, 1);

    /* Create an array large enough to hold trees for each element of the
     * table.
     */
    struct HuffmanTree** array_tree = 
        (struct HuffmanTree**) malloc(
            sizeof(struct HuffmanTree*) * ptable->size
        );

    /* Initialize each element of the tree array with an element from the
     * HuffmanTable pushed into its own tree.
     */
    int j;
    for (j = 0; j < ptable->size; ++j) {
        array_tree[j] =
            HuffmanTree_ctor(
                HuffmanTreeNode_ctor_leaf(
                    ptable->names[j],
                    ptable->probs[j]
                )
            );
    } /* OK: Each element in the array of trees is initalized to a leaf node. */

    /* While we don't have only 1 tree left, sort, then merge. */
    int i = ptable->size;
    struct HuffmanTree** array_it = array_tree;
    for (; i > 1; --i) { 
        HuffmanTreeArray_sort(array_it, i);
        fprintf(stdout, "Merging %d and %d...\n", array_it[0]->head->name, array_it[1]->head->name);
        array_it[1] = HuffmanTree_merge(array_it[0], array_it[1]);
        ++array_it;
    }

    return array_it[0]; 
}


/** Sorts an array of HuffmanTrees by probability using insertion sort. */
struct HuffmanTree** HuffmanTreeArray_sort(struct HuffmanTree** arr, int size) {
    int i = 0;
    for (i = 0; i < size; ++i) {
       int j = i;
       while (j > 0 && arr[j-1]->head->prob > arr[j]->head->prob) {
            struct HuffmanTree* temp = arr[j];
            arr[j] = arr[j-1];
            arr[j-1] = temp;
            --j;
       }
    }
    return arr;
}
