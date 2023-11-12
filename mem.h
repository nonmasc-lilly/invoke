#include "invoke.h"
#ifndef MALLOC_H
#define MALLOC_H

struct block_meta {
    long size;
    struct block_meta *next;
    int free;
};

void memcpy(void *dest, const void *str, long size);
void *sbrk(long size);
struct block_meta *get_free_block(struct block_meta **last, long size);
struct block_meta *req_block(struct block_meta *last, long size);
struct block_meta *get_block(void *ptr);
void *malloc(long size);
void free(void *ptr);
void *realloc(void *ptr, long size);

#endif
