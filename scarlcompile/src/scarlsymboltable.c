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

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "scarlastnode.h"
#include "scarlsymboltable.h"

const unsigned debug_st = 1;

// symbol table construct initialization functions
struct scarl_symbol_table *create_st() {
	struct scarl_symbol_table *st = (struct scarl_symbol_table*)malloc(sizeof(struct scarl_symbol_table));
	st->entries = NULL;
	st->parent_st = NULL;
	st->next_sibling = NULL;
	st->first_child = NULL;
	return st;
}

struct scarl_symbol_table *create_st_from_ast(
		struct scarl_symbol_table *current_scope_st, 
		struct scarl_symbol_table *st, // the newly created st, responsibility of the callee
		struct scarl_ast_node *node
) {
	//struct scarl_symbol_table *st = create_st();
	
	if (debug_st) {
		//printf("Creating symbol table from st: top-level node is of type %s\n", get_ast_node_type_string(node->node_type)); 
	}
	
	// add this to the parent st if it exists
	if (current_scope_st != NULL) {
		if (debug_st) {
			//printf("Adding this symbol table as a child of another symbol table\n");
		}
		add_child_st(current_scope_st, st); // to be able to search parent scope
	}
	
	// variables used 
	struct scarl_ast_node *statement = NULL;
	struct scarl_ast_node *statement_block_level = NULL;
	struct scarl_ast_node *class_attribute = NULL;
		
	/*
		For each context,
		1. Construct entry
		2. Create symbol table recursively if necessary, set other properties
		3. Add entry to this symbol table,
		4. Add symbol table children if necessary
	*/
	switch(node->node_type) {
		case NON_TERMINAL_STATEMENT_LIST:
		{
			// we are creating the root symbol table
			assert(current_scope_st == NULL); // no scope above this one
			// iterate through 
			statement = node->first_child;
			while(statement != NULL) {
				switch(statement->node_type) {
					case NON_TERMINAL_VARIABLE_DEFINITION_STATEMENT:
					{
						//if (debug_st) { 
						//	printf("statement_list variable_definition_statement\n");
						//}
						
						struct scarl_ast_node *type_node = statement->first_child->first_child;
						struct scarl_ast_node *ident_node = statement->first_child->first_child->next_sibling;
						struct scarl_type_descriptor *type_desc = create_type_descriptor_for_entry_identifier(st, type_node);
						struct scarl_symbol_table_entry_identifier *var_def_ident = create_st_entry_identifier(strdup(ident_node->str_value), NULL);
						struct scarl_symbol_table_entry *var_def_entry = create_st_entry(var_def_ident, type_desc);
						var_def_entry->defined = 1;
						add_st_entry(st, var_def_entry);
					}	
					break;
					case NON_TERMINAL_VARIABLE_DECLARATION_STATEMENT:
					{
						//if (debug_st) {
						//	printf("statement_list variable_declaration_statement\n");
						//}
						
						struct scarl_ast_node *type_node = statement->first_child->first_child;
						struct scarl_ast_node *ident_node = statement->first_child->first_child->next_sibling;
						struct scarl_type_descriptor *type_desc = create_type_descriptor_for_entry_identifier(st, type_node);
						struct scarl_symbol_table_entry_identifier *var_decl_ident = create_st_entry_identifier(strdup(ident_node->str_value), NULL);
						struct scarl_symbol_table_entry *var_decl_entry = create_st_entry(var_decl_ident, type_desc);
						var_decl_entry->defined = 0;
						add_st_entry(st, var_decl_entry);
					}						
					break;
					case NON_TERMINAL_CONSTANT_DEFINITION_STATEMENT:
					{
						//if (debug_st) {
						//	printf("statement_list constant_definition_statement\n");
						//}
						
						struct scarl_ast_node *type_node = statement->first_child->first_child;
						struct scarl_ast_node *ident_node = statement->first_child->first_child->next_sibling;
						struct scarl_type_descriptor *type_desc = create_type_descriptor_for_entry_identifier(st, type_node);
						struct scarl_symbol_table_entry_identifier *var_const_ident = create_st_entry_identifier(strdup(ident_node->str_value), NULL);
						struct scarl_symbol_table_entry *var_const_entry = create_st_entry(var_const_ident, type_desc);
						var_const_entry->defined = 1;
						var_const_entry->is_constant = 1;
						// evaluate the expression 
						struct scarl_ast_node *expr_node = statement->first_child->next_sibling;
						if (is_constant_expression(st, expr_node)) {
							var_const_entry->compile_time_value = eval_constant_expression(st, expr_node);
						}
						add_st_entry(st, var_const_entry);
					}
					break;
					case NON_TERMINAL_CLASS_DEFINITION_STATEMENT:
					{
						//if (debug_st){
						//	printf("statement_list class_definition_statement\n");
						//}	
						
						struct scarl_ast_node *class_decl = statement->first_child;
						struct scarl_ast_node *class_attribute_list = statement->first_child->next_sibling;
						int class_decl_child_count = get_children_count(class_decl);
						char *class_name = NULL;
						char *parent_class = NULL;
						if (class_decl_child_count == 1) {
							class_name = strdup(class_decl->first_child->str_value);
						}
						else if (class_decl_child_count == 2) {
							class_name = strdup(class_decl->first_child->str_value);
							// the parent class is the one this class "extends" from
							parent_class = strdup(class_decl->first_child->next_sibling->str_value);
						}
						else {
							fprintf(stderr, "A class declarator has more than 2 child nodes\n");
							assert(0);
						}
						struct scarl_symbol_table *class_body_st = create_st();
						struct scarl_symbol_table *class_st = create_st_from_ast(st, class_body_st, class_attribute_list); // recursive call
						struct scarl_class_type *class_type_desc = create_class_type(class_name, parent_class, class_st);
						struct scarl_symbol_table_entry_identifier *class_ident = create_st_entry_identifier(strdup(class_name), NULL);
						struct scarl_symbol_table_entry *class_entry = create_st_entry(class_ident, (struct scarl_type_descriptor*)class_type_desc);
						class_entry->defined = 1;
						add_st_entry(st, class_entry);
					}
					break;
					case NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT:
					{
						//if (debug_st) {
						//	printf("statement_list function_definition_statement\n");
						//}
						
						struct scarl_ast_node *return_type_node = statement->first_child;
						struct scarl_ast_node *func_ident_node = statement->first_child->next_sibling;
						struct scarl_ast_node *formal_param_node = statement->first_child->next_sibling->next_sibling;
						struct scarl_ast_node *func_body_node = statement->first_child->next_sibling->next_sibling->next_sibling;

						//create_function_type(char *func_name, 
						//	   struct type_descriptor *return_type,
						//	   struct scarl_type_descriptor *formal_parameters, 
						//	   struct scarl_symbol_table *function_st
						//);
						
						//if (debug_st) {
						//	printf("creating return type descriptor for function type \n");
						//}
						struct scarl_type_descriptor *return_type_desc = create_type_descriptor_for_entry_identifier(st, return_type_node);
						//if (debug_st) {
						//	printf("counting the number of formal parameters in the function\n");
						//}
						int formal_param_count = get_children_count(formal_param_node);
						if (debug_st) {
							printf("This function has %i formal parameters\n", formal_param_count);
						}
						struct scarl_type_descriptor *formal_parameter_td_list = NULL; // the list of type descriptors that describe this function (to support overloading)
						if (formal_param_count > 0) {
							struct scarl_ast_node *fp_to_process = formal_param_node->first_child;
							//if (debug_st) {
							//	printf("creating the type descriptor for the entry identifier from the first formal parameter\n");
							//	printf("node type of first formal parameter: %s\n", get_ast_node_type_string(fp_to_process->first_child->node_type));
							//}
							formal_parameter_td_list = create_type_descriptor_for_entry_identifier(st, fp_to_process->first_child);
							fp_to_process = fp_to_process->next_sibling;
							for (int i = 1; i < formal_param_count; i++) {
								//if (debug_st) {
								//	printf("creating the type descriptor for the entry identifier from formal parameters %i\n", i);
								//}
								struct scarl_type_descriptor *current_fp_td = create_type_descriptor_for_entry_identifier(st, fp_to_process->first_child);
								append_type_descriptor(formal_parameter_td_list, current_fp_td);
								fp_to_process = fp_to_process->next_sibling;
								
							}
						}
						// reusing the same list and string, which should be ok as long as they are only read from 
						// need to test this intensely or just pay attention to code 
						struct scarl_symbol_table_entry_identifier* func_entry_identifier = create_st_entry_identifier(func_ident_node->str_value, formal_parameter_td_list);
						
						// need to stamp down architecture for this 
						// function types need a type descriptor list for both
						// formal parameters and entry identifiers?
						
						struct scarl_symbol_table *function_body_st = create_st();
						
						//  add formal parameters to symbol table before processing
						if (formal_param_count > 0) {
							struct scarl_ast_node *fp_to_process = formal_param_node->first_child;
							while (fp_to_process != NULL) {
								struct scarl_ast_node *fp_type_node = fp_to_process->first_child;
								struct scarl_ast_node *fp_ident_node = fp_to_process->first_child->next_sibling;
								struct scarl_type_descriptor *fp_type_desc = create_type_descriptor_for_entry_identifier(st, fp_type_node);
								struct scarl_symbol_table_entry_identifier *fp_var_decl_ident = create_st_entry_identifier(strdup(fp_ident_node->str_value), NULL);
								struct scarl_symbol_table_entry *fp_var_decl_entry = create_st_entry(fp_var_decl_ident, fp_type_desc);
								fp_var_decl_entry->defined = 0;
								add_st_entry(function_body_st, fp_var_decl_entry);
								fp_to_process = fp_to_process->next_sibling;
							}
						}
						
						struct scarl_symbol_table *function_st = create_st_from_ast(st, function_body_st, func_body_node);
						struct scarl_function_type *func_type_desc = create_function_type(
							func_ident_node->str_value,
							return_type_desc,
							formal_parameter_td_list,
							function_st
						);
						
						struct scarl_symbol_table_entry *func_entry = create_st_entry(func_entry_identifier, (struct scarl_type_descriptor*)func_type_desc);
						func_entry->defined = 1;
						add_st_entry(st, func_entry);
					}
					break;
				}
				statement = statement->next_sibling;
			}
		}
		break;
		case NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL:
		{
			// a function body
			assert(current_scope_st != NULL); // must be in a scope
			// iterate through 
			statement_block_level = node->first_child;
			while(statement_block_level != NULL) {
				switch(statement_block_level->node_type) {
					case NON_TERMINAL_VARIABLE_DEFINITION_STATEMENT:
					{
						//if (debug_st) printf("statement_list_block_level variable_definition_statement\n");
						// define this variable as the expression (1 new symbol table entry)
						struct scarl_ast_node *type_node = statement_block_level->first_child->first_child;
						struct scarl_type_descriptor *type_desc_var = create_type_descriptor_for_entry_identifier(st, type_node);
						struct scarl_ast_node *ident_node = type_node->next_sibling;
						struct scarl_symbol_table_entry_identifier *var_def_ident = create_st_entry_identifier(strdup(ident_node->str_value), NULL);
						struct scarl_symbol_table_entry *var_def_entry = create_st_entry(var_def_ident, type_desc_var);
						//if (statement_block_level->first_child->first_child->node_type == NON_TERMINAL_IDENTIFIER_VALUE && debug_st) {
						//	printf("Parsing a variable with a user defined type %s\n", type_node->str_value);
						//	printf("this user defined type has identifier: %s\n", ident_node->str_value);
						//}
						var_def_entry->defined = 1;
						add_st_entry(st, var_def_entry);
					}
					break;
					case NON_TERMINAL_VARIABLE_DECLARATION_STATEMENT:
					{
						//if (debug_st) printf("statement_list_block_level variable_declaration_statement\n");
						// declare this variable (1 new symbol table entry)
						struct scarl_type_descriptor *type_desc_var = create_type_descriptor_for_entry_identifier(st, statement_block_level->first_child->first_child);
						struct scarl_ast_node *ident_node = statement_block_level->first_child->first_child->next_sibling;
						struct scarl_symbol_table_entry_identifier *var_decl_ident = create_st_entry_identifier(strdup(ident_node->str_value), NULL);
						struct scarl_symbol_table_entry *var_decl_entry = create_st_entry(var_decl_ident, type_desc_var);
						var_decl_entry->defined = 0;
						add_st_entry(st, var_decl_entry);
					}
					break;
					case NON_TERMINAL_VARIABLE_SET_STATEMENT:
					{
						//if (debug_st) printf("statement_list_block_level variable_set_statement\n");
						// set the variable (no new symbol table entry)
						
					}
					break;
					case NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL:
					{
						//if (debug_st) printf("statement_list_block_level statement_list_block_level\n");
						// recursive call to this function (no new symbol table entry)
						struct scarl_symbol_table *block_internal_st = create_st();
						struct scarl_symbol_table *block_st = create_st_from_ast(st, block_internal_st, statement_block_level);
					}
					break;
					case NON_TERMINAL_FUNCTION_INVOCATION:
					{
						// call this function (no new symbol table entry)
						//if (debug_st) printf("statement_list_block_level function_invocation\n");
						
					}
					break;
					case NON_TERMINAL_METHOD_INVOCATION:
					{
						// call this method (no new symbol table entry)
						//if (debug_st) printf("statement_list_block_level method_invocation\n");
						
					}
					break;
					case NON_TERMINAL_IF_BLOCK_STATEMENT:
					{
						// if statement (no new symbol table entry)
						//if (debug_st) printf("statement_list_block_level if_block_statement\n");
						
						int child_count = get_children_count(statement_block_level);
						if (child_count == 2) {
							struct scarl_symbol_table *if_internal_block = create_st();
							struct scarl_symbol_table *if_block = create_st_from_ast(st, if_internal_block, statement_block_level->first_child->next_sibling);
							//add_child_st(st, if_block); // already added - see the start of this function
						}
						else if (child_count == 3) {
							struct scarl_symbol_table *if_internal_block = create_st();
							struct scarl_symbol_table *if_block = create_st_from_ast(st, if_internal_block, statement_block_level->first_child->next_sibling);
							struct scarl_symbol_table *else_internal_block = create_st();
							struct scarl_symbol_table *else_block = create_st_from_ast(st, else_internal_block, statement_block_level->first_child->next_sibling->next_sibling);
							//add_child_st(st, if_block); // already added - see the start of this function
							//add_child_st(st, else_block); // already added - see the start of this function
						}
					}
					break;
					case NON_TERMINAL_WHILE_BLOCK_STATEMENT:
					{
						// while statement (no new symbol table entry)
						//if (debug_st) printf("statement_list_block_level while_block_statement\n");
						
						struct scarl_symbol_table *internal_while_block = create_st();
						struct scarl_symbol_table *while_block = create_st_from_ast(st, internal_while_block, statement_block_level->first_child->next_sibling);
						//add_child_st(st, while_block); // already added - see the start of this function
					}
					break;
					case NON_TERMINAL_DELETE_STATEMENT:
					{
						// delete statement (no new symbol table entry)
						//if (debug_st) printf("statement_list_block_level delete_statement\n");
						
					}
					break;
				}
				statement_block_level = statement_block_level->next_sibling;
			}
		}
		break;
		// should this be here or moved to its own function?
		case NON_TERMINAL_CLASS_ATTRIBUTE_LIST:
		{
			// a class body
			assert(current_scope_st != NULL); // must be in a scope
			class_attribute = node->first_child;
			while(class_attribute != NULL) {
					switch(class_attribute->node_type) {
						case NON_TERMINAL_VARIABLE_DECLARATION_STATEMENT:
						{
							// add a class attribute to this class (1 new entry)
							//if (debug_st) printf("class_attribute variable_declaration\n");
							
							struct scarl_type_descriptor *type_desc_var = create_type_descriptor_for_entry_identifier(st, class_attribute->first_child->first_child);
							struct scarl_ast_node *ident_node = class_attribute->first_child->first_child->next_sibling;
							struct scarl_symbol_table_entry_identifier *var_decl_ident = create_st_entry_identifier(strdup(ident_node->str_value), NULL);
							struct scarl_symbol_table_entry *var_decl_entry = create_st_entry(var_decl_ident, type_desc_var);
							var_decl_entry->defined = 0;
							add_st_entry(st, var_decl_entry);
						}
						break;
						case NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT:
						{
							// define a new method for this class (1 new entry)
							//if (debug_st) printf("class_attribute function_definition_statement\n");
							
							// copy and pasted from NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT above.....
							
							struct scarl_ast_node *return_type_node = class_attribute->first_child;
							struct scarl_ast_node *func_ident_node = class_attribute->first_child->next_sibling;
							struct scarl_ast_node *formal_param_node = class_attribute->first_child->next_sibling->next_sibling;
							struct scarl_ast_node *func_body_node = class_attribute->first_child->next_sibling->next_sibling->next_sibling;

							//create_function_type(char *func_name, 
							//	   struct type_descriptor *return_type,
							//	   struct scarl_type_descriptor *formal_parameters, 
							//	   struct scarl_symbol_table *function_st
							//);
							
							//if (debug_st) {
							//	printf("creating return type descriptor for function type \n");
							//}
							struct scarl_type_descriptor *return_type_desc = create_type_descriptor_for_entry_identifier(st, return_type_node);
							//if (debug_st) {
							//	printf("counting the number of formal parameters in the function\n");
							//}
							int formal_param_count = get_children_count(formal_param_node);
							struct scarl_type_descriptor *formal_parameter_td_list = NULL; // the list of type descriptors that describe this function (to support overloading)
							if (formal_param_count > 0) {
								struct scarl_ast_node *fp_to_process = formal_param_node->first_child;
								//if (debug_st) {
								//	printf("creating the type descriptor for the entry identifier from the first formal parameter\n");
								//	printf("node type of first formal parameter: %s\n", get_ast_node_type_string(fp_to_process->first_child->node_type));
								//}
								formal_parameter_td_list = create_type_descriptor_for_entry_identifier(st, fp_to_process->first_child);
								fp_to_process = fp_to_process->next_sibling;
								for (int i = 1; i <formal_param_count; i++) {
									//if (debug_st) {
									//	printf("creating the type descriptor for the entry identifier from formal parameters %i\n", i);
									//}
									struct scarl_type_descriptor *current_fp_td = create_type_descriptor_for_entry_identifier(st, fp_to_process->first_child);
									append_type_descriptor(formal_parameter_td_list, current_fp_td);
									fp_to_process = fp_to_process->next_sibling;
								}
							}
							// reusing the same list and string, which should be ok as long as they are only read from 
							// need to test this intensely or just pay attention to code 
							struct scarl_symbol_table_entry_identifier* func_entry_identifier = create_st_entry_identifier(func_ident_node->str_value, formal_parameter_td_list);
							
							// need to stamp down architecture for this 
							// function types need a type descriptor list for both
							// formal parameters and entry identifiers?
							
							struct scarl_symbol_table *function_body_st = create_st();
							
							// add formal parameters to symbol table before processing
							if (formal_param_count > 0) {
								struct scarl_ast_node *fp_to_process = formal_param_node->first_child;
								while (fp_to_process != NULL) {
									struct scarl_ast_node *fp_type_node = fp_to_process->first_child;
									struct scarl_ast_node *fp_ident_node = fp_to_process->first_child->next_sibling;
									struct scarl_type_descriptor *fp_type_desc = create_type_descriptor_for_entry_identifier(st, fp_type_node);
									struct scarl_symbol_table_entry_identifier *fp_var_decl_ident = create_st_entry_identifier(strdup(fp_ident_node->str_value), NULL);
									struct scarl_symbol_table_entry *fp_var_decl_entry = create_st_entry(fp_var_decl_ident, fp_type_desc);
									fp_var_decl_entry->defined = 0;
									add_st_entry(function_body_st, fp_var_decl_entry);
									fp_to_process = fp_to_process->next_sibling;
								}
							}
						
							struct scarl_symbol_table *function_st = create_st_from_ast(st, function_body_st, func_body_node);
							struct scarl_function_type *func_type_desc = create_function_type(
								func_ident_node->str_value,
								return_type_desc,
								formal_parameter_td_list,
								function_st
							);
							
							struct scarl_symbol_table_entry *func_entry = create_st_entry(func_entry_identifier, (struct scarl_type_descriptor*)func_type_desc);
							func_entry->defined = 1;
							add_st_entry(st, func_entry);
						}
						break;
					}
					class_attribute = class_attribute->next_sibling;
			}
		}
		break; 
		default:
			// invalid 
			free(st);
			st = NULL;
	}
	assert(st != NULL);
	printf("Finished processing this symbol table with %i entries\n", get_entry_count(st));
	return st;
}

