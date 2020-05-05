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
		
	write_char_to_block(heap, b1, 0, 'a');
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
	
	heap_tests();
	
	if (argc == 1) {
		printf("Must supply ARCL code file to execute\n");
		exit(0);
	}
	char *input_file = argv[1];
	printf("running %s\n", input_file);
	
	FILE *arcl_code_stream = fopen(input_file, "r");
	if (arcl_code_stream != NULL) {
		char *ln_buf = (char*)malloc(255*sizeof(char));
		char *code_buf = (char*)malloc(50*sizeof(char));
		while(!feof(arcl_code_stream)) {
			fgets(ln_buf, 255, arcl_code_stream);
			// get type of instruction to begin parsing the parameters
			sscanf(ln_buf, "%s[ \n]+", code_buf);
			printf("Got token %s\n", code_buf);
			if (!strcmp(code_buf, "MOV")) {
				//handle MOV instruction
				
			}
			else if (!strcmp(code_buf, "LOADL")) {
				//handle LOADL instruction
				
			}
			else if (!strcmp(code_buf, "LOADF")) {
				//handle LOADF instruction
				
			}
			else if (!strcmp(code_buf, "LOADR")) {
				//handle LOADR instruction
				
			}
			else if (!strcmp(code_buf, "STORF")) {
				//handle STORF instruction
				
			}
			else if (!strcmp(code_buf, "STORR")) {
				//handle STORR instruction
				
			}
		}
		free(code_buf);
		free(ln_buf);
		fclose(arcl_code_stream);
	}
	else {
		fprintf(stderr, "Cannot find %s\n", input_file);
	}
	return 0;
}