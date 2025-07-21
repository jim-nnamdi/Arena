#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

/*
    let's say i have a MDA
    static int size = 20;
    ssize_t * dat
    for(ssize_t o = 0; o < sz; ++o)
        dat[o] = 0;
    int multi_dim_arr[size];
    for(size_t i = 0; i < size; ++i)
        multi_dim_arr[i] = 0;
 */
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