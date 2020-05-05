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

#include "arclregister.h"

static int register_values[12] = {
	0, 0, 0, 0, 
	0, 0, 0, 0,
	0, 0, 0, 0
};

int get_reg_val(int arcl_register) {
	return register_values[arcl_register - ARCL_R0];
}


void set_reg_val(int arcl_register, int value) {
	register_values[arcl_register - ARCL_R0] = value;
}

