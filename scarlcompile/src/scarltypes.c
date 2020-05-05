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
#include "y.tab.h"

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

/* This function attempts to figure out which type the expression will eventually be converted to,    */
/* taking the "most straightforward" approach to guessing, given its context (symbol table)    */
struct scarl_type_descriptor *assume_type_of_expression_st(struct scarl_symbol_table *current_scope_st, struct scarl_ast_node *expr_node) {
	
	
	return NULL;
}

/* Determines if the expression can be converted to a requested type given its context (symbol table)  */
int can_coerce_expression_to_type_class(struct scarl_symbol_table *current_scope_st, struct scarl_ast_node *expr_node, struct scarl_type_descriptor *type) {
	return 0;
}

// declare for recursive call
int is_constant_expression_r(struct scarl_symbol_table *current_scope_st, struct scarl_ast_node *expr_node);

int is_constant_expression_r(struct scarl_symbol_table *current_scope_st, struct scarl_ast_node *expr_node) {
	// assumed true until proven false
	int is_constant = 1;
	if (is_int_value_node(expr_node)) {
		return 1;
	} else if (is_int_operator_node(expr_node)) {
		int child_count = get_children_count(expr_node);
		assert(child_count == 1 || child_count == 2);
		if (child_count == 1) {
			return is_constant_expression_r(current_scope_st, expr_node->first_child);
		} else if (child_count == 2) {
			return is_constant_expression_r(current_scope_st, expr_node->first_child);
			return is_constant_expression_r(current_scope_st, expr_node->first_child->next_sibling);
		}
	} 
	else if (is_str_value_node(expr_node)) {
		// this is an identifier to lookup in the current scope
		struct scarl_symbol_table_entry *entry = lookup_char_str(current_scope_st, expr_node->str_value);
		if (entry == NULL) {
			return 0; // does not exists in this scope
		}
		else {
			return entry->is_constant;
		}
	}
	// may discover more situations down the road and in testing
	else {
		return 0;
	}
	return is_constant;
}

/* Determines if the expression is constant. That is, is its value deterministic at compile time? TRUE/FALSE */
int is_constant_expression(struct scarl_symbol_table *current_scope_st, struct scarl_ast_node *expr_node) {
	// determined recursively 
	// assumed true until proven false
	return is_constant_expression_r(current_scope_st, expr_node);
}


int eval_constant_expression_r(struct scarl_symbol_table *current_scope_st, struct scarl_ast_node *expr_node);

int eval_constant_expression_r(struct scarl_symbol_table *current_scope_st, struct scarl_ast_node *expr_node) {
	// this function is only called if it passes the is_constant_expression function
	if (is_int_value_node(expr_node)) {
		return expr_node->int_value;
	} else if (is_int_operator_node(expr_node)) {
		int child_count = get_children_count(expr_node);
		assert(child_count == 1 || child_count == 2);
		if (child_count == 1) {
			if (expr_node->type_value == MINUS) {
				return -eval_constant_expression_r(current_scope_st, expr_node->first_child);
			}
		} else if (child_count == 2) {
			if (expr_node->type_value == PLUS) {
				return eval_constant_expression_r(current_scope_st, expr_node->first_child)
						+ eval_constant_expression_r(current_scope_st, expr_node->first_child->next_sibling);
			}
			else if (expr_node->type_value == MINUS) {
				return eval_constant_expression_r(current_scope_st, expr_node->first_child)
						- eval_constant_expression_r(current_scope_st, expr_node->first_child->next_sibling);
			}
			else if (expr_node->type_value == STAR) {
				return eval_constant_expression_r(current_scope_st, expr_node->first_child)
						* eval_constant_expression_r(current_scope_st, expr_node->first_child->next_sibling);
			}
			else if (expr_node->type_value == SLASH) {
				return eval_constant_expression_r(current_scope_st, expr_node->first_child)
						/ eval_constant_expression_r(current_scope_st, expr_node->first_child->next_sibling);
			}
		}
	} 
	else if (is_str_value_node(expr_node)) {
		// this is an identifier to lookup in the current scope
		struct scarl_symbol_table_entry *entry = lookup_char_str(current_scope_st, expr_node->str_value);
		return entry->compile_time_value;
	}
}

