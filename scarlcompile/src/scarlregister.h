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

#ifndef __SCARL_REGISTER_H__
#define __SCARL_REGISTER_H__

/*
struct scarl_register_pair {
	int reg1;
	int reg2;
};
 
typedef struct scarl_register_pair scarl_rp;
*/
 
int register_available();
int allocate_register();
void free_register(int reg);
const char *register_str(int reg);

#endif // __STRING_STACK_SCARL_H__