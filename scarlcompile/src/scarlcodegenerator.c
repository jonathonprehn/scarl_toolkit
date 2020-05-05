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
#include <string.h>
#include <assert.h>

#include "y.tab.h"
#include "scarltypes.h"
#include "scarlregister.h"
#include "scarlcodegenerator.h"

extern int debug_compilation;

/* Support the implementation of different target languages */

// taken from the original scarlcodegen.h file
void generate_code_file(FILE *output) {
	
}

void generate_code_ast(FILE *output, struct scarl_symbol_table *associated_scope_st, struct scarl_ast_node *node) {
	assert(associated_scope_st != NULL); // must be in a scope
	// variables used 
	struct scarl_ast_node *statement = NULL;
	
	switch(node->node_type) {
		case NON_TERMINAL_STATEMENT_LIST:
		{
			statement = node->first_child;
			while(statement != NULL) {
				switch(statement->node_type) {
					case NON_TERMINAL_VARIABLE_DEFINITION_STATEMENT:
					{
						
						
						// 1. Is the expression used to define the variable valid for its type?
						
						struct scarl_ast_node *type_declarator_node = statement->first_child;
						struct scarl_ast_node *type_node = type_declarator_node->first_child;
						struct scarl_ast_node *ident_node = type_declarator_node->first_child->next_sibling;
						struct scarl_ast_node *expr_node = statement->first_child->next_sibling;
						
						// determine the type of the expression 
						struct scarl_type_descriptor *expr_assumed_type = assume_type_of_expression_st(associated_scope_st, expr_node);
						
						// generate the code to evaluate the expression 
						generate_expression_value(output, associated_scope_st, expr_node);
						
						// generate global variable definition
						// load the value of the registers into the memory location of this variable
						struct scarl_symbol_table_entry *defining_variable_st_entry = lookup_char_str(associated_scope_st, ident_node->str_value);
						assert(defining_variable_st_entry != NULL);
						
						//load the registers into that global location and free them
						int globalOffset = defining_variable_st_entry->frameByteOffset;
						int globalSize = defining_variable_st_entry->frameByteSize;
						assert(defining_variable_st_entry->type != NULL);
						
						fprintf(output, "TODO: Write output of expression to global memory space\n");
						
						/*
						TODO: Write output of expression to global memory space
						
						// write the output of the program to global memory space 
						if (defining_variable_st_entry->type->type_class == PRIMITIVE_TYPE) {
							if (globalSize == 2) {
								assert(expr_node->reg_low != SCARL_NULL && expr_node->reg_high != SCARL_NULL);
								fprintf(output, "STORR %s %i\n", register_str(expr_node->reg_low), globalOffset);
								fprintf(output, "STORR %s %i\n", register_str(expr_node->reg_high), globalOffset+1); 
							}
							else if (globalSize == 1)
							{
								assert(expr_node->reg_low != SCARL_NULL);
								//truncation done here
								//TODO: truncate value
								fprintf(output, "STORR %s %i\n", register_str(expr_node->reg_low), globalOffset);
							}
						}
						else {
							fprintf(stderr, "Can\'t generate code for type class: %s\n", get_type_class_str(defining_variable_st_entry->type->type_class));
						}
						*/
						
						// free used registers
						free_register(expr_node->reg_low);
						free_register(expr_node->reg_high);
						
						
					}	
					break;
					case NON_TERMINAL_VARIABLE_DECLARATION_STATEMENT:
					{
						// generate global variable declaration
						
						// no code necessary here since it just creates spacing in the symbol tables
					}						
					break;
					case NON_TERMINAL_CONSTANT_DEFINITION_STATEMENT:
					{						
						// 1. Is the expression valid?  ( must be since it was already evaluated at compile time? 
						//		This is going to be strange to handle)
						
						
						// generate global constant variable definition
						
						// no code necessary since the constant expression value 
						// was already evaluated at compile time.
						
						// this kind of definition really doesn't require space either, but 
						// going to leave it for now since it doesn't hurt anything
					}
					break;
					case NON_TERMINAL_CLASS_DEFINITION_STATEMENT:
					{
						// generate class definition (this may not mean much other than maintaining the structure of the class)
						
						struct scarl_ast_node *class_type_declarator_node = statement->first_child;
						struct scarl_ast_node *class_body_node = statement->first_child->next_sibling;
						
						char *class_name = class_type_declarator_node->first_child->str_value;
						assert(class_name != NULL);
						
						// get class body symbol table 
						struct scarl_symbol_table_entry *class_st_entry = lookup_char_str(associated_scope_st, class_name);
						struct scarl_class_type *class_td = (struct scarl_class_type*)class_st_entry->type;
						
						// generates the methods for this class. attributes do not generate anything in the 
						// class definition itself (only when object instances are created)
						generate_class_body(output, class_name, class_td->class_st, class_body_node);
						
					}
					break;
					case NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT:
					{												
						
						// generate function definition
						// build function name from name and parameters
						struct scarl_ast_node *func_return_type_node = statement->first_child;
						struct scarl_ast_node *func_ident_node = statement->first_child->next_sibling;
						struct scarl_ast_node *func_formal_parameters_node = statement->first_child->next_sibling->next_sibling;
						struct scarl_ast_node *func_statement_block_node = statement->first_child->next_sibling->next_sibling->next_sibling;
					
						assert(func_return_type_node != NULL);
						assert(func_ident_node != NULL);
						assert(func_formal_parameters_node != NULL);
						assert(func_statement_block_node != NULL);
						
						struct scarl_type_descriptor *formal_parameter_td_list = create_type_descriptor_list_from_formal_parameter_node(associated_scope_st, func_formal_parameters_node);
						struct scarl_symbol_table_entry_identifier* func_entry_identifier = create_st_entry_identifier(func_ident_node->str_value, formal_parameter_td_list);
						struct scarl_symbol_table_entry *func_st_entry = lookup_in_scope(associated_scope_st, func_entry_identifier);
					
						assert(func_st_entry != NULL);
						//printf("Found function symbol table entry for %s\n", func_ident_node->str_value);
						
						char *proc_name = build_arcl_procedure_name(NULL, func_entry_identifier); // give class name in class attribute body
						fprintf(output, "PROC %s\n", proc_name);
						free(proc_name);
						
						struct scarl_function_type *func_td = (struct scarl_function_type*)func_st_entry->type;
						
						// generate code for function statements here 
						generate_statements_in_block(output, func_td->function_st, func_statement_block_node);
						//setup return value 
						
						fprintf(output, "RET\n");
					}
					break;
				}
				statement = statement->next_sibling;
			}
		}
		break; 
		default:
		{
		} 
	}
}


