#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#define YYPREFIX "yy"
#line 20 "scarl_tokens.y"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "scarltypes.h"
#include "scarlastnode.h"
#include "stringstack.h"

int yylex(void);
void yyerror(char *);
int yydebug = 1;

/*for counting line numbers. Lines are incremented in scarl.l*/
extern unsigned line_number;
/*handled in scarl.l. for hinting at where error occured*/
extern char *last_token_text;
/*for passing back to scarl.l, where it is declared*/
extern struct scarl_ast_node *program_ast;

/*for performing actions on the code file*/
/*for the compiling unit, this is intermediatary code*/
extern FILE *code_file;

unsigned debugging_grammar = 1;

#line 39 "y.tab.c"
#define IDENTIFIER 257
#define PLUS 258
#define MINUS 259
#define STAR 260
#define SLASH 261
#define BANG 262
#define BOOL 263
#define INT 264
#define CHAR 265
#define POINTER 266
#define VOID 267
#define LPAREN 268
#define RPAREN 269
#define GTR 270
#define LESS 271
#define GTR_EQ 272
#define LESS_EQ 273
#define DBL_EQ 274
#define EQ 275
#define NOT_EQ 276
#define OR 277
#define AND 278
#define COMMA 279
#define SEMICOLON 280
#define IF 281
#define ELSE 282
#define WHILE 283
#define LBRACE 284
#define RBRACE 285
#define DECIMAL 286
#define OCTAL 287
#define HEX 288
#define BINARY 289
#define LIGHT_ACTUATOR 290
#define SERVO_ACTUATOR 291
#define SOUND_SENSOR 292
#define LIGHT_SENSOR 293
#define DISTANCE_SENSOR 294
#define TEMPERATURE_SENSOR 295
#define TRUE 296
#define FALSE 297
#define CONSTANT 298
#define RETURN 299
#define ALLOCATE 300
#define DELETE 301
#define DEREF 302
#define SUPER 303
#define CLASS 304
#define EXTENDS 305
#define LBRACKET 306
#define RBRACKET 307
#define DOT 308
#define STRING_LITERAL 309
#define CHAR_LITERAL 310
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    1,    1,    2,    2,    2,    2,    2,    8,    9,
    9,   10,   10,   10,   10,   10,   10,   10,   10,   10,
   10,   10,    3,   20,   21,   21,   21,   21,   22,   23,
   25,    4,   17,   18,    7,    6,   28,   28,   30,   31,
   29,   32,   32,   33,   33,    5,   11,   15,   15,   35,
   12,   37,   16,   38,   38,   13,   13,   14,   34,   34,
   34,   36,   36,   36,   27,   27,   40,   41,   41,   39,
   39,   42,   42,   43,   43,   43,   44,   44,   44,   44,
   44,   45,   45,   26,   26,   26,   46,   46,   46,   47,
   47,   47,   48,   48,   48,   48,   48,   48,   48,   48,
   48,   52,   53,   54,   54,   55,   49,   49,   49,   49,
   50,   51,   51,   24,   24,   24,   24,   19,   19,   19,
   19,   19,   19,
};
short yylen[] = {                                         2,
    1,    1,    2,    1,    1,    1,    1,    1,    3,    1,
    2,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    3,    2,    1,    1,    1,    1,    4,    2,
    1,    4,    2,    3,    5,    2,    1,    2,    2,    2,
    3,    1,    2,    1,    1,    6,    4,    3,    2,    4,
    2,    4,    2,    3,    3,    5,    7,    5,    1,    3,
    0,    1,    3,    0,    1,    1,    2,    4,    4,    1,
    3,    1,    3,    1,    3,    3,    1,    3,    3,    3,
    3,    1,    2,    1,    3,    3,    1,    3,    3,    1,
    2,    3,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    4,    2,    1,    1,    3,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,
};
short yydefred[] = {                                      0,
   31,  114,  115,  116,  117,  118,  119,  120,  121,  122,
  123,    0,    0,    0,    1,    0,    4,    5,    6,    7,
    8,    0,    0,    0,   25,   26,   27,   28,    0,    0,
    0,    0,   39,    3,    0,    0,    0,   30,    0,    0,
   36,    0,   38,    0,   24,   23,    0,    0,    0,    0,
    0,  107,  108,  109,  110,  112,  113,    0,    0,  104,
  111,    0,    0,   97,   99,    0,    0,   66,    0,    0,
    0,   77,    0,   87,   90,   94,   95,   96,   98,  100,
  101,  105,    0,    0,   44,   45,    0,    0,    0,   40,
    0,    0,    0,    0,   91,    0,    0,    0,    0,    0,
    0,   67,  103,    0,    0,   32,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   29,
   33,   41,   43,   35,    0,    0,    0,   55,   92,    0,
  106,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   78,   79,   80,   81,   88,   89,    0,    0,   50,  102,
   63,    0,    0,   52,   60,    0,   46,   68,   69,    0,
    0,    0,    0,    0,   12,   22,   13,    0,    0,   14,
   15,   16,   17,   18,   19,   20,   21,    0,    0,    0,
    0,    0,    0,   49,    0,    0,    9,   11,   51,   53,
    0,    0,    0,   48,   34,   47,    0,    0,    0,   58,
    0,   57,
};
short yydgoto[] = {                                      14,
   15,   16,   17,   18,   19,   20,   21,  167,  168,  169,
  170,  171,  172,  173,  174,  175,   86,  177,   22,   23,
   32,   25,   26,   27,   28,   62,   98,   29,   41,   30,
   43,   88,   89,  119,   64,   99,   65,   66,   67,   68,
  102,   69,   70,   71,   72,   73,   74,   75,   76,   77,
   78,   79,   80,   81,   82,
};
short yysindex[] = {                                     20,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   25, -252,    0,    0,   20,    0,    0,    0,    0,
    0, -238, -228, -250,    0,    0,    0,    0, -218, -224,
 -186, -245,    0,    0, -176, -194, -161,    0, -118,   25,
    0, -123,    0, -194,    0,    0, -258, -118, -118, -118,
 -194,    0,    0,    0,    0,    0,    0,   25, -121,    0,
    0, -236, -140,    0,    0, -108, -132,    0, -136, -178,
  -90,    0, -147,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   25, -227,    0,    0, -117, -120,   25,    0,
 -116, -194, -118,  -85,    0, -236, -139, -106, -109,  -91,
  -79,    0,    0, -118, -118,    0, -194, -135, -135, -135,
 -135, -135, -135, -135, -135, -118, -118,  -89,  -76,    0,
    0,    0,    0,    0,  -75, -219, -113,    0,    0, -194,
    0, -194, -194, -147, -147,  -67, -136, -178,  -90,  -90,
    0,    0,    0,    0,    0,    0,   25,  -74,    0,    0,
    0,  -58,  -52,    0,    0,   65,    0,    0,    0, -241,
  -43,  -32, -251,  -39,    0,    0,    0,  -48,   65,    0,
    0,    0,    0,    0,    0,    0,    0, -193,  -47,  -42,
 -194, -194, -194,    0,  -41,  -40,    0,    0,    0,    0,
  -24,  -28,  -21,    0,    0,    0,  -74,  -74,  -23,    0,
  -74,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  260,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -22,
    0,    0,    0,    0,    0,    0, -137,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  -73,    0,    0,    0,
  -14,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   82,    0,    0,    0,    0,  126,    0, -148, -225,
   17,    0,  -50,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   -8,    0,    0,    0,    0,    0,   -6,    0,
    0,   -5,    0,    0,    0,   99,    0, -244,    0,    0,
    0,    0,    0,    0,    0,    0,   -5,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    9,    0,    0,
    0,    0,    0,    0,    0,    0,   30,    0,    0, -207,
    0,   -5,   -5,  -27,   -4,    0,  135, -168,  111,  123,
    0,    0,    0,    0,    0,    0,   -8,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, -242,
    0,    0,    0,    0,    0,    0,    0,    0,   15,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   42,    0,
    0,    0,
};
short yygindex[] = {                                      0,
  247,    0,    0, -126,  -20,    0,  -86, -122,  132,    0,
    0,    0,    0,    0,    0,    0,  -72,    0,    0,  -12,
    2,    0,    0,  246,  250,  -36,  -35,    0,    0,    0,
    0,  227,    0,  170,  -70,   -7,  -51,  225,    0,    0,
    0,  212,  222,   45,  101,   54,  -44,    0,    0,    0,
    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 420
short yytable[] = {                                      31,
   63,   24,   84,   95,   33,   47,   37,   48,   91,   92,
   49,   45,   96,   97,   31,   38,   50,   24,   35,   85,
   38,  104,  105,   31,   62,  157,   92,   87,  184,  165,
  104,  105,   51,  181,   52,   53,   54,   55,  104,  105,
   62,   24,  165,   72,   56,   57,   36,   93,   58,   94,
   59,   72,   72,   72,   72,   39,  126,   60,   61,   72,
   39,   64,   47,   31,   48,   40,   94,   49,   85,  166,
  118,  145,  146,   50,  199,  200,   87,   64,  202,  120,
   42,   36,  166,  176,  125,  179,  121,  150,   44,   51,
   24,   52,   53,   54,   55,  110,  176,  111,  179,  136,
   73,   56,   57,   46,  180,   58,   83,   59,   73,   73,
   73,   73,  116,  117,   60,   61,   73,  180,  104,  105,
   70,   47,  151,   48,  152,  153,   49,  185,   70,  129,
   70,   70,   50,   90,  118,  103,   70,   24,   47,  106,
   48,  109,   24,  178,  108,  191,  192,  193,   51,   50,
   52,   53,   54,   55,  139,  140,  178,  134,  135,  107,
   56,   57,  121,  124,  122,   51,   59,   52,   53,   54,
   55,  127,  130,   60,   61,  131,  132,   56,   57,  112,
  113,  114,  115,   59,   93,   93,   93,   93,  133,  147,
   60,   61,  148,  149,   94,   93,   93,   93,   93,   93,
   93,  154,   93,   93,   93,   93,   93,   84,   84,  156,
  158,   93,  141,  142,  143,  144,  159,  186,   84,   84,
   84,   84,   84,   84,  182,   84,   84,   84,   84,   84,
   85,   85,  189,   93,   84,  183,  187,  190,  194,  195,
  197,   85,   85,   85,   85,   85,   85,  198,   85,   85,
   85,   85,   85,   86,   86,  196,   84,   85,  201,    2,
   61,   37,   34,   64,   86,   86,   86,   86,   86,   86,
   64,   86,   86,   86,   86,   86,    1,   59,   42,   85,
   86,    1,    2,    3,    4,   74,    5,    2,    3,    4,
   74,    5,   74,   74,   74,   74,   74,   54,   56,   10,
  188,   74,   86,  100,   56,   56,   56,  101,   56,    6,
    7,    8,    9,   10,   11,  123,  155,   12,  128,  137,
    0,  160,   56,   13,   56,   56,   56,    2,    3,    4,
  138,    5,    0,    0,    0,    0,    0,    0,    0,   56,
   56,    0,   56,    0,    0,  161,    0,  162,  156,    0,
   82,   82,   82,   82,   82,   82,    0,   82,   82,   82,
   82,   82,   12,  163,    0,  164,   82,   83,   83,   83,
   83,   83,   83,    0,   83,   83,   83,   83,   83,   75,
    0,    0,    0,   83,   75,    0,   75,   75,   75,   75,
   75,   76,    0,    0,   65,   75,   76,    0,   76,   76,
   76,   76,   76,   71,   65,   65,    0,   76,    0,    0,
   65,   71,    0,   71,   71,    0,    0,    0,    0,   71,
};
short yycheck[] = {                                      12,
   36,    0,   39,   48,  257,  257,  257,  259,   44,  268,
  262,  257,   49,   50,  257,  266,  268,   16,  257,   40,
  266,  258,  259,  266,  269,  148,  268,   40,  280,  156,
  258,  259,  284,  275,  286,  287,  288,  289,  258,  259,
  285,   40,  169,  269,  296,  297,  275,  306,  300,  308,
  302,  277,  278,  279,  280,  306,   93,  309,  310,  285,
  306,  269,  257,  306,  259,  284,  308,  262,   89,  156,
   83,  116,  117,  268,  197,  198,   89,  285,  201,  307,
  305,  275,  169,  156,   92,  156,  280,  307,  275,  284,
   89,  286,  287,  288,  289,  274,  169,  276,  169,  107,
  269,  296,  297,  280,  156,  300,  268,  302,  277,  278,
  279,  280,  260,  261,  309,  310,  285,  169,  258,  259,
  269,  257,  130,  259,  132,  133,  262,  163,  277,  269,
  279,  280,  268,  257,  147,  257,  285,  275,  257,  280,
  259,  278,  280,  156,  277,  181,  182,  183,  284,  268,
  286,  287,  288,  289,  110,  111,  169,  104,  105,  268,
  296,  297,  280,  280,  285,  284,  302,  286,  287,  288,
  289,  257,  279,  309,  310,  285,  268,  296,  297,  270,
  271,  272,  273,  302,  258,  259,  260,  261,  268,  279,
  309,  310,  269,  269,  308,  269,  270,  271,  272,  273,
  274,  269,  276,  277,  278,  279,  280,  258,  259,  284,
  269,  285,  112,  113,  114,  115,  269,  257,  269,  270,
  271,  272,  273,  274,  268,  276,  277,  278,  279,  280,
  258,  259,  280,  307,  285,  268,  285,  280,  280,  280,
  269,  269,  270,  271,  272,  273,  274,  269,  276,  277,
  278,  279,  280,  258,  259,  280,  307,  285,  282,    0,
  269,  284,   16,  269,  269,  270,  271,  272,  273,  274,
  285,  276,  277,  278,  279,  280,  257,  269,  285,  307,
  285,  257,  263,  264,  265,  269,  267,  263,  264,  265,
  274,  267,  276,  277,  278,  279,  280,  268,  257,  285,
  169,  285,  307,   58,  263,  264,  265,   58,  267,  290,
  291,  292,  293,  294,  295,   89,  147,  298,   94,  108,
   -1,  257,  281,  304,  283,  284,  285,  263,  264,  265,
  109,  267,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  298,
  299,   -1,  301,   -1,   -1,  281,   -1,  283,  284,   -1,
  269,  270,  271,  272,  273,  274,   -1,  276,  277,  278,
  279,  280,  298,  299,   -1,  301,  285,  269,  270,  271,
  272,  273,  274,   -1,  276,  277,  278,  279,  280,  269,
   -1,   -1,   -1,  285,  274,   -1,  276,  277,  278,  279,
  280,  269,   -1,   -1,  269,  285,  274,   -1,  276,  277,
  278,  279,  280,  269,  279,  280,   -1,  285,   -1,   -1,
  285,  277,   -1,  279,  280,   -1,   -1,   -1,   -1,  285,
};
#define YYFINAL 14
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 310
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"IDENTIFIER","PLUS","MINUS",
"STAR","SLASH","BANG","BOOL","INT","CHAR","POINTER","VOID","LPAREN","RPAREN",
"GTR","LESS","GTR_EQ","LESS_EQ","DBL_EQ","EQ","NOT_EQ","OR","AND","COMMA",
"SEMICOLON","IF","ELSE","WHILE","LBRACE","RBRACE","DECIMAL","OCTAL","HEX",
"BINARY","LIGHT_ACTUATOR","SERVO_ACTUATOR","SOUND_SENSOR","LIGHT_SENSOR",
"DISTANCE_SENSOR","TEMPERATURE_SENSOR","TRUE","FALSE","CONSTANT","RETURN",
"ALLOCATE","DELETE","DEREF","SUPER","CLASS","EXTENDS","LBRACKET","RBRACKET",
"DOT","STRING_LITERAL","CHAR_LITERAL",
};
char *yyrule[] = {
"$accept : program",
"program : statement_list",
"statement_list : statement",
"statement_list : statement statement_list",
"statement : device_declarator_statement",
"statement : variable_definition_statement",
"statement : function_definition_statement",
"statement : class_definition_statement",
"statement : constant_definition_statement",
"block_statement : LBRACE statement_list_block_level RBRACE",
"statement_list_block_level : statement_block_level",
"statement_list_block_level : statement_block_level statement_list_block_level",
"statement_block_level : variable_definition_statement",
"statement_block_level : block_statement",
"statement_block_level : variable_set_statement",
"statement_block_level : function_invocation_statement",
"statement_block_level : if_block_statement",
"statement_block_level : while_block_statement",
"statement_block_level : return_statement",
"statement_block_level : method_invocation_statement",
"statement_block_level : variable_declaration_statement",
"statement_block_level : delete_statement",
"statement_block_level : constant_definition_statement",
"device_declarator_statement : device_type IDENTIFIER SEMICOLON",
"type_declarator : any_type IDENTIFIER",
"any_type : array_type",
"any_type : pointer_type",
"any_type : primitive_type",
"any_type : user_type",
"array_type : any_type LBRACKET arithmetic_expression RBRACKET",
"pointer_type : any_type POINTER",
"user_type : IDENTIFIER",
"variable_definition_statement : type_declarator EQ expression SEMICOLON",
"variable_declaration_statement : type_declarator SEMICOLON",
"delete_statement : DELETE IDENTIFIER SEMICOLON",
"constant_definition_statement : CONSTANT type_declarator EQ expression SEMICOLON",
"class_definition_statement : class_declarator class_body",
"class_declarator : class_name",
"class_declarator : class_name class_extending",
"class_name : CLASS IDENTIFIER",
"class_extending : EXTENDS IDENTIFIER",
"class_body : LBRACE class_attribute_list RBRACE",
"class_attribute_list : class_attribute",
"class_attribute_list : class_attribute class_attribute_list",
"class_attribute : function_definition_statement",
"class_attribute : variable_declaration_statement",
"function_definition_statement : any_type IDENTIFIER LPAREN formal_parameter_list RPAREN block_statement",
"variable_set_statement : IDENTIFIER EQ expression SEMICOLON",
"return_statement : RETURN expression SEMICOLON",
"return_statement : RETURN SEMICOLON",
"function_invocation : IDENTIFIER LPAREN parameter_list RPAREN",
"function_invocation_statement : function_invocation SEMICOLON",
"method_invocation : class_attribute_identifier LPAREN parameter_list RPAREN",
"method_invocation_statement : method_invocation SEMICOLON",
"class_attribute_identifier : IDENTIFIER DOT IDENTIFIER",
"class_attribute_identifier : IDENTIFIER DOT class_attribute_identifier",
"if_block_statement : IF LPAREN expression RPAREN block_statement",
"if_block_statement : IF LPAREN expression RPAREN block_statement ELSE block_statement",
"while_block_statement : WHILE LPAREN expression RPAREN block_statement",
"formal_parameter_list : type_declarator",
"formal_parameter_list : type_declarator COMMA formal_parameter_list",
"formal_parameter_list :",
"parameter_list : expression",
"parameter_list : expression COMMA parameter_list",
"parameter_list :",
"expression : logical_expression",
"expression : allocation_expression",
"allocation_expression : ALLOCATE allocation_invocation",
"allocation_invocation : primitive_type LPAREN parameter_list RPAREN",
"allocation_invocation : user_type LPAREN parameter_list RPAREN",
"logical_expression : logical_and_expression",
"logical_expression : logical_expression OR logical_and_expression",
"logical_and_expression : equality_expression",
"logical_and_expression : logical_and_expression AND equality_expression",
"equality_expression : relational_expression",
"equality_expression : equality_expression DBL_EQ relational_expression",
"equality_expression : equality_expression NOT_EQ relational_expression",
"relational_expression : bool_expression",
"relational_expression : relational_expression GTR bool_expression",
"relational_expression : relational_expression LESS bool_expression",
"relational_expression : relational_expression GTR_EQ bool_expression",
"relational_expression : relational_expression LESS_EQ bool_expression",
"bool_expression : arithmetic_expression",
"bool_expression : BANG arithmetic_expression",
"arithmetic_expression : arithmetic_factor",
"arithmetic_expression : arithmetic_expression PLUS arithmetic_factor",
"arithmetic_expression : arithmetic_expression MINUS arithmetic_factor",
"arithmetic_factor : arithmetic_unary",
"arithmetic_factor : arithmetic_factor STAR arithmetic_unary",
"arithmetic_factor : arithmetic_factor SLASH arithmetic_unary",
"arithmetic_unary : unit",
"arithmetic_unary : MINUS arithmetic_unary",
"arithmetic_unary : LPAREN arithmetic_expression RPAREN",
"unit : IDENTIFIER",
"unit : integer_value",
"unit : char_value",
"unit : bool_value",
"unit : function_invocation",
"unit : array_accessor_unit",
"unit : method_invocation",
"unit : dereferenced_pointer",
"unit : array_value",
"array_accessor_unit : IDENTIFIER LBRACKET arithmetic_expression RBRACKET",
"dereferenced_pointer : DEREF IDENTIFIER",
"array_value : STRING_LITERAL",
"array_value : array_initializer",
"array_initializer : LBRACE parameter_list RBRACE",
"integer_value : DECIMAL",
"integer_value : OCTAL",
"integer_value : HEX",
"integer_value : BINARY",
"char_value : CHAR_LITERAL",
"bool_value : TRUE",
"bool_value : FALSE",
"primitive_type : BOOL",
"primitive_type : INT",
"primitive_type : CHAR",
"primitive_type : VOID",
"device_type : LIGHT_ACTUATOR",
"device_type : SERVO_ACTUATOR",
"device_type : SOUND_SENSOR",
"device_type : LIGHT_SENSOR",
"device_type : DISTANCE_SENSOR",
"device_type : TEMPERATURE_SENSOR",
};
#endif
#ifndef YYSTYPE
typedef int YYSTYPE;
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
#line 1143 "scarl_tokens.y"

