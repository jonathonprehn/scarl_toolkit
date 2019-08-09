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
#include <string.h>

#include "stringstack.h"

char *the_string_stack[SCARL_STRING_STACK_SIZE];
int scarl_string_stack_top = 0;

void string_stack_push(char *str) {
	char *dup = strdup(str);
	the_string_stack[scarl_string_stack_top] = dup;
	scarl_string_stack_top++;
}

char *string_stack_pop() {
	scarl_string_stack_top--;
	char *val = the_string_stack[scarl_string_stack_top];
	the_string_stack[scarl_string_stack_top] = NULL;
	return val;
}


int the_int_stack[SCARL_INT_STACK_SIZE];
int scarl_int_stack_top = 0;

void int_stack_push(int value) {
	the_int_stack[scarl_int_stack_top] = value;
	scarl_int_stack_top++;
}

int int_stack_pop() {
	scarl_int_stack_top--;
	int val = the_int_stack[scarl_int_stack_top];
	return val;
}

