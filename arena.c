#include "arena.h"

struct arena* arena_init(size_t cap) {
    struct arena* temp = malloc(sizeof(struct arena));
    if (!temp) return NULL;

    temp->cap = cap;
    temp->siz = 0;

    temp->dat = malloc(sizeof(size_t) * cap);
    if(!temp->dat){
        free(temp);
        return NULL;
    }
    memset(temp->dat, 0, sizeof(size_t) * cap);
    temp->N = NULL;
    return temp;
}

struct arena* arena_init_2(size_t cap) {
    struct arena* temp_arena_obj = malloc(sizeof(struct arena));
    if (!temp_arena_obj) return NULL;

    temp_arena_obj->cap = cap;
    temp_arena_obj->siz = 0;

    temp_arena_obj->dat = malloc(sizeof(size_t) * cap);
    if(!temp_arena_obj->dat) {
        free(temp_arena_obj);
        return NULL;
    }
    memset(temp_arena_obj->dat, 0, sizeof(size_t) * cap);
    temp_arena_obj->N = NULL;
    return temp_arena_obj;
}

void* arena_alloc_head_2(size_t cap){
    struct arena* temp = malloc(sizeof(struct arena));
    temp->siz = 0;
    temp->cap = cap;

    temp->dat = malloc(sizeof(size_t) * cap);
    if(!temp->dat) {
        free(temp);
        return;
    }

    temp->N = head;
    head =  temp;
}

void* arena_alloc_arbitrary(size_t sz, size_t idx) {
    struct arena* temp = head;
    while(temp != NULL) {
        if(temp->dat[idx] == 0 ){
            temp->dat[idx] = sz;
            return &temp->dat[idx];
        }
        temp = temp->N;
    }
    return NULL;
}

void* arena_alloc_last(size_t sz){
    struct arena* Node = malloc(sizeof(struct arena));
    Node->siz = 0;
    Node->dat = malloc(sizeof(size_t) * sz);
    if(!Node->dat) {
        free(Node);
        return;
    }
    Node->cap = sz;
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

/*
    for normal Linked lists the second parameter i'll pass
    would be the index of the element am trying to remove 
    on the List at a particular memory Location from head.
    ** points to a double memory arena Location. in this case
    idx shows that the index exists and if there's data there
    remove the data and index all together ...
*/
void* arena_delete_node(struct arena **head, size_t idx) {
    struct arena* temp_arena_node;
    if((*head)->dat[idx] != 0){
        temp_arena_node = *head;
        *head = (*head)->N;
        free(temp_arena_node);
    } else {
        struct arena* current = *head;
        while(current->N != NULL){
            if(current->N->dat[idx] != 0){
                temp_arena_node = current->N;
                current->N = current->N->N;
                free(temp_arena_node);
                break;
            } else 
                current = current->N;
        }
    }
}

void* arena_alloc(arena* arena,size_t siz) {
    if((arena->siz + siz) <= arena->cap){
        void* data = &arena->dat[arena->siz];
        arena->siz += siz;
        arena->dat = malloc(sizeof(size_t) * arena->cap);
        arena->N = NULL;
        return data;
    }
    struct arena* N = arena_init(arena->cap);
    return N;
}

void* arena_reset(arena* arena) {
    arena->siz = 0;
}

void* arena_free(arena* arena) {
    arena->siz = 0;
    arena->cap = 0;
    free(arena->dat);
    free(arena);
}

void* arena_free_all(arena* arena) {
    while(arena != NULL) {
        struct arena* next_arena = arena->N;
        free(arena->dat);
        free(arena);
        arena = next_arena;
    }
}

int main(void) {}