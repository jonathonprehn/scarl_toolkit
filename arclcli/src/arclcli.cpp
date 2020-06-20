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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arclcli.h"
#include "arclregister.h"
#include "arclmemory.h"

void heap_tests() {
	struct arcl_heap *heap = allocate_arcl_heap(64);
	
	struct arcl_memory_block *b1 = allocate_block(heap, 5);
	// struct arcl_memory_block *b2 = allocate_block(heap, 7);
	// struct arcl_memory_block *b3 = allocate_block(heap, 8);
	// struct arcl_memory_block *b4 = allocate_block(heap, 10);
	// free_block(heap, b3);
	// struct arcl_memory_block *b5 = allocate_block(heap, 12);
	// struct arcl_memory_block *b6 = allocate_block(heap, 2);
	//struct arcl_memory_block *b7 = allocate_block(heap, 40); //out of memory error
	print_heap(heap);
		
	for (int i = 0; i < 5; i++) {
		write_char_to_block(heap, b1, i, 'a');
		print_memory_block(heap, b1);
	}
	//write_char_to_block(heap, b1, 1, 'b');
	//write_char_to_block(heap, b1, 2, 'c');
	char c = read_char_from_block(heap, b1, 0);
	printf("Got char from block: %c\n", c);
	
	write_arcl_int_to_block(heap, b1, 1, 427);
	int i = read_arcl_int_from_block(heap, b1, 1);
	printf("Got arcl int from block: %i\n", i);
	
	write_arcl_byte_to_block(heap, b1, 4, 64);
	int k = read_arcl_byte_from_block(heap, b1, 4);
	printf("Got arcl byte from block: %i\n", k);
	
	print_memory_block(heap, b1);
}


