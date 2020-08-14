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

#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <map>
#include <chrono>
#include <thread>

#include "arclcli.h"
#include "arclregister.h"
#include "arclmemory.h"

using namespace std;

/*
	This will see if the current position can match the matching string.
	If it does this function will return true, otherwise it will return false. 
	
	cur_pos will be the position of the first letter of the matching_with
	string in the text block. This is a tester function, not a searcher.
*/
bool match(char *text, unsigned cur_pos, const string &matching_with) {
	unsigned matching_len = matching_with.length();
	unsigned text_len = strlen(text);
	int offset = 0;
	//printf("Comparing %c and ahead with %s (text len = %i, matching len = %i\n", text[cur_pos], matching_with.c_str(), text_len, matching_len);
	while (cur_pos + offset < text_len && offset < matching_len && text[cur_pos + offset] == matching_with.c_str()[offset]) {
		offset++;
	}
	//printf("Stopped comparing at offset = %i\n", offset);
	return (offset == matching_len);
}

void mark_labels(map<string, unsigned> &labels_map, char *code) {
	unsigned ptr = 0;
	unsigned code_len = strlen(code);
	while (ptr < code_len) {
		if (match(code, ptr, "LABEL")) {
			//grab the label text.
			unsigned label_start = ptr;
			ptr += 5;
			while (code[ptr] == ' ') ptr++; //skip spaces between label and what the label actually is
			string label_string = "";
			unsigned temp_ptr = ptr;
			while (temp_ptr < code_len && code[temp_ptr] != '\n') {
				label_string.append(1, code[temp_ptr]);
				temp_ptr++;
			}
			//printf("Found label: %s at %i\n", label_string.c_str(), label_start);
			labels_map[label_string] = label_start;
		}
		else if (match(code, ptr, "PROC")) {
			//grab the label text. /* lazy copy paste from section above*/
			unsigned label_start = ptr;
			ptr += 4;
			while (code[ptr] == ' ') ptr++; //skip spaces between label and what the label actually is
			string label_string = "";
			unsigned temp_ptr = ptr;
			while (temp_ptr < code_len && code[temp_ptr] != '\n') {
				label_string.append(1, code[temp_ptr]);
				temp_ptr++;
			}
			//printf("Found proc: %s at %i\n", label_string.c_str(), label_start);
			labels_map[label_string] = label_start;
		}
		ptr++;
	}
}

