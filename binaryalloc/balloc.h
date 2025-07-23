#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/** 
 * Data - This struct holds the info for the 
 * Binary Tree structure that would control
 * The data flow in the Allocator after being
 * Assigned some location based on filters ..
*/
typedef struct {
    size_t root;
    size_t left;
    size_t right;
}Data;

/**
 * BTAllocator - This struct holds the wrapper
 * For the Data struct and an unsigned data type
 * To clarify when a memory location is free
 */
typedef struct {
    Data* data;
    uint8_t free;
} BTAllocator;

