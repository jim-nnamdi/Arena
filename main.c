#include "arena.h"

int allocate(void);
int main(void){
    int chunk = allocate();
    return chunk;
}
