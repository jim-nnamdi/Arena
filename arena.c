#include "arena.h"

struct arena *head = NULL;

/** 
 * arena_init - Initializes a new arena block with a given capacity.
 * Allocates memory for the arena structure and its data array.
 * Sets initial size to 0 and next pointer to NULL.
 * Returns pointer to the newly allocated arena on success.
 * Returns NULL if memory allocation fails at any point.
 */
struct arena *arena_init(size_t cap) {
  struct arena *temp = malloc(sizeof(struct arena));
  if (!temp)
    return NULL;

  temp->cap = cap;
  temp->siz = 0;

  temp->dat = malloc(sizeof(size_t) * cap);
  if (!temp->dat) {
    free(temp);
    return NULL;
  }
  memset(temp->dat, 0, sizeof(size_t) * cap);
  temp->N = NULL;
  return temp;
}

/** 
 * arena_init_2 - Same as arena_init, but uses different variable naming.
 * Demonstrates alternative naming for readability or stylistic preference.
 * Still allocates memory for the structure and zeroes out the data.
 * Used when creating a new arena manually from client code.
 * Returns pointer to a valid arena or NULL on failure.
 */
struct arena *arena_init_2(size_t cap) {
  struct arena *temp_arena_obj = malloc(sizeof(struct arena));
  if (!temp_arena_obj)
    return NULL;

  temp_arena_obj->cap = cap;
  temp_arena_obj->siz = 0;

  temp_arena_obj->dat = malloc(sizeof(size_t) * cap);
  if (!temp_arena_obj->dat) {
    free(temp_arena_obj);
    return NULL;
  }
  memset(temp_arena_obj->dat, 0, sizeof(size_t) * cap);
  temp_arena_obj->N = NULL;
  return temp_arena_obj;
}

/** 
 * arena_alloc_head_2 - Allocates memory from head arena or next arena recursively.
 * Checks if there's space in current arena block for allocation.
 * If not, initializes a new arena block and links it as next.
 * This supports chained arena allocations.
 * Returns a pointer to allocated memory.
 */
void *arena_alloc_head_2(struct arena *arena, size_t size) {
  if ((arena->siz + size) <= arena->cap) {
    void *data = &arena->dat[arena->siz];
    arena->siz += size;
    return data;
  } else {
    arena->N = arena_init(size);
    return arena_alloc_head_2(arena->N, size);
  }
}

/** 
 * arena_alloc_arbitrary - Allocates memory at a specific index.
 * Iterates through the linked arenas to find available slot at given index.
 * Marks the index with the given size and returns a pointer to it.
 * Does not allocate new arenas; only searches existing ones.
 * Returns NULL if index is already used or not found.
 */
void *arena_alloc_arbitrary(size_t sz, size_t idx) {
  struct arena *temp = head;
  while (temp != NULL) {
    if (temp->dat[idx] == 0) {
      temp->dat[idx] = sz;
      return &temp->dat[idx];
    }
    temp = temp->N;
  }
  return NULL;
}

/** 
 * arena_alloc_last - Appends a new arena block at the end of the chain.
 * Creates a new arena node with specified capacity.
 * If this is the first node, it sets the global head pointer.
 * Otherwise, traverses the list and appends at the tail.
 * Returns pointer to the new last node.
 */
void *arena_alloc_last(size_t sz) {
  struct arena *Node = malloc(sizeof(struct arena));
  Node->siz = 0;
  Node->dat = malloc(sizeof(size_t) * sz);
  if (!Node->dat) {
    free(Node);
    return NULL;
  }
  Node->cap = sz;
  Node->N = NULL;
  if (head == NULL)
    head = Node;
  else {
    struct arena *temp_node = head;
    while (temp_node->N != NULL) {
      temp_node = temp_node->N;
    }
    temp_node->N = Node;
    return temp_node->N;
  }
  return NULL;
}

/** 
 * arena_delete_node - Removes a specific node from the arena chain.
 * Takes a pointer to the head and the target node to delete.
 * If target is head, updates head and frees memory.
 * Otherwise, finds the target and unlinks it from the list.
 * Frees the node’s memory and data array.
 */
void *arena_delete_node(struct arena **head, struct arena *target) {
  if (!head || !(*head) || !target)
    return NULL;

  if (*head == target) {
    *head = (*head)->N;
    free(target->dat);
    free(target);
  }

  struct arena *current = *head;
  while (current->N != NULL) {
    if (current->N == target) {
      struct arena *temp = current->N;
      current->N = current->N->N;
      free(temp->dat);
      free(temp);
      break;
    } else
      current = current->N;
  }
  return NULL;
}

/** 
 * arena_alloc - Allocates memory within the current arena if there's space.
 * If full, it creates and links a new arena with same capacity.
 * This enables seamless continuous allocation across multiple arenas.
 * Returns pointer to the allocated memory or NULL on failure.
 * Uses recursion to traverse arena list.
 */
void *arena_alloc(arena *arena, size_t siz) {
  if ((arena->siz + siz) <= arena->cap) {
    void *data = &arena->dat[arena->siz];
    arena->siz += siz;
    return data;
  }

  arena->N = arena_init(arena->cap);
  return arena_alloc(arena->N, siz);
}

/** 
 * arena_reset - Resets the usage size of an arena block to 0.
 * Does not free memory, only marks it reusable.
 * Useful for reusing arena blocks without reallocating memory.
 * Does not affect next arenas in the chain.
 * Returns the same arena pointer.
 */
void *arena_reset(arena *arena) {
  arena->siz = 0;
  return arena;
}

/** 
 * arena_free - Frees the memory of a single arena block.
 * Releases the data array and the arena structure itself.
 * Does not affect linked arenas via the next pointer.
 * Used when deleting a standalone arena.
 * Returns NULL after freeing.
 */
void *arena_free(arena *arena) {
  arena->siz = 0;
  arena->cap = 0;
  free(arena->dat);
  free(arena);
  return NULL;
}

/** 
 * arena_free_all - Frees an entire chain of arena blocks.
 * Iterates through all arenas using the next pointer.
 * Frees each data array and arena structure.
 * Cleans up memory to avoid leaks after bulk allocation.
 * Returns NULL after freeing the entire chain.
 */
void *arena_free_all(arena *arena) {
  while (arena != NULL) {
    struct arena *next_arena = arena->N;
    free(arena->dat);
    free(arena);
    arena = next_arena;
  }
  return NULL;
}

/** 
 * arena_print - Displays content of all arena blocks.
 * Useful for debugging and inspection of internal arena state.
 * Iterates through each arena in the list.
 * Prints each block's index and its data values.
 * Does not modify the arena.
 */
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

/** 
 * allocate - Example test function to allocate and use an arena.
 * Initializes a global arena head with given capacity.
 * Allocates two size_t elements and assigns values.
 * Prints the arena contents and frees all memory afterward.
 * Returns 0 on success, 1 on failure.
 */
int allocate(size_t capacity) {
  head = arena_init(capacity);
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
