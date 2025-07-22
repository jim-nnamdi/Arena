#include "arena.h"

int allocate(size_t capacity);
int main(void){
    int chunk = allocate(5);
    return chunk;
}
