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
struct Arena* arena_init(size_t cap);
void* arena_alloc(Arena* arena,size_t siz);
void* arena_reset(Arena* arena);
void* arena_free(Arena* arena);