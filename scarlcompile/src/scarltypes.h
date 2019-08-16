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
#define NON_TERMINAL_DEVICE_DECLARATOR_STATEMENT	0x307
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

#define TYPES_EQUAL									0x400
#define TYPES_CONVERTABLE							0x401
#define TYPES_NOT_EQUAL								0x402

#define PRIMITIVE_TYPE								0x403
#define POINTER_TYPE								0x404
#define ARRAY_TYPE									0x405
#define FUNCTION_TYPE								0x406
#define CLASS_TYPE									0x407
#define DEVICE_TYPE									0x408


// We have primitive types, pointer types, array types,
// function types and class types
// all type definitions besides primitive types rely
// on other Type_Descriptor objects to be constructed.

struct scarl_type_descriptor {
	int type_class;
};

struct scarl_primitive_type {
	int type_class; // Must be PRIMITIVE_TYPE
    int primitive_type;
};

struct scarl_pointer_type {
	int type_class; // Must be POINTER_TYPE
    struct scarl_type_descriptor *pointingTo;
};

struct scarl_array_type {
	int type_class; // Must be ARRAY_TYPE
    struct scarl_type_descriptor *containingType;
    int length;
};

struct scarl_function_type {
    int type_class; // Must be FUNCTION_TYPE
	struct type_descriptor *returnType;
	//need to support a list type
    //formalParameters;
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

struct scarl_class_type;

struct scarl_class_type {
	int type_class;
	struct scarl_class_type *parent_class;
	//descendents
	//fields
	//methods
};

// global functions related to class relations

/* Is the right hand side a descendent of the left hand side? */
int is_descendant_of(struct scarl_class_type *lhs, struct scarl_class_type *rhs);

/* Is the right hand side a direct descendent (immediate child) of the left hand side? */
int is_direct_descendant_of(struct scarl_class_type *lhs, struct scarl_class_type *rhs);

/* Is the right hand side an ancestor of the left hand side? */
int is_ancestor_of(struct scarl_class_type *lhs, struct scarl_class_type *rhs);


#endif // SCARLTYPES_H_INCLUDED