void generate_expression_value(FILE *output, struct scarl_symbol_table *associated_scope_st, struct scarl_ast_node *node) {
	/*
	
	possible node values in an expression 
	
	node_type, type_value               | description
	----------------------------------------------------------------------------------------------------------
	NON_TERMINAL_POINTER_VALUE              | allocating pointer value expression 
	NON_TERMINAL_OPERAND_VALUE, OR          | boolean OR (lhs, rhs should be bool)
	NON_TERMINAL_OPERAND_VALUE, AND         | boolean AND (lhs, rhs should be bool)
	NON_TERMINAL_OPERAND_VALUE, DBL_EQ      | boolean == (lhs, rhs should be same type)
	NON_TERMINAL_OPERAND_VALUE, NOT_EQ      | boolean != (lhs, rhs should be same type)
	NON_TERMINAL_OPERAND_VALUE, GTR         | boolean > (lhs, rhs should be int)
	NON_TERMINAL_OPERAND_VALUE, LESS        | boolean < (lhs, rhs should be int)
	NON_TERMINAL_OPERAND_VALUE, GTR_EQ      | boolean >= (lhs, rhs should be int)
	NON_TERMINAL_OPERAND_VALUE, LESS_EQ     | boolean <= (lhs, rhs should be int)
	NON_TERMINAL_OPERAND_VALUE, BANG        | boolean <= (one child, should be bool)
	NON_TERMINAL_OPERAND_VALUE, PLUS        | int + (lhs, rhs should be int)
	NON_TERMINAL_OPERAND_VALUE, MINUS       | int - (lhs, rhs should be int)
	NON_TERMINAL_OPERAND_VALUE, MINUS       | int - (one child should be int)
	NON_TERMINAL_OPERAND_VALUE, STAR        | int * (lhs, rhs should be int)
	NON_TERMINAL_OPERAND_VALUE, SLASH       | int / (lhs, rhs should be int)
	NON_TERMINAL_IDENTIFIER_VALUE           | takes on the type as listed in its symbol
                                            | table entry and returns the value of it in 
										    | a register pair/single register
	NON_TERMINAL_CLASS_ATTRIBUTE_IDENTIFIER | like identifier but for class fields
	NON_TERMINAL_ARRAY_ACCESSOR_TYPE        | takes on the containing type of the array 
	                                        | its identifier refers to
	NON_TERMINAL_DEREFERENCED_VALUE         | takes on the type its pointer identifier 
	                                        | is pointing to 
	NON_TERMINAL_ARRAY_TYPE                 | takes on the type of its children 
	                                        | (which should be the same)
	NON_TERMINAL_INTEGER_VALUE              | int typed literal value in int_value
	NON_TERMINAL_CHAR_VALUE                 | char typed literal value in str_type
	NON_TERMINAL_BOOL_VALUE                 | bool typed literal, value in int_value
	NON_TERMINAL_BOOL_VALUE                 | bool typed literal, value in int_value
	NON_TERMINAL_FUNCTION_INVOCATION        | obtain the return type and value of the function call
	NON_TERMINAL_METHOD_INVOCATION          | obtain the return type and value of the method call
	
	*/
	switch(node->node_type) {
		case NON_TERMINAL_INTEGER_VALUE:
		{
			int value_raw = node->int_value;
			int value_low = value_raw % 128;
			int value_high = value_raw / 128;
			
			// store in two registers until it is time to extract it
			int reg_low = allocate_register();
			int reg_high = allocate_register();
			// load the high and low values of this literal into the 
			// high and low registers
			fprintf(output, "LOADL %s %i\n", register_str(reg_low), value_low);
			fprintf(output, "LOADL %s %i\n", register_str(reg_high), value_high);
			
			node->reg_low = reg_low;
			node->reg_high = reg_high;
		}
		break;
		case NON_TERMINAL_CHAR_VALUE:
		{
			// char value stored in 1 register as a byte
			// compiler places character code into int valued register 
			int c = node->int_value;
			printf("%c\n", (char)c);
			
			int reg = allocate_register();
			fprintf(output, "LOADL %s %i\n", register_str(reg), c);
			node->reg_low = reg;
			node->reg_high = SCARL_NULL;
		}
		break;
		case NON_TERMINAL_BOOL_VALUE:
		{
			// stored in 1 register as 0 or 1 (lots of wasted space for now)
			int register_value = SCARL_NULL;
			if (node->int_value == TRUE) {
				register_value = 1;
			}
			else if (node->int_value == FALSE) {
				register_value = 0;
			}
			assert(register_value != SCARL_NULL);
			int reg = allocate_register();
			fprintf(output, "LOADL %s %i\n", register_str(reg), register_value);
			
			node->reg_low = reg;
			node->reg_high = SCARL_NULL;
		}
		break;
		case NON_TERMINAL_IDENTIFIER_VALUE:
		{
			// load value from identifier into registers
			struct scarl_symbol_table_entry *ident_entry = lookup_char_str(associated_scope_st, node->str_value);
			assert(ident_entry != NULL);
			
			// is this variable in global memory or local memory
			
		}
		break;
		case NON_TERMINAL_CLASS_ATTRIBUTE_IDENTIFIER:
		{
			fprintf(output, "TODO: load value of object field into register values\n");
		}
		break;
		case NON_TERMINAL_OPERAND_VALUE:
		{
			switch(node->type_value) {
				case PLUS:
				{
					
				}
				break;
				case MINUS:
				{
					
				}
				break;
				case STAR:
				{
					
				}
				break;
				case SLASH:
				{
					
				}
				break;
			}
		}
		break;
		case NON_TERMINAL_FUNCTION_INVOCATION:
		{
			
		}
		break;
		case NON_TERMINAL_METHOD_INVOCATION:
		{
			
		}
		break;
		default:
		{
			fprintf(stderr, "Unrecognizable node type code: %i", node->node_type);
			assert(0);
		}
	}
	return;
}


