#pragma once
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  size_t *dat;
  struct arena *N;
} arena;

/* NodeLink would hold other external declared */
/* user initialised data structures as data source */
/* then implement the core Logic using LL Formats */
typedef struct {
  struct arena *link_arena;
  struct NodeLink *next_link;
} NodeLink;

/* generic implementation Logic */
extern struct arena *head;
struct arena *arena_init(size_t cap);
void *arena_alloc(arena *arena, size_t siz);
void *arena_reset(arena *arena);
void *arena_free(arena *arena);

/* arena arch based on Linked Lists */
void *arena_alloc_last(size_t sz);
void *arena_free_all(arena *arena);
void arena_print(struct arena *arena);
void *arena_alloc_head_2(struct arena *arena, size_t size);
void *arena_alloc_arbitrary(size_t sz, size_t idx);
void *arena_delete_node(struct arena **head, struct arena *target);
