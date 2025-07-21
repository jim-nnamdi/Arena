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

void* arena_alloc(size_t siz) {
    struct Arena* temp = head;
    while (temp->N != NULL) {
        if((temp->siz + siz) <= temp->cap) {
            temp->siz += siz;
            void* data = &temp->dat[temp->siz];
            return data;
        }
        Arena* next = arena_init(temp->cap);
        temp->N = next;
    }
}

int main(void) {}