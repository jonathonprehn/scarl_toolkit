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


%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "scarltypes.h"
#include "scarlastnode.h"
#include "scarlsymboltable.h"
#include "stringstack.h"

int yylex(void);
void yyerror(char *);
int yydebug = 1;

//for counting line numbers. Lines are incremented in scarl.l
extern unsigned line_number;
//handled in scarl.l. for hinting at where error occured
extern char *last_token_text;
//for passing back to scarl.l, where it is declared
extern struct scarl_ast_node *program_ast;

//for performing actions on the code file
//for the compiling unit, this is intermediatary code
extern FILE *code_file;

unsigned debugging_grammar = 0;

%}

%token IDENTIFIER PLUS MINUS STAR SLASH BANG
%token BOOL INT CHAR POINTER VOID LPAREN RPAREN
%token GTR LESS GTR_EQ LESS_EQ DBL_EQ EQ
%token NOT_EQ OR AND COMMA SEMICOLON IF ELSE
%token WHILE LBRACE RBRACE DECIMAL OCTAL HEX
%token BINARY LIGHT_ACTUATOR SERVO_ACTUATOR
%token SOUND_SENSOR LIGHT_SENSOR DISTANCE_SENSOR
%token TEMPERATURE_SENSOR TRUE FALSE CONSTANT
%token RETURN ALLOCATE DELETE DEREF SUPER CLASS
%token EXTENDS LBRACKET RBRACKET DOT STRING_LITERAL
%token CHAR_LITERAL SERIAL_SENSOR SERIAL_ACTUATOR
%token BYTE


%%

program : statement_list {
	printf("Match program\n");
	//pass the completed AST back to the main program for further processing
	program_ast = $1;
	$$ = $1;
};

statement_list : statement {
    // finish off the statement list
	struct scarl_ast_node *statement_node = $1;
	if (debugging_grammar) printf("Match statement_list (with statement %s)\n", get_ast_node_type_string(statement_node->node_type));
	struct scarl_ast_node *statement_list_node = create_typed_ast_node(NON_TERMINAL_STATEMENT_LIST, NON_TERMINAL_STATEMENT_LIST);
	add_child_node(statement_list_node, statement_node);
	$$ = statement_list_node;
}

statement_list : statement statement_list {
    // add the statement to the statement list
	if (debugging_grammar) printf("Match statement_list\n");
	struct scarl_ast_node *statement_list_node = $2;
	struct scarl_ast_node *statement_node = $1;
	push_child_node_front(statement_list_node, statement_node);
	$$ = statement_list_node;
}

statement : variable_definition_statement {
	if (debugging_grammar) printf("Match statement\n");
	$$ = $1;
}

statement : function_definition_statement {
	if (debugging_grammar) printf("Match statement\n");
	$$ = $1;
}

statement : class_definition_statement {
	if (debugging_grammar) printf("Match statement\n");
	$$ = $1;
}

statement : constant_definition_statement {
	if (debugging_grammar) printf("Match statement\n");
	$$ = $1;
}

statement : variable_declaration_statement {
	if (debugging_grammar) printf("Match statement\n");
	// this is its own node if it is a statement and not a class field 
	$$ = $1;
}

block_statement : LBRACE statement_list_block_level RBRACE {
	if (debugging_grammar) printf("Match block_statement\n");
	$$ = $2;
}

statement_list_block_level : statement_block_level {
    // finish the block level statement list
	if (debugging_grammar) printf("Match statement_list_block_level\n");
	struct scarl_ast_node *statement_list_node = create_typed_ast_node(NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL, NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL);
	struct scarl_ast_node *statement_node = $1;
	add_child_node(statement_list_node, statement_node);
	$$ = statement_list_node;
}

statement_list_block_level : statement_block_level statement_list_block_level {
    // add a block level statement to the statement list
	if (debugging_grammar) printf("Match statement_list_block_level\n");
	struct scarl_ast_node *statement_list_node = $2;
	struct scarl_ast_node *statement_node = $1;
	push_child_node_front(statement_list_node, statement_node);
	$$ = $2;
}

statement_block_level : variable_definition_statement {
	if (debugging_grammar) printf("Match statement_block_level\n");
	$$ = $1;
}

statement_block_level : block_statement {
	if (debugging_grammar) printf("Match statement_block_level\n");
	$$ = $1;
}

statement_block_level : variable_set_statement {
	if (debugging_grammar) printf("Match statement_block_level\n");
	$$ = $1;
}

statement_block_level : function_invocation_statement {
	if (debugging_grammar) printf("Match statement_block_level\n");
	$$ = $1;
}

statement_block_level : if_block_statement {
	if (debugging_grammar) printf("Match statement_block_level\n");
	$$ = $1;
}

statement_block_level : while_block_statement {
	if (debugging_grammar) printf("Match statement_block_level\n");
	$$ = $1;
}

statement_block_level : return_statement {
	if (debugging_grammar) printf("Match statement_block_level\n");
	$$ = $1;
}

statement_block_level : method_invocation_statement {
	if (debugging_grammar) printf("Match statement_block_level\n");
	$$ = $1;
}

statement_block_level : variable_declaration_statement {
	if (debugging_grammar) printf("Match statement_block_level\n");
	$$ = $1;
}

statement_block_level : delete_statement {
	if (debugging_grammar) printf("Match statement_block_level\n");
	$$ = $1;
}

statement_block_level : constant_definition_statement {
	if (debugging_grammar) printf("Match statement_block_level\n");
	$$ = $1;
}