struct scarl_symbol_table_entry *create_st_entry(
		struct scarl_symbol_table_entry_identifier *ident, 
		struct scarl_type_descriptor *type
) {
	struct scarl_symbol_table_entry *entry = (struct scarl_symbol_table_entry*)malloc(sizeof(struct scarl_symbol_table_entry));
    entry->ident = ident;
	entry->next = NULL; // set when an entry is added to the symbol table it is in
    entry->type = type;
	entry->is_constant = 0; //false by default
	entry->defined = 0; //false by default, remember to change when defined
    entry->containing_st = NULL; // set when added to a symbol table 
	return entry;
}

struct scarl_symbol_table_entry_identifier *create_st_entry_identifier(
		char *ident_str, 
		struct scarl_type_descriptor *parameter_list // parameter list already built
) { 
	struct scarl_symbol_table_entry_identifier *id = (struct scarl_symbol_table_entry_identifier*)malloc(sizeof(struct scarl_symbol_table_entry_identifier));
	id->ident_str = ident_str; // don't copy unless it seems to become necessary
	id->parameter_list = parameter_list;
	return id;
}

struct scarl_symbol_table_entry_identifier *create_st_entry_identifier_var(char *ident_str, int param_count, ...) {
	// a variable number of type descriptors for creating 
	// a parameter list on the fly (first one is the head)
	va_list ap;
	va_start(ap, param_count);
	int i;
	struct scarl_type_descriptor *lst = va_arg(ap, struct scarl_type_descriptor*);
	for (i = 1; i < param_count; i++) {
		struct scarl_type_descriptor *next_param = va_arg(ap, struct scarl_type_descriptor*);
		append_type_descriptor(lst, next_param);
	}
	
