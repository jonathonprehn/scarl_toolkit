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

#ifndef SCARLTYPES_H_INCLUDED
#define SCARLTYPES_H_INCLUDED

/*
    This file provides definitions for
    types that are used throughout the
    program.

    It also provides mechanisms for creating
    a type hierarchy
*/

#define SCARL_NULL			                           -3

//each terminal and non-terminal
//gets its own flag so we can
//distinguish between the types

//TODO: Update nonterminals and terminals to reflect new grammar

#define NON_TERMINAL_PROGRAM						0x301
#define NON_TERMINAL_STATEMENT_LIST					0x302
#define NON_TERMINAL_STATEMENT						0x303
#define NON_TERMINAL_BLOCK_STATEMENT				0x304
#define NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL		0x305
#define NON_TERMINAL_STATEMENT_BLOCK_LEVEL			0x306
///////////#define NON_TERMINAL_DEVICE_DECLARATOR_STATEMENT	0x307
#define NON_TERMINAL_PRIMITIVE_DECLARATOR			0x308
#define NON_TERMINAL_VARIABLE_DEFINITION_STATEMENT	0x309
#define NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT	0x30A
#define NON_TERMINAL_VARIABLE_SET_STATEMENT			0x30B
#define NON_TERMINAL_FUNCTION_INVOCATION			0x30C
#define NON_TERMINAL_FUNCTION_INVOCATION_STATEMENT	0x30D
#define NON_TERMINAL_IF_BLOCK_STATEMENT				0x30E
#define NON_TERMINAL_WHILE_BLOCK_STATEMENT			0x30F
#define NON_TERMINAL_FORMAL_PARAMETER_LIST			0x310
#define NON_TERMINAL_PARAMETER_LIST					0x311
#define NON_TERMINAL_EXPRESSION						0x312
#define NON_TERMINAL_LOGICAL_EXPRESSION				0x313
#define NON_TERMINAL_LOGICAL_AND_EXPRESSION			0x314
#define NON_TERMINAL_EQUALITY_EXPRESSION			0x315
#define NON_TERMINAL_RELATIONAL_EXPRESSION			0x316
#define NON_TERMINAL_BOOL_EXPRESSION				0x317
#define NON_TERMINAL_ARITHMETIC_EXPRESSION			0x318
#define NON_TERMINAL_ARITHMETIC_FACTOR				0x319
#define NON_TERMINAL_ARITHMETIC_UNARY				0x31A
#define NON_TERMINAL_UNIT							0x31B
#define NON_TERMINAL_INTEGER_VALUE					0x31C
#define NON_TERMINAL_BOOL_VALUE						0x31D
#define NON_TERMINAL_PRIMITIVE_TYPE					0x31E
#define NON_TERMINAL_DEVICE_TYPE					0x31F
#define NON_TERMINAL_RETURN_STATEMENT				0x320
// the ones after this line are new from last time
#define NON_TERMINAL_CLASS_DEFINITION_STATEMENT     0x321
#define NON_TERMINAL_CONSTANT_DEFINITION_STATEMENT  0x322
#define NON_TERMINAL_DELETE_STATEMENT	            0x323
#define NON_TERMINAL_TYPE_DECLARATOR		    	0x324
#define NON_TERMINAL_USER_DECLARATOR		    	0x325
#define NON_TERMINAL_POINTER_TYPE					0x326
#define NON_TERMINAL_ARRAY_TYPE						0x327
#define NON_TERMINAL_CHAR_VALUE						0x328
#define NON_TERMINAL_ARRAY_VALUE					0x329
#define NON_TERMINAL_POINTER_VALUE					0x32A
#define NON_TERMINAL_DEREFERENCED_VALUE 			0x32B
#define NON_TERMINAL_ARRAY_ACCESSOR_TYPE 			0x32C
#define NON_TERMINAL_IDENTIFIER_VALUE 				0x32D
#define NON_TERMINAL_OPERAND_VALUE	 				0x32E
#define NON_TERMINAL_CLASS_ATTRIBUTE_IDENTIFIER	 	0x32F
#define NON_TERMINAL_METHOD_INVOCATION				0x330
#define NON_TERMINAL_CLASS_ATTRIBUTE_LIST			0x331
#define NON_TERMINAL_CLASS_DECLARATOR				0x332
#define NON_TERMINAL_VARIABLE_DECLARATION_STATEMENT	0x333

#define TYPES_EQUAL									0x400
#define TYPES_CONVERTABLE							0x401
#define TYPES_NOT_EQUAL								0x402

#define PRIMITIVE_TYPE								0x403
#define POINTER_TYPE								0x404
#define ARRAY_TYPE									0x405
#define FUNCTION_TYPE								0x406
#define CLASS_TYPE									0x407
#define DEVICE_TYPE									0x408

#include "scarlsymboltable.h"
#include "scarlastnode.h"

// We have primitive types, pointer types, array types,
// function types and class types
// all type definitions besides primitive types rely
// on other Type_Descriptor objects to be constructed.

struct scarl_ast_node;

struct scarl_type_descriptor;

struct scarl_type_descriptor {
	// a flag that indicates which type structure this 
	// matches up with (it must be the first field in all 
	// type structures)
	int type_class;
	
	// allow for type descriptors to be act as 
	// a linked list. All type descriptors must  
	// have this as the second field
	struct scarl_type_descriptor *next;
};

struct scarl_primitive_type {
	int type_class; // Must be PRIMITIVE_TYPE
	struct scarl_type_descriptor *next;
    int primitive_type;
};

struct scarl_device_type {
	int type_class; // Must be PRIMITIVE_TYPE
	struct scarl_type_descriptor *next;
    int device_type;
};