type_declarator : any_type IDENTIFIER {
    // for any variable declared with a type
	char *declarator_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match type_declarator (%s)\n", declarator_identifier);
	struct scarl_ast_node *type_declarator_node = create_typed_ast_node(NON_TERMINAL_TYPE_DECLARATOR, NON_TERMINAL_TYPE_DECLARATOR);
	struct scarl_ast_node *type_node = $1;
	struct scarl_ast_node *declarator_identifier_node = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, declarator_identifier);
	add_child_node(type_declarator_node, type_node);
	add_child_node(type_declarator_node, declarator_identifier_node);
	$$ = type_declarator_node;
}

any_type : array_type {
	if (debugging_grammar) printf("Match any_type\n");
	$$ = $1;
}

any_type : pointer_type {
	if (debugging_grammar) printf("Match any_type\n");
	$$ = $1;
}

any_type : primitive_type {
	if (debugging_grammar) printf("Match any_type\n");
	$$ = $1;
}

any_type : user_type {
	if (debugging_grammar) printf("Match any_type\n");
	$$ = $1;
}

// new addition - pass device types as parameters (references to the device)
any_type : device_type {
	if (debugging_grammar) printf("Match any_type\n");
	$$ = $1;
}

array_type : any_type LBRACKET arithmetic_expression RBRACKET  {
	if (debugging_grammar) printf("Match array_type\n");
	struct scarl_ast_node *array_type_node = create_typed_ast_node(NON_TERMINAL_ARRAY_TYPE, NON_TERMINAL_ARRAY_TYPE);
	struct scarl_ast_node *type_node = $1;
	struct scarl_ast_node *arithmetic_expression_node = $3;
	add_child_node(array_type_node, type_node);
	add_child_node(array_type_node, arithmetic_expression_node);
	$$ = array_type_node;
}

pointer_type : any_type POINTER {
	if (debugging_grammar) printf("Match pointer_type\n");
	struct scarl_ast_node *pointer_node = create_typed_ast_node(NON_TERMINAL_POINTER_TYPE, NON_TERMINAL_POINTER_TYPE);
	struct scarl_ast_node *type_node = $1;
	add_child_node(pointer_node, type_node);
	$$ = pointer_node;
}

user_type : IDENTIFIER {
	char *user_type_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match user_type (%s)\n", user_type_identifier);
	$$ = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, user_type_identifier);
}

variable_definition_statement : type_declarator EQ expression SEMICOLON {
    // we must ensure that the evaluated type
    // on the right hand side of the = sign is
    // the same type or can be converted to the
    // type on the left hand side
	if (debugging_grammar) printf("Match variable_definition_statement\n");
	struct scarl_ast_node *variable_definition_statement_node = create_typed_ast_node(NON_TERMINAL_VARIABLE_DEFINITION_STATEMENT, NON_TERMINAL_VARIABLE_DEFINITION_STATEMENT);
	struct scarl_ast_node *type_declarator_node = $1;
	struct scarl_ast_node *expression_node = $3;
	add_child_node(variable_definition_statement_node, type_declarator_node);
	add_child_node(variable_definition_statement_node, expression_node);
	$$ = variable_definition_statement_node;
}

variable_declaration_statement : type_declarator SEMICOLON {
	// declares a variable without giving it a value - cannot
	// refer to this variable without assigning it, otherwise 
	// the compiler will give an error
	if (debugging_grammar) printf("Match variable_declaration_statement\n");
	struct scarl_ast_node *variable_declaration_node = create_typed_ast_node(NON_TERMINAL_VARIABLE_DECLARATION_STATEMENT, NON_TERMINAL_VARIABLE_DECLARATION_STATEMENT);
	add_child_node(variable_declaration_node, $1);
	$$ = variable_declaration_node;
}

delete_statement : DELETE IDENTIFIER SEMICOLON {
	// for deallocating a pointer variable
	// be sure this only occurs on pointer types 
	char *deleting_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match delete_statement (%s)\n", deleting_identifier);
	struct scarl_ast_node *delete_statement_node = create_typed_ast_node(NON_TERMINAL_DELETE_STATEMENT, NON_TERMINAL_DELETE_STATEMENT);
	struct scarl_ast_node *deleting_identifier_node = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, deleting_identifier);
	add_child_node(delete_statement_node, deleting_identifier_node);
	$$ = delete_statement_node;
}

constant_definition_statement : CONSTANT type_declarator EQ expression SEMICOLON {
    // functions like the variable_definition_statement
    // except it can only be in global scope and
    // the value will be evaluated at compile time
    // (array lengths can be defined as literals or constant values)
	if (debugging_grammar) printf("Match constant_definition_statement\n");
	struct scarl_ast_node *const_set_statement_node = create_typed_ast_node(NON_TERMINAL_CONSTANT_DEFINITION_STATEMENT, NON_TERMINAL_CONSTANT_DEFINITION_STATEMENT);
	struct scarl_ast_node *type_declarator_node = $2;
	struct scarl_ast_node *expression_node = $4;
	add_child_node(const_set_statement_node, type_declarator_node);
	add_child_node(const_set_statement_node, expression_node);
	$$ = const_set_statement_node;
}

class_definition_statement : class_declarator class_body {
    // add this declared class into the symbol
    // table for global scope (classes can only be
    // declared in global scope) and give it the
    // type attributes listed in the class body
	if (debugging_grammar) printf("Match class_definition_statement\n");
	struct scarl_ast_node *class_definition_statement_node = create_typed_ast_node(NON_TERMINAL_CLASS_DEFINITION_STATEMENT, NON_TERMINAL_CLASS_DEFINITION_STATEMENT);
	struct scarl_ast_node *class_declarator_node = $1;
	struct scarl_ast_node *class_body_node = $2;
	add_child_node(class_definition_statement_node, class_declarator_node);
	add_child_node(class_definition_statement_node, class_body_node);
	$$ = class_definition_statement_node;
}