void generate_local_memory_write(FILE *output, struct scarl_symbol_table *associated_scope_st, struct scarl_symbol_table_entry *st_entry, struct scarl_ast_node *result_node) {
	
	//load the registers into that global location and free them
	int localOffset = st_entry->frameByteOffset;
	int localSize = st_entry->frameByteSize;
	assert(st_entry->type != NULL);
	
	fprintf(output, "TODO: Writing %s into stack memory offset %i\n", register_str(result_node->reg_low), localOffset);
	fprintf(output, "TODO: Writing %s into stack memory offset %i\n", register_str(result_node->reg_high), localOffset+1);
	
	// free used registers
	free_register(result_node->reg_low);
	free_register(result_node->reg_high);
}


void generate_class_body(FILE *output, char *class_name, struct scarl_symbol_table *associated_scope_st, struct scarl_ast_node *node) {
	/*
	node_type, type_value                        | description
	------------------------------------------------------------------------------------------------------------------------
	NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT   | Defines a method for this class
	NON_TERMINAL_VARIABLE_DECLARATION_STATEMENT  | Defines an attribute for instances of this class 
	
	*/
	struct scarl_ast_node *class_attribute = NULL;
	class_attribute = node->first_child;
	while(class_attribute != NULL) {
			switch(class_attribute->node_type) {
				case NON_TERMINAL_VARIABLE_DECLARATION_STATEMENT:
				{
					// 1. Is this field identifier declared in the class body elsewhere?
					//   --- this is already checked in the symbol table construction
					
					// how will class definitions be included in the language?
					// ensure that constructor methods are used/created -- validate that
					// the class has a constructor during symbol table construction / program validation
					
				}
				break;
				case NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT:
				{
					// 1. Is this method a duplicate definition in this class body?
					
					// 2. Verify the method body (recursive call)
					
					
					// generate function definition
					// build function name from name and parameters
					struct scarl_ast_node *func_return_type_node = class_attribute->first_child;
					struct scarl_ast_node *func_ident_node = class_attribute->first_child->next_sibling;
					struct scarl_ast_node *func_formal_parameters_node = class_attribute->first_child->next_sibling->next_sibling;
					struct scarl_ast_node *func_statement_block_node = class_attribute->first_child->next_sibling->next_sibling->next_sibling;
				
					assert(func_return_type_node != NULL);
					assert(func_ident_node != NULL);
					assert(func_formal_parameters_node != NULL);
					assert(func_statement_block_node != NULL);
					
					struct scarl_type_descriptor *formal_parameter_td_list = create_type_descriptor_list_from_formal_parameter_node(associated_scope_st, func_formal_parameters_node);
					struct scarl_symbol_table_entry_identifier* func_entry_identifier = create_st_entry_identifier(func_ident_node->str_value, formal_parameter_td_list);
					struct scarl_symbol_table_entry *func_st_entry = lookup_in_scope(associated_scope_st, func_entry_identifier);
				
					assert(func_st_entry != NULL);
					//printf("Found function symbol table entry for %s\n", func_ident_node->str_value);
					
					char *proc_name = build_arcl_procedure_name(class_name, func_entry_identifier); // class_name != NULL signifies class method
					fprintf(output, "PROC %s\n", proc_name);
					free(proc_name);
					
					// generate code for function statements here 
					
					// this code will be identical to the one used for global function generation, except the 
					// "current object" will be stacked as a local pointer variable
					
					//setup return value 
					
					fprintf(output, "RET\n");
									
				}
				break;
			}
			class_attribute = class_attribute->next_sibling;
	}
}

