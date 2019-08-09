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

#ifndef SCARLASTNODE_H_INCLUDED
#define SCARLASTNODE_H_INCLUDED

#include "scarltypes.h"

struct scarl_ast_node;

struct scarl_ast_node {
    // the node as it is in the grammar
    int node_type;
	// if the node is representing a "type" of some sort, this will be filled out
	int type_value;
    int int_value;
    char *str_value;
    
	//tree functionality
	struct scarl_ast_node *parent;
	// a general tree is a binary tree in disguise
	struct scarl_ast_node *next_sibling;
	struct scarl_ast_node *first_child;
};

struct scarl_ast_node *create_template_ast_node();
struct scarl_ast_node *create_typed_ast_node(int node_type, int type_value);
struct scarl_ast_node *create_int_value_ast_node(int node_type, int int_value);
struct scarl_ast_node *create_str_value_ast_node(int node_type, char *str_value);
void add_child_node(struct scarl_ast_node *parent, struct scarl_ast_node *adding);
int has_children(struct scarl_ast_node *node);
int get_children_count(struct scarl_ast_node *node);
void print_tree(struct scarl_ast_node *node);
const char *get_ast_node_type_string(int node_type);

#endif // SCARLASTNODE_H_INCLUDED
