#include "arena.h"

struct Arena* arena_init(size_t cap) {
    struct Arena* temp = malloc(sizeof(size_t) * cap);
    temp->cap = cap;
    temp->siz = 0;
    temp->dat = sizeof(size_t) * cap;
    temp->N = NULL;
    return temp;
}

struct Arena* arena_init_2(size_t cap) {
    struct Arena* temp_arena_obj = malloc(sizeof(struct Arena));
    temp_arena_obj->cap = cap;
    temp_arena_obj->siz = 0;
    temp_arena_obj->dat = NULL;
    temp_arena_obj->N = NULL;
    return temp_arena_obj;
}

void* arena_alloc_head_2(size_t sz){
    if (head != NULL){
        if (head->siz + sz <= head->cap){
            struct Arena* temp_arena = arena_init_2(head->cap);
            temp_arena->siz = sz;
            temp_arena->cap = sz * 2;
            temp_arena->dat = NULL;
            temp_arena->N = head; 
            head = temp_arena;
        }
    }
    struct Arena* temp_arena = arena_init_2(sz * 2);
    temp_arena->siz = sz;
    temp_arena->cap = sz * 2;
    temp_arena->dat = NULL;
    temp_arena->N = head;
    head = temp_arena;
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