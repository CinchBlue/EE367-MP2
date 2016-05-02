#include "HuffmanTable.h"

int main() {
    struct HuffmanTable* table =
        HuffmanTable_ctor_filename("test.table");
   
    HuffmanTable_print(table);

    printf("Is (-1) a valid index? %d\n",
        HuffmanTable_check_isValidIndex(table, -1));
    printf("Is (9) a valid index? %d\n",
        HuffmanTable_check_isValidIndex(table, 9));

    printf("Sorted table by probability (ascending):\n");
       HuffmanTable_sort(table, 1);
       HuffmanTable_print(table);
    printf("Sorted table by probability (desending):\n");
       HuffmanTable_sort(table, 0);
       HuffmanTable_print(table);

    printf("Destroyed HuffmanTable.\n");
        HuffmanTable_dtor(table);

    return 0;
}