int main(int argc, char *argv[]) {
	
	initialize_memory_block_ids();
	
	struct arcl_heap *heap = allocate_arcl_heap(128); //heap byte size, should make it option
	struct arcl_stack *stack = create_arcl_stack(64); //stack byte size, should make it option
	
	if (argc == 1) {
		printf("Must supply ARCL code file to execute\n");
		exit(0);
	}
	char *input_file = argv[1];
	printf("running %s\n", input_file);
	
	FILE *arcl_code_stream = fopen(input_file, "r");
	unsigned code_file_length = 0;
	fseek(arcl_code_stream, 0, SEEK_END);
	code_file_length = ftell(arcl_code_stream);
	rewind(arcl_code_stream);
	
	//read into memory
	//printf("Loading instruction file into memory (%i bytes)\n", code_file_length);
	char *code_file_in_mem = (char*)malloc(code_file_length * sizeof(char));
	size_t success_read = fread(code_file_in_mem, 1, code_file_length, arcl_code_stream);
	code_file_in_mem[success_read] = '\0';
	//printf("Loaded %i bytes into memory\n", success_read);
	fclose(arcl_code_stream);

	//print newlines
	/*int i = 0;
	while (i < strlen(code_file_in_mem)) {
		if (code_file_in_mem[i] == '\n') printf("new line at %i\n", i);
		i++;
	}*/
	
	if (arcl_code_stream != NULL) {
		/* TODO: Allow for this to be encoded instead of read in real time */
		char *ln_buf = (char*)malloc(255*sizeof(char));
		char *code_buf = (char*)malloc(50*sizeof(char));
		char *param0_buf = (char*)malloc(50*sizeof(char));
		char *param1_buf = (char*)malloc(50*sizeof(char));
		char *param2_buf = (char*)malloc(50*sizeof(char));
		unsigned cur_start = 0;
		unsigned cur_end = 0;
		while(cur_end < strlen(code_file_in_mem)) {
			while(cur_end < strlen(code_file_in_mem) && code_file_in_mem[cur_end] != '\n') {
				cur_end++;
			}
			//don't read out of memory, no more lines 
			if (cur_end >= strlen(code_file_in_mem)) {
				break;
			}
			//reached end of line, load into buffer
			//(doing it this way because the code file is in memory)
			int i = 0;
			for (i = 0; i < cur_end-cur_start; i++) {
				ln_buf[i] = code_file_in_mem[cur_start+i];
			}
			ln_buf[i] = '\0';
			cur_start = cur_end + 1;
			cur_end = cur_start; //reset for next time
			
			printf("Get line: %s\n", ln_buf);
			// get type of instruction to begin parsing the parameters
			sscanf(ln_buf, "%s[ \n]+", code_buf);
			if (!strcmp(code_buf, "ADD")) {
				sscanf(ln_buf, "%s %s %s[ \n]+", code_buf, param0_buf, param1_buf);
				int left_reg = parse_register(param0_buf);
				int right_reg = parse_register(param1_buf);
				int left_val = get_reg_val(left_reg);
				int right_val = get_reg_val(right_reg);
				int result = left_val + right_val;
				set_reg_val(right_reg, result);
			}
			else if (!strcmp(code_buf, "SUB")) {
				sscanf(ln_buf, "%s %s %s[ \n]+", code_buf, param0_buf, param1_buf);
				int left_reg = parse_register(param0_buf);
				int right_reg = parse_register(param1_buf);
				int left_val = get_reg_val(left_reg);
				int right_val = get_reg_val(right_reg);
				int result = left_val - right_val;
				set_reg_val(right_reg, result);
			}
			else if (!strcmp(code_buf, "MULT")) {
				sscanf(ln_buf, "%s %s %s[ \n]+", code_buf, param0_buf, param1_buf);
				int left_reg = parse_register(param0_buf);
				int right_reg = parse_register(param1_buf);
				int left_val = get_reg_val(left_reg);
				int right_val = get_reg_val(right_reg);
				int result = left_val * right_val;
				set_reg_val(right_reg, result);
			}
			else if (!strcmp(code_buf, "DIV")) {
				sscanf(ln_buf, "%s %s %s[ \n]+", code_buf, param0_buf, param1_buf);
				int left_reg = parse_register(param0_buf);
				int right_reg = parse_register(param1_buf);
				int left_val = get_reg_val(left_reg);
				int right_val = get_reg_val(right_reg);
				int result = left_val / right_val;
				set_reg_val(right_reg, result);
			}
			else if (!strcmp(code_buf, "FLIP")) {
				sscanf(ln_buf, "%s %s[ \n]+", code_buf, param0_buf);
				int reg = parse_register(param0_buf);
				int val = get_reg_val(reg);
				set_reg_val(reg, -val);
			}
			else if (!strcmp(code_buf, "MOV")) {
				//handle MOV instruction
				sscanf(ln_buf, "%s %s %s[ \n]+", code_buf, param0_buf, param1_buf);	
				int literal_src = parse_register(param0_buf);
				int literal_dst = parse_register(param1_buf);
				set_reg_val(literal_dst, get_reg_val(literal_src));
			}
			else if (!strcmp(code_buf, "LOADL")) {
				//handle LOADL instruction
				sscanf(ln_buf, "%s %s %s[ \n]+", code_buf, param0_buf, param1_buf);
				int parse_id = parse_register(param0_buf);
				unsigned literal = atoi(param1_buf);
				set_reg_val(parse_id, literal);
			}
			else if (!strcmp(code_buf, "LOADF")) {
				//handle LOADF instruction
				sscanf(ln_buf, "%s %s %s[ \n]+", code_buf, param0_buf, param1_buf);
				int reg = parse_register(param0_buf);
				int offset = atoi(param1_buf);
				int read_val = read_arcl_byte_from_stack(stack, offset);
				set_reg_val(reg, read_val);
			}
			else if (!strcmp(code_buf, "STORF")) {
				//handle LOADF instruction
				sscanf(ln_buf, "%s %s %s[ \n]+", code_buf, param0_buf, param1_buf);
				int reg = parse_register(param0_buf);
				int offset = atoi(param1_buf);
				int reg_value = get_reg_val(reg);
				write_arcl_byte_to_stack(stack, offset, reg_value);
			}
			else if (!strcmp(code_buf, "FRAMEU")) {
				sscanf(ln_buf, "%s %s[ \n]+", code_buf, param0_buf);
				int offset = atoi(param0_buf);
				push_stack_frame(stack, offset);
			}
			else if (!strcmp(code_buf, "FRAMEO")) {
				sscanf(ln_buf, "%s %s[ \n]+", code_buf, param0_buf);
				int offset = atoi(param0_buf);
				pop_stack_frame(stack, offset);
			}
			else if (!strcmp(code_buf, "RSAVE")) {
				//push all registers onto the stack 
				unsigned reg_count = ARCL_R12-ARCL_R0;
				for (int i = 0; i <= reg_count; i++) {
					int val = get_reg_val(ARCL_R0+i);
					write_arcl_int_to_stack(stack, i*2, val); //2 byte ints
				}
				push_stack_frame(stack, reg_count*2);
			}
			else if (!strcmp(code_buf, "RLOAD")) {
				//load all register values from the stack
				unsigned reg_count = ARCL_R12-ARCL_R0;
				pop_stack_frame(stack, reg_count*2);
				for (int i = 0; i <= reg_count; i++) {
					int val = read_arcl_int_from_stack(stack, i*2); //2 byte ints
					set_reg_val(ARCL_R0+i, val);
				}
			}
			else if (!strcmp(code_buf, "ALLOC")) {
				//handle ALLOC instruction
				sscanf(ln_buf, "%s %s %s[ \n]+", code_buf, param0_buf, param1_buf);
				int regblock = parse_register(param0_buf);
				int bytes = atoi(param1_buf);
				struct arcl_memory_block *allocated = allocate_block(heap, bytes);
				set_reg_val(regblock, allocated->block_id);
			}
			else if (!strcmp(code_buf, "FREE")) {
				//handle FREE instruction
				sscanf(ln_buf, "%s %s[ \n]+", code_buf, param0_buf);
				int regblock = parse_register(param0_buf);
				int id = get_reg_val(regblock);
				struct arcl_memory_block *found = find_block_by_id(heap, id);
				if (found != NULL) {
					free_block(heap, found);
				}
				else {
					//report an error. How to handle this kind of thing?
					fprintf(stderr, "Unable to find memory block with id: %i\n", id);
				}
				
			}
			else if (!strcmp(code_buf, "LOADR")) {
				//handle LOADR instruction
				sscanf(ln_buf, "%s %s %s %s[ \n]+", code_buf, param0_buf, param1_buf, param2_buf);
				int regstor = parse_register(param0_buf);
				int regblock = parse_register(param1_buf);
				int block_id = get_reg_val(regblock);
				int offset = atoi(param2_buf);
				
				struct arcl_memory_block *found = find_block_by_id(heap, block_id);
				if (found != NULL) {
					int value = read_arcl_byte_from_block(heap, found, offset);
					set_reg_val(regstor, value);
				}
				else {
					//report an error. How to handle this kind of thing?
					fprintf(stderr, "Unable to find memory block with id: %i\n", block_id);
				}
			}
			else if (!strcmp(code_buf, "STORR")) {
				//handle STORR instruction
				sscanf(ln_buf, "%s %s %s %s[ \n]+", code_buf, param0_buf, param1_buf, param2_buf);
				int regvalue = parse_register(param0_buf);
				int value = get_reg_val(regvalue);
				int regblock = parse_register(param1_buf);
				int block_id = get_reg_val(regblock);
				int offset = atoi(param2_buf);
				
				struct arcl_memory_block *found = find_block_by_id(heap, block_id);
				if (found != NULL) {
					write_arcl_byte_to_block(heap, found, offset, value);
				}
				else {
					//report an error. How to handle this kind of thing?
					fprintf(stderr, "Unable to find memory block with id: %i\n", block_id);
				}
			}
			
		
			ln_buf[0] = '\0';
			code_buf[0] = '\0';
			param0_buf[0] = '\0';
			param1_buf[0] = '\0';
			param2_buf[0] = '\0';
		}
		free(code_buf);
		free(ln_buf);
	}
	else {
		fprintf(stderr, "Cannot find %s\n", input_file);
	}
	free(code_file_in_mem);
	
	print_registers();
	
	return 0;
}