	struct scarl_symbol_table_entry_identifier *id = (struct scarl_symbol_table_entry_identifier*)malloc(sizeof(struct scarl_symbol_table_entry_identifier));
	id->ident_str = ident_str; // don't copy unless it seems to become necessary
	id->parameter_list = lst;
	
	va_end(ap);
	return id;
}

/*
struct scarl_symbol_table_entry_identifier *create_st_entry_identifier_from_ast_node(struct scarl_symbol_table *current_scope_st, struct scarl_ast_node *node) { 
	// direct from the AST
	
	// must pay attention to the type of the node 
	// to know how to create it 
	
	/*
		A list of ast nodes that can be used to create entries 
		1. Variable Declarator statement 
		2. Variable Definition statement
		3. Constant Variable Definition statement
		4. Function Definition statement
		5. Class Definition statement 
		
		The function is the only one that uses 
		the parameter_list 
	*/
/*
	struct scarl_symbol_table_entry_identifier *returning_entry = NULL;
	char *ident_cpy = NULL;
	
	//function definition variables
	struct scarl_ast_node *fp_node = NULL;
	struct scarl_ast_node *fp_cur_node = NULL;
	int fp_count = 0;
	struct scarl_type_descriptor *fp_list = NULL;
	struct scarl_type_descriptor *current_p = NULL;
	
	switch(node->node_type) {
		// removed device declarator statement /
		// type determined by TYPE_DECLARATOR (DEVICE_TYPE node type)
		//case NON_TERMINAL_DEVICE_DECLARATOR_STATEMENT:
		//	ident_cpy = strdup(node->first_child->next_sibling->str_value);
		//	returning_entry = create_st_entry_identifier(ident_cpy, NULL);
		//break;
		case NON_TERMINAL_VARIABLE_DECLARATION_STATEMENT:
		{
			ident_cpy = strdup(node->first_child->first_child->next_sibling->str_value);
			returning_entry = create_st_entry_identifier(ident_cpy, NULL);
		}
		break;
		case NON_TERMINAL_VARIABLE_DEFINITION_STATEMENT:
		{
			ident_cpy = strdup(node->first_child->first_child->next_sibling->str_value);
			returning_entry = create_st_entry_identifier(ident_cpy, NULL);
		}
		break;
		case NON_TERMINAL_CONSTANT_DEFINITION_STATEMENT:
		{
			ident_cpy = strdup(node->first_child->first_child->next_sibling->str_value);
			returning_entry = create_st_entry_identifier(ident_cpy, NULL);
		}
		break;
		case NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT:
		{
			ident_cpy = strdup(node->first_child->next_sibling->str_value);
			// includes the formal parameter list 
			fp_node = node->first_child->next_sibling->next_sibling;
			fp_cur_node = fp_node;
			fp_count = get_children_count(fp_node);
			// must create distinct type descriptors for identification
			for (int i = 0; i < fp_count; i++) {
				current_p = create_type_descriptor_for_entry_identifier(current_scope_st, fp_cur_node->first_child);
				if (fp_list == NULL) {
					fp_list = current_p;
				}
				else {
					append_type_descriptor(fp_list, current_p);
				}
				fp_cur_node = fp_cur_node->next_sibling;
			}
			// have a newly created parameter list from the list of formal parameters
			returning_entry = create_st_entry_identifier(ident_cpy, fp_list);
		}
		break;
		case NON_TERMINAL_CLASS_DEFINITION_STATEMENT:
		{
			ident_cpy = strdup(node->first_child->first_child->str_value);
			returning_entry = create_st_entry_identifier(ident_cpy, NULL);
		}
		break;
		default:
			fprintf(stderr, "Cannot convert this node into an entry identifier: %s\n", get_ast_node_type_string(node->node_type));
	}
	// invalid 
	assert(returning_entry != NULL);
	return returning_entry;
}
*/