class_declarator : class_name {
    // this class declarator is a "normal"
    // class. It is not derived from another
    // class
	if (debugging_grammar) printf("Match class_declarator\n");
	struct scarl_ast_node *class_declarator_node = create_typed_ast_node(NON_TERMINAL_CLASS_DECLARATOR, NON_TERMINAL_CLASS_DECLARATOR);
	struct scarl_ast_node *class_name_node = $1;
	add_child_node(class_declarator_node, class_name_node);
	$$ = class_declarator_node;
}

class_declarator : class_name class_extending {
    // this class is derived from some other
    // class. We need to ensure that the
    // "extending" class already exists in
    // the symbol table before we can place
    // this derived one in the symbol table too
    // (we are going to refer to the parent class
    //  to construct this class definition)

    // the check for it the extending class exists
    // takes place in the class_extending production rule
	if (debugging_grammar) printf("Match class_declarator\n");
	struct scarl_ast_node *class_declarator_node = create_typed_ast_node(NON_TERMINAL_CLASS_DECLARATOR, NON_TERMINAL_CLASS_DECLARATOR);
	struct scarl_ast_node *class_name_node = $1;
	struct scarl_ast_node *class_extending_node = $2;
	add_child_node(class_declarator_node, class_name_node);
	add_child_node(class_declarator_node, class_extending_node);
	$$ = class_declarator_node;
}

class_name : CLASS IDENTIFIER {
    // ensure that the identifier is not
    // being used for something else in
    // this (global) scope
	char *class_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match class_name (%s)\n", class_identifier);
	$$ = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, class_identifier);
}

class_extending : EXTENDS IDENTIFIER {
    // we need to ensure that the
    // identifier is actually a class
    // name defined in the symbol table
	char *extending_class_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match class_extending (%s)\n", extending_class_identifier);
	$$ = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, extending_class_identifier);
}

class_body : LBRACE class_attribute_list RBRACE {
    // a list of class attributes
    // processing takes place in the
    // class_definition_statement
    // production rule
	if (debugging_grammar) printf("Match class_body\n");
	$$ = $2;
}

class_attribute_list : class_attribute {
    // finish off the class attribute list
	if (debugging_grammar) printf("Match class_attribute_list\n");
	struct scarl_ast_node *class_attribute_list_node = create_typed_ast_node(NON_TERMINAL_CLASS_ATTRIBUTE_LIST, NON_TERMINAL_CLASS_ATTRIBUTE_LIST);
	struct scarl_ast_node *class_attribute_node = $1;
	add_child_node(class_attribute_list_node, class_attribute_node);
	$$ = class_attribute_list_node;
}

class_attribute_list : class_attribute class_attribute_list {
    // add another attribute to the list
	if (debugging_grammar) printf("Match class_attribute_list\n");
	struct scarl_ast_node *class_attribute_node = $1;
	struct scarl_ast_node *class_attribute_list_node = $2;
	push_child_node_front(class_attribute_list_node, class_attribute_node);
	$$ = class_attribute_list_node;
}

class_attribute : function_definition_statement {
    // a special location for functions
    // this function definition is actually
    // going to be a method for this class
	if (debugging_grammar) printf("Match class_attribute\n");
	$$ = $1;
}

class_attribute : variable_declaration_statement {
    // a special kind of declarator
    // that does not require an initial
    // value. This can only take place
    // in a class body. This will be
    // a field for instances of this class
	if (debugging_grammar) printf("Match class_attribute\n");
	$$ = $1;
}

function_definition_statement : any_type IDENTIFIER LPAREN formal_parameter_list RPAREN block_statement {
    // functions will only be able to return
    // primitives for this version. Hopefully
    // extend it to pointer types later on. Can
    // always pass pointer types as parameters
    // to functions
	char *function_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match function_definition_statement (%s)\n", function_identifier);
	struct scarl_ast_node *function_definition_statement_node = create_typed_ast_node(NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT, NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT);
	struct scarl_ast_node *any_type_node = $1;
	struct scarl_ast_node *function_identifier_node = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, function_identifier);
	struct scarl_ast_node *formal_parameter_list_node = $4;
	struct scarl_ast_node *block_statement_node = $6;
	add_child_node(function_definition_statement_node, any_type_node);
	add_child_node(function_definition_statement_node, function_identifier_node);
	add_child_node(function_definition_statement_node, formal_parameter_list_node);
	add_child_node(function_definition_statement_node, block_statement_node);
	$$ = function_definition_statement_node;
}

variable_set_statement : IDENTIFIER EQ expression SEMICOLON {
    // sets the value for the identifier to the evaluated
    // value of the expression. Need to ensure that the type
    // of the identifier matches or can be converted to the type
    // of the expression. Also ensure that the identifier is in scope
	char *variable_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match variable_set_statement (%s)\n", variable_identifier);
	struct scarl_ast_node *variable_set_statement_node = create_typed_ast_node(NON_TERMINAL_VARIABLE_SET_STATEMENT, NON_TERMINAL_VARIABLE_SET_STATEMENT);
	struct scarl_ast_node *variable_identifier_node = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, variable_identifier);
	struct scarl_ast_node *expression_node = $3;
	add_child_node(variable_set_statement_node, variable_identifier_node);
	add_child_node(variable_set_statement_node, expression_node);
	$$ = variable_set_statement_node;
}

return_statement : RETURN expression SEMICOLON {
    // can only appear in functions.
    // acts like a normal C return statement
    // the expression type for all return
    // statements in a function must match
    // the return type for that function

    // additionally, void functions cannot have
    // return statements with expressions
	if (debugging_grammar) printf("Match return_statement\n");
	struct scarl_ast_node *return_statement_node = create_typed_ast_node(NON_TERMINAL_RETURN_STATEMENT, NON_TERMINAL_RETURN_STATEMENT);
	struct scarl_ast_node *expression_node = $2;
	add_child_node(return_statement_node, expression_node);
	$$ = return_statement_node;
}