void yyerror(char *s) {
	fprintf(stderr, "%s at line %i near \'%s\'\n", s, line_number, last_token_text);
}
#line 478 "y.tab.c"
#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 1:
#line 63 "scarl_tokens.y"
{
	printf("Match program\n");
	/*pass the completed AST back to the main program for further processing*/
	program_ast = yyvsp[0];
	yyval = yyvsp[0];
}
break;
case 2:
#line 70 "scarl_tokens.y"
{
    /* finish off the statement list*/
	struct scarl_ast_node *statement_node = yyvsp[0];
	if (debugging_grammar) printf("Match statement_list (with statement %s)\n", get_ast_node_type_string(statement_node->node_type));
	struct scarl_ast_node *statement_list_node = create_typed_ast_node(NON_TERMINAL_STATEMENT_LIST, NON_TERMINAL_STATEMENT_LIST);
	add_child_node(statement_list_node, statement_node);
	yyval = statement_list_node;
}
break;
case 3:
#line 79 "scarl_tokens.y"
{
    /* add the statement to the statement list*/
	if (debugging_grammar) printf("Match statement_list\n");
	struct scarl_ast_node *statement_list_node = yyvsp[0];
	struct scarl_ast_node *statement_node = yyvsp[-1];
	push_child_node_front(statement_list_node, statement_node);
	yyval = statement_list_node;
}
break;
case 4:
#line 88 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement\n");
	yyval = yyvsp[0];
}
break;
case 5:
#line 93 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement\n");
	yyval = yyvsp[0];
}
break;
case 6:
#line 98 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement\n");
	yyval = yyvsp[0];
}
break;
case 7:
#line 103 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement\n");
	yyval = yyvsp[0];
}
break;
case 8:
#line 108 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement\n");
	yyval = yyvsp[0];
}
break;
case 9:
#line 113 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match block_statement\n");
	yyval = yyvsp[-1];
}
break;
case 10:
#line 118 "scarl_tokens.y"
{
    /* finish the block level statement list*/
	if (debugging_grammar) printf("Match statement_list_block_level\n");
	struct scarl_ast_node *statement_list_node = create_typed_ast_node(NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL, NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL);
	struct scarl_ast_node *statement_node = yyvsp[0];
	add_child_node(statement_list_node, statement_node);
	yyval = statement_list_node;
}
break;
case 11:
#line 127 "scarl_tokens.y"
{
    /* add a block level statement to the statement list*/
	if (debugging_grammar) printf("Match statement_list_block_level\n");
	struct scarl_ast_node *statement_list_node = yyvsp[0];
	struct scarl_ast_node *statement_node = yyvsp[-1];
	push_child_node_front(statement_list_node, statement_node);
	yyval = yyvsp[0];
}
break;
case 12:
#line 136 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
	yyval = yyvsp[0];
}
break;
case 13:
#line 141 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
	yyval = yyvsp[0];
}
break;
case 14:
#line 146 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
	yyval = yyvsp[0];
}
break;
case 15:
#line 151 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
	yyval = yyvsp[0];
}
break;
case 16:
#line 156 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
	yyval = yyvsp[0];
}
break;
case 17:
#line 161 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
	yyval = yyvsp[0];
}
break;
case 18:
#line 166 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
	yyval = yyvsp[0];
}
break;
case 19:
#line 171 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
	yyval = yyvsp[0];
}
break;
case 20:
#line 176 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
	yyval = yyvsp[0];
}
break;
case 21:
#line 181 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
	yyval = yyvsp[0];
}
break;
case 22:
#line 186 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
	yyval = yyvsp[0];
}
break;
case 23:
#line 191 "scarl_tokens.y"
{
	char *device_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match device_declarator_statement (%s)\n", device_identifier);
	struct scarl_ast_node *device_declarator_node = create_typed_ast_node(NON_TERMINAL_DEVICE_DECLARATOR_STATEMENT, NON_TERMINAL_DEVICE_DECLARATOR_STATEMENT);
	struct scarl_ast_node *device_type_node = yyvsp[-2];
	struct scarl_ast_node *device_identifier_node = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, device_identifier);
	add_child_node(device_declarator_node, device_type_node);
	add_child_node(device_declarator_node, device_identifier_node);
	yyval = device_declarator_node;
}
break;
case 24:
#line 202 "scarl_tokens.y"
{
    /* for any variable declared with a type*/
	char *declarator_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match type_declarator (%s)\n", declarator_identifier);
	struct scarl_ast_node *type_declarator_node = create_typed_ast_node(NON_TERMINAL_TYPE_DECLARATOR, NON_TERMINAL_TYPE_DECLARATOR);
	struct scarl_ast_node *type_node = yyvsp[-1];
	struct scarl_ast_node *declarator_identifier_node = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, declarator_identifier);
	add_child_node(type_declarator_node, type_node);
	add_child_node(type_declarator_node, declarator_identifier_node);
	yyval = type_declarator_node;
}
break;
case 25:
#line 214 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match any_type\n");
	yyval = yyvsp[0];
}
break;
case 26:
#line 219 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match any_type\n");
	yyval = yyvsp[0];
}
break;
case 27:
#line 224 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match any_type\n");
	yyval = yyvsp[0];
}
break;
case 28:
#line 229 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match any_type\n");
	yyval = yyvsp[0];
}
break;
case 29:
#line 234 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match array_type\n");
	struct scarl_ast_node *array_type_node = create_typed_ast_node(NON_TERMINAL_ARRAY_TYPE, NON_TERMINAL_ARRAY_TYPE);
	struct scarl_ast_node *type_node = yyvsp[-3];
	struct scarl_ast_node *arithmetic_expression_node = yyvsp[-1];
	add_child_node(array_type_node, type_node);
	add_child_node(array_type_node, arithmetic_expression_node);
	yyval = array_type_node;
}
break;
case 30:
#line 244 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match pointer_type\n");
	struct scarl_ast_node *pointer_node = create_typed_ast_node(NON_TERMINAL_POINTER_TYPE, NON_TERMINAL_POINTER_TYPE);
	struct scarl_ast_node *type_node = yyvsp[-1];
	add_child_node(pointer_node, type_node);
	yyval = pointer_node;
}
break;
case 31:
#line 252 "scarl_tokens.y"
{
	char *user_type_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match user_type (%s)\n", user_type_identifier);
	yyval = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, user_type_identifier);
}
break;
case 32:
#line 258 "scarl_tokens.y"
{
    /* we must ensure that the evaluated type*/
    /* on the right hand side of the = sign is*/
    /* the same type or can be converted to the*/
    /* type on the left hand side*/
	if (debugging_grammar) printf("Match variable_definition_statement\n");
	struct scarl_ast_node *variable_definition_statement_node = create_typed_ast_node(NON_TERMINAL_VARIABLE_DEFINITION_STATEMENT, NON_TERMINAL_VARIABLE_DEFINITION_STATEMENT);
	struct scarl_ast_node *type_declarator_node = yyvsp[-3];
	struct scarl_ast_node *expression_node = yyvsp[-1];
	add_child_node(variable_definition_statement_node, type_declarator_node);
	add_child_node(variable_definition_statement_node, expression_node);
	yyval = variable_definition_statement_node;
}
break;
case 33:
#line 272 "scarl_tokens.y"
{
	/* declares a variable without giving it a value - cannot*/
	/* refer to this variable without assigning it, otherwise */
	/* the compiler will give an error*/
	if (debugging_grammar) printf("Match variable_declaration_statement\n");
	yyval = yyvsp[-1];
}
break;
case 34:
#line 280 "scarl_tokens.y"
{
	/* for deallocating a pointer variable*/
	/* be sure this only occurs on pointer types */
	char *deleting_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match delete_statement (%s)\n", deleting_identifier);
	struct scarl_ast_node *delete_statement_node = create_typed_ast_node(NON_TERMINAL_DELETE_STATEMENT, NON_TERMINAL_DELETE_STATEMENT);
	struct scarl_ast_node *deleting_identifier_node = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, deleting_identifier);
	add_child_node(delete_statement_node, deleting_identifier_node);
	yyval = delete_statement_node;
}
break;
case 35:
#line 291 "scarl_tokens.y"
{
    /* functions like the variable_definition_statement*/
    /* except it can only be in global scope and*/
    /* the value will be evaluated at compile time*/
    /* (array lengths can be defined as literals or constant values)*/
	if (debugging_grammar) printf("Match constant_definition_statement\n");
	struct scarl_ast_node *const_set_statement_node = create_typed_ast_node(NON_TERMINAL_CONSTANT_DEFINITION_STATEMENT, NON_TERMINAL_CONSTANT_DEFINITION_STATEMENT);
	struct scarl_ast_node *type_declarator_node = yyvsp[-3];
	struct scarl_ast_node *expression_node = yyvsp[-1];
	add_child_node(const_set_statement_node, type_declarator_node);
	add_child_node(const_set_statement_node, expression_node);
	yyval = const_set_statement_node;
}
break;
case 36:
#line 305 "scarl_tokens.y"
{
    /* add this declared class into the symbol*/
    /* table for global scope (classes can only be*/
    /* declared in global scope) and give it the*/
    /* type attributes listed in the class body*/
	if (debugging_grammar) printf("Match class_definition_statement\n");
	struct scarl_ast_node *class_definition_statement_node = create_typed_ast_node(NON_TERMINAL_CLASS_DEFINITION_STATEMENT, NON_TERMINAL_CLASS_DEFINITION_STATEMENT);
	struct scarl_ast_node *class_declarator_node = yyvsp[-1];
	struct scarl_ast_node *class_body_node = yyvsp[0];
	add_child_node(class_definition_statement_node, class_declarator_node);
	add_child_node(class_definition_statement_node, class_body_node);
	yyval = class_definition_statement_node;
}
break;
case 37:
#line 319 "scarl_tokens.y"
{
    /* this class declarator is a "normal"*/
    /* class. It is not derived from another*/
    /* class*/
	if (debugging_grammar) printf("Match class_declarator\n");
	struct scarl_ast_node *class_declarator_node = create_typed_ast_node(NON_TERMINAL_CLASS_DECLARATOR, NON_TERMINAL_CLASS_DECLARATOR);
	struct scarl_ast_node *class_name_node = yyvsp[0];
	add_child_node(class_declarator_node, class_name_node);
	yyval = class_declarator_node;
}
break;
case 38:
#line 330 "scarl_tokens.y"
{
    /* this class is derived from some other*/
    /* class. We need to ensure that the*/
    /* "extending" class already exists in*/
    /* the symbol table before we can place*/
    /* this derived one in the symbol table too*/
    /* (we are going to refer to the parent class*/
    /*  to construct this class definition)*/

    /* the check for it the extending class exists*/
    /* takes place in the class_extending production rule*/
	if (debugging_grammar) printf("Match class_declarator\n");
	struct scarl_ast_node *class_declarator_node = create_typed_ast_node(NON_TERMINAL_CLASS_DECLARATOR, NON_TERMINAL_CLASS_DECLARATOR);
	struct scarl_ast_node *class_name_node = yyvsp[-1];
	struct scarl_ast_node *class_extending_node = yyvsp[0];
	add_child_node(class_declarator_node, class_name_node);
	add_child_node(class_declarator_node, class_extending_node);
	yyval = class_declarator_node;
}
break;
case 39:
#line 350 "scarl_tokens.y"
{
    /* ensure that the identifier is not*/
    /* being used for something else in*/
    /* this (global) scope*/
	char *class_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match class_name (%s)\n", class_identifier);
	yyval = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, class_identifier);
}
break;
case 40:
#line 359 "scarl_tokens.y"
{
    /* we need to ensure that the*/
    /* identifier is actually a class*/
    /* name defined in the symbol table*/
	char *extending_class_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match class_extending (%s)\n", extending_class_identifier);
	yyval = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, extending_class_identifier);
}
break;
case 41:
#line 368 "scarl_tokens.y"
{
    /* a list of class attributes*/
    /* processing takes place in the*/
    /* class_definition_statement*/
    /* production rule*/
	if (debugging_grammar) printf("Match class_body\n");
	yyval = yyvsp[-1];
}
break;
case 42:
#line 377 "scarl_tokens.y"
{
    /* finish off the class attribute list*/
	if (debugging_grammar) printf("Match class_attribute_list\n");
	struct scarl_ast_node *class_attribute_list_node = create_typed_ast_node(NON_TERMINAL_CLASS_ATTRIBUTE_LIST, NON_TERMINAL_CLASS_ATTRIBUTE_LIST);
	struct scarl_ast_node *class_attribute_node = yyvsp[0];
	add_child_node(class_attribute_list_node, class_attribute_node);
	yyval = class_attribute_list_node;
}
break;
case 43:
#line 386 "scarl_tokens.y"
{
    /* add another attribute to the list*/
	if (debugging_grammar) printf("Match class_attribute_list\n");
	struct scarl_ast_node *class_attribute_node = yyvsp[-1];
	struct scarl_ast_node *class_attribute_list_node = yyvsp[0];
	push_child_node_front(class_attribute_list_node, class_attribute_node);
	yyval = class_attribute_list_node;
}
break;
case 44:
#line 395 "scarl_tokens.y"
{
    /* a special location for functions*/
    /* this function definition is actually*/
    /* going to be a method for this class*/
	if (debugging_grammar) printf("Match class_attribute\n");
	yyval = yyvsp[0];
}
break;
case 45:
#line 403 "scarl_tokens.y"
{
    /* a special kind of declarator*/
    /* that does not require an initial*/
    /* value. This can only take place*/
    /* in a class body. This will be*/
    /* a field for instances of this class*/
	if (debugging_grammar) printf("Match class_attribute\n");
	yyval = yyvsp[0];
}
break;
case 46:
#line 413 "scarl_tokens.y"
{
    /* functions will only be able to return*/
    /* primitives for this version. Hopefully*/
    /* extend it to pointer types later on. Can*/
    /* always pass pointer types as parameters*/
    /* to functions*/
	char *function_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match function_definition_statement (%s)\n", function_identifier);
	struct scarl_ast_node *function_definition_statement_node = create_typed_ast_node(NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT, NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT);
	struct scarl_ast_node *any_type_node = yyvsp[-5];
	struct scarl_ast_node *function_identifier_node = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, function_identifier);
	struct scarl_ast_node *formal_parameter_list_node = yyvsp[-2];
	struct scarl_ast_node *block_statement_node = yyvsp[0];
	add_child_node(function_definition_statement_node, any_type_node);
	add_child_node(function_definition_statement_node, function_identifier_node);
	add_child_node(function_definition_statement_node, formal_parameter_list_node);
	add_child_node(function_definition_statement_node, block_statement_node);
	yyval = function_definition_statement_node;
}
break;
case 47:
#line 433 "scarl_tokens.y"
{
    /* sets the value for the identifier to the evaluated*/
    /* value of the expression. Need to ensure that the type*/
    /* of the identifier matches or can be converted to the type*/
    /* of the expression. Also ensure that the identifier is in scope*/
	char *variable_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match variable_set_statement (%s)\n", variable_identifier);
	struct scarl_ast_node *variable_set_statement_node = create_typed_ast_node(NON_TERMINAL_VARIABLE_SET_STATEMENT, NON_TERMINAL_VARIABLE_SET_STATEMENT);
	struct scarl_ast_node *variable_identifier_node = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, variable_identifier);
	struct scarl_ast_node *expression_node = yyvsp[-1];
	add_child_node(variable_set_statement_node, variable_identifier_node);
	add_child_node(variable_set_statement_node, expression_node);
	yyval = variable_set_statement_node;
}
break;
case 48:
#line 448 "scarl_tokens.y"
{
    /* can only appear in functions.*/
    /* acts like a normal C return statement*/
    /* the expression type for all return*/
    /* statements in a function must match*/
    /* the return type for that function*/

    /* additionally, void functions cannot have*/
    /* return statements with expressions*/
	if (debugging_grammar) printf("Match return_statement\n");
	struct scarl_ast_node *return_statement_node = create_typed_ast_node(NON_TERMINAL_RETURN_STATEMENT, NON_TERMINAL_RETURN_STATEMENT);
	struct scarl_ast_node *expression_node = yyvsp[-1];
	add_child_node(return_statement_node, expression_node);
	yyval = return_statement_node;
}
break;
case 49:
#line 464 "scarl_tokens.y"
{
    /* empty return statement.*/
    /* can only occur in void functions*/
	if (debugging_grammar) printf("Match return_statement\n");
	yyval = create_typed_ast_node(NON_TERMINAL_RETURN_STATEMENT, NON_TERMINAL_RETURN_STATEMENT);
}
break;
case 50:
#line 471 "scarl_tokens.y"
{
    /* invoke the function with the name*/
    /* of identifier. The types of the parameters*/
    /* must match that of a defined invocation*/

    /* this may also be a call to a constructor*/
    /* in which case the identifier must also*/
    /* be checked against a class name and*/
    /* the parameter list against the class's*/
    /* constructors*/
	char *function_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match function_invocation (%s)\n", function_identifier);
	struct scarl_ast_node *function_invocation_node = create_typed_ast_node(NON_TERMINAL_FUNCTION_INVOCATION, NON_TERMINAL_FUNCTION_INVOCATION);
	struct scarl_ast_node *identifier_node = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, function_identifier);
	struct scarl_ast_node *parameter_list_node = yyvsp[-1];
	add_child_node(function_invocation_node, identifier_node);
	add_child_node(function_invocation_node, parameter_list_node);
	yyval = function_invocation_node;
}
break;
case 51:
#line 491 "scarl_tokens.y"
{
    /* allows for there to be statements that*/
    /* only call functions*/
	if (debugging_grammar) printf("Match function_invocation_statement\n");
	yyval = yyvsp[-1];
}
break;
case 52:
#line 498 "scarl_tokens.y"
{
    /* requires more heavy lifting than*/
    /* a function invocation because we need*/
    /* to resolve the scope to where the*/
    /* class_attribute_identifier leads to.*/
    /* A method invocation is calling a*/
    /* method of an object instance*/
	if (debugging_grammar) printf("Match method_invocation\n");
	struct scarl_ast_node *method_invocation_node = create_typed_ast_node(NON_TERMINAL_METHOD_INVOCATION, NON_TERMINAL_METHOD_INVOCATION);
	struct scarl_ast_node *class_attribute_identifier_node = yyvsp[-3];
	struct scarl_ast_node *parameter_list_node = yyvsp[-1];
	add_child_node(method_invocation_node, class_attribute_identifier_node);
	add_child_node(method_invocation_node, parameter_list_node);
	yyval = method_invocation_node;
}
break;
case 53:
#line 514 "scarl_tokens.y"
{
    /* allows for a statement to be only*/
    /* a method invocation*/
	if (debugging_grammar) printf("Match method_invocation_statement\n");
	yyval = yyvsp[-1];
}
break;
case 54:
#line 522 "scarl_tokens.y"
{
    /* the last case in the chain of*/
    /* identifiers dot identifiers for a method*/
    /* identifier*/
    /* this could also just lead to a field of*/
    /* an object instance, not a method*/
	char *second_identifier = string_stack_pop();
	char *first_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match class_attribute_identifier (%s.%s)\n", first_identifier, second_identifier);
	struct scarl_ast_node *class_attribute_node = create_typed_ast_node(NON_TERMINAL_CLASS_ATTRIBUTE_IDENTIFIER, NON_TERMINAL_CLASS_ATTRIBUTE_IDENTIFIER);
	struct scarl_ast_node *first_identifier_node = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, yyvsp[-2]);
	struct scarl_ast_node *second_identifier_node = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, yyvsp[0]);
	/* this node's value is the sum of its children (an ordered list of identifiers)*/
	add_child_node(class_attribute_node, first_identifier_node);
	add_child_node(class_attribute_node, second_identifier_node);
	yyval = class_attribute_node;
}
break;
case 55:
#line 540 "scarl_tokens.y"
{
    /* enables the dot operator to*/
    /* act as far as it needs to to*/
    /* get to where a field or method is*/
    /* this could also just lead to a field of*/
    /* an object instance, not a method*/
	char *identifier = string_stack_pop();
	if (debugging_grammar) printf("Match class_attribute_identifier (%s.<more stuff>)\n", identifier);
	/* we want the children to appear in the order as  they do in the code for the AST*/
	struct scarl_ast_node *next_identifier = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, yyvsp[-2]);
	struct scarl_ast_node *class_attribute_identifier_node = yyvsp[0];
	push_child_node_front(class_attribute_identifier_node, next_identifier);
	yyval = class_attribute_identifier_node;
}
break;
case 56:
#line 555 "scarl_tokens.y"
{
    /* if without else*/
	if (debugging_grammar) printf("Match if_block_statement\n");
	struct scarl_ast_node *if_statement_node = create_typed_ast_node(NON_TERMINAL_IF_BLOCK_STATEMENT, NON_TERMINAL_IF_BLOCK_STATEMENT);
	struct scarl_ast_node *expression_node = yyvsp[-2];
	struct scarl_ast_node *block_statement_node = yyvsp[0];
	add_child_node(if_statement_node, expression_node);
	add_child_node(if_statement_node, block_statement_node);
	yyval = if_statement_node;
}
break;
case 57:
#line 566 "scarl_tokens.y"
{
    /* if with else*/
	if (debugging_grammar) printf("Match if_block_statement\n");
	struct scarl_ast_node *if_statement_node = create_typed_ast_node(NON_TERMINAL_IF_BLOCK_STATEMENT, NON_TERMINAL_IF_BLOCK_STATEMENT);
	struct scarl_ast_node *expression_node = yyvsp[-4];
	struct scarl_ast_node *if_true_block_statement_node = yyvsp[-2];
	struct scarl_ast_node *if_false_block_statement_node = yyvsp[0];
	add_child_node(if_statement_node, expression_node);
	add_child_node(if_statement_node, if_true_block_statement_node);
	add_child_node(if_statement_node, if_false_block_statement_node);
	yyval = if_statement_node;
}
break;
case 58:
#line 579 "scarl_tokens.y"
{
    /* regular while statement.*/
	if (debugging_grammar) printf("Match while_block_statement\n");
	struct scarl_ast_node *while_statement_node = create_typed_ast_node(NON_TERMINAL_WHILE_BLOCK_STATEMENT, NON_TERMINAL_WHILE_BLOCK_STATEMENT);
	struct scarl_ast_node *expression_node = yyvsp[-2];
	struct scarl_ast_node *block_statement_node = yyvsp[0];
	add_child_node(while_statement_node, expression_node);
	add_child_node(while_statement_node, block_statement_node);
	yyval = while_statement_node;
}
break;
case 59:
#line 592 "scarl_tokens.y"
{
    /* finish the rest of the formal parameter*/
    /* list or this function has 1 parameter*/
	if (debugging_grammar) printf("Match formal_parameter_list\n");
	struct scarl_ast_node *parameter_list_node = create_typed_ast_node(NON_TERMINAL_FORMAL_PARAMETER_LIST, NON_TERMINAL_FORMAL_PARAMETER_LIST);
	struct scarl_ast_node *type_declarator_node = yyvsp[0];
	add_child_node(parameter_list_node, type_declarator_node);
	yyval = parameter_list_node;
}
break;
case 60:
#line 602 "scarl_tokens.y"
{
    /* continue the list of formal parameters*/
	if (debugging_grammar) printf("Match formal_parameter_list\n");
	struct scarl_ast_node *type_declarator_node = yyvsp[-2];
	struct scarl_ast_node *formal_parameter_list_node = yyvsp[0];
	push_child_node_front(formal_parameter_list_node, type_declarator_node);
	yyval = formal_parameter_list_node;
}
break;
case 61:
#line 611 "scarl_tokens.y"
{
    /* allow for empty parameter lists*/
	if (debugging_grammar) printf("Match formal_parameter_list\n");
	yyval = create_typed_ast_node(NON_TERMINAL_FORMAL_PARAMETER_LIST, NON_TERMINAL_FORMAL_PARAMETER_LIST);
}
break;
case 62:
#line 617 "scarl_tokens.y"
{
    /* finish the rest of the  parameter*/
    /* list or this function has 1 argument*/
	if (debugging_grammar) printf("Match parameter_list (one expression)\n");
	struct scarl_ast_node *parameter_list_node = create_typed_ast_node(NON_TERMINAL_PARAMETER_LIST, NON_TERMINAL_PARAMETER_LIST);
	struct scarl_ast_node *expression_node = yyvsp[0];
	push_child_node_front(parameter_list_node, expression_node);
	yyval = parameter_list_node;
}
break;
case 63:
#line 627 "scarl_tokens.y"
{
    /* continue the list of argument*/
	if (debugging_grammar) printf("Match parameter_list (expression list)\n");
	struct scarl_ast_node *expression_node = yyvsp[-2];
	struct scarl_ast_node *parameter_list_node = yyvsp[0];
	add_child_node(parameter_list_node, expression_node);
	yyval = parameter_list_node;
}
break;
case 64:
#line 636 "scarl_tokens.y"
{
    /* allow for empty argument function calls*/
	if (debugging_grammar) printf("Match parameter_list (empty list)\n");
	/* create an empty parameter list */
	yyval = create_typed_ast_node(NON_TERMINAL_PARAMETER_LIST, NON_TERMINAL_PARAMETER_LIST);
}
break;
case 65:
#line 643 "scarl_tokens.y"
{
    /* base expression*/
	if (debugging_grammar) printf("Match expression\n");
	yyval = yyvsp[0];
}
break;
case 66:
#line 649 "scarl_tokens.y"
{
    /* allocates are a special kind of*/
    /* expression that can only occur*/
    /* by themselves*/
	if (debugging_grammar) printf("Match expression\n");
	yyval = yyvsp[0];
}
break;
case 67:
#line 657 "scarl_tokens.y"
{
    /* the allocation invocation is*/
    /* a special kind of function invocation*/
    /* that needs its own production rule to*/
    /* avoid confusion*/
	if (debugging_grammar) printf("Match allocation_expression\n");
	yyval = yyvsp[0]; /* obvious that this is an allocation, unless NON_TERMINAL_POINTER_VALUE ends up showin elsewhere*/
}
break;
case 68:
#line 677 "scarl_tokens.y"
{
    /* primitive allocation*/
	if (debugging_grammar) printf("Match allocation_invocation\n");
	struct scarl_ast_node *allocate_node = create_typed_ast_node(NON_TERMINAL_POINTER_VALUE, NON_TERMINAL_POINTER_VALUE);
	struct scarl_ast_node *primitive_type_node = yyvsp[-3];
	struct scarl_ast_node *parameter_list_node = yyvsp[-1];
	add_child_node(allocate_node, primitive_type_node); /* type defined as a pointer of this type */
	add_child_node(allocate_node, parameter_list_node); /* constructed with these parameters*/
	yyval = allocate_node;
}
break;
case 69:
#line 688 "scarl_tokens.y"
{
    /* class type allocation*/
    /* identifier must be a class in the*/
    /* symbol table and the parameter list*/
    /* must match one of the constructors*/
	char *allocating_type_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match allocation_invocation\n", allocating_type_identifier);
	struct scarl_ast_node *allocate_node = create_typed_ast_node(NON_TERMINAL_POINTER_VALUE, NON_TERMINAL_POINTER_VALUE);
	struct scarl_ast_node *identifier_node = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, allocating_type_identifier);
	struct scarl_ast_node *parameter_list_node = yyvsp[-1];
	add_child_node(allocate_node, identifier_node); /* type defined as a pointer of this type */
	add_child_node(allocate_node, parameter_list_node); /* constructed with these parameters*/
	yyval = allocate_node;
}
break;
case 70:
#line 703 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match logical_expression\n");
	yyval = yyvsp[0];
}
break;
case 71:
#line 708 "scarl_tokens.y"
{
	/*     logical_expression && logical_and_expression*/
	/*     logical_expression should be on the LEFT*/
	/*     logical_and_expression should be on the RIGHT*/
	/*     OR should be the parent node*/
	if (debugging_grammar) printf("Match logical_expression\n");
	struct scarl_ast_node *lhs = yyvsp[-2];
	struct scarl_ast_node *operand = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, OR);
	struct scarl_ast_node *rhs = yyvsp[0];
	add_child_node(operand, lhs);
	add_child_node(operand, rhs);
	yyval = operand;
}
break;
case 72:
#line 722 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match logical_and_expression\n");
	yyval = yyvsp[0];
}
break;
case 73:
#line 727 "scarl_tokens.y"
{
	/*     logical_and_expression && equality_expression*/
	/*     logical_and_expression should be on the LEFT*/
	/*     equality_expression should be on the RIGHT*/
	/*     AND should be the parent node*/
	if (debugging_grammar) printf("Match logical_and_expression\n");
	struct scarl_ast_node *lhs = yyvsp[-2];
	struct scarl_ast_node *operand = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, AND);
	struct scarl_ast_node *rhs = yyvsp[0];
	add_child_node(operand, lhs);
	add_child_node(operand, rhs);
	yyval = operand;
}
break;
case 74:
#line 741 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match equality_expression\n");
	yyval = yyvsp[0];
}
break;
case 75:
#line 746 "scarl_tokens.y"
{
	/*     equality_expression == relational_expression*/
	/*     equality_expression should be on the LEFT*/
	/*     relational_expression should be on the RIGHT*/
	/*     NOT_EQ should be the parent node*/
	if (debugging_grammar) printf("Match equality_expression\n");
	struct scarl_ast_node *lhs = yyvsp[-2];
	struct scarl_ast_node *operand = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, DBL_EQ);
	struct scarl_ast_node *rhs = yyvsp[0];
	add_child_node(operand, lhs);
	add_child_node(operand, rhs);
	yyval = operand;
}
break;
case 76:
#line 760 "scarl_tokens.y"
{
	/*     equality_expression != relational_expression*/
	/*     equality_expression should be on the LEFT*/
	/*     relational_expression should be on the RIGHT*/
	/*     NOT_EQ should be the parent node*/
	if (debugging_grammar) printf("Match equality_expression\n");
	struct scarl_ast_node *lhs = yyvsp[-2];
	struct scarl_ast_node *operand = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, NOT_EQ);
	struct scarl_ast_node *rhs = yyvsp[0];
	add_child_node(operand, lhs);
	add_child_node(operand, rhs);
	yyval = operand;
}
break;
case 77:
#line 774 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match relational_expression\n");
	yyval = yyvsp[0];
}
break;
case 78:
#line 779 "scarl_tokens.y"
{
	/*     relational_expression > bool_expression*/
	/*     relational_expression should be on the LEFT*/
	/*     bool_expression should be on the RIGHT*/
	/*     GTR should be the parent node*/
	if (debugging_grammar) printf("Match relational_expression\n");
	struct scarl_ast_node *lhs = yyvsp[-2];
	struct scarl_ast_node *operand = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, GTR);
	struct scarl_ast_node *rhs = yyvsp[0];
	add_child_node(operand, lhs);
	add_child_node(operand, rhs);
	yyval = operand;
}
break;
case 79:
#line 793 "scarl_tokens.y"
{
	/*     relational_expression < bool_expression*/
	/*     relational_expression should be on the LEFT*/
	/*     bool_expression should be on the RIGHT*/
	/*     LESS should be the parent node*/
	if (debugging_grammar) printf("Match relational_expression\n");
	struct scarl_ast_node *lhs = yyvsp[-2];
	struct scarl_ast_node *operand = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, LESS);
	struct scarl_ast_node *rhs = yyvsp[0];
	add_child_node(operand, lhs);
	add_child_node(operand, rhs);
	yyval = operand;
}
break;
case 80:
#line 807 "scarl_tokens.y"
{
	/*     relational_expression >= bool_expression*/
	/*     relational_expression should be on the LEFT*/
	/*     bool_expression should be on the RIGHT*/
	/*     GTR_EQ should be the parent node*/
	if (debugging_grammar) printf("Match relational_expression\n");
	struct scarl_ast_node *lhs = yyvsp[-2];
	struct scarl_ast_node *operand = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, GTR_EQ);
	struct scarl_ast_node *rhs = yyvsp[0];
	add_child_node(operand, lhs);
	add_child_node(operand, rhs);
	yyval = operand;
}
break;
case 81:
#line 821 "scarl_tokens.y"
{
	/*     relational_expression <= bool_expression*/
	/*     relational_expression should be on the LEFT*/
	/*     bool_expression should be on the RIGHT*/
	/*     LESS_EQ should be the parent node*/
	if (debugging_grammar) printf("Match relational_expression\n");
	struct scarl_ast_node *lhs = yyvsp[-2];
	struct scarl_ast_node *operand = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, LESS_EQ);
	struct scarl_ast_node *rhs = yyvsp[0];
	add_child_node(operand, lhs);
	add_child_node(operand, rhs);
	yyval = operand;
}
break;
case 82:
#line 835 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match bool_expression\n");
	yyval = yyvsp[0];
}
break;
case 83:
#line 840 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match bool_expression\n");
	struct scarl_ast_node *operand = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, BANG);
	struct scarl_ast_node *expression = yyvsp[0];
	add_child_node(operand, expression);
	yyval = operand;
}
break;
case 84:
#line 848 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match arithmetic_expression\n");
	yyval = yyvsp[0];
}
break;
case 85:
#line 853 "scarl_tokens.y"
{
	/*     arithmetic_expression - arithmetic_factor*/
	/*     arithmetic_expression should be on the LEFT*/
	/*     arithmetic_factor should be on the RIGHT*/
	/*     MINUS should be the parent node*/
	if (debugging_grammar) printf("Match arithmetic_expression\n");
	struct scarl_ast_node *lhs = yyvsp[-2];
	struct scarl_ast_node *operand = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, PLUS);
	struct scarl_ast_node *rhs = yyvsp[0];
	add_child_node(operand, lhs);
	add_child_node(operand, rhs);
	yyval = operand;
}
break;
case 86:
#line 867 "scarl_tokens.y"
{
	/*     arithmetic_expression - arithmetic_factor*/
	/*     arithmetic_expression should be on the LEFT*/
	/*     arithmetic_factor should be on the RIGHT*/
	/*     MINUS should be the parent node*/
	if (debugging_grammar) printf("Match arithmetic_expression\n");
	struct scarl_ast_node *lhs = yyvsp[-2];
	struct scarl_ast_node *operand = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, MINUS);
	struct scarl_ast_node *rhs = yyvsp[0];
	add_child_node(operand, lhs);
	add_child_node(operand, rhs);
	yyval = operand;
}
break;
case 87:
#line 881 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match arithmetic_factor\n");
	yyval = yyvsp[0];
}
break;
case 88:
#line 886 "scarl_tokens.y"
{
	/*     arithmetic_factor * arithmetic_unary*/
	/*     arithmetic_factor should be on the LEFT*/
	/*     arithmetic_unary should be on the RIGHT*/
	/*     STAR should be the parent node*/
	if (debugging_grammar) printf("Match arithmetic_factor\n");
	struct scarl_ast_node *lhs = yyvsp[-2];
	struct scarl_ast_node *operand = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, STAR);
	struct scarl_ast_node *rhs = yyvsp[0];
	add_child_node(operand, lhs);
	add_child_node(operand, rhs);
	yyval = operand;
}
break;
case 89:
#line 900 "scarl_tokens.y"
{
	/*     arithmetic_factor / arithmetic_unary*/
	/*     arithmetic_factor should be on the LEFT*/
	/*     arithmetic_unary should be on the RIGHT*/
	/*     SLASH should be the parent node*/
	if (debugging_grammar) printf("Match arithmetic_factor\n");
	struct scarl_ast_node *lhs = yyvsp[-2];
	struct scarl_ast_node *operand = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, SLASH);
	struct scarl_ast_node *rhs = yyvsp[0];
	add_child_node(operand, lhs);
	add_child_node(operand, rhs);
	yyval = operand;
}
break;
case 90:
#line 914 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match arithmetic_unary\n");
	yyval = yyvsp[0];
}
break;
case 91:
#line 919 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match arithmetic_unary\n");
	struct scarl_ast_node *unary_node = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, MINUS);
	struct scarl_ast_node *arithmetic_unary_node = yyvsp[0];
	add_child_node(unary_node, arithmetic_unary_node);
	yyval = unary_node;
}
break;
case 92:
#line 927 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match arithmetic_unary\n");
	yyval = yyvsp[-1];
}
break;
case 93:
#line 932 "scarl_tokens.y"
{
	char *identifier = string_stack_pop();
	if (debugging_grammar) printf("Match unit (%s)\n", identifier);
	yyval = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, identifier);
}
break;
case 94:
#line 938 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match unit\n");
	yyval = yyvsp[0];
}
break;
case 95:
#line 943 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match unit\n");
	yyval = yyvsp[0];
}
break;
case 96:
#line 948 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match unit\n");
	yyval = yyvsp[0];
}
break;
case 97:
#line 953 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match unit\n");
	yyval = yyvsp[0];
}
break;
case 98:
#line 958 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match unit\n");
	yyval = yyvsp[0];
}
break;
case 99:
#line 963 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match unit\n");
	yyval = yyvsp[0];
}
break;
case 100:
#line 968 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match unit\n");
	yyval = yyvsp[0];
}
break;
case 101:
#line 973 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match unit\n");
	yyval = yyvsp[0];
}
break;
case 102:
#line 978 "scarl_tokens.y"
{
    /* ensure that the used identifier is*/
    /* an array type*/
	char *array_variable_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match array_accessor_unit (%s)\n", array_variable_identifier);
	struct scarl_ast_node *array_accessor_unit = create_typed_ast_node(NON_TERMINAL_ARRAY_ACCESSOR_TYPE, NON_TERMINAL_ARRAY_ACCESSOR_TYPE);
	struct scarl_ast_node *identifier_node = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, array_variable_identifier);
	struct scarl_ast_node *arithmetic_expression_node = yyvsp[-1];
	add_child_node(array_accessor_unit, identifier_node);
	add_child_node(array_accessor_unit, arithmetic_expression_node);
	yyval = array_accessor_unit;
}
break;
case 103:
#line 991 "scarl_tokens.y"
{
    /* ensure that the identifier*/
    /* is a pointer type that is*/
    /* in this scope*/
	char *dereferenced_variable_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match dereferenced_pointer\n", dereferenced_variable_identifier);
	struct scarl_ast_node *deref_node = create_typed_ast_node(NON_TERMINAL_DEREFERENCED_VALUE, NON_TERMINAL_DEREFERENCED_VALUE); 
	struct scarl_ast_node *dereferenced_variable_node = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, dereferenced_variable_identifier); 
	add_child_node(deref_node, dereferenced_variable_node);
	yyval = deref_node;
}
break;
case 104:
#line 1003 "scarl_tokens.y"
{
	/* string literals are syntactic*/
	/* sugar for character arrays*/
	char *string_literal = string_stack_pop();
	if (debugging_grammar) printf("Match array_value (%s)\n", string_literal);
	struct scarl_ast_node *string_node = create_typed_ast_node(NON_TERMINAL_ARRAY_TYPE, NON_TERMINAL_ARRAY_VALUE);
	/* composite value. An array value node has its type and value defined by its children*/
	for (int i = 1; i < strlen(string_literal) - 1; i++) {
		struct scarl_ast_node *char_value_node = create_int_value_ast_node(NON_TERMINAL_CHAR_VALUE, string_literal[i]);
		printf("Adding character node\n");
		add_child_node(string_node, char_value_node);
	}
	yyval = string_node;
	/* NON_TERMINAL_ARRAY_VALUE*/
}
break;
case 105:
#line 1019 "scarl_tokens.y"
{
	/* array initializer for arbitrarily typed*/
	/* initialzers*/
	if (debugging_grammar) printf("Match array_value\n");
	yyval = yyvsp[0];
}
break;
case 106:
#line 1026 "scarl_tokens.y"
{
	/* in order to be a valid array initializer,*/
	/* the types that make up the list of values */
	/* must be the same type or must be convertable*/
	/* to a type*/
	/* the type of the array initializer includes*/
	/* the number of elements in the array and the */
	/* type of the "parameters"*/
	if (debugging_grammar) printf("Match array_initializer\n");
	struct scarl_ast_node *parameter_list_node = yyvsp[-1];
	parameter_list_node->node_type = NON_TERMINAL_ARRAY_TYPE;
	parameter_list_node->type_value = NON_TERMINAL_ARRAY_TYPE;
	yyval = parameter_list_node;
	/* NON_TERMINAL_ARRAY_VALUE*/
}
break;
case 107:
#line 1042 "scarl_tokens.y"
{
	int decimal_value = int_stack_pop();
	if (debugging_grammar) printf("Match integer_value (%i)\n", decimal_value);
	yyval = create_int_value_ast_node(NON_TERMINAL_INTEGER_VALUE, decimal_value);
}
break;
case 108:
#line 1048 "scarl_tokens.y"
{
	int octal_value = int_stack_pop();
	if (debugging_grammar) printf("Match integer_value (%i)\n", octal_value);
	yyval = create_int_value_ast_node(NON_TERMINAL_INTEGER_VALUE, octal_value);
}
break;
case 109:
#line 1054 "scarl_tokens.y"
{
	int hex_value = int_stack_pop();
	if (debugging_grammar) printf("Match integer_value (%i)\n", hex_value);
	yyval = create_int_value_ast_node(NON_TERMINAL_INTEGER_VALUE, hex_value);
}
break;
case 110:
#line 1060 "scarl_tokens.y"
{
	int binary_value = int_stack_pop();
	if (debugging_grammar) printf("Match integer_value (%i)\n", binary_value);
	yyval = create_int_value_ast_node(NON_TERMINAL_INTEGER_VALUE, binary_value);
}
break;
case 111:
#line 1066 "scarl_tokens.y"
{
    /* ensure that the identifier is*/
    /* only a single character long.*/
    /* this identifier is going to be the*/
    /* value of the character literal, and*/
    /* not actually be an identifier in the*/
    /* language*/
	char *character_literal = string_stack_pop();
	if (debugging_grammar) printf("Match char_value (%s)\n", character_literal);
	/* the int value of this node is the character, just cast it back to retrieve the character*/
    struct scarl_ast_node *char_value_node = create_int_value_ast_node(NON_TERMINAL_CHAR_VALUE, character_literal[1]);
	free(character_literal);
	yyval = char_value_node;
	/* NON_TERMINAL_CHAR_VALUE*/
}
break;
case 112:
#line 1082 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match bool_value\n");
    yyval = create_int_value_ast_node(NON_TERMINAL_BOOL_VALUE, TRUE);
}
break;
case 113:
#line 1087 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match bool_value\n");
    yyval = create_int_value_ast_node(NON_TERMINAL_BOOL_VALUE, FALSE);
}
break;
case 114:
#line 1092 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match primitive_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_PRIMITIVE_TYPE, VOID);
}
break;
case 115:
#line 1097 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match primitive_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_PRIMITIVE_TYPE, INT);
}
break;
case 116:
#line 1102 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match primitive_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_PRIMITIVE_TYPE, CHAR);
}
break;
case 117:
#line 1107 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match primitive_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_PRIMITIVE_TYPE, VOID);
}
break;
case 118:
#line 1112 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match device_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, LIGHT_ACTUATOR);
}
break;
case 119:
#line 1117 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match device_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, SERVO_ACTUATOR);
}
break;
case 120:
#line 1122 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match device_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, SOUND_SENSOR);
}
break;
case 121:
#line 1127 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match device_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, LIGHT_SENSOR);
}
break;
case 122:
#line 1132 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match device_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, DISTANCE_SENSOR);
}
break;
case 123:
#line 1137 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match device_type\n");
	yyval = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, TEMPERATURE_SENSOR);
}
break;
#line 1930 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