// structure and debugging functions
void add_child_st(struct scarl_symbol_table *parent, struct scarl_symbol_table *adding) {
	assert(parent != NULL && adding != NULL);
	if (parent->first_child == NULL) {
		parent->first_child = adding;
		adding->parent_st = parent;
		if (debug_st) {
			printf("Added a symbol table as the first child to another symbol table\n");
		}
	}
	else {
		int nth = 1;
		struct scarl_symbol_table *n = parent->first_child;
		while(n->next_sibling != NULL) {
			n = n->next_sibling;
			nth++;
		}
		// add the ast node to the next sibling, which is
		// in the list of children for this parent
		n->next_sibling = adding;
		adding->parent_st = parent;
		printf("Added a symbol table as its %i'th child to another symbol table\n", nth);
	}
}

int has_child_st(struct scarl_symbol_table *st) {
	return st->first_child != NULL;
}

int get_child_st_count(struct scarl_symbol_table *st) {
	if (!has_child_st(st)) {
		return 0;
	}
	else {
		int count = 1;
		struct scarl_symbol_table *n = st->first_child;
		while(n != NULL) {
			n = n->next_sibling;
			count++;
		}
		return count;
	}
}


void print_st_r(struct scarl_symbol_table *st, int level);

void print_st(struct scarl_symbol_table *st) {
	print_st_r(st, 0);
}