return_statement : RETURN SEMICOLON {
    // empty return statement.
    // can only occur in void functions
	if (debugging_grammar) printf("Match return_statement\n");
	$$ = create_typed_ast_node(NON_TERMINAL_RETURN_STATEMENT, NON_TERMINAL_RETURN_STATEMENT);
}

function_invocation : IDENTIFIER LPAREN parameter_list RPAREN {
    // invoke the function with the name
    // of identifier. The types of the parameters
    // must match that of a defined invocation

    // this may also be a call to a constructor
    // in which case the identifier must also
    // be checked against a class name and
    // the parameter list against the class's
    // constructors
	char *function_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match function_invocation (%s)\n", function_identifier);
	struct scarl_ast_node *function_invocation_node = create_typed_ast_node(NON_TERMINAL_FUNCTION_INVOCATION, NON_TERMINAL_FUNCTION_INVOCATION);
	struct scarl_ast_node *identifier_node = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, function_identifier);
	struct scarl_ast_node *parameter_list_node = $3;
	add_child_node(function_invocation_node, identifier_node);
	add_child_node(function_invocation_node, parameter_list_node);
	$$ = function_invocation_node;
}

function_invocation_statement : function_invocation SEMICOLON {
    // allows for there to be statements that
    // only call functions
	if (debugging_grammar) printf("Match function_invocation_statement\n");
	$$ = $1;
}

method_invocation : class_attribute_identifier LPAREN parameter_list RPAREN {
    // requires more heavy lifting than
    // a function invocation because we need
    // to resolve the scope to where the
    // class_attribute_identifier leads to.
    // A method invocation is calling a
    // method of an object instance
	if (debugging_grammar) printf("Match method_invocation\n");
	struct scarl_ast_node *method_invocation_node = create_typed_ast_node(NON_TERMINAL_METHOD_INVOCATION, NON_TERMINAL_METHOD_INVOCATION);
	struct scarl_ast_node *class_attribute_identifier_node = $1;
	struct scarl_ast_node *parameter_list_node = $3;
	add_child_node(method_invocation_node, class_attribute_identifier_node);
	add_child_node(method_invocation_node, parameter_list_node);
	$$ = method_invocation_node;
}

method_invocation_statement : method_invocation SEMICOLON {
    // allows for a statement to be only
    // a method invocation
	if (debugging_grammar) printf("Match method_invocation_statement\n");
	$$ = $1;
}


class_attribute_identifier : IDENTIFIER DOT IDENTIFIER {
    // the last case in the chain of
    // identifiers dot identifiers for a method
    // identifier
    // this could also just lead to a field of
    // an object instance, not a method
	char *second_identifier = string_stack_pop();
	char *first_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match class_attribute_identifier (%s.%s)\n", first_identifier, second_identifier);
	struct scarl_ast_node *class_attribute_node = create_typed_ast_node(NON_TERMINAL_CLASS_ATTRIBUTE_IDENTIFIER, NON_TERMINAL_CLASS_ATTRIBUTE_IDENTIFIER);
	struct scarl_ast_node *first_identifier_node = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, $1);
	struct scarl_ast_node *second_identifier_node = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, $3);
	// this node's value is the sum of its children (an ordered list of identifiers)
	add_child_node(class_attribute_node, first_identifier_node);
	add_child_node(class_attribute_node, second_identifier_node);
	$$ = class_attribute_node;
}

class_attribute_identifier : IDENTIFIER DOT class_attribute_identifier {
    // enables the dot operator to
    // act as far as it needs to to
    // get to where a field or method is
    // this could also just lead to a field of
    // an object instance, not a method
	char *identifier = string_stack_pop();
	if (debugging_grammar) printf("Match class_attribute_identifier (%s.<more stuff>)\n", identifier);
	// we want the children to appear in the order as  they do in the code for the AST
	struct scarl_ast_node *next_identifier = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, $1);
	struct scarl_ast_node *class_attribute_identifier_node = $3;
	push_child_node_front(class_attribute_identifier_node, next_identifier);
	$$ = class_attribute_identifier_node;
}

if_block_statement : IF LPAREN expression RPAREN block_statement {
    // if without else
	if (debugging_grammar) printf("Match if_block_statement\n");
	struct scarl_ast_node *if_statement_node = create_typed_ast_node(NON_TERMINAL_IF_BLOCK_STATEMENT, NON_TERMINAL_IF_BLOCK_STATEMENT);
	struct scarl_ast_node *expression_node = $3;
	struct scarl_ast_node *block_statement_node = $5;
	add_child_node(if_statement_node, expression_node);
	add_child_node(if_statement_node, block_statement_node);
	$$ = if_statement_node;
}

if_block_statement : IF LPAREN expression RPAREN block_statement ELSE block_statement {
    // if with else
	if (debugging_grammar) printf("Match if_block_statement\n");
	struct scarl_ast_node *if_statement_node = create_typed_ast_node(NON_TERMINAL_IF_BLOCK_STATEMENT, NON_TERMINAL_IF_BLOCK_STATEMENT);
	struct scarl_ast_node *expression_node = $3;
	struct scarl_ast_node *if_true_block_statement_node = $5;
	struct scarl_ast_node *if_false_block_statement_node = $7;
	add_child_node(if_statement_node, expression_node);
	add_child_node(if_statement_node, if_true_block_statement_node);
	add_child_node(if_statement_node, if_false_block_statement_node);
	$$ = if_statement_node;
}

