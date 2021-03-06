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
public:
	unsigned int index; // identifier
	unsigned int size;
	unsigned block_id; //identifier for VM user to interface
	struct arcl_memory_block *next;
	
	arcl_memory_block();
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

class block_id_pool {
public:
	block_id_pool() = default;
	~block_id_pool();
	void initialize_memory_block_ids();
	unsigned get_available_block_id();
	void free_block_id(unsigned id);
private:
	int *memory_id_pool;
};

struct arcl_heap *allocate_arcl_heap(unsigned bytes);
void free_arcl_heap(struct arcl_heap *heap);
struct arcl_stack *create_arcl_stack(unsigned bytes);
void destroy_arcl_stack(struct arcl_stack *stack);
struct arcl_memory_block *allocate_block(struct arcl_heap *heap, unsigned size, block_id_pool &block_pool);
struct arcl_memory_block *find_block_by_id(struct arcl_heap *heap, unsigned id);
unsigned get_available_block_id();
void initialize_memory_block_ids();
void free_block(struct arcl_heap *heap, struct arcl_memory_block *block, block_id_pool &bi_pool);
void write_char_to_block(struct arcl_heap *heap, struct arcl_memory_block *in_block, unsigned int offset, char char_value);
void write_arcl_int_to_block(struct arcl_heap *heap, struct arcl_memory_block *in_block, unsigned int offset, int int_value);
void write_arcl_byte_to_block(struct arcl_heap *heap, struct arcl_memory_block *in_block, unsigned int offset, int byte_value);
char read_char_from_block(struct arcl_heap *heap, struct arcl_memory_block *from_block, unsigned int offset);
int read_arcl_int_from_block(struct arcl_heap *heap, struct arcl_memory_block *from_block, unsigned int offset);
int read_arcl_byte_from_block(struct arcl_heap *heap, struct arcl_memory_block *from_block, unsigned int offset);
void push_stack_frame(struct arcl_stack *stack, unsigned int offset);
void pop_stack_frame(struct arcl_stack *stack, unsigned int offset);
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