void heap_tests() {
	struct arcl_heap *heap = allocate_arcl_heap(64);
	
	block_id_pool *pool = new block_id_pool;
	pool->initialize_memory_block_ids();
	
	struct arcl_memory_block *b1 = allocate_block(heap, 5, *pool);

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

/*
void test_match() {
	if (match("match", 0, "match")) {
		printf("match matches match\n");
	}
	if (!match("match", 0, "not match")) {
		printf("match does not match not match\n");
	}
}
*/

int main(int argc, char *argv[]) {
	block_id_pool *pool = new block_id_pool;
	pool->initialize_memory_block_ids();
	
	struct arcl_heap *heap = allocate_arcl_heap(128); //heap byte size, should make it option
	struct arcl_stack *stack = create_arcl_stack(64); //stack byte size, should make it option
	
	if (argc == 1) {
		printf("Must supply ARCL code file to execute\n");
		exit(0);
	}
	char *input_file = argv[1];
	//printf("running %s\n", input_file);
	
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

	//did we preserve newlines?
	unsigned newlines = 0;
	int ptr = 0;
	while (code_file_in_mem[ptr] != '\0') {
		if (code_file_in_mem[ptr] == '\n') 
			newlines++;
		ptr++;
	}
	//printf("I think the ARCL file has %i lines\n", newlines+1);
	
	// the device peripherals are simple
	const int stdinDeviceId = 1;
	const int stdoutDeviceId = 2;
	const int stderrDeviceId = 3;

	bool flag_equal = false;
	bool flag_greater = false;
	bool flag_less = false;
	bool flag_and = false;
	bool flag_or = false;

	//find labels and mark the locations
	map<string, unsigned> labels;
	mark_labels(labels, code_file_in_mem);

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
			
			//printf("Get line: %s\n", ln_buf);
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
				//printf("about to pop %i register values off the stack\n", reg_count);
				pop_stack_frame(stack, reg_count*2); 
				for (int i = 0; i < reg_count; i++) {
					//printf("about to read from stack with offset %i\n", i*2);
					int val = read_arcl_int_from_stack(stack, i*2); //2 byte ints
					//printf("Got %i\n", val);
					set_reg_val(ARCL_R0+i, val);
				}
			}
			else if (!strcmp(code_buf, "ALLOC")) {
				//handle ALLOC instruction
				sscanf(ln_buf, "%s %s %s[ \n]+", code_buf, param0_buf, param1_buf);
				int regblock = parse_register(param0_buf);
				//printf("1\n");
				int bytes = atoi(param1_buf);
				//printf("2\n");
				struct arcl_memory_block *allocated = allocate_block(heap, bytes, *pool); //breaking now 
				//printf("3\n");
				set_reg_val(regblock, allocated->block_id);
			}
			else if (!strcmp(code_buf, "FREE")) {
				//handle FREE instruction
				sscanf(ln_buf, "%s %s[ \n]+", code_buf, param0_buf);
				int regblock = parse_register(param0_buf);
				int id = get_reg_val(regblock);
				struct arcl_memory_block *found = find_block_by_id(heap, id);
				if (found != NULL) {
					free_block(heap, found, *pool);
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
			/*LABEL <label> handled earlier*/
			/*PROC <proc-name> is handled like LABEL*/
			else if (!strcmp(code_buf, "RET")) { //pop return address and go back 
				sscanf(ln_buf, "%s[ \n]+", code_buf);
				/*Does not include the RLOAD - responsibility of the compiler */
				int return_spot = read_arcl_int_from_stack(stack, 0);
				pop_stack_frame(stack, 2);
				cur_start = return_spot;
				cur_end = return_spot;
			}
			else if (!strcmp(code_buf, "CALL")) { //stack return 'address' and jump
				sscanf(ln_buf, "%s %s[ \n]+", code_buf, param0_buf);
				/*Does not include the RSAVE - responsibility of the compiler */
				int return_spot = cur_end;
				while ((return_spot == ' ' || return_spot == '\n') && return_spot != '\0') return return_spot++;
				push_stack_frame(stack, 2);
				write_arcl_int_to_stack(stack, 0, return_spot);
				string procName = string(param0_buf);
				unsigned lblSpot = labels[procName];
				cur_start = lblSpot;
				cur_end = lblSpot;
			}
			else if (!strcmp(code_buf, "JMP")) { //unconditional jump
				sscanf(ln_buf, "%s %s[ \n]+", code_buf, param0_buf);
				string temp = string(param0_buf);
				unsigned lblSpot = labels[temp];
				cur_start = lblSpot;
				cur_end = lblSpot;
			}
			else if (!strcmp(code_buf, "CMP")) {
				sscanf(ln_buf, "%s %s %s[ \n]+", code_buf, param0_buf, param1_buf);
				int left_reg = parse_register(param0_buf);
				int right_reg = parse_register(param1_buf);
				int left_val = get_reg_val(left_reg);
				int right_val = get_reg_val(right_reg);
				flag_equal = left_val == right_val;
				flag_greater = left_val > right_val;
				flag_less = left_val < right_val;
				flag_and = (left_val != 0) && (right_val != 0);
				flag_or = (left_val != 0) || (right_val != 0);
			}
			//conditional jumps
			else if (!strcmp(code_buf, "JPE")) { //jump if equal
				sscanf(ln_buf, "%s %s[ \n]+", code_buf, param0_buf);
				if (flag_equal) {
					string temp = string(param0_buf);
					unsigned lblSpot = labels[temp];
					cur_start = lblSpot;
					cur_end = lblSpot;
				}
			}
			else if (!strcmp(code_buf, "JPE")) { //jump if not equal
				sscanf(ln_buf, "%s %s[ \n]+", code_buf, param0_buf);
				if (!flag_equal) {
					string temp = string(param0_buf);
					unsigned lblSpot = labels[temp];
					cur_start = lblSpot;
					cur_end = lblSpot;
				}
			}
			else if (!strcmp(code_buf, "JPGR")) { //jump if greater
				sscanf(ln_buf, "%s %s[ \n]+", code_buf, param0_buf);
				if (flag_greater) {
					string temp = string(param0_buf);
					unsigned lblSpot = labels[temp];
					cur_start = lblSpot;
					cur_end = lblSpot;
				}
			}
			else if (!strcmp(code_buf, "JPLS")) { //jump if less
				sscanf(ln_buf, "%s %s[ \n]+", code_buf, param0_buf);
				if (flag_less) { //could also be "not greater"
					string temp = string(param0_buf);
					unsigned lblSpot = labels[temp];
					cur_start = lblSpot;
					cur_end = lblSpot;
				}
			}
			else if (!strcmp(code_buf, "JPGE")) { //jump if greater than or equal to 
				sscanf(ln_buf, "%s %s[ \n]+", code_buf, param0_buf);
				if (flag_greater || flag_equal) { 
					string temp = string(param0_buf);
					unsigned lblSpot = labels[temp];
					cur_start = lblSpot;
					cur_end = lblSpot;
				}
			}
			else if (!strcmp(code_buf, "JPLE")) { //jump if less than or equal to 
				sscanf(ln_buf, "%s %s[ \n]+", code_buf, param0_buf);
				if (flag_less || flag_equal) { 
					string temp = string(param0_buf);
					unsigned lblSpot = labels[temp];
					cur_start = lblSpot;
					cur_end = lblSpot;
				}
			}
			else if (!strcmp(code_buf, "JAND")) { //jump if logical AND  
				sscanf(ln_buf, "%s %s[ \n]+", code_buf, param0_buf);
				if (flag_and) { 
					string temp = string(param0_buf);
					unsigned lblSpot = labels[temp];
					cur_start = lblSpot;
					cur_end = lblSpot;
				}
			}
			else if (!strcmp(code_buf, "JOR")) { //jump if logical OR  
				sscanf(ln_buf, "%s %s[ \n]+", code_buf, param0_buf);
				if (flag_or) { 
					string temp = string(param0_buf);
					unsigned lblSpot = labels[temp];
					cur_start = lblSpot;
					cur_end = lblSpot;
				}
			}
			else if (!strcmp(code_buf, "DELAY")) {
				sscanf(ln_buf, "%s %s[ \n]+", code_buf, param0_buf);
				int reg = parse_register(param0_buf);
				int val = get_reg_val(reg);
				//not yet implemented
				//std::this_thread::sleep_for(std::chrono::milliseconds(val)); //thanks to https://stackoverflow.com/questions/4184468/sleep-for-milliseconds
			}
			else if (!strcmp(code_buf, "OUTPUT")) {
				sscanf(ln_buf, "%s %s[ \n]+", code_buf, param0_buf);
				int reg = parse_register(param0_buf);
				int val = get_reg_val(reg);
				//can't control OUTPUT / INPUT pins on this device 
			}
			else if (!strcmp(code_buf, "INPUT")) {
				sscanf(ln_buf, "%s %s[ \n]+", code_buf, param0_buf);
				int reg = parse_register(param0_buf);
				int val = get_reg_val(reg);
				//can't control OUTPUT / INPUT pins on this device 
			}
			else if (!strcmp(code_buf, "WRITE")) {
				sscanf(ln_buf, "%s %s %s[ \n]+", code_buf, param0_buf, param1_buf);
				int regPinReg = parse_register(param0_buf);
				int regDataReg = parse_register(param1_buf);
				int regPinVal = get_reg_val(regPinReg);
				int regDataVal = get_reg_val(regDataReg);
				if (regPinVal == stdoutDeviceId) {
					char writeOut = (char)regDataVal;
					fputc(writeOut, (FILE*)stdout);
				}
				else if (regPinVal == stderrDeviceId) {
					char writeOut = (char)regDataVal;
					fputc(writeOut, (FILE*)stderr);
				}
				
			}
			else if (!strcmp(code_buf, "READ")) {
				sscanf(ln_buf, "%s %s %s[ \n]+", code_buf, param0_buf, param1_buf);
				int regPinReg = parse_register(param0_buf);
				int regDataReg = parse_register(param1_buf);
				int regPinVal = get_reg_val(regPinReg);
				if (regPinVal == stdinDeviceId) {
					char readIn = fgetc((FILE*)stdin);
					set_reg_val(regDataReg, readIn);
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
		//fprintf(stderr, "Cannot find %s\n", input_file);
	}
	free(code_file_in_mem);
	
	//print_registers();
	
	return 0;
}