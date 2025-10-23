#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mab {
    int offset, size, allocated;
    struct mab *next, *prev;
};
typedef struct mab Mab;
typedef Mab* MabPtr;

MabPtr lastAlloc = NULL;

MabPtr memChk(MabPtr m, int size, const char *policy) {
    MabPtr best = NULL, worst = NULL;

    if (strcmp(policy, "Next") == 0 && lastAlloc != NULL)
        m = lastAlloc;  // start from last allocated block

    MabPtr start = m; // for Next Fit loop
    int wrapped = 0;

    while (m != NULL) {
        if (!m->allocated && m->size >= size) {
            if (strcmp(policy, "First") == 0) {
                return m;
            } 
            else if (strcmp(policy, "Best") == 0) {
                if (best == NULL || m->size < best->size)
                    best = m;
            } 
            else if (strcmp(policy, "Worst") == 0) {
                if (worst == NULL || m->size > worst->size)
                    worst = m;
            } 
            else if (strcmp(policy, "Next") == 0) {
                lastAlloc = m;
                return m;
            }
        }
        m = m->next;

        // For Next Fit wrap-around
        if (strcmp(policy, "Next") == 0 && m == NULL && !wrapped) {
            m = start;  // wrap to beginning
            wrapped = 1;
        } else if (strcmp(policy, "Next") == 0 && wrapped && m == start)
            break;
    }

    if (strcmp(policy, "Best") == 0) return best;
    if (strcmp(policy, "Worst") == 0) return worst;
    return NULL;
}

// Allocate memory
MabPtr memAlloc(MabPtr m, int size, const char *policy) {
    MabPtr blk = memChk(m, size, policy);
    if (blk == NULL) {
        printf("No suitable block found for size %d (%s Fit)\n", size, policy);
        return NULL;
    }
    if (blk->size > size)
        blk = memSplit(blk, size);
    blk->allocated = 1;
    lastAlloc = blk;
    printf("Allocated %d bytes at offset %d using %s Fit\n", blk->size, blk->offset, policy);
    return blk;
}

// Free memory
MabPtr memFree(MabPtr m) {
    if (!m->allocated) {
        printf("Block already free.\n");
        return m;
    }
    printf("Freeing block at offset %d (size %d)\n", m->offset, m->size);
    m->allocated = 0;
    if (m->prev && !m->prev->allocated)
        m = memMerge(m->prev);
    if (m->next && !m->next->allocated)
        m = memMerge(m);
    return m;
}

// Merge adjacent free blocks
MabPtr memMerge(MabPtr m) {
    if (m->next && !m->next->allocated) {
        MabPtr temp = m->next;
        m->size += temp->size;
        m->next = temp->next;
        if (m->next)
            m->next->prev = m;
        free(temp);
    }
    return m;
}

// Split block
MabPtr memSplit(MabPtr m, int size) {
    if (size >= m->size)
        return m;

    MabPtr newBlk = (MabPtr)malloc(sizeof(Mab));
    newBlk->offset = m->offset + size;
    newBlk->size = m->size - size;
    newBlk->allocated = 0;
    newBlk->next = m->next;
    newBlk->prev = m;

    if (m->next)
        m->next->prev = newBlk;

    m->next = newBlk;
    m->size = size;
    return m;
}
void show(MabPtr m){
    printf("\nOffset\tSize\tAlloc\n");
    while(m){ printf("%d\t%d\t%s\n",m->offset,m->size,m->allocated?"Yes":"No"); m=m->next; }
    puts("----------------");
}

int main(){
    MabPtr mem=malloc(sizeof(Mab));
    mem->offset=0; mem->size=1000; mem->allocated=0;
    mem->next=mem->prev=NULL;
    show(mem);

    MabPtr b1=memAlloc(mem,200,"Best");
    MabPtr b2=memAlloc(mem,300,"First");
    MabPtr b3=memAlloc(mem,100,"Worst");
    show(mem);

    memFree(b2);
    show(mem);

    MabPtr b4=memAlloc(mem,250,"Next");
    show(mem);

    memFree(b1); memFree(b3); memFree(b4);
    show(mem);
    return 0;
}



// #include <stdio.h>
// #include <stdlib.h>

// typedef struct mab {
//     int offset;
//     int size;
//     int allocated;
//     struct mab *next;
//     struct mab *prev;
// } Mab, *MabPtr;

// // Check if block has enough space
// MabPtr memChk(MabPtr m, int size) {
//     while (m != NULL) {
//         if (!m->allocated && m->size >= size) return m;
//         m = m->next;
//     }
//     return NULL;
// }

// // Split block
// MabPtr memSplit(MabPtr m, int size) {
//     if (m->size > size) {
//         MabPtr newBlock = (MabPtr)malloc(sizeof(Mab));
//         newBlock->offset = m->offset + size;
//         newBlock->size = m->size - size;
//         newBlock->allocated = 0;
//         newBlock->next = m->next;
//         newBlock->prev = m;
//         if (m->next) m->next->prev = newBlock;
//         m->next = newBlock;
//         m->size = size;
//     }
//     return m;
// }

