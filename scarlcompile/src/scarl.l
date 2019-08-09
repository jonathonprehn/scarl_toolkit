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
#include <stdlib.h>
#include <string.h>

#include "stringstack.h"
#include "linked_list.h"
#include "y.tab.h"

unsigned line_number = 0;
char *last_token_text = NULL;
FILE *code_file = NULL;

void setLastTokenText(char *txt) {
	if (last_token_text != NULL) {
		free(last_token_text);
		last_token_text = NULL;
	}
	last_token_text = strdup(txt);
}

%}

letter [a-zA-Z]
digit [0-9]
nonzero_digit [1-9]
binary_digit [01]
octal_digit [0-7]
hex_digit [0-9a-fA-F]

%%

"//".*   { /*Ignore everything for the rest of this line */ }
[ \t]+	{ /* Do nothing for whitespace */ }
[\n]	{ /*Count lines for debug*/ line_number++; }
\"[^\n]*\" 		{  
	setLastTokenText(yytext);
	string_stack_push(yytext);  // retrieve at parser
	return STRING_LITERAL;
}
{letter}({letter}|{digit})*	  {
	//can set up a binary search later
	setLastTokenText(yytext);

	if (strcmp(yytext, "LightActuator") == 0)
	{
		return LIGHT_ACTUATOR;
	}
	else if (strcmp(yytext, "ServoActuator") == 0)
	{
		return SERVO_ACTUATOR;
	}
	else if (strcmp(yytext, "SoundSensor") == 0)
	{
		return SOUND_SENSOR;
	}
	else if (strcmp(yytext, "LightSensor") == 0)
	{
		return LIGHT_SENSOR;
	}
	else if (strcmp(yytext, "DistanceSensor") == 0)
	{
		return DISTANCE_SENSOR;
	}
	else if (strcmp(yytext, "TemperatureSensor") == 0)
	{
		return TEMPERATURE_SENSOR;
	}
	else if (strcmp(yytext, "true") == 0)
	{
		return TRUE;
	}
	else if (strcmp(yytext, "false") == 0)
	{
		return FALSE;
	}
	else if (strcmp(yytext, "bool") == 0)
	{
		return BOOL;
	}
	else if (strcmp(yytext, "int") == 0)
	{
		return INT;
	}
	else if (strcmp(yytext, "char") == 0)
	{
		return CHAR;
	}
	else if (strcmp(yytext, "pointer") == 0)
	{
		return POINTER;
	}
	else if (strcmp(yytext, "if") == 0)
	{
		return IF;
	}
	else if (strcmp(yytext, "else") == 0)
	{
		return ELSE;
	}
	else if (strcmp(yytext, "pointer") == 0)
	{
		return POINTER;
	}
	else if (strcmp(yytext, "while") == 0)
	{
		return WHILE;
	}
	else if (strcmp(yytext, "void") == 0)
	{
		return VOID;
	}
	else if (strcmp(yytext, "return") == 0)
	{
		return RETURN;
	}
	/* Additional reserved words added */
	else if (strcmp(yytext, "allocate") == 0)
	{
        return ALLOCATE;
	}
	else if (strcmp(yytext, "delete") == 0)
	{
        return DELETE;
	}
	else if (strcmp(yytext, "deref") == 0)
	{
        return DEREF;
	}
	else if (strcmp(yytext, "class") == 0)
	{
        return CLASS;
	}
	else if (strcmp(yytext, "super") == 0)
	{
        return SUPER;
	}
	else if (strcmp(yytext, "extends") == 0)
	{
        return EXTENDS;
	}
	else if (strcmp(yytext, "constant") == 0)
	{
        return CONSTANT;
	}
	else if (strcmp(yytext, "platform") == 0)
	{
		fprintf(stderr, "Cannot use \"platform\" as an identifier. Use something else\n");
		exit(0);
		return 0;
	}
	else
	{
		string_stack_push(yytext); // retrieve at parser
		return IDENTIFIER;
	}
}
{nonzero_digit}{digit}*		{
	setLastTokenText(yytext);
	int parsed_value = atoi(yytext);
	int_stack_push(parsed_value);
	return DECIMAL;
}
("0"){octal_digit}+			{
	setLastTokenText(yytext);
	return OCTAL;
}
("0")("x"|"X"){hex_digit}+	{
	setLastTokenText(yytext);
	return HEX;
}
("0b"){binary_digit}+		{
	setLastTokenText(yytext);
	return BINARY;
}
"0" {/* Weird "just 0" case */
	setLastTokenText(yytext);
	return DECIMAL;
}
"+"		{
	setLastTokenText(yytext);
	return PLUS;
}
"-"		{
	setLastTokenText(yytext);
	return MINUS;
}
"*"		{
	setLastTokenText(yytext);
	return STAR;
}
"/"		{
	setLastTokenText(yytext);
	return SLASH;
}
"!"		{
	setLastTokenText(yytext);
	return BANG;
}
"("		{
	setLastTokenText(yytext);
	return LPAREN;
}
")"		{
	setLastTokenText(yytext);
	return RPAREN;
}
">"		{
	setLastTokenText(yytext);
	return GTR;
}
"<"		{
	setLastTokenText(yytext);
	return LESS;
}
">="	{
	setLastTokenText(yytext);
	return GTR_EQ;
}
"<="	{
	setLastTokenText(yytext);
	return LESS_EQ;
}
"=="	{
	setLastTokenText(yytext);
	return DBL_EQ;
}
"="		{
	setLastTokenText(yytext);
	return EQ;
}
"!="	{
	setLastTokenText(yytext);
	return NOT_EQ;
}
"||"	{
	setLastTokenText(yytext);
	return OR;
}
"&&"	{
	setLastTokenText(yytext);
	return AND;
}
","		{
	setLastTokenText(yytext);
	return COMMA;
}
";"		{
	setLastTokenText(yytext);
	return SEMICOLON;
}
"{"		{
	setLastTokenText(yytext);
	return LBRACE;
}
"}"		{
	setLastTokenText(yytext);
	return RBRACE;
}
"["		{
	setLastTokenText(yytext);
	return LBRACKET;
}
"]"		{
	setLastTokenText(yytext);
	return RBRACKET;
}
"."     {
    setLastTokenText(yytext);
    return DOT;
}
\'[^\']\' 	{
	setLastTokenText(yytext);
	string_stack_push(yytext); // to be retrieved by the parser
	return CHAR_LITERAL;
}