void generate_statements_in_block(FILE *output, struct scarl_symbol_table *associated_scope_st, struct scarl_ast_node *node) {
	/*
	
	possible node values (definite steps for statements) in a block statement 
	
	node_type, type_value                        | description
	------------------------------------------------------------------------------------------------------------------------
	NON_TERMINAL_VARIABLE_DEFINITION_STATEMENT   | Define a variale to allocate its space and set its value to an expression
	NON_TERMINAL_VARIABLE_DECLARATION_STATEMENT  | Declare a variable to allocate space, but have no value 
	NON_TERMINAL_DELETE_STATEMENT                | Deallocate the pointer referred to in the statement
	NON_TERMINAL_CONSTANT_DEFINITION_STATEMENT   | Set a constant lhs to an rhs expression
	NON_TERMINAL_VARIABLE_SET_STATEMENT          | Set a valid lhs to a rhs expression
	NON_TERMINAL_RETURN_STATEMENT                | Return from current function scope 
	NON_TERMINAL_IF_BLOCK_STATEMENT              | Boolean expression and if block, optional else block
	NON_TERMINAL_WHILE_BLOCK_STATEMENT           | Boolean expression and while block
	NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL      | Block within a block statement
	NON_TERMINAL_FUNCTION_INVOCATION             | A simple function invocation 
	NON_TERMINAL_METHOD_INVOCATION               | A simple method invocation
	
	*/
	struct scarl_ast_node *statement_block_level = NULL;
	statement_block_level = node->first_child;
	while(statement_block_level != NULL) {
		switch(statement_block_level->node_type) {
			case NON_TERMINAL_VARIABLE_DEFINITION_STATEMENT:
			{

				// 1. Is the expression used to define the variable valid for its type?
				
				struct scarl_ast_node *type_declarator_node = statement_block_level->first_child;
				struct scarl_ast_node *type_node = type_declarator_node->first_child;
				struct scarl_ast_node *ident_node = type_declarator_node->first_child->next_sibling;
				struct scarl_ast_node *expr_node = statement_block_level->first_child->next_sibling;
				
				// determine the type of the expression 
				struct scarl_type_descriptor *expr_assumed_type = assume_type_of_expression_st(associated_scope_st, expr_node);
				
				// generate the code to evaluate the expression 
				generate_expression_value(output, associated_scope_st, expr_node);
				
				// generate global variable definition
				// load the value of the registers into the memory location of this variable
				struct scarl_symbol_table_entry *defining_variable_st_entry = lookup_char_str(associated_scope_st, ident_node->str_value);
				assert(defining_variable_st_entry != NULL);
				
				//printf("Generating definition for %s\n", defining_variable_st_entry->ident->ident_str);
				//fprintf(output, "TODO: Write output of expression to local (stack frame) memory space\n");
				generate_local_memory_write(output, associated_scope_st, defining_variable_st_entry, expr_node);
				
			}
			break;
			case NON_TERMINAL_VARIABLE_DECLARATION_STATEMENT:
			{
				// 1. Is this a duplicate identifier name in this scope?
				
				
				// generate local variable declaration
				
			}
			break;
			case NON_TERMINAL_VARIABLE_SET_STATEMENT:
			{
				struct scarl_ast_node *ident_node = statement_block_level->first_child;
				struct scarl_ast_node *expr_node = statement_block_level->first_child->next_sibling;
				
				// 1. Is the left-hand side a valid variable or class attribute?
				struct scarl_symbol_table_entry *variable_entry = NULL;
				
				// 2. If it is a class attribute, is the object used defined?
				
				// 3. Is the expression to set the left-hand side valid for its type?

				if (ident_node->node_type == NON_TERMINAL_IDENTIFIER_VALUE) {
					variable_entry = lookup_char_str(associated_scope_st, ident_node->str_value);
				}
				else if (ident_node->node_type == NON_TERMINAL_CLASS_ATTRIBUTE_IDENTIFIER) {
					//fprintf(output, "TODO: Generate variable lookup for class attribute\n");
					
					struct scarl_ast_node *instance_name_node = ident_node->first_child;
					struct scarl_ast_node *field_node = instance_name_node->next_sibling;
					//printf("Finding field %s in object instance %s\n", field_node->str_value, instance_name_node->str_value);
					
					struct scarl_symbol_table_entry *instance_entry = NULL;
					instance_entry = lookup_char_str(associated_scope_st, instance_name_node->str_value);
					assert(instance_entry != NULL);
					
					//printf("Got symbol table entry for %s\n", instance_name_node->str_value);
					
					// this will only have the class name, the symbol table is in the root somewhere
					struct scarl_class_type *class_type = (struct scarl_class_type*)instance_entry->type;
					char *class_name = class_type->class_name_identifier;
					//printf("Class name of %s is %s\n", instance_name_node->str_value, class_name);
					
					
					//get the type name and obtain the symbol table of the class type 
					struct scarl_symbol_table_entry *class_def_entry = lookup_char_str(associated_scope_st, class_name);
					assert(class_def_entry != NULL);
					//printf("Got symbol table entry for %s\n", class_name);
					
					// the type object of the class definition should have the symbol table
					struct scarl_class_type *complete_class_type = (struct scarl_class_type*)class_def_entry->type;
					
					struct scarl_symbol_table_entry *field_entry = lookup_char_str(complete_class_type->class_st, field_node->str_value);
					assert(field_entry != NULL);
					//printf("Got class field entry %s, byte offset %i\n", field_node->str_value, field_entry->frameByteOffset);
					
					//TODO: enhance to allow for more levels of field access (objects within objects)
					//need a way to keep the reference to the other symbol table entries, might need to 
					//jump between different symbol tables to get the correct location of the field in memory
					variable_entry = field_entry; 
				}
				else {
					fprintf(stderr, "Invalid node used for variable identifier: %s\n", get_ast_node_type_string(ident_node->node_type));
				}
				
				assert(variable_entry != NULL);
				
				// determine the type of the expression 
				struct scarl_type_descriptor *expr_assumed_type = assume_type_of_expression_st(associated_scope_st, expr_node);
				
				// generate the code to evaluate the expression 
				//printf("Expr root type: %s\n", get_ast_node_type_string(expr_node->node_type));
				generate_expression_value(output, associated_scope_st, expr_node);
				
				//fprintf(output, "Write expression output to variable\n");
				generate_local_memory_write(output, associated_scope_st, variable_entry, expr_node);
				
			}
			break;
			case NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL:
			{
				// 1. Verify this scope (recursive call)
				
				
				
			}
			break;
			case NON_TERMINAL_FUNCTION_INVOCATION:
			{
				// 1. Does the function exist? Is there a matching definition for the used parameters?
				
				// 2. Are the expressions that makeup the parameter list valid for a candidate definition?
				
				// 3. Is this function call ambiguous in that there are two or more functions it could potentially be matched up with?
				
				
				// generate function call
				
			}
			break;
			case NON_TERMINAL_METHOD_INVOCATION:
			{
				// 1. Is the callee class instance defined?
				
				// 2. Does the method exist? Is there a matching definition for the used parameters?
				
				// 3. Are the expressions that makeup the parameter list valid for a candidate definition?
				
				// 4. Is this function call ambiguous in that there are two or more functions it could potentially be matched up with?
				
				
				// generate method call
				
			}
			break;
			case NON_TERMINAL_IF_BLOCK_STATEMENT:
			{
				// 1. Is the control structure's expression valid and evaluate to a bool?
				
				// 2. Verify the if block (recursive call)
				
				// 3. Verify the else block (if it exists, recursive call)
				
				
				// generate if block logic
				
			}
			break;
			case NON_TERMINAL_WHILE_BLOCK_STATEMENT:
			{
				// 1. Is the control structure's expression valid and evaluate to a bool?
			
				// 2. Verify the while statement body (recursive call)
				
				
				// generate while block generation
				
			}
			break;
			case NON_TERMINAL_DELETE_STATEMENT:
			{						
				// 1. Does the deleting variable exist and is defined?
				
				// 2. Is the deleting variable a deleteable type?
				
				
				// generate deallocation
				 
			}
			break;
		}
		statement_block_level = statement_block_level->next_sibling;
	}
}