// // Allocate
// MabPtr memAlloc(MabPtr m, int size) {
//     MabPtr block = memChk(m, size);
//     if (!block) return NULL;
//     memSplit(block, size);
//     block->allocated = 1;
//     return block;
// }

// // Free
// MabPtr memFree(MabPtr m) {
//     m->allocated = 0;
//     return m;
// }

// // Merge adjacent free blocks
// MabPtr memMerge(MabPtr m) {
//     while (m && m->next && !m->allocated && !m->next->allocated) {
//         m->size += m->next->size;
//         MabPtr temp = m->next;
//         m->next = temp->next;
//         if (temp->next) temp->next->prev = m;
//         free(temp);
//     }
//     return m;
// }

// int main() {
//     // Create one large block of memory
//     MabPtr memory = (MabPtr)malloc(sizeof(Mab));
//     memory->offset = 0;
//     memory->size = 1000;
//     memory->allocated = 0;
//     memory->next = memory->prev = NULL;

//     MabPtr a = memAlloc(memory, 200);
//     MabPtr b = memAlloc(memory, 300);

//     printf("Allocated blocks: A(offset=%d,size=%d), B(offset=%d,size=%d)\n",
//            a->offset, a->size, b->offset, b->size);

//     memFree(a);
//     memMerge(memory);

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mab {
    int offset, size, allocated;
    struct mab *next, *prev;
};
typedef struct mab Mab;
typedef Mab* MabPtr;

MabPtr lastAlloc = NULL;

MabPtr memMerge(MabPtr m){
    if(m->next && !m->next->allocated){
        MabPtr t = m->next;
        m->size += t->size;
        m->next = t->next;
        if(m->next) m->next->prev = m;
        free(t);
    }
    return m;
}
MabPtr memSplit(MabPtr m,int s){
    if(s>=m->size) return m;
    MabPtr n = malloc(sizeof(Mab));
    n->offset = m->offset + s;
    n->size = m->size - s;
    n->allocated = 0;
    n->next = m->next;
    n->prev = m;
    if(m->next) m->next->prev = n;
    m->next = n;
    m->size = s;
    return m;
}
MabPtr memChk(MabPtr m,int s,const char* p){
    MabPtr best=NULL,worst=NULL;
    if(!strcmp(p,"Next") && lastAlloc) m=lastAlloc;
    MabPtr start=m; int wrap=0;
    while(m){
        if(!m->allocated && m->size>=s){
            if(!strcmp(p,"First")) return m;
            if(!strcmp(p,"Best") && (!best||m->size<best->size)) best=m;
            if(!strcmp(p,"Worst") && (!worst||m->size>worst->size)) worst=m;
            if(!strcmp(p,"Next")) { lastAlloc=m; return m; }
        }
        m=m->next;
        if(!strcmp(p,"Next") && !m && !wrap){ m=start; wrap=1; }
        else if(!strcmp(p,"Next") && wrap && m==start) break;
    }
    if(!strcmp(p,"Best")) return best;
    if(!strcmp(p,"Worst")) return worst;
    return NULL;
}
MabPtr memAlloc(MabPtr m,int s,const char* p){
    MabPtr b=memChk(m,s,p);
    if(!b){ printf("No block for %d (%s)\n",s,p); return NULL; }
    if(b->size>s) b=memSplit(b,s);
    b->allocated=1; lastAlloc=b;
    printf("Allocated %d bytes at %d using %s Fit\n",b->size,b->offset,p);
    return b;
}
MabPtr memFree(MabPtr m){
    if(!m||!m->allocated) return m;
    printf("Freeing block %d (%d)\n",m->offset,m->size);
    m->allocated=0;
    if(m->prev && !m->prev->allocated) m=memMerge(m->prev);
    if(m->next && !m->next->allocated) m=memMerge(m);
    return m;
}
void show(MabPtr m){
    printf("\nOffset\tSize\tAlloc\n");
    while(m){ printf("%d\t%d\t%s\n",m->offset,m->size,m->allocated?"Yes":"No"); m=m->next; }
    puts("----------------");
}

int main(){
    MabPtr mem=malloc(sizeof(Mab));
    mem->offset=0; mem->size=1000; mem->allocated=0;
    mem->next=mem->prev=NULL;
    show(mem);

    MabPtr b1=memAlloc(mem,200,"Best");
    MabPtr b2=memAlloc(mem,300,"First");
    MabPtr b3=memAlloc(mem,100,"Worst");
    show(mem);

    memFree(b2);
    show(mem);

    MabPtr b4=memAlloc(mem,250,"Next");
    show(mem);

    memFree(b1); memFree(b3); memFree(b4);
    show(mem);
    return 0;
}

