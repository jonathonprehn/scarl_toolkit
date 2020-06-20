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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "arclmemory.h"

struct arcl_heap *allocate_arcl_heap(unsigned bytes) {
	struct arcl_heap *heap = (struct arcl_heap*)malloc(sizeof(struct arcl_heap));
	heap->bytes = bytes;
	heap->allocated_blocks = NULL;
	heap->raw = (uint8_t*)malloc(bytes*sizeof(uint8_t)); //relying on C's heap memory management for this 
	for (unsigned i = 0; i < bytes; i++) {
		heap->raw[i] = '0';
	}
	return heap; 
}

void free_arcl_heap(struct arcl_heap *heap) {
	//free all memory blocks 
	//all memory blocks do, however, have space
	//inside of the heap (writing your own memory manager 
	//   would be a good learning experience)
	struct arcl_memory_block *blk_ptr = heap->allocated_blocks;
	while(blk_ptr != NULL) {
		struct arcl_memory_block *deleting_block = blk_ptr;
		blk_ptr = blk_ptr->next;
		free(deleting_block);
	}
	free(heap->raw);
	free(heap);
}

struct arcl_stack *create_arcl_stack(unsigned bytes) {
	struct arcl_stack *stk = (struct arcl_stack*)malloc(sizeof(struct arcl_stack));
	stk->bytes = bytes;
	stk->frame_pointer = bytes-1; // grow towards 0 like most guides on stack programming have it
	stk->raw = (uint8_t*)malloc(bytes);
	return stk;
}

void destroy_arcl_stack(struct arcl_stack *stack) {
	free(stack->raw);
	free(stack);
}

struct arcl_memory_block *allocate_block(struct arcl_heap *heap, unsigned size) {
	//TODO: make it able to be more dynamic
	//the memory block list should be sorted in ascending offset order
	//so that this can efficiently find empty space 
	
	//make the template object
	struct arcl_memory_block *allocating = (struct arcl_memory_block*)malloc(sizeof(struct arcl_memory_block));
	allocating->index = 0; // unknown
	allocating->size = size;
	allocating->block_id = get_available_block_id();
	allocating->next = NULL;
	
	struct arcl_memory_block *cur = heap->allocated_blocks;
	if (cur == NULL) {
		//it just starts at the beginning of the heap
		heap->allocated_blocks = allocating;
		return allocating;
	}
	else {
		
		/******
		
		                           |  insert here    
		0       1        2       3 \/            4         end of memory
		|_______|________|_______|_______________|________|_______...
		
		running_size = sum(blocks_so_far)
		if cur->index - (prev->index + prev->size) can fit the requested block 
		   then place it there, otherwise, just keeping going until you reach the end (cur == NULL, insert at end)
		   
		   do a range check if you are going to insert it at the end to see if you ran out of memory
		******/
		
		//do insertion sort 
		struct arcl_memory_block *prev = cur;
		cur = cur->next;
		while(cur != NULL) {
			prev = cur;
			cur = cur->next;
			if (cur != NULL) {
				int space_between = cur->index - (prev->index+prev->size);
				//printf("There are %i bytes between indicies %i and %i\n", space_between, prev->index, cur->index);
				if (space_between >= allocating->size) {
					break; //can fit in between these two
				}
			}
		}
		
		//if either condition is violated, then insert after prev and push the list 
		//forward if cur is not NULL 
		
		//first make sure we aren't going to run out of space!
		if (prev->index+prev->size+allocating->size < heap->bytes) {
			allocating->index = prev->index + prev->size;
			//printf("%i is less than \n", allocating->index);
			prev->next = allocating;
			allocating->next = cur;
			return allocating;
		}
		else {
			fprintf(stderr, "FATAL: The arcl heap tried to allocate a memory block, but it ran out of memory!\n");
			exit(1);
		}
		
		//no need to shift any indicies, no blocks are moving
	}
	
	assert(0);
	return NULL;
}


struct arcl_memory_block *find_block_by_id(struct arcl_heap *heap, unsigned id) {
	struct arcl_memory_block *block = heap->allocated_blocks;
	while(block != NULL) {
		if (block->block_id == id) {
			return block;
		}
		block = block->next;
	}
	return NULL;
}


static int MAX_MEMORY_BLOCKS = 255;
static int *memory_id_pool;

void initialize_memory_block_ids() {
	memory_id_pool = (int*)malloc(sizeof(int)*MAX_MEMORY_BLOCKS);
	for (unsigned i = 0; i < MAX_MEMORY_BLOCKS; i++) {
		memory_id_pool[i] = 0;
	}
}

unsigned get_available_block_id() {
	unsigned ptr = 0;
	unsigned id = 0; //ID of 0 means it failed.
	while(ptr < MAX_MEMORY_BLOCKS) {
		ptr++;
		if (memory_id_pool[ptr] == 0) {
			memory_id_pool[ptr] = 1; //allocate
			id = ptr + 1;
			break;
		}
	}
	return id;
}

