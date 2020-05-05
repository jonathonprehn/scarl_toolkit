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

#ifndef SCARLCODEGENERATOR_H_INCLUDED
#define SCARLCODEGENERATOR_H_INCLUDED

#include "scarlastnode.h"
#include "scarlsymboltable.h"
#include "scarlregister.h"

/* Support the implementation of different target languages */

// taken from the original scarlcodegen.h file
void generate_code_file(FILE *output);
void generate_code_ast(FILE *output, struct scarl_symbol_table *associated_scope_st, struct scarl_ast_node *node);
void generate_expression_value(FILE *output, struct scarl_symbol_table *associated_scope_st, struct scarl_ast_node *node);
void generate_local_memory_write(FILE *output, struct scarl_symbol_table *associated_scope_st, struct scarl_symbol_table_entry *st_entry, struct scarl_ast_node *result_node);
void generate_statements_in_block(FILE *output, struct scarl_symbol_table *associated_scope_st, struct scarl_ast_node *node);
void generate_class_body(FILE *output, char *class_name, struct scarl_symbol_table *associated_scope_st, struct scarl_ast_node *node);
void generate_function_invocation(FILE *output, struct scarl_symbol_table *associated_scope_st, struct scarl_ast_node *node);
void generate_register_save(FILE *output);
void generate_register_load(FILE *output);

char *build_arcl_procedure_name(char *class_name, struct scarl_symbol_table_entry_identifier* func_entry_identifier);

#endif // SCARLCODEGENERATOR_H_INCLUDED
