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
#include <assert.h>
#include <string.h>

#include "scarltypes.h"


/* Is the right hand side a descendent of the left hand side? */
int is_descendant_of(struct scarl_class_type *lhs, struct scarl_class_type *rhs) {
	return 0;
}

/* Is the right hand side a direct descendent (immediate child) of the left hand side? */
int is_direct_descendant_of(struct scarl_class_type *lhs, struct scarl_class_type *rhs) {
	return 0;
}

/* Is the right hand side an ancestor of the left hand side? */
int is_ancestor_of(struct scarl_class_type *lhs, struct scarl_class_type *rhs) {
	return 0;
}

/* Returns TYPES_EQUAL, TYPES_NOT_EQUAL or TYPES_CONVERTABLE */
/* It is directional in that for two given types A and B, you might be able to convert from A to B but  */
/* not be able to convert from B back to A (think about class hierarchies in polymorphism)              */
int directional_type_equality(struct scarl_type_descriptor *from_type, struct scarl_type_descriptor *to_type) {
	return 0;
}

/* Returns one of: PRIMITIVE_TYPE, POINTER_TYPE, ARRAY_TYPE, FUNCTION_TYPE, CLASS_TYPE or DEVICE_TYPE */
/* This function attempts to figure out which type the expression will eventually be converted to,    */
/* taking the "most straightforward" approach to guessing, given its context (symbol table)    */
int assume_type_class_of_expression_st(struct scarl_symbol_table *current_scope_st, struct scarl_ast_node *expr_node) {
	return 0;
}

/* Determines if the expression can be converted to a requested type given its context (symbol table)  */
int can_coerce_expression_to_type_class(struct scarl_symbol_table *current_scope_st, struct scarl_ast_node *expr_node, struct scarl_type_descriptor *type) {
	return 0;
}


/* Determines if the expression is constant. That is, is its value deterministic at compile time? TRUE/FALSE */
int is_constant_expression(struct scarl_symbol_table *current_scope_st, struct scarl_ast_node *expr_node) {
	
	return 0;
}

/* Gets the compile time value of a constant expression */
int eval_constant_expression(struct scarl_symbol_table *current_scope_st, struct scarl_ast_node *expr_node) {
	
	return 0;
}

// initialization
// make sure to verify the input data 
struct scarl_primitive_type *create_primitive_type(int primitive_type) {
	struct scarl_primitive_type *pt = (struct scarl_primitive_type*)malloc(sizeof(struct scarl_primitive_type));
	pt->type_class = PRIMITIVE_TYPE;
	pt->next = NULL;
	pt->primitive_type = primitive_type;
	return pt;
}

struct scarl_device_type *create_device_type(int device_type) {
	struct scarl_device_type *dt = (struct scarl_device_type*)malloc(sizeof(struct scarl_device_type));
	dt->type_class = DEVICE_TYPE;
	dt->next = NULL;
	dt->device_type = device_type;
	return dt;
}

struct scarl_pointer_type *create_pointer_type(struct scarl_type_descriptor *pointing_to) {
	struct scarl_pointer_type *pt = (struct scarl_pointer_type*)malloc(sizeof(struct scarl_pointer_type));
	pt->type_class = POINTER_TYPE;
	pt->next = NULL;
	pt->pointing_to = pointing_to;
	return pt;
}

struct scarl_array_type *create_array_type(struct scarl_type_descriptor *containing_type, int length) {
	struct scarl_array_type *at = (struct scarl_array_type*)malloc(sizeof(struct scarl_array_type));
	at->type_class = ARRAY_TYPE;
	at->next = NULL;
	at->containing_type = containing_type;
	at->length = length;
	return at;
}

struct scarl_function_type *create_function_type(
		char *func_name,
		struct scarl_type_descriptor *return_type, 
		struct scarl_type_descriptor *formal_parameters, 
		struct scarl_symbol_table *function_st
) {
	struct scarl_function_type *ft = (struct scarl_function_type*)malloc(sizeof(struct scarl_function_type));
	ft->type_class = FUNCTION_TYPE;
	ft->next = NULL;
	ft->func_name = func_name;
	ft->return_type = return_type;
	ft->formal_parameters = formal_parameters;
	ft->function_st = function_st;
	return ft;
}

