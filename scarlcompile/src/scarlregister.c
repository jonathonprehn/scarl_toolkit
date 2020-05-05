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

#include "scarlregister.h"

#define SCARL_REGISTER_COUNT 12

int scarl_reg_ptr = 0;

// 0 indicates available, 1 is taken
int register_pool[SCARL_REGISTER_COUNT] = {
	0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0
};

const char *register_codes[SCARL_REGISTER_COUNT] = {
	"R0", "R1", "R2", "R3", "R4", "R5", 
	"R6", "R7", "R8", "R9", "R10", "R11"
};

int register_available() {
	if (register_pool[scarl_reg_ptr] == 0) {
		return 1;
	}
	else {
		int tries = 0;
		while (tries < SCARL_REGISTER_COUNT) {
			scarl_reg_ptr++;
			if (scarl_reg_ptr >= SCARL_REGISTER_COUNT) {
				scarl_reg_ptr = 0;
			}
			if (register_pool[scarl_reg_ptr] == 0) {
				return 1;
			}
			else {
				tries++;
			}
		}
		return 0; // no available register found
	}
}

int allocate_register() {
	if (register_pool[scarl_reg_ptr] == 0) {
		register_pool[scarl_reg_ptr] = 1;
		return scarl_reg_ptr;
	}
	else {
		int tries = 0;
		while (tries < SCARL_REGISTER_COUNT) {
			scarl_reg_ptr++;
			if (scarl_reg_ptr >= SCARL_REGISTER_COUNT) {
				scarl_reg_ptr = 0;
			}
			if (register_pool[scarl_reg_ptr] == 0) {
				register_pool[scarl_reg_ptr] = 1;
				return scarl_reg_ptr;
			}
			else {
				tries++;
			}
		}
		return -1; // no available register found
	}
}

void free_register(int reg) {
	// safe deallocation. Invalid codes do nothing
	if (reg >= 0 && reg < SCARL_REGISTER_COUNT) {
		register_pool[reg] = 0;
	}
}

const char *register_str(int reg) {
	return register_codes[reg];
}