void free_block(struct arcl_heap *heap, struct arcl_memory_block *block) {
	// find the block in the heap and deallocate it / readjust pointers
	
	//this block can be identified by its index and size 
	struct arcl_memory_block *cur = heap->allocated_blocks;
	if (heap->allocated_blocks == NULL || block == NULL) {
		fprintf(stderr, "Tried to free a NULL block, or the target heap has no allocated blocks");
		return;
	}
	
	//is the first one the block in question?
	if (block->index == cur->index && block->size == cur->size) {
		if (cur->next != NULL) {
			heap->allocated_blocks = cur->next;
			memory_id_pool[cur->block_id - 1] = 0;
			free(cur);
		}
		else {
			memory_id_pool[cur->block_id - 1] = 0;
			free(cur);
			heap->allocated_blocks = NULL;
		}
	}
	else {
		//need to do more work to find the allocated block
		struct arcl_memory_block *prev = cur;
		cur = cur->next;
		while (cur != NULL && !(block->index == cur->index && block->size == cur->size)) {
			prev = cur;
			cur = cur->next;
		}
		if (cur != NULL) {
			prev->next = cur->next;
			memory_id_pool[cur->block_id - 1] = 0;
			free(cur);
		}
	}
}

void write_char_to_block(struct arcl_heap *heap, struct arcl_memory_block *in_block, unsigned int offset, char char_value) {
	unsigned int i = in_block->index + offset;
	printf("Writing %c to %i\n", char_value, i);
	heap->raw[i] = (uint8_t)char_value;
}

void write_arcl_int_to_block(struct arcl_heap *heap, struct arcl_memory_block *in_block, unsigned int offset, int int_value) {
	heap->raw[in_block->index + offset] = (uint8_t)(int_value & 0xFF);
	heap->raw[in_block->index + offset + 1] = (uint8_t)((int_value >> 8) & 0xFF);
}

void write_arcl_byte_to_block(struct arcl_heap *heap, struct arcl_memory_block *in_block, unsigned int offset, int byte_value) {
	heap->raw[in_block->index + offset] = (uint8_t)(byte_value & 0xFF);
}

char read_char_from_block(struct arcl_heap *heap, struct arcl_memory_block *from_block, unsigned int offset) {
	return (char)(heap->raw[from_block->index + offset]);
}

int read_arcl_int_from_block(struct arcl_heap *heap, struct arcl_memory_block *from_block, unsigned int offset) {
	return (int)(heap->raw[from_block->index + offset] & 0xFF)
			| (int)((heap->raw[from_block->index + offset + 1] & 0xFF) << 8);
}

int read_arcl_byte_from_block(struct arcl_heap *heap, struct arcl_memory_block *from_block, unsigned int offset) {
	return (int)(heap->raw[from_block->index + offset]);
}

void push_stack_frame(struct arcl_stack *stack, unsigned int offset) {
	stack->frame_pointer += offset;
}

void pop_stack_frame(struct arcl_stack *stack, unsigned int offset) {
	stack->frame_pointer -= offset;
}

void write_char_to_stack(struct arcl_stack *stack, unsigned int offset, char char_value) {
	stack->raw[stack->frame_pointer + offset] = (uint8_t)char_value;
}

void write_arcl_int_to_stack(struct arcl_stack *stack, unsigned int offset, int int_value) {
	stack->raw[stack->frame_pointer + offset] = (uint8_t)(int_value & 0xFF);
	stack->raw[stack->frame_pointer + offset + 1] = (uint8_t)((int_value >> 8) & 0xFF);
}

void write_arcl_byte_to_stack(struct arcl_stack *stack, unsigned int offset, int byte_value) {
	stack->raw[stack->frame_pointer + offset] = (uint8_t)(byte_value & 0xFF);
}

char read_char_from_stack(struct arcl_stack *stack, unsigned int offset) {
	return (char)(stack->raw[stack->frame_pointer + offset]);;
}

int read_arcl_int_from_stack(struct arcl_stack *stack, unsigned int offset) {
	return (int)(stack->raw[stack->frame_pointer + offset] & 0xFF)
			| (int)((stack->raw[stack->frame_pointer + offset + 1] & 0xFF) << 8);
}

int read_arcl_byte_from_stack(struct arcl_stack *stack, unsigned int offset) {
	return (int)(stack->raw[stack->frame_pointer + offset]);
}



/**** DEBUG FUNCTIONS *********/
void print_heap(struct arcl_heap *heap) {
	printf("Arcl Heap Print:\n");
	printf("Bytes: %i\n", heap->bytes);
	printf("Allocated blocks:\n");
	struct arcl_memory_block* blk = heap->allocated_blocks;
	//int block_counter = 0;
	while(blk != NULL) { 
		printf("Block ID %i:\n", blk->block_id);
		printf("Index %i , size %i\n\n", blk->index, blk->size);
		blk = blk->next;
	}
	printf("\n");
}

void print_memory_block(struct arcl_heap *heap, struct arcl_memory_block *block) {
	for (unsigned i = 0; i < block->size; i++) {
		unsigned offset_i = block->index + i;
		printf("%c", (char)heap->raw[offset_i]);
	}
	printf("\n");
}