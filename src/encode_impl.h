#ifndef ENCODE_IMPL_H
#define ENCODE_IMPL_H

#define ENCODING_BUFFER_SIZE (size_t)257


struct EncodingTable {
    int name[255];
    char encoding[255][ENCODING_BUFFER_SIZE];
};


struct EncodingBuffer {
    int iterator;
    char buffer[ENCODING_BUFFER_SIZE];
    struct EncodingTable* table;
};


void EncodingBuffer_ctor(struct EncodingBuffer* pthis,
                         struct EncodingTable* ptable) {
    pthis->table = ptable;
    pthis->iterator = ENCODING_BUFFER_SIZE-2;
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

void traverseTreeAndEncode(struct HuffmanTreeNode* node,
                           struct EncodingBuffer*  buffer) {


    if (node->left != NULL) {
        buffer->buffer[buffer->iterator] = '0';
        printEncodingBuffer(buffer);
        buffer->iterator--;
        traverseTreeAndEncode(node->left, buffer);
        
    }
    
    if (node->right != NULL) {
        buffer->buffer[buffer->iterator] = '1';
        printEncodingBuffer(buffer);
        buffer->iterator--;
        traverseTreeAndEncode(node->right, buffer);
    }


    buffer->iterator++;
    printf("buffer iterator: %d\n", buffer->iterator);

    strcpy(buffer->table->encoding[node->name], &buffer->buffer[buffer->iterator]);
    reverseString(
        buffer->table->encoding[node->name],
        ENCODING_BUFFER_SIZE-1-buffer->iterator);
    buffer->table->name[node->name] = node->name;
    printf("Encoding: %3d : %s\n",
            buffer->table->name[node->name],
            buffer->table->encoding[node->name]);
}


#endif /* ENCODE_IMPL_H */