struct scarl_pointer_type {
	int type_class; // Must be POINTER_TYPE
	struct scarl_type_descriptor *next;
    struct scarl_type_descriptor *pointing_to;
};

struct scarl_array_type {
	int type_class; // Must be ARRAY_TYPE
	struct scarl_type_descriptor *next;
    struct scarl_type_descriptor *containing_type;
    int length;
};

struct scarl_function_type {
    int type_class; // Must be FUNCTION_TYPE
	struct scarl_type_descriptor *next;
	char *func_name;
	struct scarl_type_descriptor *return_type;
	//need to support a list type
    struct scarl_type_descriptor *formal_parameters;
	struct scarl_symbol_table *function_st;
};

/*
	C++ class for the class type - moving to C as the implementation language
	class Class_Type_Table_Entry {
	public:
		Class_Type_Table_Entry(string className, vector<Type_Descriptor*> classFields, vector<Function_Type*> classMethods, string parentClass);
		~Class_Type_Table_Entry();
		vector<Type_Descriptor*> &getClassFields();
		vector<Function_Type*> &getClassMethods();
		string getClassName();
		Class_Type getParentClass();
	private:
		vector<Type_Descriptor*> classFields;
		vector<Function_Type*> classMethods;
		string parentClass;
		string className;
	};
*/

// "user type" would be another good name for this
struct scarl_class_type;

// what is a good way to organize these?
struct scarl_class_type {
	int type_class; // Must be CLASS_TYPE
	struct scarl_type_descriptor *next;
	char *class_name_identifier;
	char *parent_class_identifier;
	struct scarl_symbol_table *class_st;
};


// global functions related to class relations

/* Is the right hand side a descendent of the left hand side? */
int is_descendant_of(struct scarl_class_type *lhs, struct scarl_class_type *rhs);

/* Is the right hand side a direct descendent (immediate child) of the left hand side? */
int is_direct_descendant_of(struct scarl_class_type *lhs, struct scarl_class_type *rhs);

/* Is the right hand side an ancestor of the left hand side? */
int is_ancestor_of(struct scarl_class_type *lhs, struct scarl_class_type *rhs);


// For dynamic type conversions

/* Returns TYPES_EQUAL, TYPES_NOT_EQUAL or TYPES_CONVERTABLE */
/* It is directional in that for two given types A and B, you might be able to convert from A to B but  */
/* not be able to convert from B back to A (think about class hierarchies in polymorphism)              */
int directional_type_equality(struct scarl_type_descriptor *from_type, struct scarl_type_descriptor *to_type);

/* This function attempts to figure out which type the expression will eventually be converted to,    */
/* taking the "most straightforward" approach to guessing, given its context (symbol table)    */
struct scarl_type_descriptor *assume_type_of_expression_st(struct scarl_symbol_table *current_scope_st, struct scarl_ast_node *expr_node);

/* Determines if the expression can be converted to a requested type given its context (symbol table)  */
int can_coerce_expression_to_type_class(struct scarl_symbol_table *current_scope_st, struct scarl_ast_node *expr_node, struct scarl_type_descriptor *type);

/* Determines if the expression is constant. That is, is its value deterministic at compile time? TRUE/FALSE */
int is_constant_expression(struct scarl_symbol_table *current_scope_st, struct scarl_ast_node *expr_node);
// gets the compile time value of the constant expression (this assumes it has already been checked to be constant)
int eval_constant_expression(struct scarl_symbol_table *current_scope_st, struct scarl_ast_node *expr_node);

// classification functions to help the above functions
int is_bool_operator_node(struct scarl_ast_node *node); // !, &&, ||, <, >, <=, >=, ==
int is_int_operator_node(struct scarl_ast_node *node); // +, -, *, /
int is_int_value_node(struct scarl_ast_node *node); // constant int value
int is_str_value_node(struct scarl_ast_node *node); // identifier node

// initialization
// make sure to verify the input data 
struct scarl_primitive_type *create_primitive_type(int primitive_type);
struct scarl_device_type *create_device_type(int device_type);
struct scarl_pointer_type *create_pointer_type(struct scarl_type_descriptor *pointing_to);
struct scarl_array_type *create_array_type(struct scarl_type_descriptor *containing_type, int length);
struct scarl_function_type *create_function_type(char *func_name, struct scarl_type_descriptor *return_type, struct scarl_type_descriptor *formal_parameters, struct scarl_symbol_table *function_st);
struct scarl_class_type *create_class_type(char *class_name_identifier, char *parent_class_identifier, struct scarl_symbol_table *class_st);
// type descriptors for identifiers - does not create symbol tables 
struct scarl_type_descriptor *create_type_descriptor_for_entry_identifier(struct scarl_symbol_table *current_scope, struct scarl_ast_node *node);
struct scarl_type_descriptor *create_type_descriptor_list_from_formal_parameter_node(struct scarl_symbol_table *current_scope, struct scarl_ast_node *formal_param_node);
// type descriptors for the symbol table entry - creates symbol tables from nodes
// -- has different expectations for nodes than the entry_identifier one 
//struct scarl_type_descriptor *create_type_descriptor_for_symbol_table(struct scarl_symbol_table *current_scope, struct scarl_ast_node *node);
// exact match, TRUE/FALSE equals
int compare_type_descriptors(struct scarl_type_descriptor *lhs, struct scarl_type_descriptor *rhs);

// list functions 
void append_type_descriptor(struct scarl_type_descriptor *lst, struct scarl_type_descriptor *adding);
int get_type_descriptor_list_count(struct scarl_type_descriptor *lst);

// memory management 
int size_of_scarl_type(struct scarl_type_descriptor *type, struct scarl_symbol_table *st);

// debug
char *get_type_class_str(int type_class);

#endif // SCARLTYPES_H_INCLUDED
