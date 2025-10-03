#include <stdio.h>
#include <stdlib.h>

typedef struct mab {
    int offset;
    int size;
    int allocated;
    struct mab *next;
    struct mab *prev;
} Mab, *MabPtr;

// Check if block has enough space
MabPtr memChk(MabPtr m, int size) {
    while (m != NULL) {
        if (!m->allocated && m->size >= size) return m;
        m = m->next;
    }
    return NULL;
}

// Split block
MabPtr memSplit(MabPtr m, int size) {
    if (m->size > size) {
        MabPtr newBlock = (MabPtr)malloc(sizeof(Mab));
        newBlock->offset = m->offset + size;
        newBlock->size = m->size - size;
        newBlock->allocated = 0;
        newBlock->next = m->next;
        newBlock->prev = m;
        if (m->next) m->next->prev = newBlock;
        m->next = newBlock;
        m->size = size;
    }
    return m;
}

// Allocate
MabPtr memAlloc(MabPtr m, int size) {
    MabPtr block = memChk(m, size);
    if (!block) return NULL;
    memSplit(block, size);
    block->allocated = 1;
    return block;
}

// Free
MabPtr memFree(MabPtr m) {
    m->allocated = 0;
    return m;
}

// Merge adjacent free blocks
MabPtr memMerge(MabPtr m) {
    while (m && m->next && !m->allocated && !m->next->allocated) {
        m->size += m->next->size;
        MabPtr temp = m->next;
        m->next = temp->next;
        if (temp->next) temp->next->prev = m;
        free(temp);
    }
    return m;
}

int main() {
    // Create one large block of memory
    MabPtr memory = (MabPtr)malloc(sizeof(Mab));
    memory->offset = 0;
    memory->size = 1000;
    memory->allocated = 0;
    memory->next = memory->prev = NULL;

    MabPtr a = memAlloc(memory, 200);
    MabPtr b = memAlloc(memory, 300);

    printf("Allocated blocks: A(offset=%d,size=%d), B(offset=%d,size=%d)\n",
           a->offset, a->size, b->offset, b->size);

    memFree(a);
    memMerge(memory);

    return 0;
}