void print_st_r(struct scarl_symbol_table *st, int level) {
	struct scarl_symbol_table_entry *entry = st->entries; // first entry
	for (int i = 0; i < level; i++) printf("    "); // indent for level
	if (level == 0) printf("ROOT ");
	printf("Symbol table:\n");
	if (entry == NULL) {
		for (int i = 0; i < level; i++) printf("    "); // indent for level
		printf("empty symbol table\n");
	} else {		
		int entry_index = 0;
		while (entry != NULL) {
			for (int i = 0; i < level; i++) printf("    "); // indent for level
			printf("%i - ident: %s; ", entry_index, entry->ident->ident_str);
			if (entry->is_constant) {
				printf("constant; ");
			}
			printf("type %s; ", get_type_class_str(entry->type->type_class));
			switch(entry->type->type_class) {
				case PRIMITIVE_TYPE: {
					
				}
				break;
				case POINTER_TYPE: {
					struct scarl_pointer_type *ptr_type = (struct scarl_pointer_type*)entry->type;
					printf("pointer to type: %s; ", get_type_class_str(ptr_type->pointing_to->type_class));
				}
				break;
				case ARRAY_TYPE: {
					struct scarl_array_type *arr_type = (struct scarl_array_type*)entry->type;
					printf("array of type: %s; ", get_type_class_str(arr_type->containing_type->type_class));
					printf("length = %i; ", arr_type->length);
				}
				break;
				case FUNCTION_TYPE: { 
					struct scarl_function_type *func_type = (struct scarl_function_type*)entry->type;
					printf("returns %s; ", get_type_class_str(func_type->return_type->type_class));
					int param_count = get_type_descriptor_list_count(func_type->formal_parameters);
					printf("parameter count: %i; ", param_count);
					if (param_count > 0) {
						printf("parameter type(s): ");
						struct scarl_type_descriptor *fp = func_type->formal_parameters;
						while (fp != NULL) {
							printf("%s", get_type_class_str(fp->type_class));
							fp = fp->next;
							if (fp != NULL) {
								printf(", ");
							}
						}
					}
				}
				break;
				case CLASS_TYPE: {
					struct scarl_class_type *class_type = (struct scarl_class_type*)entry->type;
					printf("class name: %s; ", class_type->class_name_identifier);
					if (class_type->class_st != NULL) {
						// describes the definition of the class 
						printf("class type definition; ");
						if (class_type->parent_class_identifier != NULL) {
							printf("parent class: %s; ", class_type->parent_class_identifier);
						}
						int attribute_count = get_entry_count(class_type->class_st);
						printf("attribute count: %i; ", attribute_count);
					}
					else {
						// this is a reference to the class 
						printf("class type declaration; ");
					}
				}
				break;
				case DEVICE_TYPE: {
					
				}
				break;
			}
			printf("\n");
			entry = entry->next;
			entry_index++;
		}
	}
	for (int i = 0; i < level; i++) printf("    "); // indent for level
	
	struct scarl_symbol_table *child_st = st->first_child;
	if (child_st == NULL) {
		printf("no child symbol tables\n");
	} else {
		printf("Child symbol tables {\n");
		int table_index = 0;
		while (child_st != NULL) {
			for (int i = 0; i < level; i++) printf("    "); // indent for level
			printf("Table Index: %i\n", table_index);
			print_st_r(child_st, level + 1);
			child_st = child_st->next_sibling;
			table_index++;
		}
		for (int i = 0; i < level; i++) printf("    "); // indent for level
		printf("}\n");
	}
}

