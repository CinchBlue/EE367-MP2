/* EE367  - Machine Problem 2
 * Author - Austin Tasato
 */

#include <stdlib.h>
#include <stdio.h>

#include "HuffmanTable.h"
#include "HuffmanTree.h"
#include "createcode_impl.h"
#include "util.h"

int main(int argc, char* argv[]) {
    if (main_validConsoleInput(argc, argv) == 1) {
        /* TEST: main_validConsoleInput and main_printConsoleUsageMessage */
        printf("Correct input.\n\n");
        
        /* TEST: got correct inputs */
        char* const input_file      = argv[1];
        char* const output_file     = argv[2];
        printf("Input: %s, Output: %s\n\n", input_file, output_file);

        /* TEST: file -> HuffmanTable */
        struct HuffmanTable* huffman_table =
            HuffmanTable_ctor_filename(input_file);

        /* TEST: sort(huffman_table), ascending */
        huffman_table =
            HuffmanTable_sort(huffman_table, 1);
        
        HuffmanTable_print(huffman_table);
        printf("\n\n");

        /* TEST: Construct HuffmanTree */
        struct HuffmanTree* huffman_tree =
            HuffmanTree_ctor_HuffmanTable(huffman_table);

        HuffmanTree_traverse_clr(huffman_tree, HuffmanTreeNode_print, NULL);
        printf("\n\n");

        
        /* TEST: Print the encoding */
        FILE* file_temp = fopen("temp.createcode", "w");
        if (file_temp == NULL) {
            fprintf(stdout, "ERROR: Could not open temp output file.\n");
        }
       
        HuffmanTree_traverse_clr(
            huffman_tree,
            main_HuffmanTreeNode_printCodebookEncoding,
            (void*) file_temp
        );

        fclose(file_temp);

 
        /* reopen the temp file, but for reading. */
        file_temp = fopen("temp.createcode", "r");
        if (file_temp == NULL) {
            fprintf(stdout, "ERROR: Could not open temp output file.\n");
        }

        /* Get the codebook file size. */
        fseek(file_temp, 0L, SEEK_END);
        long file_temp_size = ftell(file_temp);
        fseek(file_temp, 0L, SEEK_SET); 

        fprintf(stdout, "file temp size: %014lu\n", file_temp_size);

        /* open the read output file */
        FILE* file_out = fopen(output_file, "w");
        if (file_out == NULL) {
            fprintf(stdout, "ERROR: Could not open codebook output file.\n");
        }

        /* Print the final file size in "binary" format out to output file */
        char file_size_buffer[15];
        intToBinString(file_temp_size+14, file_size_buffer, 15);
        fprintf(
            file_out,
            "%s",
            file_size_buffer);

        fprintf(
            stdout,
            "file_temp_size(binary): %s",
            file_size_buffer);
        

        /* copy the codebook into the output file */
        char buffer[200];
        while(fgets(buffer, 200, file_temp)) {
            fputs(buffer, file_out);
        }
        
        fclose(file_out);
        fclose(file_temp);

        return 0;

    } else {
        main_printConsoleUsageMessage(argc, argv);
    }

}