/* Gets the compile time value of a constant expression */
int eval_constant_expression(struct scarl_symbol_table *current_scope_st, struct scarl_ast_node *expr_node) {
	// this function is only called if it passes the is_constant_expression function
	return eval_constant_expression_r(current_scope_st, expr_node);
}

// !, &&, ||, <, >, <=, >=, ==
int is_bool_operator_node(struct scarl_ast_node *node) {
	if (node->node_type == NON_TERMINAL_OPERAND_VALUE) {
		return node->type_value == BANG ||
			node->type_value == LESS_EQ ||
			node->type_value == GTR_EQ ||
			node->type_value == LESS ||
			node->type_value == GTR ||
			node->type_value == NOT_EQ ||
			node->type_value == DBL_EQ ||
			node->type_value == AND ||
			node->type_value == OR;
	}
	else {
		return 0;
	}
}

// +, -, *, /
int is_int_operator_node(struct scarl_ast_node *node) {
	if (node->node_type == NON_TERMINAL_OPERAND_VALUE) {
		return node->type_value == PLUS ||
			node->type_value == MINUS ||
			node->type_value == STAR ||
			node->type_value == SLASH;
	}
	else {
		return 0;
	}
}

// constant int value
int is_int_value_node(struct scarl_ast_node *node) {
	return node->node_type == NON_TERMINAL_INTEGER_VALUE;
}

// identifier node
int is_str_value_node(struct scarl_ast_node *node) {
	return node->node_type == NON_TERMINAL_IDENTIFIER_VALUE;
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
	
	//printf("Creating type descriptor for entry identifier node type: %s\n", get_ast_node_type_string(node->node_type));
	
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
			char *class_name = strdup(node->str_value);
			//see if a parent class exists to attach to the type descriptor
			char *parent_class = NULL;
			struct scarl_symbol_table_entry *class_entry = lookup_char_str(current_scope_st, class_name);
			struct scarl_class_type *base_class_td = (struct scarl_class_type *)class_entry->type;
			if (base_class_td->parent_class_identifier != NULL) {
				parent_class = strdup(base_class_td->parent_class_identifier);
			}
			class_td = create_class_type(class_name, parent_class, NULL);
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


struct scarl_type_descriptor *create_type_descriptor_list_from_formal_parameter_node(struct scarl_symbol_table *current_scope, struct scarl_ast_node *formal_param_node) {
	int formal_param_count = get_children_count(formal_param_node);
	struct scarl_type_descriptor *formal_parameter_td_list = NULL; // the list of type descriptors that describe this function (to support overloading)
	if (formal_param_count > 0) {
		struct scarl_ast_node *fp_to_process = formal_param_node->first_child;
		//if (debug_st) {
		//	printf("creating the type descriptor for the entry identifier from the first formal parameter\n");
		//	printf("node type of first formal parameter: %s\n", get_ast_node_type_string(fp_to_process->first_child->node_type));
		//}
		formal_parameter_td_list = create_type_descriptor_for_entry_identifier(current_scope, fp_to_process->first_child);
		fp_to_process = fp_to_process->next_sibling;
		for (int i = 1; i <formal_param_count; i++) {
			//if (debug_st) {
			//	printf("creating the type descriptor for the entry identifier from formal parameters %i\n", i);
			//}
			struct scarl_type_descriptor *current_fp_td = create_type_descriptor_for_entry_identifier(current_scope, fp_to_process->first_child);
			append_type_descriptor(formal_parameter_td_list, current_fp_td);
			fp_to_process = fp_to_process->next_sibling;
		}
	}
	return formal_parameter_td_list;
}


/*
// assuming that the entire definition is there
// for applicable nodes 
// so that all type information can be created
struct scarl_type_descriptor *create_type_descriptor_for_symbol_table(struct scarl_symbol_table *current_scope, struct scarl_ast_node *node) {
	
	return NULL;
}
*/


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
		while (td->next != NULL) {
			td = td->next;
		}
		td->next = adding;
	}
}

