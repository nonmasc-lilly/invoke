#include "malloc.h"

void *global_base = NULL;

void *sbrk(long size) {
    long old = SYS_BRK(-1);
    void *new = SYS_BRK(old + size);
    if(new != old+size) return (void*)-1;
    return old;
}

struct block_meta *get_free_block(struct block_meta **last, long size) {
    struct block_meta *cur = global_base;
    while(cur && !(cur->free && cur->size >= size)) {
        *last = cur;
        cur = cur->next;
    }
    return cur;
}

struct block_meta *req_block(struct block_meta *last, long size) {
    struct block_meta *block = sbrk(0);
    void *req = sbrk(size + sizeof(struct block_meta));
    if(req == (void*)-1) return NULL;
    if(last) last->next = block;
    block->size = size;
    block->next = NULL;
    block->free = 0;
    return block;
}

void *malloc(long size) {
    struct block_meta *block;
    if(size < 1) return NULL;
    if(!global_base) {
        block = req_block(NULL, size);
        if(!block) return NULL;
        global_base = block;
    } else {
        struct block_meta *last = global_base;
        block = get_free_block(&last, size);
        if(!block) {
            block = req_block(last, size);
            if(!block) return NULL;
        } else block->free = 0;
    }
    return block + 1;
}

struct block_meta *get_block(void *ptr) {
    return (struct block_meta*)ptr - 1;
}

void free(void *ptr) {
    if(!ptr) return;
    struct block_meta *block_ptr = get_block(ptr);
    if(block_ptr->free != 0) return;
    block_ptr->free = 1;
}

void *realloc(void *ptr, long size) {
    if(!ptr) return malloc(size);
    struct block_meta* block_ptr = get_block(ptr);
    if(block_ptr->size >= size) return ptr;
    void *new_ptr;
    new_ptr = malloc(size);
    if(!new_ptr) return NULL;
    memcpy(new_ptr, ptr, block_ptr->size);
    free(ptr);
    return new_ptr;
}

void memcpy(void *dest, const void *src, long size) {
    while(size--) *(char*)(dest++) = *(char*)(src++);
}









