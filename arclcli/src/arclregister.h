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

#ifndef ARCLCLI_REGISTER_H_INCLUDED
#define ARCLCLI_REGISTER_H_INCLUDED

//register codes
#define ARCL_R0      0xBB33
#define ARCL_R1      0xBB34
#define ARCL_R2      0xBB35
#define ARCL_R3      0xBB36
#define ARCL_R4      0xBB37
#define ARCL_R5      0xBB38
#define ARCL_R6      0xBB39
#define ARCL_R7      0xBB40
#define ARCL_R8      0xBB41
#define ARCL_R9      0xBB42
#define ARCL_R10     0xBB43
#define ARCL_R11     0xBB44
#define ARCL_R12     0xBB45

int get_reg_val(int arcl_register);
void set_reg_val(int arcl_register, int value);

#endif // ARCLCLI_REGISTER_H_INCLUDED