void generate_function_invocation(FILE *output, struct scarl_symbol_table *associated_scope_st, struct scarl_ast_node *node) {
	
}

void generate_register_save(FILE *output) {
	
}

void generate_register_load(FILE *output) {
	
}

int recursive_procedure_name_append(char *at_str, struct scarl_type_descriptor *td) {
	int chars_written = 0;
	
	// variables to cast to 
	struct scarl_primitive_type *prim_td = NULL;
	struct scarl_device_type *dev_td = NULL;
	struct scarl_pointer_type *point_td = NULL;
	struct scarl_array_type *array_td = NULL;
	struct scarl_function_type *func_td = NULL;
	struct scarl_class_type *class_td = NULL;
	
	switch(td->type_class) {
		case PRIMITIVE_TYPE:
		{
			prim_td = (struct scarl_primitive_type*)td;
			chars_written = sprintf(at_str, "_%i_", prim_td->primitive_type);
		}
		break;
		case POINTER_TYPE:
		{
			point_td = (struct scarl_pointer_type*)td;
			int initial_write = sprintf(at_str, "_p_");
			chars_written = recursive_procedure_name_append(at_str+initial_write, point_td->pointing_to) + initial_write;
		}
		break;
		case ARRAY_TYPE:
		{
			array_td = (struct scarl_array_type*)td;
			int initial_write = sprintf(at_str, "_a%i_", array_td->length);
			chars_written = recursive_procedure_name_append(at_str+initial_write, array_td->containing_type) + initial_write;
		}
		break;
		case CLASS_TYPE:
		{
			class_td = (struct scarl_class_type*)td;
			chars_written = sprintf(at_str, "_c%s_", class_td->class_name_identifier);
		}
		break;
		case DEVICE_TYPE:
		{
			dev_td = (struct scarl_device_type*)td;
			chars_written = sprintf(at_str, "_d%i_", dev_td->device_type);
		}
		break;	
	}
	return chars_written;
}