while_block_statement : WHILE LPAREN expression RPAREN block_statement {
    // regular while statement.
	if (debugging_grammar) printf("Match while_block_statement\n");
	struct scarl_ast_node *while_statement_node = create_typed_ast_node(NON_TERMINAL_WHILE_BLOCK_STATEMENT, NON_TERMINAL_WHILE_BLOCK_STATEMENT);
	struct scarl_ast_node *expression_node = $3;
	struct scarl_ast_node *block_statement_node = $5;
	add_child_node(while_statement_node, expression_node);
	add_child_node(while_statement_node, block_statement_node);
	$$ = while_statement_node;
}



formal_parameter_list : type_declarator {
    // finish the rest of the formal parameter
    // list or this function has 1 parameter
	if (debugging_grammar) printf("Match formal_parameter_list\n");
	struct scarl_ast_node *parameter_list_node = create_typed_ast_node(NON_TERMINAL_FORMAL_PARAMETER_LIST, NON_TERMINAL_FORMAL_PARAMETER_LIST);
	struct scarl_ast_node *type_declarator_node = $1;
	add_child_node(parameter_list_node, type_declarator_node);
	$$ = parameter_list_node;
}

formal_parameter_list : type_declarator COMMA formal_parameter_list {
    // continue the list of formal parameters
	if (debugging_grammar) printf("Match formal_parameter_list\n");
	struct scarl_ast_node *type_declarator_node = $1;
	struct scarl_ast_node *formal_parameter_list_node = $3;
	push_child_node_front(formal_parameter_list_node, type_declarator_node);
	$$ = formal_parameter_list_node;
}

formal_parameter_list : {
    // allow for empty parameter lists
	if (debugging_grammar) printf("Match formal_parameter_list\n");
	$$ = create_typed_ast_node(NON_TERMINAL_FORMAL_PARAMETER_LIST, NON_TERMINAL_FORMAL_PARAMETER_LIST);
}

parameter_list : expression {
    // finish the rest of the  parameter
    // list or this function has 1 argument
	if (debugging_grammar) printf("Match parameter_list (one expression)\n");
	struct scarl_ast_node *parameter_list_node = create_typed_ast_node(NON_TERMINAL_PARAMETER_LIST, NON_TERMINAL_PARAMETER_LIST);
	struct scarl_ast_node *expression_node = $1;
	push_child_node_front(parameter_list_node, expression_node);
	$$ = parameter_list_node;
}

parameter_list : expression COMMA parameter_list {
    // continue the list of argument
	if (debugging_grammar) printf("Match parameter_list (expression list)\n");
	struct scarl_ast_node *expression_node = $1;
	struct scarl_ast_node *parameter_list_node = $3;
	add_child_node(parameter_list_node, expression_node);
	$$ = parameter_list_node;
}

parameter_list : {
    // allow for empty argument function calls
	if (debugging_grammar) printf("Match parameter_list (empty list)\n");
	// create an empty parameter list 
	$$ = create_typed_ast_node(NON_TERMINAL_PARAMETER_LIST, NON_TERMINAL_PARAMETER_LIST);
}

expression : logical_expression {
    // base expression
	if (debugging_grammar) printf("Match expression\n");
	$$ = $1;
}

expression : allocation_expression {
    // allocates are a special kind of
    // expression that can only occur
    // by themselves
	if (debugging_grammar) printf("Match expression\n");
	$$ = $1;
}

allocation_expression : ALLOCATE allocation_invocation {
    // the allocation invocation is
    // a special kind of function invocation
    // that needs its own production rule to
    // avoid confusion
	if (debugging_grammar) printf("Match allocation_expression\n");
	$$ = $2; // obvious that this is an allocation, unless NON_TERMINAL_POINTER_VALUE ends up showin elsewhere
}

// NOTE for allocation_invocation

// can "call" a primitive type
// or a user type and then give
// the constructor a list of parameters
// that must either be a single expression
// that evaluates to the primitive type
// or can be converted to the primitive type
// or match the formal parameters to one of
// the constructors for the allocating user type

allocation_invocation : primitive_type LPAREN parameter_list RPAREN {
    // primitive allocation
	if (debugging_grammar) printf("Match allocation_invocation\n");
	struct scarl_ast_node *allocate_node = create_typed_ast_node(NON_TERMINAL_POINTER_VALUE, NON_TERMINAL_POINTER_VALUE);
	struct scarl_ast_node *primitive_type_node = $1;
	struct scarl_ast_node *parameter_list_node = $3;
	add_child_node(allocate_node, primitive_type_node); // type defined as a pointer of this type 
	add_child_node(allocate_node, parameter_list_node); // constructed with these parameters
	$$ = allocate_node;
}

allocation_invocation : user_type LPAREN parameter_list RPAREN {
    // class type allocation
    // identifier must be a class in the
    // symbol table and the parameter list
    // must match one of the constructors
	char *allocating_type_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match allocation_invocation\n", allocating_type_identifier);
	struct scarl_ast_node *allocate_node = create_typed_ast_node(NON_TERMINAL_POINTER_VALUE, NON_TERMINAL_POINTER_VALUE);
	struct scarl_ast_node *identifier_node = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, allocating_type_identifier);
	struct scarl_ast_node *parameter_list_node = $3;
	add_child_node(allocate_node, identifier_node); // type defined as a pointer of this type 
	add_child_node(allocate_node, parameter_list_node); // constructed with these parameters
	$$ = allocate_node;
}

logical_expression : logical_and_expression {
	if (debugging_grammar) printf("Match logical_expression\n");
	$$ = $1;
}

