#ifndef ENCODE_IMPL_H
#define ENCODE_IMPL_H

#define ENCODING_BUFFER_SIZE (size_t)257


struct EncodingTable {
    int name[255];
    char encoding[255][ENCODING_BUFFER_SIZE];
};


struct EncodingBuffer {
    int iterator;
    int left_or_right; /* 0 for left, 1 for right */
    char buffer[ENCODING_BUFFER_SIZE];
    struct EncodingTable* table;
};


int main_isConsoleInputGood(int argc, char* argv[]) {
    return argc == 4;
}

void main_printConsoleUsageEncode() {
    printf("./encode367 <codebook file> <data file> <compressed data file>\n");

}



void reverseString(char* buffer, int size) {
    int i = 0;
    for(i = 0; i <= (size-1)/2; ++i) {
        char temp = buffer[i];
        buffer[i] = buffer[size-1-i];
        buffer[size-1-i] = temp;
    }

}

void printTreeEncodingForChar(struct HuffmanTreeNode* node,
                              void* info) {

    /* Here, we will have a buffer to store the encoding, of length
     * char[257].
     *
     * We can assume that the very final 
     */
    struct EncodingBuffer* buffer = (struct EncodingBuffer*) info;
    /* If the current node is 1,
     *      - push a 1 onto the encoding buffer.
     * If the current node is 0,
     *      - push a 0 onto the encoding buffer,
     *      - copy the encoding buffer onto the leaf node's character buffer in
     *        the EncodingTable,
     *      - copy the node's name onto the name in the EncodingTable,
     *      - pop a 0 from the encoding buffer.
     */ 
    if (node->code == 1) {
        buffer->buffer[buffer->iterator] = '1';
        buffer->iterator--;
    } else if (node->code == 0) {
        /* Set the next character of the code to be '0' or '1' depending on
         * if it's a left or right node.
         */
        buffer->buffer[buffer->iterator] = (buffer->left_or_right? ('0') : ('1'));
        /* iterate left/right */
        buffer->left_or_right = !buffer->left_or_right;
        
        strcpy(buffer->table->encoding[node->name], &buffer->buffer[buffer->iterator]);
        reverseString(
            buffer->table->encoding[node->name],
            ENCODING_BUFFER_SIZE-1-buffer->iterator);
        buffer->table->name[node->name] = node->name;
        printf("Encoding: %3d : %s\n",
               buffer->table->name[node->name],
               buffer->table->encoding[node->name]);
        if (buffer->left_or_right == 1) {
            buffer->iterator++;
        }
    }
        
}

#endif /* ENCODE_IMPL_H */