char *build_arcl_procedure_name(char *class_name, struct scarl_symbol_table_entry_identifier* func_entry_identifier) {
	
	// variables to cast to 
	struct scarl_primitive_type *prim_td = NULL;
	struct scarl_device_type *dev_td = NULL;
	struct scarl_pointer_type *point_td = NULL;
	struct scarl_array_type *array_td = NULL;
	struct scarl_function_type *func_td = NULL;
	struct scarl_class_type *class_td = NULL;
	
	// buffer for generated procedure name
	char *name_buffer = (char*)malloc(sizeof(char)*255);
	unsigned ptr = 0;
	if (class_name != NULL) {
		const char *cmethod = "CMethod_";
		int cname = sprintf(name_buffer+ptr, "%s%s_", cmethod, class_name);
		ptr += cname;
	}
	name_buffer[ptr++] = '_';
	int ident_len = strlen(func_entry_identifier->ident_str);
	for (int i = 0; i < ident_len; i++) {
		name_buffer[ptr++] = func_entry_identifier->ident_str[i];
	}
	name_buffer[ptr++] = '_';
	struct scarl_type_descriptor *cur_td = func_entry_identifier->parameter_list;
	while(cur_td != NULL) {
		switch(cur_td->type_class) {
			case PRIMITIVE_TYPE:
			{
				prim_td = (struct scarl_primitive_type*)cur_td;
				int chars_written = sprintf(name_buffer+ptr, "_%i_", prim_td->primitive_type);
				ptr += chars_written;
			}
			break;
			case POINTER_TYPE:
			{
				point_td = (struct scarl_pointer_type*)cur_td;
				int initial_write = sprintf(name_buffer+ptr, "_p_");
				ptr += initial_write;
				int chars_written = recursive_procedure_name_append(name_buffer+ptr, point_td->pointing_to);
				ptr += chars_written;
			}
			break;
			case ARRAY_TYPE:
			{
				array_td = (struct scarl_array_type*)cur_td;
				int initial_write = sprintf(name_buffer+ptr, "_a%i_", array_td->length);
				ptr += initial_write;
				int chars_written = recursive_procedure_name_append(name_buffer+ptr, array_td->containing_type);
				ptr += chars_written;
			}
			break;
			case CLASS_TYPE:
			{
				class_td = (struct scarl_class_type*)cur_td;
				int chars_written = sprintf(name_buffer+ptr, "_c%s_", class_td->class_name_identifier);
				ptr += chars_written;
			}
			break;
			case DEVICE_TYPE:
			{
				dev_td = (struct scarl_device_type*)cur_td;
				int chars_written = sprintf(name_buffer+ptr, "_d%i_", dev_td->device_type);
				ptr += chars_written;
			}
			break;
		}
		cur_td = cur_td->next;
	}
	assert(ptr < 255);
	name_buffer[ptr] = '\0';
	char *cpy = strdup(name_buffer);
	free(name_buffer);
	return cpy; // creates copy of stack allocated string on the heap 
}
