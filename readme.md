#  🔺 Arena Allocator in C

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Build: Manual](https://img.shields.io/badge/build-manual-blue)]()
[![Made with C](https://img.shields.io/badge/Made%20with-C-blue.svg)]()

A minimal, educational **arena memory allocator** implemented in C, using a **linked-list-based structure** to support arbitrary allocations within fixed-size memory blocks. This project is great for learning custom memory management strategies, optimizing memory reuse, and understanding data locality.

## What is an Arena Allocator?

An **arena allocator** (also called a **region allocator**) is a fast memory allocation strategy that allocates memory from large pre-allocated blocks. It's especially useful when:

- You need fast and frequent allocations.
- You don't need to free individual allocations—just reset or free the entire arena.
- You're managing memory manually (e.g., in embedded systems, game engines, or custom interpreters).

This implementation supports:

- Chunked allocations from fixed-capacity blocks  
- Seamless allocation across linked arena nodes  
- Efficient mass reset and freeing  
- Simple debug print view  


## File Structure

```bash
.
├── arena.c        # Arena allocator core logic
├── arena.h        # Arena struct and function declarations
├── main.c         # Example usage and testing
```


## Features

- **Linked Arena Nodes**: Automatically grows when capacity is exceeded.
- **Head / Tail / Arbitrary Allocation**: Choose where to allocate.
- **Reset and Free**: Zero-cost reset, and recursive free.
- **Debugging Support**: Print arena layout with `arena_print()`.


## Struct Overview

```c
typedef struct arena {
  size_t cap;         // Capacity of arena block
  size_t siz;         // Current usage
  size_t *dat;        // Pointer to memory data
  struct arena *N;    // Next arena node
} arena;
```


## 🔧 Usage

### Initialize an arena

```c
arena *head = arena_init(5);
```

### Allocate memory

```c
size_t *a = (size_t *)arena_alloc(head, 1);
*a = 100;
```

### Reuse or reset

```c
arena_reset(head); // Reuse the same arena
```

### Free all memory

```c
arena_free_all(head);
```

## Example Output

```
Before printing ... 

 Arena Block(0) 100200000
```

## Sample: `main.c`

```c
int main(void) {
  size_t cap = 5;
  head = arena_init(cap);
  if (!head) {
    printf("'failed to initialise arena'\n");
    return (1);
  }

  size_t *ptr_one = (size_t *)arena_alloc(head, 1);
  *ptr_one = 100;
  size_t *ptr_two = (size_t *)arena_alloc(head, 1);
  *ptr_two = 200;

  printf("Before printing ... \n");
  arena_print(head);

  arena_free_all(head);
  head = NULL;
  return 0;
}
```


## 🔍 Advanced Functions

### `arena_alloc_head_2(arena*, size_t)`
Recursively allocates from the head arena, expanding if full.

### `arena_alloc_last(size_t size)`
Appends a new arena block at the end of the chain.

### `arena_alloc_arbitrary(size_t size, size_t index)`
Allocates at a specific index in the arena chain if available.

### `arena_delete_node(arena **head, arena *target)`
Deletes a specific arena node from the linked structure.


## 🧪 Debugging with `arena_print`

```c
void arena_print(struct arena *arena) {
  int arena_block_count = 0;
  struct arena *temp = arena;
  while (temp != NULL) {
    printf("\n Arena Block(%d) ", arena_block_count++);
    for (size_t i = 0; i < temp->cap; i++)
      printf("%zu", temp->dat[i]);
    printf("\n");
    temp = temp->N;
  }
}
```

## 🧰 Included Utilities

```c
void *arena_reset(arena *arena);
void *arena_free(arena *arena);
void *arena_free_all(arena *arena);
void *arena_alloc_head_2(struct arena *arena, size_t size);
void *arena_alloc_last(size_t sz);
void *arena_alloc_arbitrary(size_t sz, size_t idx);
void *arena_delete_node(struct arena **head, struct arena *target);
```

## 📚 Learn More

This arena allocator is intentionally simple and modular. It's great for learning how manual memory management works—especially without a garbage collector. Extend it to build:

- Memory pools
- Fast linear allocators
- Custom interpreters or language runtimes
- Low-latency systems with predictable memory usage


## 🤝 Contributing

Pull requests welcome! For major changes, please open an issue first to discuss what you would like to change or improve.

## 📜 License

MIT License. Feel free to use this for learning, teaching, or real-world systems.


## 👨‍💻 Author

Made with 💡 and a touch of C by **Jim**.