struct scarl_class_type *create_class_type(char *class_name_identifier, char *parent_class_identifier, struct scarl_symbol_table *class_st) {
	struct scarl_class_type *ct = (struct scarl_class_type*)malloc(sizeof(struct scarl_class_type));
	ct->type_class = CLASS_TYPE;
	ct->next = NULL;
	ct->class_name_identifier = class_name_identifier;
	ct->parent_class_identifier = parent_class_identifier;
	ct->class_st = class_st;
	return ct;
}

// requires a symbol table to lookup user type (class type) characteristics
struct scarl_type_descriptor *create_type_descriptor_for_entry_identifier(struct scarl_symbol_table *current_scope_st, struct scarl_ast_node *node) {
	// creates the type descriptor node for an ast node 
	// the symbol table is for class descriptors and 
	// array length evaluation
	
	/*
		The kinds of types:
		1. Primitive type
		2. Device type 
		3. Class type ("user type", calls this function recursively)
			a. Does not build symbol table or specifies parent class
		4. Pointer type (calls this function recursively)
		5. Array type (calls this function recursively)
	*/
	
	// store the created type descriptor here
	struct scarl_type_descriptor *returning_td = NULL;
	
	// variables for the switch statement
	struct scarl_primitive_type *prim_td = NULL;
	struct scarl_device_type *dev_td = NULL;
	struct scarl_pointer_type *point_td = NULL;
	struct scarl_array_type *array_td = NULL;
	struct scarl_class_type *class_td = NULL;
	
	int array_length = 0;
	
	switch(node->node_type) {
		case NON_TERMINAL_PRIMITIVE_TYPE:
		{
			prim_td = create_primitive_type(node->type_value);
			returning_td = (struct scarl_type_descriptor*)prim_td;
		}
		break;
		case NON_TERMINAL_DEVICE_TYPE:
		{
			dev_td = create_device_type(node->type_value);
			returning_td = (struct scarl_type_descriptor*)dev_td;
		}
		break;
		case NON_TERMINAL_IDENTIFIER_VALUE:
		{
			// expecting this to be a valid class name / user type
			// this is for identification purposes for a formal 
			// parameter list, so it is not a full class definition
			// -- this is something that will be acknowledged in implementing
			// 
			class_td = create_class_type(strdup(node->str_value), NULL, NULL);
			returning_td = (struct scarl_type_descriptor*)class_td;
		}
		break;
		case NON_TERMINAL_POINTER_TYPE:
		{
			//contains other types - create recursively
			point_td = create_pointer_type(
				// recursive data structure
				create_type_descriptor_for_entry_identifier(current_scope_st, node->first_child)
			);
			returning_td = (struct scarl_type_descriptor*)point_td;
		}
		break;
		case NON_TERMINAL_ARRAY_TYPE:
		{
			//contains other types - create recursively
			//the "length" node must be a constant expression
			if (is_constant_expression(current_scope_st, node->first_child->next_sibling)) {
				array_length = eval_constant_expression(current_scope_st, node->first_child->next_sibling);
				array_td = create_array_type(
					create_type_descriptor_for_entry_identifier(current_scope_st, node->first_child),
					array_length
				);
				returning_td = (struct scarl_type_descriptor*)array_td;
			}
			else {
				// not constant, explode 
				// or even better, raise an error here 
				// about an array length 
				// not being a constant expression
			}
		}
		break;
	}
	assert(returning_td != NULL);
	return returning_td;
}

// assuming that the entire definition is there
// for applicable nodes 
// so that all type information can be created
struct scarl_type_descriptor *create_type_descriptor_for_symbol_table(struct scarl_symbol_table *current_scope, struct scarl_ast_node *node) {
	
