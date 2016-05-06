#ifndef ENCODE_IMPL_H
#define ENCODE_IMPL_H

#define ENCODING_BUFFER_SIZE (size_t)256


struct EncodingTable {
    unsigned char name[256];
    unsigned char encoding[256][ENCODING_BUFFER_SIZE];
};


struct EncodingBuffer {
    size_t iterator;
    unsigned char buffer[ENCODING_BUFFER_SIZE];
    struct EncodingTable* table;
};


void EncodingBuffer_ctor(struct EncodingBuffer* pthis,
                         struct EncodingTable* ptable) {
    pthis->table = ptable;
    pthis->iterator = ENCODING_BUFFER_SIZE-1;
    pthis->buffer[ENCODING_BUFFER_SIZE-1] = '\0';
}

void printEncodingBuffer(struct EncodingBuffer* pthis) {
    printf("ENCODING: %s\n", &pthis->buffer[pthis->iterator]);
}


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

void traverseTreeAndEncode(struct HuffmanTreeNode* const node,
                           struct EncodingBuffer* const  buffer) {

    struct EncodingBuffer* const buffer_const = buffer;
    struct HuffmanTreeNode* const node_const = node;
 

    if (node_const->left != NULL) {
        buffer->iterator--;
        buffer->buffer[buffer->iterator] = '0';
        traverseTreeAndEncode(node_const->left, buffer_const); 
    }
    
    if (node_const->right != NULL) {
        buffer->iterator--;
        buffer->buffer[buffer->iterator] = '1';
        traverseTreeAndEncode(node_const->right, buffer_const);
    }
    
    if (node_const->code == 0) {
        strcpy(buffer->table->encoding[(unsigned char)node_const->name], &buffer->buffer[buffer->iterator]);
        reverseString(
            buffer->table->encoding[(unsigned char)node_const->name],
            strlen(buffer->table->encoding[(unsigned char)node_const->name]));
        buffer->table->name[(unsigned char)node_const->name] = node_const->name;
        printf("Encoding: %3hhu : %s\n",
                buffer->table->name[(unsigned char)node_const->name],
                buffer->table->encoding[(unsigned char)node_const->name]);
    } 
      
    buffer->iterator++;
}


#endif /* ENCODE_IMPL_H */

