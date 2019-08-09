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

#ifndef SCARLSYMBOLTABLE_H_INCLUDED
#define SCARLSYMBOLTABLE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "scarltypes.h"

struct scarl_symbol_table_entry;
struct scarl_symbol_table;

struct scarl_symbol_table {
    // scoping will be kept track of with a tree of symbol tables
    struct scarl_symbol_table *parent_st;
    // entries;
    // child_tables;
};

struct scarl_symbol_table_entry {
    char *ident;
    // a more complex type description structure
    struct type_descriptor *typeDescriptor;
    // the symbol table this entry resides in
    struct scarl_symbol_table *st;
};

#endif // SCARLSYMBOLTABLE_H_INCLUDED