logical_expression : logical_expression OR logical_and_expression {
	//     logical_expression && logical_and_expression
	//     logical_expression should be on the LEFT
	//     logical_and_expression should be on the RIGHT
	//     OR should be the parent node
	if (debugging_grammar) printf("Match logical_expression\n");
	struct scarl_ast_node *lhs = $1;
	struct scarl_ast_node *operand = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, OR);
	struct scarl_ast_node *rhs = $3;
	add_child_node(operand, lhs);
	add_child_node(operand, rhs);
	$$ = operand;
}

logical_and_expression : equality_expression {
	if (debugging_grammar) printf("Match logical_and_expression\n");
	$$ = $1;
}

logical_and_expression : logical_and_expression AND equality_expression {
	//     logical_and_expression && equality_expression
	//     logical_and_expression should be on the LEFT
	//     equality_expression should be on the RIGHT
	//     AND should be the parent node
	if (debugging_grammar) printf("Match logical_and_expression\n");
	struct scarl_ast_node *lhs = $1;
	struct scarl_ast_node *operand = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, AND);
	struct scarl_ast_node *rhs = $3;
	add_child_node(operand, lhs);
	add_child_node(operand, rhs);
	$$ = operand;
}

equality_expression : relational_expression {
	if (debugging_grammar) printf("Match equality_expression\n");
	$$ = $1;
}

equality_expression : equality_expression DBL_EQ relational_expression {
	//     equality_expression == relational_expression
	//     equality_expression should be on the LEFT
	//     relational_expression should be on the RIGHT
	//     NOT_EQ should be the parent node
	if (debugging_grammar) printf("Match equality_expression\n");
	struct scarl_ast_node *lhs = $1;
	struct scarl_ast_node *operand = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, DBL_EQ);
	struct scarl_ast_node *rhs = $3;
	add_child_node(operand, lhs);
	add_child_node(operand, rhs);
	$$ = operand;
}

equality_expression : equality_expression NOT_EQ relational_expression {
	//     equality_expression != relational_expression
	//     equality_expression should be on the LEFT
	//     relational_expression should be on the RIGHT
	//     NOT_EQ should be the parent node
	if (debugging_grammar) printf("Match equality_expression\n");
	struct scarl_ast_node *lhs = $1;
	struct scarl_ast_node *operand = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, NOT_EQ);
	struct scarl_ast_node *rhs = $3;
	add_child_node(operand, lhs);
	add_child_node(operand, rhs);
	$$ = operand;
}

relational_expression : bool_expression {
	if (debugging_grammar) printf("Match relational_expression\n");
	$$ = $1;
}

relational_expression : relational_expression GTR bool_expression {
	//     relational_expression > bool_expression
	//     relational_expression should be on the LEFT
	//     bool_expression should be on the RIGHT
	//     GTR should be the parent node
	if (debugging_grammar) printf("Match relational_expression\n");
	struct scarl_ast_node *lhs = $1;
	struct scarl_ast_node *operand = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, GTR);
	struct scarl_ast_node *rhs = $3;
	add_child_node(operand, lhs);
	add_child_node(operand, rhs);
	$$ = operand;
}

relational_expression : relational_expression LESS bool_expression {
	//     relational_expression < bool_expression
	//     relational_expression should be on the LEFT
	//     bool_expression should be on the RIGHT
	//     LESS should be the parent node
	if (debugging_grammar) printf("Match relational_expression\n");
	struct scarl_ast_node *lhs = $1;
	struct scarl_ast_node *operand = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, LESS);
	struct scarl_ast_node *rhs = $3;
	add_child_node(operand, lhs);
	add_child_node(operand, rhs);
	$$ = operand;
}

relational_expression : relational_expression GTR_EQ bool_expression {
	//     relational_expression >= bool_expression
	//     relational_expression should be on the LEFT
	//     bool_expression should be on the RIGHT
	//     GTR_EQ should be the parent node
	if (debugging_grammar) printf("Match relational_expression\n");
	struct scarl_ast_node *lhs = $1;
	struct scarl_ast_node *operand = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, GTR_EQ);
	struct scarl_ast_node *rhs = $3;
	add_child_node(operand, lhs);
	add_child_node(operand, rhs);
	$$ = operand;
}

relational_expression : relational_expression LESS_EQ bool_expression {
	//     relational_expression <= bool_expression
	//     relational_expression should be on the LEFT
	//     bool_expression should be on the RIGHT
	//     LESS_EQ should be the parent node
	if (debugging_grammar) printf("Match relational_expression\n");
	struct scarl_ast_node *lhs = $1;
	struct scarl_ast_node *operand = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, LESS_EQ);
	struct scarl_ast_node *rhs = $3;
	add_child_node(operand, lhs);
	add_child_node(operand, rhs);
	$$ = operand;
}

bool_expression : arithmetic_expression {
	if (debugging_grammar) printf("Match bool_expression\n");
	$$ = $1;
}

bool_expression : BANG arithmetic_expression {
	if (debugging_grammar) printf("Match bool_expression\n");
	struct scarl_ast_node *operand = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, BANG);
	struct scarl_ast_node *expression = $2;
	add_child_node(operand, expression);
	$$ = operand;
}

arithmetic_expression : arithmetic_factor {
	if (debugging_grammar) printf("Match arithmetic_expression\n");
	$$ = $1;
}

arithmetic_expression : arithmetic_expression PLUS arithmetic_factor {
	//     arithmetic_expression - arithmetic_factor
	//     arithmetic_expression should be on the LEFT
	//     arithmetic_factor should be on the RIGHT
	//     MINUS should be the parent node
	if (debugging_grammar) printf("Match arithmetic_expression\n");
	struct scarl_ast_node *lhs = $1;
	struct scarl_ast_node *operand = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, PLUS);
	struct scarl_ast_node *rhs = $3;
	add_child_node(operand, lhs);
	add_child_node(operand, rhs);
	$$ = operand;
}