	return NULL;
}



// "shallow" comparison, putting faith in
// the other parts of the compiler --
// focus on the values that were
// created in the "for entry identifier" function
// except for the function type, where the parameter list is 
// the one to focus on
int compare_type_descriptors(struct scarl_type_descriptor *lhs, struct scarl_type_descriptor *rhs) {
	if (lhs->type_class != rhs->type_class) {
		return 0; // can't be equal if type classes are different
	}
	
	// variables to cast to 
	struct scarl_primitive_type *lhs_prim_td = NULL;
	struct scarl_primitive_type *rhs_prim_td = NULL;
	struct scarl_device_type *lhs_dev_td = NULL;
	struct scarl_device_type *rhs_dev_td = NULL;
	struct scarl_pointer_type *lhs_point_td = NULL;
	struct scarl_pointer_type *rhs_point_td = NULL;
	struct scarl_array_type *lhs_array_td = NULL;
	struct scarl_array_type *rhs_array_td = NULL;
	struct scarl_function_type *lhs_func_td = NULL;
	struct scarl_function_type *rhs_func_td = NULL;
	struct scarl_class_type *lhs_class_td = NULL;
	struct scarl_class_type *rhs_class_td = NULL;
	
	int cmp_res = 0;
	
	// comparison is different for different type classes 
	// it is already established that they are the same class 
	switch(lhs->type_class) {
		case PRIMITIVE_TYPE:
		{
			lhs_prim_td = (struct scarl_primitive_type*)lhs;
			rhs_prim_td = (struct scarl_primitive_type*)rhs;
			return lhs_prim_td->primitive_type == rhs_prim_td->primitive_type;
		}
		break;
		case POINTER_TYPE:
		{
			lhs_point_td = (struct scarl_pointer_type*)lhs;
			rhs_point_td = (struct scarl_pointer_type*)rhs;
			// recursive call to pointing to type
			cmp_res = compare_type_descriptors(lhs_point_td->pointing_to, rhs_point_td->pointing_to);
			return cmp_res;
		}
		break;
		case ARRAY_TYPE:
		{
			lhs_array_td = (struct scarl_array_type*)lhs;
			rhs_array_td = (struct scarl_array_type*)rhs;
			// recursive call to containing type
			cmp_res = compare_type_descriptors(lhs_array_td->containing_type, rhs_array_td->containing_type);
			return cmp_res && lhs_array_td->length == rhs_array_td->length;
		}
		break;
		case FUNCTION_TYPE:
		{
			lhs_func_td = (struct scarl_function_type*)lhs;
			rhs_func_td = (struct scarl_function_type*)rhs;
			return strcmp(lhs_func_td->func_name, rhs_func_td->func_name) == 0;
		}
		break;
		case CLASS_TYPE:
		{
			lhs_class_td = (struct scarl_class_type*)lhs;
			rhs_class_td = (struct scarl_class_type*)rhs;
			return strcmp(lhs_class_td->class_name_identifier, rhs_class_td->class_name_identifier) == 0;
		}
		break;
		case DEVICE_TYPE:
		{
			lhs_dev_td = (struct scarl_device_type*)lhs;
			rhs_dev_td = (struct scarl_device_type*)rhs;
			return lhs_dev_td->device_type == rhs_dev_td->device_type;
		}
		break;
	}
	return 0;
}

void append_type_descriptor(struct scarl_type_descriptor *lst, struct scarl_type_descriptor *adding) {
	if (lst->next == NULL) {
		lst->next = adding;
	}
	else {
		struct scarl_type_descriptor *td = lst;
		while (td->next == NULL) {
			td = td->next;
		}
		td->next = adding;
	}
}

int get_type_descriptor_list_count(struct scarl_type_descriptor *lst) {
	if (lst->next == NULL) {
		return 1;
	}
	else {
		struct scarl_type_descriptor *td = lst;
		int count = 0;
		while(td->next != NULL) {
			td = td->next;
			count++;
		}
		return count;
	}
}