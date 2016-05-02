#include "HuffmanTable.h"

/** Constructs a HuffmanTable from a file.
 *   - Returns NULL if invalid file.
 *   - Returns the HuffmanTable otherwise. 
 *      - Not required to return a non-zero size; it's all according to the file.
 */
struct HuffmanTable* HuffmanTable_ctor_filename(char* filename) {
    /* Check if file is valid. */
    FILE* file;
    file = fopen(filename, "r");
    if (file == NULL) {
       return (struct HuffmanTable*) NULL;
    }

    /* Read in number of entries. */
    int num_entries = 0;
    fscanf(file, "%d\n", &num_entries);

    /* Allocate the static part of the table */
    struct HuffmanTable* ptable =
        (struct HuffmanTable*) malloc(sizeof(struct HuffmanTable));     

    /* Allocate the memory for the entries */
    ptable->size      = num_entries;
    ptable->names     = (char*)  malloc(sizeof(char)  * ptable->size);
    ptable->probs     = (float*) malloc(sizeof(float) * ptable->size);

    /* For each entry, read in the row in the table. */
    int i = 0;
    for (i = 0; i < ptable->size; ++i) {
        fscanf(file,
            "%hhu %f\n", /* %hhu is for (unsigned char) number literal. */
            &ptable->names[i],
            &ptable->probs[i]
        );
    }

    /* Return a pointer to the table. */
    return ptable;
}


/** Check if in bounds. */
int HuffmanTable_check_isValidIndex(struct HuffmanTable* pthis,
                                    int i) {
    return (i >= 0 && i < pthis->size);
}

/** Swaps two elements in the table.
 *  - Returns 0/1 for failure/success. 
 */
int HuffmanTable_swapElements(struct HuffmanTable* pthis,
                             int i,
                             int j) {

    /* Check for validity. */
    if (HuffmanTable_check_isValidIndex(pthis, i) 
        && HuffmanTable_check_isValidIndex(pthis, j)
        && pthis != NULL) {
        
        /* Swap */
        char name    = '\0';
        float prob  = 0.0; 

        /* i -> temp */
        name = pthis->names[i]; 
        prob = pthis->probs[i]; 
        /* j -> i */
        pthis->names[i] = pthis->names[j];
        pthis->probs[i] = pthis->probs[j];
        /* temp -> j */ 
        pthis->names[j] = name;
        pthis->probs[j] = prob; 
        return 1;
    } else {
        fprintf(stderr, "HuffmanTable_swapElements: Could not swap HuffmanTable indices (%d, %d)\n", i, j);
        return 0;
    } 
}



/** Sorts a HuffmanTable in ascending/descending order using insertion sort 
 *  - 1 => ascending, 0 => descending.
 */ 
struct HuffmanTable* HuffmanTable_sort(struct HuffmanTable* pthis,
                                       int ascending) {
    if (ascending == 1) {
        int i = 0;
        for (i = 0; i < pthis->size; ++i) {
            int j = i;
            while (j > 0 && pthis->probs[j-1] > pthis->probs[j]) {
                HuffmanTable_swapElements(pthis, j, j-1);
                --j;
            }
        }

    } else { /* Descending */
        int i = 0;
        for (i = 0; i < pthis->size; ++i) {
            int j = i;
            while (j > 0 && pthis->probs[j-1] < pthis->probs[j]) {
                HuffmanTable_swapElements(pthis, j, j-1);
                --j;
            }
        }

    }
    return pthis;
}

/** Prints out the current state of the HuffmanTable similar to its input file */
int HuffmanTable_print(struct HuffmanTable* pthis) {
    /* Print out the size and each row. */
    fprintf(stdout, "Size:\t%3d\n", pthis->size); 

    int i = 0;
    for (i = 0; i < pthis->size; ++i) {
        fprintf(stdout, "[%3d]\t%3d\t%f\n", i, pthis->names[i], pthis->probs[i]);
    }
    
    /* Should always succeed */
    return 1;
}

int HuffmanTable_dtor(struct HuffmanTable* pthis) {
    free(pthis->names);
    free(pthis->probs);
    return 1;
}

