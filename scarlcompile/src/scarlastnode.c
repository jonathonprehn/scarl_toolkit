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
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "scarlregister.h"
#include "scarltypes.h"
#include "scarlastnode.h"

struct scarl_ast_node *create_template_ast_node() {
	struct scarl_ast_node *ast_node = (struct scarl_ast_node*)malloc(sizeof(struct scarl_ast_node));
	ast_node->node_type =  SCARL_NULL;
	ast_node->type_value = SCARL_NULL;
    ast_node->int_value = SCARL_NULL;
    ast_node->str_value = NULL;
	ast_node->parent = NULL;
	ast_node->next_sibling = NULL;
	ast_node->first_child = NULL;
	ast_node->assoc_st = NULL;
	ast_node->reg_low = SCARL_NULL;
	ast_node->reg_high = SCARL_NULL;
	return ast_node;
}

struct scarl_ast_node *create_typed_ast_node(int node_type, int type_value) {
	struct scarl_ast_node *tmplt = create_template_ast_node();
	tmplt->node_type = node_type;
	tmplt->type_value = type_value;
	return tmplt;
}

struct scarl_ast_node *create_int_value_ast_node(int node_type, int int_value) {
	struct scarl_ast_node *tmplt = create_template_ast_node();
	tmplt->node_type = node_type;
	tmplt->int_value = int_value;
	return tmplt;
}

struct scarl_ast_node *create_str_value_ast_node(int node_type, char *str_value) {
	struct scarl_ast_node *tmplt = create_template_ast_node();
	tmplt->node_type = node_type;
	tmplt->str_value = str_value;
	return tmplt;
}

void add_child_node(struct scarl_ast_node *parent, struct scarl_ast_node *adding) {
	assert(parent != NULL && adding != NULL);
	if (parent->first_child == NULL) {
		parent->first_child = adding;
		adding->parent = parent;
	}
	else {
		struct scarl_ast_node *n = parent->first_child;
		while(n->next_sibling != NULL) {
			n = n->next_sibling;
		}
		// add the ast node to the next sibling, which is
		// in the list of children for this parent
		n->next_sibling = adding;
		adding->parent = parent;
	}
}

void push_child_node_front(struct scarl_ast_node *parent, struct scarl_ast_node *adding) {
	assert(parent != NULL && adding != NULL);
	adding->next_sibling = parent->first_child;
	parent->first_child = adding;
	adding->parent = parent;
}

int has_children(struct scarl_ast_node *node) {
	return node->first_child != NULL;
}

int get_children_count(struct scarl_ast_node *node) {
	if (!has_children(node)) {
		return 0;
	}
	else {
		int count = 0;
		struct scarl_ast_node *n = node->first_child;
		while(n != NULL) {
			n = n->next_sibling;
			count++;
		}
		return count;
	}
}

