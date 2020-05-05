/*
This file is part of the SCARL toolkit.

SCARL is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

SCARL is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with SCARL.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef ARCLCLI_MEMORY_H_INCLUDED
#define ARCLCLI_MEMORY_H_INCLUDED

#include <stdint.h>

struct arcl_memory_block;

struct arcl_memory_block {
	unsigned int index; // identifier
	unsigned int size;
	struct arcl_memory_block *next;
};

// runtime memory heap
// this is so we have 
// strict control over the 
// number of bytes used in memory
struct arcl_heap {
	uint8_t *raw;
	unsigned bytes;
	// naive implementation for now 
	struct arcl_memory_block *allocated_blocks;
};

// runtime stack
struct arcl_stack {
	uint8_t *raw;
	unsigned bytes;
	unsigned frame_pointer;
};

struct arcl_heap *allocate_arcl_heap(unsigned bytes);
void free_arcl_heap(struct arcl_heap *heap);
struct arcl_stack *create_arcl_stack(unsigned bytes);
void destroy_arcl_stack(struct arcl_stack *stack);
struct arcl_memory_block *allocate_block(struct arcl_heap *heap, unsigned size);
void free_block(struct arcl_heap *heap, struct arcl_memory_block *block);
void write_char_to_block(struct arcl_heap *heap, struct arcl_memory_block *in_block, unsigned int offset, char char_value);
void write_arcl_int_to_block(struct arcl_heap *heap, struct arcl_memory_block *in_block, unsigned int offset, int int_value);
void write_arcl_byte_to_block(struct arcl_heap *heap, struct arcl_memory_block *in_block, unsigned int offset, int byte_value);
char read_char_from_block(struct arcl_heap *heap, struct arcl_memory_block *from_block, unsigned int offset);
int read_arcl_int_from_block(struct arcl_heap *heap, struct arcl_memory_block *from_block, unsigned int offset);
int read_arcl_byte_from_block(struct arcl_heap *heap, struct arcl_memory_block *from_block, unsigned int offset);
void push_stack_frame(struct arcl_stack *stack, unsigned int offset);
void pop_stack_frame(struct arcl_stack *stack);
void write_char_to_stack(struct arcl_stack *stack, unsigned int offset, char char_value);
void write_arcl_int_to_stack(struct arcl_stack *stack, unsigned int offset, int int_value);
void write_arcl_byte_to_stack(struct arcl_stack *stack, unsigned int offset, int byte_value);
char read_char_from_stack(struct arcl_stack *stack, unsigned int offset);
int read_arcl_int_from_stack(struct arcl_stack *stack, unsigned int offset);
int read_arcl_byte_from_stack(struct arcl_stack *stack, unsigned int offset);

//debug functions
void print_heap(struct arcl_heap *heap);
void print_memory_block(struct arcl_heap *heap, struct arcl_memory_block *block);

#endif // ARCLCLI_MEMORY_H_INCLUDED