.       { setLastTokenText(yytext); fprintf(stderr, "unrecognized characters: \'%s\'\n", yytext); }

%%

int yyparse();

int yywrap() {
	//get the next source file 
	//to be implemented later
	
	return 1;
}

int main(int argc, char *argv[]) {
    printf("Welcome to the SCARL compiler version 2\n");
	
	// process arguments here
	if (argc <= 1) {
		//print help
		
		return 0;
	}
	//otherwise we have arguments to process
	int i;
	int src_file_counter = 0;
	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			// this is an option
			if (i+1 >= argc) {
				fprintf(stderr, "Expected parameter for option %s\n", argv[i]);
				return 1;
			}
			else {
				printf("get option and parameter\n");
				char *option = argv[i];
				char *param = argv[i+1];
				i++;
				
				//process option here
				printf("Processed option %s with parameter %s\n", option, param);
			}
		}
		else {
			// this is a source file 
			// check file extension
			if (src_file_counter > 0) {
				fprintf(stderr, "scarlcompile only supports 1 source file at a time currently\n");
				return 1;
			}
			else {
				yyin = fopen(argv[i], "r");
				if (yyin == NULL) {
					fprintf(stderr, "ERROR: Cannot open or find source code file %s\n", argv[i]);
					return 1;
				}
				else {
					src_file_counter++;
				}
			}
		}
	}
	
	printf("Compiling file...\n");
	
	line_number = 1;
	extern FILE *yyin;
	if (!yyparse()) {
		//hey it parsed according to the grammar correctly
		//say nothing like a real compiler
	}
	else {
		fprintf(stderr, "\nFailed to parse. Check your file.\n");
		return 1; //error
	}
    return 0;
}