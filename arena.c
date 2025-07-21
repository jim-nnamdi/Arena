#include "arena.h"

struct arena* arena_init(size_t cap) {
    struct arena* temp = malloc(sizeof(size_t) * cap);
    temp->cap = cap;
    temp->siz = 0;
    temp->dat = sizeof(size_t) * cap;
    temp->N = NULL;
    return temp;
}

struct arena* arena_init_2(size_t cap) {
    struct arena* temp_arena_obj = malloc(sizeof(struct arena));
    temp_arena_obj->cap = cap;
    temp_arena_obj->siz = 0;
    temp_arena_obj->dat = NULL;
    temp_arena_obj->N = NULL;
    return temp_arena_obj;
}

void* arena_alloc_head_2(size_t sz){
    struct arena* temp = malloc(sizeof(struct arena));
    temp->dat = (sz * 2);
    temp->siz = sz;
    temp->cap = (sz * 2);
    temp->N = head;
    head =  temp;
}

void* arena_alloc_arbitrary(size_t sz, size_t idx) {
    struct arena* temp = head;
    while(temp != NULL && temp->N != NULL) {
        if (temp->dat[idx] != NULL)
            temp = temp->N;
    }
    temp->dat[idx] = NULL;
}

void* arena_alloc_last(size_t sz){
    struct arena* Node = malloc(sizeof(struct arena));
    Node->siz = sz;
    Node->dat = (sz * 2);
    Node->cap = (sz * 2);
    Node->N = NULL;
    if (head == NULL)
        head = Node;
    else {
        struct arena* temp_node = head;
        while(temp_node->N != NULL){
            temp_node = temp_node->N;
        }
        temp_node->N = Node;
    }
}

void* arena_alloc(arena* arena,size_t siz) {
    if((arena->siz + siz) <= arena->cap){
        uint8_t* data = &arena->dat[arena->siz];
        arena->siz += siz;
        return data;
    }
    struct arena* N = arena_init(arena->cap);
    arena->N = N;
}

void* arena_reset(arena* arena) {
    arena->siz = 0;
}

void* arena_free(arena* arena) {
    arena->siz = 0;
    arena->cap = 0;
    free(arena->dat);
}

int main(void) {}