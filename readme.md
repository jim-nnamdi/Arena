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