const char *get_ast_node_type_string(int node_type) {
	if (node_type == NON_TERMINAL_PROGRAM) {return "NON_TERMINAL_PROGRAM"; }
	else if (node_type == NON_TERMINAL_STATEMENT_LIST) {return "NON_TERMINAL_STATEMENT_LIST"; }
	else if (node_type == NON_TERMINAL_STATEMENT) {return "NON_TERMINAL_STATEMENT"; }
	else if (node_type == NON_TERMINAL_BLOCK_STATEMENT) {return "NON_TERMINAL_BLOCK_STATEMENT"; }
	else if (node_type == NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL) {return "NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL"; }
	else if (node_type == NON_TERMINAL_STATEMENT_BLOCK_LEVEL) {return "NON_TERMINAL_STATEMENT_BLOCK_LEVEL"; }
	//////else if (node_type == NON_TERMINAL_DEVICE_DECLARATOR_STATEMENT) {return "NON_TERMINAL_DEVICE_DECLARATOR_STATEMENT"; }
	else if (node_type == NON_TERMINAL_PRIMITIVE_DECLARATOR) {return "NON_TERMINAL_PRIMITIVE_DECLARATOR"; }
	else if (node_type == NON_TERMINAL_VARIABLE_DEFINITION_STATEMENT) {return "NON_TERMINAL_VARIABLE_DEFINITION_STATEMENT"; }
	else if (node_type == NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT) {return "NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT"; }
	else if (node_type == NON_TERMINAL_VARIABLE_SET_STATEMENT) {return "NON_TERMINAL_VARIABLE_SET_STATEMENT"; }
	else if (node_type == NON_TERMINAL_FUNCTION_INVOCATION) {return "NON_TERMINAL_FUNCTION_INVOCATION"; }
	else if (node_type == NON_TERMINAL_FUNCTION_INVOCATION_STATEMENT) {return "NON_TERMINAL_FUNCTION_INVOCATION_STATEMENT"; }
	else if (node_type == NON_TERMINAL_IF_BLOCK_STATEMENT) {return "NON_TERMINAL_IF_BLOCK_STATEMENT"; }
	else if (node_type == NON_TERMINAL_WHILE_BLOCK_STATEMENT) {return "NON_TERMINAL_WHILE_BLOCK_STATEMENT"; }
	else if (node_type == NON_TERMINAL_FORMAL_PARAMETER_LIST) {return "NON_TERMINAL_FORMAL_PARAMETER_LIST"; }
	else if (node_type == NON_TERMINAL_PARAMETER_LIST) {return "NON_TERMINAL_PARAMETER_LIST"; }
	else if (node_type == NON_TERMINAL_EXPRESSION) {return "NON_TERMINAL_EXPRESSION"; }
	else if (node_type == NON_TERMINAL_LOGICAL_EXPRESSION) {return "NON_TERMINAL_LOGICAL_EXPRESSION"; }
	else if (node_type == NON_TERMINAL_LOGICAL_AND_EXPRESSION) {return "NON_TERMINAL_LOGICAL_AND_EXPRESSION"; }
	else if (node_type == NON_TERMINAL_EQUALITY_EXPRESSION) {return "NON_TERMINAL_EQUALITY_EXPRESSION"; }
	else if (node_type == NON_TERMINAL_RELATIONAL_EXPRESSION) {return "NON_TERMINAL_RELATIONAL_EXPRESSION"; }
	else if (node_type == NON_TERMINAL_BOOL_EXPRESSION) {return "NON_TERMINAL_BOOL_EXPRESSION"; }
	else if (node_type == NON_TERMINAL_ARITHMETIC_EXPRESSION) {return "NON_TERMINAL_ARITHMETIC_EXPRESSION"; }
	else if (node_type == NON_TERMINAL_ARITHMETIC_FACTOR) {return "NON_TERMINAL_ARITHMETIC_FACTOR"; }
	else if (node_type == NON_TERMINAL_ARITHMETIC_UNARY) {return "NON_TERMINAL_ARITHMETIC_UNARY"; }
	else if (node_type == NON_TERMINAL_UNIT) {return "NON_TERMINAL_UNIT"; }
	else if (node_type == NON_TERMINAL_INTEGER_VALUE) {return "NON_TERMINAL_INTEGER_VALUE"; }
	else if (node_type == NON_TERMINAL_BOOL_VALUE) {return "NON_TERMINAL_BOOL_VALUE"; }
	else if (node_type == NON_TERMINAL_PRIMITIVE_TYPE) {return "NON_TERMINAL_PRIMITIVE_TYPE"; }
	else if (node_type == NON_TERMINAL_DEVICE_TYPE) {return "NON_TERMINAL_DEVICE_TYPE"; }
	else if (node_type == NON_TERMINAL_RETURN_STATEMENT) {return "NON_TERMINAL_RETURN_STATEMENT"; }
	else if (node_type == NON_TERMINAL_CLASS_DEFINITION_STATEMENT) {return "NON_TERMINAL_CLASS_DEFINITION_STATEMENT"; }
	else if (node_type == NON_TERMINAL_CONSTANT_DEFINITION_STATEMENT) {return "NON_TERMINAL_CONSTANT_DEFINITION_STATEMENT"; }
	else if (node_type == NON_TERMINAL_DELETE_STATEMENT) {return "NON_TERMINAL_DELETE_STATEMENT"; }
	else if (node_type == NON_TERMINAL_TYPE_DECLARATOR) {return "NON_TERMINAL_TYPE_DECLARATOR"; }
	else if (node_type == NON_TERMINAL_USER_DECLARATOR) {return "NON_TERMINAL_USER_DECLARATOR"; }
	else if (node_type == NON_TERMINAL_POINTER_TYPE) {return "NON_TERMINAL_POINTER_TYPE"; }
	else if (node_type == NON_TERMINAL_ARRAY_TYPE) {return "NON_TERMINAL_ARRAY_TYPE"; }
	else if (node_type == NON_TERMINAL_CHAR_VALUE) {return "NON_TERMINAL_CHAR_VALUE"; }
	else if (node_type == NON_TERMINAL_ARRAY_VALUE) {return "NON_TERMINAL_ARRAY_VALUE"; }
	else if (node_type == NON_TERMINAL_POINTER_VALUE) {return "NON_TERMINAL_POINTER_VALUE"; }
	else if (node_type == NON_TERMINAL_DEREFERENCED_VALUE) {return "NON_TERMINAL_DEREFERENCED_VALUE"; }
	else if (node_type == NON_TERMINAL_ARRAY_ACCESSOR_TYPE) {return "NON_TERMINAL_ARRAY_ACCESSOR_TYPE"; }
	else if (node_type == NON_TERMINAL_IDENTIFIER_VALUE) {return "NON_TERMINAL_IDENTIFIER_VALUE"; }
	else if (node_type == NON_TERMINAL_OPERAND_VALUE) {return "NON_TERMINAL_OPERAND_VALUE"; }
	else if (node_type == TYPES_EQUAL) {return "TYPES_EQUAL"; }
	else if (node_type == TYPES_CONVERTABLE) {return "TYPES_CONVERTABLE"; }
	else if (node_type == TYPES_NOT_EQUAL) {return "TYPES_NOT_EQUAL"; }
	else if (node_type == PRIMITIVE_TYPE) {return "PRIMITIVE_TYPE"; }
	else if (node_type == POINTER_TYPE) {return "POINTER_TYPE"; }
	else if (node_type == ARRAY_TYPE) {return "ARRAY_TYPE"; }
	else if (node_type == FUNCTION_TYPE) {return "FUNCTION_TYPE"; }
	else if (node_type == CLASS_TYPE) {return "CLASS_TYPE"; }
	else if (node_type == DEVICE_TYPE) {return "DEVICE_TYPE"; }
	else if (node_type == NON_TERMINAL_CLASS_ATTRIBUTE_IDENTIFIER) {return "NON_TERMINAL_CLASS_ATTRIBUTE_IDENTIFIER"; }
	else if (node_type == NON_TERMINAL_METHOD_INVOCATION) {return "NON_TERMINAL_METHOD_INVOCATION"; }
	else if (node_type == NON_TERMINAL_CLASS_ATTRIBUTE_LIST) {return "NON_TERMINAL_CLASS_ATTRIBUTE_LIST"; }
	else if (node_type == NON_TERMINAL_CLASS_DECLARATOR) {return "NON_TERMINAL_CLASS_DECLARATOR"; }
	else if (node_type == NON_TERMINAL_VARIABLE_DECLARATION_STATEMENT) {return "NON_TERMINAL_VARIABLE_DECLARATION_STATEMENT"; }
	else { return "<INVALID NODE TYPE>"; }
}

void print_tree_r(int level, struct scarl_ast_node *subtree);

void print_tree_r(int level, struct scarl_ast_node *subtree) {
	printf("%2i ", level);
	for (int i = 0; i < level; i++) {
		printf("--");
	}
	//printf("%i\n", subtree->node_type);
	printf("%s\n", get_ast_node_type_string(subtree->node_type));

	struct scarl_ast_node *next = subtree->first_child;
	while (next != NULL) {
		print_tree_r(level + 1, next);
		next = next->next_sibling;
	}
}

void print_tree(struct scarl_ast_node *tree) {
	print_tree_r(0, tree);
}