void add_st_entry(struct scarl_symbol_table *parent, struct scarl_symbol_table_entry *entry) {
	assert(parent != NULL && entry != NULL);
	if (parent->entries == NULL) {
		parent->entries = entry;
		entry->containing_st = parent;
	}
	else {
		struct scarl_symbol_table_entry *n = parent->entries;
		while(n->next != NULL) {
			n = n->next;
		}
		// add the ast node to the next sibling, which is
		// in the list of children for this parent
		n->next = entry;
		entry->containing_st = parent;
	}
}

// lookup and usage functions

// searches current scope first, and searches parent scope recursively until it is found or the root table has been searched 
struct scarl_symbol_table_entry *lookup_char_str(struct scarl_symbol_table *current_scope_st, char* ident) {
	struct scarl_symbol_table_entry *entry = NULL;
	// search this scope
	entry = current_scope_st->entries;
	while (entry != NULL) {
		if (strcmp(ident, entry->ident->ident_str) == 0) {
			return entry;
		}
		else {
			entry = entry->next;
		}
	}
	// if we are here, it means we did not find it
	// try the outer scope if there is one 
	if (current_scope_st->parent_st != NULL) {
		return lookup_char_str(current_scope_st->parent_st, ident);
	}
	return entry;
}


// searches current scope first, and searches parent scope recursively until it is found or the root table has been searched 
struct scarl_symbol_table_entry *lookup(struct scarl_symbol_table *current_scope_st, struct scarl_symbol_table_entry_identifier *ident) {
	struct scarl_symbol_table_entry *entry = NULL;
	// search this scope
	entry = current_scope_st->entries;
	while (entry != NULL) {
		if (compare_entry_identifiers(ident, entry->ident)) {
			return entry;
		}
		else {
			entry = entry->next;
		}
	}
	// if we are here, it means we did not find it
	// try the outer scope if there is one 
	if (current_scope_st->parent_st != NULL) {
		return lookup(current_scope_st->parent_st, ident);
	}
	return entry;
}

