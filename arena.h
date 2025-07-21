#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

typedef struct arena {
    size_t cap;
    size_t siz;
    uint8_t* dat;
    struct arena* N;
} arena;

struct arena* head = NULL;
struct arena* arena_init(size_t cap);
void* arena_alloc(arena* arena,size_t siz);
void* arena_reset(arena* arena);
void* arena_free(arena* arena);