int get_type_descriptor_list_count(struct scarl_type_descriptor *lst) {
	if (lst == NULL) {
		return 0;
	}
	else {
		struct scarl_type_descriptor *td = lst;
		int count = 0;
		while(td != NULL) {
			td = td->next;
			count++;
		}
		return count;
	}
}

// returns the size of the type in bytes. Used in calculating symbol table frame size
int size_of_scarl_type(struct scarl_type_descriptor *type, struct scarl_symbol_table *st) {
	
	
	switch(type->type_class) {
		case PRIMITIVE_TYPE:
		{
			struct scarl_primitive_type *prim = (struct scarl_primitive_type *)type;
			switch(prim->primitive_type) {
				case BOOL: return 1;
				case VOID: return 0;
				case CHAR: return 1;
				case BYTE: return 1;
				case INT: return 2; 
			}
		}
		break;
		case POINTER_TYPE:
		{
			return 2; // 2^16 address space
		}
		break;
		case ARRAY_TYPE:
		{
			int containedSize;
			struct scarl_array_type *arrType = (struct scarl_array_type *)type;
			containedSize = size_of_scarl_type(arrType->containing_type, st);
			return arrType->length*containedSize;
		}
		break;
		case FUNCTION_TYPE:
		{
			return 0; // instances of functions don't use stack space (they indicate stack pushes) 
		}
		break;
		case CLASS_TYPE:
		{
			struct scarl_class_type *orig_class_type = (struct scarl_class_type*)type;
			char *class_name = orig_class_type->class_name_identifier;
			char *parent_name = orig_class_type->parent_class_identifier;
			
			/*
			printf("Getting size of %s\n", class_name);
			if (parent_name != NULL) {
				printf("this class has parent class %s\n", parent_name);
			}
			*/
			
			struct scarl_symbol_table_entry *class_full_def = lookup_char_str(st, class_name);
			assert(class_full_def != NULL); // class name must be defined
			struct scarl_symbol_table *class_table = ((struct scarl_class_type*)class_full_def->type)->class_st;
			struct scarl_symbol_table_entry *cur_entry = class_table->entries;
			int sumSize = 0;
			while (cur_entry != NULL) {
				sumSize += size_of_scarl_type(cur_entry->type, st);
				cur_entry = cur_entry->next;
			}
			
			// add the size of the parent class type as well
			if (parent_name != NULL) {
				struct scarl_symbol_table_entry *parent_full_def = lookup_char_str(st, parent_name);
				int parent_size = size_of_scarl_type(parent_full_def->type, st);
				sumSize += parent_size;
			}
			
			printf("Size of %s is %i\n", class_name, sumSize);
			return sumSize;
		}
		break;
		case DEVICE_TYPE:
		{
			return 0; // instances of devices don't use stack space
		}
		break;
	}
	// should not reach this point 
	return 0;
}

char *get_type_class_str(int type_class) {
	if (type_class == PRIMITIVE_TYPE) { return "PRIMITIVE_TYPE"; }
	else if (type_class == POINTER_TYPE) { return "POINTER_TYPE"; }
	else if (type_class == ARRAY_TYPE) { return "ARRAY_TYPE"; }
	else if (type_class == FUNCTION_TYPE) { return "FUNCTION_TYPE"; }
	else if (type_class == CLASS_TYPE) { return "CLASS_TYPE"; }
	else if (type_class == DEVICE_TYPE) { return "DEVICE_TYPE"; }
}

