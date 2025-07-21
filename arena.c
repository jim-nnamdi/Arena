#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

typedef struct Arena {
    size_t cap;
    size_t siz;
    uint8_t* dat;
    struct Arena* N;
} Arena;

struct Arena* head = NULL;
struct Arena* arena_init(size_t cap) {
    struct Arena* temp = malloc(sizeof(size_t) * cap);
    temp->cap = cap;
    temp->siz = 0;
    temp->dat = sizeof(size_t) * cap;
    temp->N = NULL;
    return temp;
}

void* arena_alloc(Arena* arena,size_t siz) {
    if((arena->siz + siz) <= arena->cap){
        uint8_t* data = &arena->dat[arena->siz];
        arena->siz += siz;
        return data;
    }
    Arena* N = arena_init(arena->cap);
    arena->N = N;
}

void* arena_reset(Arena* arena) {
    arena->siz = 0;
}

void* arena_free(Arena* arena) {
    arena->siz = 0;
    arena->cap = 0;
    free(arena->dat);
}

int main(void) {}