int get_entry_count(struct scarl_symbol_table *st) {
	int count = 0;
	struct scarl_symbol_table_entry *entry = st->entries;
	while (entry != NULL) {
		entry = entry->next;
		count++;
	}
	return count;
}

// searches the specified symbol table only
struct scarl_symbol_table_entry *lookup_in_scope(struct scarl_symbol_table *current_scope_st, struct scarl_symbol_table_entry_identifier *ident) {
	struct scarl_symbol_table_entry *entry = NULL;
	// search this scope
	entry = current_scope_st->entries;
	while (entry != NULL) {
		if (compare_entry_identifiers(ident, entry->ident)) {
			return entry;
		}
		else {
			entry = entry->next;
		}
	}
	// if we are here, it means we did not find it
	// - don't look in any other scope
	return entry;
}

// do these entry identifier structures match?
// TRUE if equal, FALSE if not equal (not like strcmp)
int compare_entry_identifiers(struct scarl_symbol_table_entry_identifier *lhs, struct scarl_symbol_table_entry_identifier *rhs) {
	if (strcmp(lhs->ident_str, rhs->ident_str) != 0) {
		return 0;
	}
	else {
		// idents are equal 
		// are the parameter lists equal?
		if (lhs->parameter_list == NULL && rhs->parameter_list == NULL) {
			// neither of them have parameter lists 
			return 1; // they must be equal 
		}
		else if (lhs->parameter_list != NULL && rhs->parameter_list != NULL) {
			int lhs_count = get_type_descriptor_list_count(lhs->parameter_list);
			int rhs_count = get_type_descriptor_list_count(rhs->parameter_list);
			if (lhs_count != rhs_count) {
				return 0; // parameter list length not equal 
			}
			else {
				// parameter list length matches, check if 
				// the types match up (exact match)
				struct scarl_type_descriptor *lhs_td = lhs->parameter_list;
				struct scarl_type_descriptor *rhs_td = rhs->parameter_list;
				for (int i = 0; i < lhs_count; i++) {
					if (compare_type_descriptors(lhs_td, rhs_td) == 0) {
						// these type descriptors did not match,
						// so these entry identifiers are not equal
						return 0;
					}
					lhs_td = lhs_td->next;
					rhs_td = rhs_td->next;
				}
				return 1; // they must be equal, no error
			}
		}
		else {
			// one list is empty and the other is not 
			return 0; //not equal 
		}
	}
	return 0;
}
