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
#include <stdarg.h>

#include "scarlastnode.h"
#include "scarltypes.h"

struct scarl_ast_node;

struct scarl_symbol_table; // maintains a list of entries in the same scope and child symbol tables
struct scarl_symbol_table_entry; // holds the data of a symbol table entry 
struct scarl_symbol_table_entry_identifier; // structure for unique identification of entries 

struct scarl_symbol_table {
    struct scarl_symbol_table_entry *entries; // linked list of entries 
	
    // scoping will be kept track of with a tree of symbol tables
    struct scarl_symbol_table *parent_st;
	struct scarl_symbol_table *next_sibling;
	struct scarl_symbol_table *first_child;
	
	int frameByteTotalSize; // the total frame size of this symbol table,
							// this frame size includes child tables
};

struct scarl_symbol_table_entry {
	// composite structure for uniquely identifying a program identifier
    struct scarl_symbol_table_entry_identifier *ident;
	
	// to allow for a list of entries 
	struct scarl_symbol_table_entry *next;
	
    // a more complex type description structure
    struct scarl_type_descriptor *type;
	
    // the symbol table this entry resides in
    struct scarl_symbol_table *containing_st;
	
	// extraneous information about this entry
	int is_constant;
	int compile_time_value; // for constant expressions only
	int defined; //operational
	
	// memory management about this entry 
	int frameByteSize; // space taken up in the frame it lives in 
	int frameByteOffset; // 0-based index offset from frame base
};

struct scarl_symbol_table_entry_identifier {
	// the string as it is in the program 
	// i.e:
	// int x = 5;
	// the identifier will be "x"
	char *ident_str;
	
	// parameters are a part of identifying 
	// a unique object to allow for overloading
	struct scarl_type_descriptor *parameter_list;
};

// symbol table construct initialization functions
struct scarl_symbol_table *create_st();
struct scarl_symbol_table *create_st_from_ast(struct scarl_symbol_table *current_scope_st, struct scarl_symbol_table *st, struct scarl_ast_node *node); // direct creation, recursive
struct scarl_symbol_table_entry *create_st_entry(struct scarl_symbol_table_entry_identifier *ident, struct scarl_type_descriptor *type);
struct scarl_symbol_table_entry_identifier *create_st_entry_identifier(char *ident_str, struct scarl_type_descriptor *parameter_list); // parameter list already built
struct scarl_symbol_table_entry_identifier *create_st_entry_identifier_var(char *ident_str, int param_count, ...); // a variable number of type descriptors
//struct scarl_symbol_table_entry_identifier *create_st_entry_identifier_from_ast_node(struct scarl_symbol_table *current_scope_st, struct scarl_ast_node *node); // direct from the AST

// structure and debugging functions
void add_child_st(struct scarl_symbol_table *parent, struct scarl_symbol_table *adding);
int has_child_st(struct scarl_symbol_table *st);
int get_child_st_count(struct scarl_symbol_table *st);
void print_st(struct scarl_symbol_table *st);
void add_st_entry(struct scarl_symbol_table *parent, struct scarl_symbol_table_entry *entry);
int get_entry_count(struct scarl_symbol_table *st);
void calculate_byte_sizes(struct scarl_symbol_table *st);

// lookup and usage functions

// searches current scope first, and searches parent scope recursively until it is found or the root table has been searched 
struct scarl_symbol_table_entry *lookup_char_str(struct scarl_symbol_table *current_scope_st, char* ident);
// searches current scope first, and searches parent scope recursively until it is found or the root table has been searched 
struct scarl_symbol_table_entry *lookup(struct scarl_symbol_table *current_scope_st, struct scarl_symbol_table_entry_identifier *ident); 
// searches the specified symbol table only
struct scarl_symbol_table_entry *lookup_in_scope(struct scarl_symbol_table *current_scope_st, struct scarl_symbol_table_entry_identifier *ident);
// do these entry identifier structures match?
int compare_entry_identifiers(struct scarl_symbol_table_entry_identifier *lhs, struct scarl_symbol_table_entry_identifier *rhs);

#endif // SCARLSYMBOLTABLE_H_INCLUDED