arithmetic_expression : arithmetic_expression MINUS arithmetic_factor {
	//     arithmetic_expression - arithmetic_factor
	//     arithmetic_expression should be on the LEFT
	//     arithmetic_factor should be on the RIGHT
	//     MINUS should be the parent node
	if (debugging_grammar) printf("Match arithmetic_expression\n");
	struct scarl_ast_node *lhs = $1;
	struct scarl_ast_node *operand = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, MINUS);
	struct scarl_ast_node *rhs = $3;
	add_child_node(operand, lhs);
	add_child_node(operand, rhs);
	$$ = operand;
}

arithmetic_factor : arithmetic_unary {
	if (debugging_grammar) printf("Match arithmetic_factor\n");
	$$ = $1;
}

arithmetic_factor : arithmetic_factor STAR arithmetic_unary {
	//     arithmetic_factor * arithmetic_unary
	//     arithmetic_factor should be on the LEFT
	//     arithmetic_unary should be on the RIGHT
	//     STAR should be the parent node
	if (debugging_grammar) printf("Match arithmetic_factor\n");
	struct scarl_ast_node *lhs = $1;
	struct scarl_ast_node *operand = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, STAR);
	struct scarl_ast_node *rhs = $3;
	add_child_node(operand, lhs);
	add_child_node(operand, rhs);
	$$ = operand;
}

arithmetic_factor : arithmetic_factor SLASH arithmetic_unary {
	//     arithmetic_factor / arithmetic_unary
	//     arithmetic_factor should be on the LEFT
	//     arithmetic_unary should be on the RIGHT
	//     SLASH should be the parent node
	if (debugging_grammar) printf("Match arithmetic_factor\n");
	struct scarl_ast_node *lhs = $1;
	struct scarl_ast_node *operand = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, SLASH);
	struct scarl_ast_node *rhs = $3;
	add_child_node(operand, lhs);
	add_child_node(operand, rhs);
	$$ = operand;
}

arithmetic_unary : unit {
	if (debugging_grammar) printf("Match arithmetic_unary\n");
	$$ = $1;
}

arithmetic_unary : MINUS arithmetic_unary {
	if (debugging_grammar) printf("Match arithmetic_unary\n");
	struct scarl_ast_node *unary_node = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, MINUS);
	struct scarl_ast_node *arithmetic_unary_node = $2;
	add_child_node(unary_node, arithmetic_unary_node);
	$$ = unary_node;
}

arithmetic_unary : LPAREN arithmetic_expression RPAREN {
	if (debugging_grammar) printf("Match arithmetic_unary\n");
	$$ = $2;
}

unit : IDENTIFIER {
	char *identifier = string_stack_pop();
	if (debugging_grammar) printf("Match unit (%s)\n", identifier);
	$$ = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, identifier);
}

unit : integer_value {
	if (debugging_grammar) printf("Match unit\n");
	$$ = $1;
}

unit : char_value {
	if (debugging_grammar) printf("Match unit\n");
	$$ = $1;
}

unit : bool_value {
	if (debugging_grammar) printf("Match unit\n");
	$$ = $1;
}

unit : function_invocation {
	if (debugging_grammar) printf("Match unit\n");
	$$ = $1;
}

unit : array_accessor_unit {
	if (debugging_grammar) printf("Match unit\n");
	$$ = $1;
}

unit : method_invocation {
	if (debugging_grammar) printf("Match unit\n");
	$$ = $1;
}

unit : dereferenced_pointer {
	if (debugging_grammar) printf("Match unit\n");
	$$ = $1;
}

unit : array_value {
	if (debugging_grammar) printf("Match unit\n");
	$$ = $1;
}

array_accessor_unit : IDENTIFIER LBRACKET arithmetic_expression RBRACKET {
    // ensure that the used identifier is
    // an array type
	char *array_variable_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match array_accessor_unit (%s)\n", array_variable_identifier);
	struct scarl_ast_node *array_accessor_unit = create_typed_ast_node(NON_TERMINAL_ARRAY_ACCESSOR_TYPE, NON_TERMINAL_ARRAY_ACCESSOR_TYPE);
	struct scarl_ast_node *identifier_node = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, array_variable_identifier);
	struct scarl_ast_node *arithmetic_expression_node = $3;
	add_child_node(array_accessor_unit, identifier_node);
	add_child_node(array_accessor_unit, arithmetic_expression_node);
	$$ = array_accessor_unit;
}

dereferenced_pointer : DEREF IDENTIFIER {
    // ensure that the identifier
    // is a pointer type that is
    // in this scope
	char *dereferenced_variable_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match dereferenced_pointer\n", dereferenced_variable_identifier);
	struct scarl_ast_node *deref_node = create_typed_ast_node(NON_TERMINAL_DEREFERENCED_VALUE, NON_TERMINAL_DEREFERENCED_VALUE); 
	struct scarl_ast_node *dereferenced_variable_node = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, dereferenced_variable_identifier); 
	add_child_node(deref_node, dereferenced_variable_node);
	$$ = deref_node;
}

array_value : STRING_LITERAL {
	// string literals are syntactic
	// sugar for character arrays
	char *string_literal = string_stack_pop();
	if (debugging_grammar) printf("Match array_value (%s)\n", string_literal);
	struct scarl_ast_node *string_node = create_typed_ast_node(NON_TERMINAL_ARRAY_TYPE, NON_TERMINAL_ARRAY_VALUE);
	// composite value. An array value node has its type and value defined by its children
	for (int i = 1; i < strlen(string_literal) - 1; i++) {
		struct scarl_ast_node *char_value_node = create_int_value_ast_node(NON_TERMINAL_CHAR_VALUE, string_literal[i]);
		printf("Adding character node\n");
		add_child_node(string_node, char_value_node);
	}
	$$ = string_node;
	// NON_TERMINAL_ARRAY_VALUE
}

array_value : array_initializer {
	// array initializer for arbitrarily typed
	// initialzers
	if (debugging_grammar) printf("Match array_value\n");
	$$ = $1;
}

array_initializer : LBRACE parameter_list RBRACE {
	// in order to be a valid array initializer,
	// the types that make up the list of values 
	// must be the same type or must be convertable
	// to a type
	// the type of the array initializer includes
	// the number of elements in the array and the 
	// type of the "parameters"
	if (debugging_grammar) printf("Match array_initializer\n");
	struct scarl_ast_node *parameter_list_node = $2;
	parameter_list_node->node_type = NON_TERMINAL_ARRAY_TYPE;
	parameter_list_node->type_value = NON_TERMINAL_ARRAY_TYPE;
	$$ = parameter_list_node;
	// NON_TERMINAL_ARRAY_VALUE
}

integer_value : DECIMAL {
	int decimal_value = int_stack_pop();
	if (debugging_grammar) printf("Match integer_value (%i)\n", decimal_value);
	$$ = create_int_value_ast_node(NON_TERMINAL_INTEGER_VALUE, decimal_value);
}

integer_value : OCTAL {
	int octal_value = int_stack_pop();
	if (debugging_grammar) printf("Match integer_value (%i)\n", octal_value);
	$$ = create_int_value_ast_node(NON_TERMINAL_INTEGER_VALUE, octal_value);
}

integer_value : HEX {
	int hex_value = int_stack_pop();
	if (debugging_grammar) printf("Match integer_value (%i)\n", hex_value);
	$$ = create_int_value_ast_node(NON_TERMINAL_INTEGER_VALUE, hex_value);
}

integer_value : BINARY {
	int binary_value = int_stack_pop();
	if (debugging_grammar) printf("Match integer_value (%i)\n", binary_value);
	$$ = create_int_value_ast_node(NON_TERMINAL_INTEGER_VALUE, binary_value);
}

char_value : CHAR_LITERAL {
    // ensure that the identifier is
    // only a single character long.
    // this identifier is going to be the
    // value of the character literal, and
    // not actually be an identifier in the
    // language
	char *character_literal = string_stack_pop();
	if (debugging_grammar) printf("Match char_value (%s)\n", character_literal);
	// the int value of this node is the character, just cast it back to retrieve the character
    struct scarl_ast_node *char_value_node = create_int_value_ast_node(NON_TERMINAL_CHAR_VALUE, character_literal[1]);
	free(character_literal);
	$$ = char_value_node;
	// NON_TERMINAL_CHAR_VALUE
}

bool_value : TRUE {
	if (debugging_grammar) printf("Match bool_value\n");
    $$ = create_int_value_ast_node(NON_TERMINAL_BOOL_VALUE, TRUE);
}

bool_value : FALSE {
	if (debugging_grammar) printf("Match bool_value\n");
    $$ = create_int_value_ast_node(NON_TERMINAL_BOOL_VALUE, FALSE);
}

primitive_type : BOOL {
	if (debugging_grammar) printf("Match primitive_type\n");
    $$ = create_typed_ast_node(NON_TERMINAL_PRIMITIVE_TYPE, VOID);
}

primitive_type : INT {
	if (debugging_grammar) printf("Match primitive_type\n");
    $$ = create_typed_ast_node(NON_TERMINAL_PRIMITIVE_TYPE, INT);
}

primitive_type : CHAR {
	if (debugging_grammar) printf("Match primitive_type\n");
    $$ = create_typed_ast_node(NON_TERMINAL_PRIMITIVE_TYPE, CHAR);
}

primitive_type : VOID  {
	if (debugging_grammar) printf("Match primitive_type\n");
    $$ = create_typed_ast_node(NON_TERMINAL_PRIMITIVE_TYPE, VOID);
}

primitive_type : BYTE  {
	if (debugging_grammar) printf("Match primitive_type\n");
    $$ = create_typed_ast_node(NON_TERMINAL_PRIMITIVE_TYPE, BYTE);
}

device_type : LIGHT_ACTUATOR {
	if (debugging_grammar) printf("Match device_type\n");
    $$ = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, LIGHT_ACTUATOR);
}

device_type : SERVO_ACTUATOR {
	if (debugging_grammar) printf("Match device_type\n");
    $$ = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, SERVO_ACTUATOR);
}

device_type : SOUND_SENSOR {
	if (debugging_grammar) printf("Match device_type\n");
    $$ = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, SOUND_SENSOR);
}

device_type : LIGHT_SENSOR {
	if (debugging_grammar) printf("Match device_type\n");
    $$ = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, LIGHT_SENSOR);
}

device_type : DISTANCE_SENSOR {
	if (debugging_grammar) printf("Match device_type\n");
    $$ = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, DISTANCE_SENSOR);
}

device_type : TEMPERATURE_SENSOR {
	if (debugging_grammar) printf("Match device_type\n");
	$$ = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, TEMPERATURE_SENSOR);
}

device_type : SERIAL_SENSOR {
	if (debugging_grammar) printf("Match device_type\n");
	$$ = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, SERIAL_SENSOR);
}

device_type : SERIAL_ACTUATOR {
	if (debugging_grammar) printf("Match device_type\n");
	$$ = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, SERIAL_ACTUATOR);
}


%%

void yyerror(char *s) {
	fprintf(stderr, "%s at line %i near \'%s\'\n", s, line_number, last_token_text);
}
