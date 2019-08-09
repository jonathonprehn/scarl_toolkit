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

/*for performing actions on the code file*/
/*for the compiling unit, this is intermediatary code*/
extern FILE *code_file;

unsigned debugging_grammar = 1;

#line 37 "y.tab.c"
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
   10,    3,   20,   21,   21,   21,   21,   22,   23,   25,
    4,   17,   18,    7,    6,   28,   28,   30,   31,   29,
   32,   32,   33,   33,    5,   11,   15,   15,   35,   12,
   37,   16,   38,   38,   13,   13,   14,   34,   34,   34,
   36,   36,   36,   27,   27,   40,   41,   41,   39,   39,
   42,   42,   43,   43,   43,   44,   44,   44,   44,   44,
   45,   45,   26,   26,   26,   46,   46,   46,   47,   47,
   47,   48,   48,   48,   48,   48,   48,   48,   48,   48,
   52,   53,   54,   54,   55,   49,   49,   49,   49,   50,
   51,   51,   24,   24,   24,   24,   19,   19,   19,   19,
   19,   19,
};
short yylen[] = {                                         2,
    1,    1,    2,    1,    1,    1,    1,    1,    3,    1,
    2,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    3,    2,    1,    1,    1,    1,    4,    2,    1,
    4,    2,    3,    5,    2,    1,    2,    2,    2,    3,
    1,    2,    1,    1,    6,    4,    3,    2,    4,    2,
    4,    2,    3,    3,    5,    7,    5,    1,    3,    0,
    1,    3,    0,    1,    1,    2,    4,    4,    1,    3,
    1,    3,    1,    3,    3,    1,    3,    3,    3,    3,
    1,    2,    1,    3,    3,    1,    3,    3,    1,    2,
    3,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    4,    2,    1,    1,    3,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,
};
short yydefred[] = {                                      0,
   30,  113,  114,  115,  116,  117,  118,  119,  120,  121,
  122,    0,    0,    0,    1,    0,    4,    5,    6,    7,
    8,    0,    0,    0,   24,   25,   26,   27,    0,    0,
    0,    0,   38,    3,    0,    0,    0,   29,    0,    0,
   35,    0,   37,    0,   23,   22,    0,    0,    0,    0,
    0,  106,  107,  108,  109,  111,  112,    0,    0,  103,
  110,    0,    0,   96,   98,    0,    0,   65,    0,    0,
    0,   76,    0,   86,   89,   93,   94,   95,   97,   99,
  100,  104,    0,    0,   43,   44,    0,    0,    0,   39,
    0,    0,    0,    0,   90,    0,    0,    0,    0,    0,
    0,   66,  102,    0,    0,   31,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   28,
   32,   40,   42,   34,    0,    0,    0,   54,   91,    0,
  105,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   77,   78,   79,   80,   87,   88,    0,    0,   49,  101,
   62,    0,    0,   51,   59,    0,   45,   68,   67,    0,
    0,    0,    0,    0,   12,   13,    0,    0,   14,   15,
   16,   17,   18,   19,   20,   21,    0,    0,    0,    0,
    0,    0,   48,    0,    0,    9,   11,   50,   52,    0,
    0,    0,   47,   33,   46,    0,    0,    0,   57,    0,
   56,
};
short yydgoto[] = {                                      14,
   15,   16,   17,   18,   19,   20,   21,  166,  167,  168,
  169,  170,  171,  172,  173,  174,   86,  176,   22,   23,
   32,   25,   26,   27,   28,   62,   98,   29,   41,   30,
   43,   88,   89,  119,   64,   99,   65,   66,   67,   68,
  102,   69,   70,   71,   72,   73,   74,   75,   76,   77,
   78,   79,   80,   81,   82,
};
short yysindex[] = {                                     15,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -10, -252,    0,    0,   15,    0,    0,    0,    0,
    0, -238, -231, -250,    0,    0,    0,    0, -259, -219,
 -197, -236,    0,    0, -228, -194, -186,    0, -104,  -10,
    0, -153,    0, -194,    0,    0, -258, -104, -104, -104,
 -194,    0,    0,    0,    0,    0,    0,   80, -147,    0,
    0, -116, -179,    0,    0, -150, -152,    0, -144, -157,
 -140,    0, -110,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -10, -232,    0,    0, -128, -126,  -10,    0,
 -123, -194, -104,  -82,    0, -116, -132, -100, -108,  -87,
  -81,    0,    0, -104, -104,    0, -194, -148, -148, -148,
 -148, -148, -148, -148, -148, -104, -104,  -84,  -73,    0,
    0,    0,    0,    0,  -66, -227, -101,    0,    0, -194,
    0, -194, -194, -110, -110,  -65, -144, -157, -140, -140,
    0,    0,    0,    0,    0,    0,  -10,  -76,    0,    0,
    0,  -60,  -53,    0,    0,   68,    0,    0,    0, -253,
  -71,  -46, -251,  -26,    0,    0,  -62,   68,    0,    0,
    0,    0,    0,    0,    0,    0, -199,  -48,  -47, -194,
 -194, -194,    0,  -39,  -28,    0,    0,    0,    0,  -24,
  -11,   -3,    0,    0,    0,  -76,  -76,  -23,    0,  -76,
    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  234,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   -7,
    0,    0,    0,    0,    0,    0, -168,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  -59,    0,    0,    0,
   -4,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  101,    0,    0,    0,    0, -109,    0,  -91, -180,
 -111,    0,  -34,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   14,    0,    0,    0,    0,    0,   -1,    0,
    0,   22,    0,    0,    0,  118,    0, -246,    0,    0,
    0,    0,    0,    0,    0,    0,   22,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   28,    0,    0,
    0,    0,    0,    0,    0,    0,   31,    0,    0, -245,
    0,   22,   22,   -9,   16,    0,   49, -156,  130,  142,
    0,    0,    0,    0,    0,    0,   14,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, -223,
    0,    0,    0,    0,    0,    0,    0,   17,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   57,    0,    0,
    0,
};
short yygindex[] = {                                      0,
  284,    0,    0, -115,  -20,    0,    0, -136,  135,    0,
    0,    0,    0,    0,    0,    0, -102,    0,    0,  -12,
    2,    0,    0,  246,    0,  -36,  -35,    0,    0,    0,
    0,  222,    0,  165,  -89,  -45,  -72,  221,    0,    0,
    0,  208,  218,   62,  115,   86,  -44,    0,    0,    0,
    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 427
short yytable[] = {                                      31,
   63,   24,   84,   95,   33,   47,   37,   48,   91,   92,
   49,  157,   96,   97,   92,   38,   50,   24,   35,   85,
   45,  180,   61,   63,   40,  104,  105,   87,  183,   38,
  104,  105,   51,   30,   52,   53,   54,   55,   61,   63,
  165,   24,   30,   36,   56,   57,  125,   93,   58,   94,
   59,   46,  165,  175,   94,   39,  126,   60,   61,  198,
  199,  136,   47,  201,   48,  175,  178,   49,   85,   39,
  118,  145,  146,   50,  120,   36,   87,   44,  178,  150,
  121,   83,   30,  179,  151,   42,  152,  153,   71,   51,
   24,   52,   53,   54,   55,  179,   71,   71,   71,   71,
  106,   56,   57,   90,   71,   58,   23,   59,   47,  103,
   48,   23,   72,   49,   60,   61,  110,  107,  111,   50,
   72,   72,   72,   72,  108,  104,  105,  184,   72,  112,
  113,  114,  115,  109,  118,   51,  129,   52,   53,   54,
   55,  104,  105,  177,  190,  191,  192,   56,   57,  116,
  117,  121,   47,   59,   48,  177,  124,   73,  122,   64,
   60,   61,   73,   50,   73,   73,   73,   73,   73,   64,
   64,  139,  140,   73,  127,   64,  131,   69,  130,   51,
  132,   52,   53,   54,   55,   69,  133,   69,   69,  134,
  135,   56,   57,   69,  147,  148,  181,   59,   92,   92,
   92,   92,  149,  154,   60,   61,   94,  156,  158,   92,
   92,   92,   92,   92,   92,  159,   92,   92,   92,   92,
   92,  182,  186,   83,   83,   92,  141,  142,  143,  144,
  185,  188,  189,    2,   83,   83,   83,   83,   83,   83,
  193,   83,   83,   83,   83,   83,    1,   92,   84,   84,
   83,  194,    2,    3,    4,  195,    5,  196,  200,   84,
   84,   84,   84,   84,   84,  197,   84,   84,   84,   84,
   84,    1,   83,   85,   85,   84,   36,    2,    3,    4,
   63,    5,   60,   41,   85,   85,   85,   85,   85,   85,
   63,   85,   85,   85,   85,   85,   58,   84,   53,   34,
   85,   10,  187,  101,    6,    7,    8,    9,   10,   11,
  123,  155,   12,   55,  128,  137,    0,   70,   13,   55,
   55,   55,   85,   55,  160,   70,  138,   70,   70,    0,
    2,    3,    4,   70,    5,    0,  100,   55,    0,   55,
   55,   55,    2,    3,    4,    0,    5,    0,  161,    0,
  162,  156,    0,    0,    0,   55,    0,   55,    0,    0,
    0,    0,    0,    0,    0,    0,  163,    0,  164,   81,
   81,   81,   81,   81,   81,    0,   81,   81,   81,   81,
   81,    0,    0,    0,    0,   81,   82,   82,   82,   82,
   82,   82,    0,   82,   82,   82,   82,   82,   74,    0,
    0,    0,   82,   74,    0,   74,   74,   74,   74,   74,
   75,    0,    0,    0,   74,   75,    0,   75,   75,   75,
   75,   75,    0,    0,    0,    0,   75,
};
short yycheck[] = {                                      12,
   36,    0,   39,   48,  257,  257,  257,  259,   44,  268,
  262,  148,   49,   50,  268,  266,  268,   16,  257,   40,
  257,  275,  269,  269,  284,  258,  259,   40,  280,  266,
  258,  259,  284,  257,  286,  287,  288,  289,  285,  285,
  156,   40,  266,  275,  296,  297,   92,  306,  300,  308,
  302,  280,  168,  156,  308,  306,   93,  309,  310,  196,
  197,  107,  257,  200,  259,  168,  156,  262,   89,  306,
   83,  116,  117,  268,  307,  275,   89,  275,  168,  307,
  280,  268,  306,  156,  130,  305,  132,  133,  269,  284,
   89,  286,  287,  288,  289,  168,  277,  278,  279,  280,
  280,  296,  297,  257,  285,  300,  275,  302,  257,  257,
  259,  280,  269,  262,  309,  310,  274,  268,  276,  268,
  277,  278,  279,  280,  277,  258,  259,  163,  285,  270,
  271,  272,  273,  278,  147,  284,  269,  286,  287,  288,
  289,  258,  259,  156,  180,  181,  182,  296,  297,  260,
  261,  280,  257,  302,  259,  168,  280,  269,  285,  269,
  309,  310,  274,  268,  276,  277,  278,  279,  280,  279,
  280,  110,  111,  285,  257,  285,  285,  269,  279,  284,
  268,  286,  287,  288,  289,  277,  268,  279,  280,  104,
  105,  296,  297,  285,  279,  269,  268,  302,  258,  259,
  260,  261,  269,  269,  309,  310,  308,  284,  269,  269,
  270,  271,  272,  273,  274,  269,  276,  277,  278,  279,
  280,  268,  285,  258,  259,  285,  112,  113,  114,  115,
  257,  280,  280,    0,  269,  270,  271,  272,  273,  274,
  280,  276,  277,  278,  279,  280,  257,  307,  258,  259,
  285,  280,  263,  264,  265,  280,  267,  269,  282,  269,
  270,  271,  272,  273,  274,  269,  276,  277,  278,  279,
  280,  257,  307,  258,  259,  285,  284,  263,  264,  265,
  285,  267,  269,  285,  269,  270,  271,  272,  273,  274,
  269,  276,  277,  278,  279,  280,  269,  307,  268,   16,
  285,  285,  168,   58,  290,  291,  292,  293,  294,  295,
   89,  147,  298,  257,   94,  108,   -1,  269,  304,  263,
  264,  265,  307,  267,  257,  277,  109,  279,  280,   -1,
  263,  264,  265,  285,  267,   -1,  257,  281,   -1,  283,
  284,  285,  263,  264,  265,   -1,  267,   -1,  281,   -1,
  283,  284,   -1,   -1,   -1,  299,   -1,  301,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  299,   -1,  301,  269,
  270,  271,  272,  273,  274,   -1,  276,  277,  278,  279,
  280,   -1,   -1,   -1,   -1,  285,  269,  270,  271,  272,
  273,  274,   -1,  276,  277,  278,  279,  280,  269,   -1,
   -1,   -1,  285,  274,   -1,  276,  277,  278,  279,  280,
  269,   -1,   -1,   -1,  285,  274,   -1,  276,  277,  278,
  279,  280,   -1,   -1,   -1,   -1,  285,
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
"allocation_invocation : IDENTIFIER LPAREN parameter_list RPAREN",
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
#line 824 "scarl_tokens.y"

void yyerror(char *s) {
	fprintf(stderr, "%s at line %i near \'%s\'\n", s, line_number, last_token_text);
}
#line 477 "y.tab.c"
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
#line 61 "scarl_tokens.y"
{
	printf("Match program\n");
	
    /* nothing to do?*/
}
break;
case 2:
#line 67 "scarl_tokens.y"
{
    /* finish off the statement list*/
	if (debugging_grammar) printf("Match statement_list\n");
}
break;
case 3:
#line 72 "scarl_tokens.y"
{
    /* add the statement to the statement list*/
	if (debugging_grammar) printf("Match statement_list\n");
}
break;
case 4:
#line 77 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement\n");
}
break;
case 5:
#line 81 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement\n");
}
break;
case 6:
#line 85 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement\n");
}
break;
case 7:
#line 89 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement\n");
}
break;
case 8:
#line 93 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement\n");
}
break;
case 9:
#line 97 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match block_statement\n");
}
break;
case 10:
#line 101 "scarl_tokens.y"
{
    /* finish the block level statement list*/
	if (debugging_grammar) printf("Match statement_list_block_level\n");
}
break;
case 11:
#line 106 "scarl_tokens.y"
{
    /* add a block level statement to the statement list*/
	if (debugging_grammar) printf("Match statement_list_block_level\n");
}
break;
case 12:
#line 111 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
}
break;
case 13:
#line 115 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
}
break;
case 14:
#line 119 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
}
break;
case 15:
#line 123 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
}
break;
case 16:
#line 127 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
}
break;
case 17:
#line 131 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
}
break;
case 18:
#line 135 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
}
break;
case 19:
#line 139 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
}
break;
case 20:
#line 143 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
}
break;
case 21:
#line 147 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
}
break;
case 22:
#line 151 "scarl_tokens.y"
{
	char *device_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match device_declarator_statement (%s)\n", device_identifier);
	
}
break;
case 23:
#line 157 "scarl_tokens.y"
{
    /* for any variable declared with a type*/
	char *declarator_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match type_declarator (%s)\n", declarator_identifier);

}
break;
case 24:
#line 164 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match any_type\n");
}
break;
case 25:
#line 168 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match any_type\n");
}
break;
case 26:
#line 172 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match any_type\n");
}
break;
case 27:
#line 176 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match any_type\n");
}
break;
case 28:
#line 180 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match array_type\n");
}
break;
case 29:
#line 184 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match pointer_type\n");
}
break;
case 30:
#line 188 "scarl_tokens.y"
{
	char *user_type_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match user_type (%s)\n", user_type_identifier);
	
}
break;
case 31:
#line 194 "scarl_tokens.y"
{
    /* we must ensure that the evaluated type*/
    /* on the right hand side of the = sign is*/
    /* the same type or can be converted to the*/
    /* type on the left hand side*/
	if (debugging_grammar) printf("Match variable_definition_statement\n");

}
break;
case 32:
#line 203 "scarl_tokens.y"
{
	/* declares a variable without giving it a value - cannot*/
	/* refer to this variable without assigning it, otherwise */
	/* the compiler will give an error*/
	if (debugging_grammar) printf("Match variable_declaration_statement\n");
}
break;
case 33:
#line 210 "scarl_tokens.y"
{
	/* for deallocating a pointer variable*/
	/* be sure this only occurs on pointer types */
	char *deleting_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match delete_statement (%s)\n", deleting_identifier);
}
break;
case 34:
#line 217 "scarl_tokens.y"
{
    /* functions like the variable_definition_statement*/
    /* except it can only be in global scope and*/
    /* the value will be evaluated at compile time*/
    /* (array lengths can be defined as literals or constant values)*/
	if (debugging_grammar) printf("Match constant_definition_statement\n");

}
break;
case 35:
#line 226 "scarl_tokens.y"
{
    /* add this declared class into the symbol*/
    /* table for global scope (classes can only be*/
    /* declared in global scope) and give it the*/
    /* type attributes listed in the class body*/
	if (debugging_grammar) printf("Match class_definition_statement\n");

}
break;
case 36:
#line 235 "scarl_tokens.y"
{
    /* this class declarator is a "normal"*/
    /* class. It is not derived from another*/
    /* class*/
	if (debugging_grammar) printf("Match class_declarator\n");

}
break;
case 37:
#line 243 "scarl_tokens.y"
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


}
break;
case 38:
#line 259 "scarl_tokens.y"
{
    /* ensure that the identifier is not*/
    /* being used for something else in*/
    /* this (global) scope*/
	char *class_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match class_name (%s)\n", class_identifier);

}
break;
case 39:
#line 268 "scarl_tokens.y"
{
    /* we need to ensure that the*/
    /* identifier is actually a class*/
    /* name defined in the symbol table*/
	char *extending_class_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match class_extending (%s)\n", extending_class_identifier);

}
break;
case 40:
#line 277 "scarl_tokens.y"
{
    /* a list of class attributes*/
    /* processing takes place in the*/
    /* class_definition_statement*/
    /* production rule*/
	if (debugging_grammar) printf("Match class_body\n");

}
break;
case 41:
#line 286 "scarl_tokens.y"
{
    /* finish off the class attribute list*/
	if (debugging_grammar) printf("Match class_attribute_list\n");

}
break;
case 42:
#line 292 "scarl_tokens.y"
{
    /* add another attribute to the list*/
	if (debugging_grammar) printf("Match class_attribute_list\n");

}
break;
case 43:
#line 298 "scarl_tokens.y"
{
    /* a special location for functions*/
    /* this function definition is actually*/
    /* going to be a method for this class*/
	if (debugging_grammar) printf("Match class_attribute\n");

}
break;
case 44:
#line 306 "scarl_tokens.y"
{
    /* a special kind of declarator*/
    /* that does not require an initial*/
    /* value. This can only take place*/
    /* in a class body. This will be*/
    /* a field for instances of this class*/
	if (debugging_grammar) printf("Match class_attribute\n");
	
}
break;
case 45:
#line 316 "scarl_tokens.y"
{
    /* functions will only be able to return*/
    /* primitives for this version. Hopefully*/
    /* extend it to pointer types later on. Can*/
    /* always pass pointer types as parameters*/
    /* to functions*/
	char *function_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match function_definition_statement (%s)\n", function_identifier);

}
break;
case 46:
#line 327 "scarl_tokens.y"
{
    /* sets the value for the identifier to the evaluated*/
    /* value of the expression. Need to ensure that the type*/
    /* of the identifier matches or can be converted to the type*/
    /* of the expression. Also ensure that the identifier is in scope*/
	char *variable_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match variable_set_statement (%s)\n", variable_identifier);
}
break;
case 47:
#line 336 "scarl_tokens.y"
{
    /* can only appear in functions.*/
    /* acts like a normal C return statement*/
    /* the expression type for all return*/
    /* statements in a function must match*/
    /* the return type for that function*/

    /* additionally, void functions cannot have*/
    /* return statements with expressions*/
	if (debugging_grammar) printf("Match return_statement\n");
	
}
break;
case 48:
#line 349 "scarl_tokens.y"
{
    /* empty return statement.*/
    /* can only occur in void functions*/
	if (debugging_grammar) printf("Match return_statement\n");
	
}
break;
case 49:
#line 356 "scarl_tokens.y"
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
	
}
break;
case 50:
#line 371 "scarl_tokens.y"
{
    /* allows for there to be statements that*/
    /* only call functions*/
	if (debugging_grammar) printf("Match function_invocation_statement\n");
	
}
break;
case 51:
#line 378 "scarl_tokens.y"
{
    /* requires more heavy lifting than*/
    /* a function invocation because we need*/
    /* to resolve the scope to where the*/
    /* class_attribute_identifier leads to.*/
    /* A method invocation is calling a*/
    /* method of an object instance*/
	if (debugging_grammar) printf("Match method_invocation\n");
}
break;
case 52:
#line 388 "scarl_tokens.y"
{
    /* allows for a statement to be only*/
    /* a method invocation*/
	if (debugging_grammar) printf("Match method_invocation_statement\n");
	
}
break;
case 53:
#line 395 "scarl_tokens.y"
{
    /* the last case in the chain of*/
    /* identifiers dot identifiers for a method*/
    /* identifier*/
    /* this could also just lead to a field of*/
    /* an object instance, not a method*/
	char *second_identifier = string_stack_pop();
	char *first_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match class_attribute_identifier (%s.%s)\n", first_identifier, second_identifier);

}
break;
case 54:
#line 407 "scarl_tokens.y"
{
    /* enables the dot operator to*/
    /* act as far as it needs to to*/
    /* get to where a field or method is*/
    /* this could also just lead to a field of*/
    /* an object instance, not a method*/
	char *identifier = string_stack_pop();
	if (debugging_grammar) printf("Match class_attribute_identifier (%s.<more stuff>)\n", identifier);

}
break;
case 55:
#line 418 "scarl_tokens.y"
{
    /* if without else*/
	if (debugging_grammar) printf("Match if_block_statement\n");
}
break;
case 56:
#line 423 "scarl_tokens.y"
{
    /* if with else*/
	if (debugging_grammar) printf("Match if_block_statement\n");
}
break;
case 57:
#line 428 "scarl_tokens.y"
{
    /* regular while statement.*/
	if (debugging_grammar) printf("Match while_block_statement\n");
}
break;
case 58:
#line 433 "scarl_tokens.y"
{
    /* finish the rest of the formal parameter*/
    /* list or this function has 1 parameter*/
	if (debugging_grammar) printf("Match formal_parameter_list\n");
}
break;
case 59:
#line 439 "scarl_tokens.y"
{
    /* continue the list of formal parameters*/
	if (debugging_grammar) printf("Match formal_parameter_list\n");
}
break;
case 60:
#line 444 "scarl_tokens.y"
{
    /* allow for empty parameter lists*/
	if (debugging_grammar) printf("Match formal_parameter_list\n");
}
break;
case 61:
#line 449 "scarl_tokens.y"
{
    /* finish the rest of the  parameter*/
    /* list or this function has 1 argument*/
	if (debugging_grammar) printf("Match parameter_list\n");
}
break;
case 62:
#line 455 "scarl_tokens.y"
{
    /* continue the list of argument*/
	if (debugging_grammar) printf("Match parameter_list\n");
}
break;
case 63:
#line 460 "scarl_tokens.y"
{
    /* allow for empty argument function calls*/
	if (debugging_grammar) printf("Match parameter_list\n");
}
break;
case 64:
#line 465 "scarl_tokens.y"
{
    /* base expression*/
	if (debugging_grammar) printf("Match expression\n");
}
break;
case 65:
#line 470 "scarl_tokens.y"
{
    /* allocates are a special kind of*/
    /* expression that can only occur*/
    /* by themselves*/
	if (debugging_grammar) printf("Match expression\n");
}
break;
case 66:
#line 477 "scarl_tokens.y"
{
    /* the allocation invocation is*/
    /* a special kind of function invocation*/
    /* that needs its own production rule to*/
    /* avoid confusion*/
	if (debugging_grammar) printf("Match allocation_expression\n");
}
break;
case 67:
#line 496 "scarl_tokens.y"
{
    /* primitive allocation*/
	if (debugging_grammar) printf("Match allocation_invocation\n");
}
break;
case 68:
#line 501 "scarl_tokens.y"
{
    /* class type allocation*/
    /* identifier must be a class in the*/
    /* symbol table and the parameter list*/
    /* must match one of the constructors*/
	char *allocating_type_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match allocation_invocation\n", allocating_type_identifier);
	
}
break;
case 69:
#line 511 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match logical_expression\n");
}
break;
case 70:
#line 515 "scarl_tokens.y"
{
	/*     logical_expression && logical_and_expression*/
	/*     logical_expression should be on the LEFT*/
	/*     logical_and_expression should be on the RIGHT*/
	/*     OR should be the parent node*/
	if (debugging_grammar) printf("Match logical_expression\n");
}
break;
case 71:
#line 523 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match logical_and_expression\n");
}
break;
case 72:
#line 527 "scarl_tokens.y"
{
	/*     logical_and_expression && equality_expression*/
	/*     logical_and_expression should be on the LEFT*/
	/*     equality_expression should be on the RIGHT*/
	/*     AND should be the parent node*/
	if (debugging_grammar) printf("Match logical_and_expression\n");

}
break;
case 73:
#line 536 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match equality_expression\n");
}
break;
case 74:
#line 540 "scarl_tokens.y"
{
	/*     equality_expression == relational_expression*/
	/*     equality_expression should be on the LEFT*/
	/*     relational_expression should be on the RIGHT*/
	/*     NOT_EQ should be the parent node*/
	if (debugging_grammar) printf("Match equality_expression\n");

}
break;
case 75:
#line 549 "scarl_tokens.y"
{
	/*     equality_expression != relational_expression*/
	/*     equality_expression should be on the LEFT*/
	/*     relational_expression should be on the RIGHT*/
	/*     NOT_EQ should be the parent node*/
	if (debugging_grammar) printf("Match equality_expression\n");

}
break;
case 76:
#line 558 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match relational_expression\n");
}
break;
case 77:
#line 562 "scarl_tokens.y"
{
	/*     relational_expression > bool_expression*/
	/*     relational_expression should be on the LEFT*/
	/*     bool_expression should be on the RIGHT*/
	/*     GTR should be the parent node*/
	if (debugging_grammar) printf("Match relational_expression\n");
}
break;
case 78:
#line 570 "scarl_tokens.y"
{
	/*     relational_expression < bool_expression*/
	/*     relational_expression should be on the LEFT*/
	/*     bool_expression should be on the RIGHT*/
	/*     LESS should be the parent node*/
	if (debugging_grammar) printf("Match relational_expression\n");
}
break;
case 79:
#line 578 "scarl_tokens.y"
{
	/*     relational_expression >= bool_expression*/
	/*     relational_expression should be on the LEFT*/
	/*     bool_expression should be on the RIGHT*/
	/*     GTR_EQ should be the parent node*/
	if (debugging_grammar) printf("Match relational_expression\n");
}
break;
case 80:
#line 586 "scarl_tokens.y"
{
	/*     relational_expression <= bool_expression*/
	/*     relational_expression should be on the LEFT*/
	/*     bool_expression should be on the RIGHT*/
	/*     LESS_EQ should be the parent node*/
	if (debugging_grammar) printf("Match relational_expression\n");
}
break;
case 81:
#line 594 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match bool_expression\n");
}
break;
case 82:
#line 598 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match bool_expression\n");
}
break;
case 83:
#line 602 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match arithmetic_expression\n");
}
break;
case 84:
#line 606 "scarl_tokens.y"
{
	/*     arithmetic_expression - arithmetic_factor*/
	/*     arithmetic_expression should be on the LEFT*/
	/*     arithmetic_factor should be on the RIGHT*/
	/*     MINUS should be the parent node*/
	if (debugging_grammar) printf("Match arithmetic_expression\n");
}
break;
case 85:
#line 614 "scarl_tokens.y"
{
	/*     arithmetic_expression - arithmetic_factor*/
	/*     arithmetic_expression should be on the LEFT*/
	/*     arithmetic_factor should be on the RIGHT*/
	/*     MINUS should be the parent node*/
	if (debugging_grammar) printf("Match arithmetic_expression\n");
}
break;
case 86:
#line 622 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match arithmetic_factor\n");
}
break;
case 87:
#line 626 "scarl_tokens.y"
{
	/*     arithmetic_factor * arithmetic_unary*/
	/*     arithmetic_factor should be on the LEFT*/
	/*     arithmetic_unary should be on the RIGHT*/
	/*     STAR should be the parent node*/
	if (debugging_grammar) printf("Match arithmetic_factor\n");
}
break;
case 88:
#line 634 "scarl_tokens.y"
{
	/*     arithmetic_factor / arithmetic_unary*/
	/*     arithmetic_factor should be on the LEFT*/
	/*     arithmetic_unary should be on the RIGHT*/
	/*     SLASH should be the parent node*/
	if (debugging_grammar) printf("Match arithmetic_factor\n");
}
break;
case 89:
#line 642 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match arithmetic_unary\n");
}
break;
case 90:
#line 646 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match arithmetic_unary\n");
}
break;
case 91:
#line 650 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match arithmetic_unary\n");
}
break;
case 92:
#line 654 "scarl_tokens.y"
{
	char *identifier = string_stack_pop();
	if (debugging_grammar) printf("Match unit (%s)\n", identifier);
}
break;
case 93:
#line 659 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match unit\n");
}
break;
case 94:
#line 663 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match unit\n");
}
break;
case 95:
#line 667 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match unit\n");
}
break;
case 96:
#line 671 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match unit\n");
}
break;
case 97:
#line 675 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match unit\n");
}
break;
case 98:
#line 679 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match unit\n");
}
break;
case 99:
#line 683 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match unit\n");
}
break;
case 100:
#line 687 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match unit\n");
}
break;
case 101:
#line 691 "scarl_tokens.y"
{
    /* ensure that the used identifier is*/
    /* an array type*/
	char *array_variable_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match array_accessor_unit (%s)\n", array_variable_identifier);
}
break;
case 102:
#line 698 "scarl_tokens.y"
{
    /* ensure that the identifier*/
    /* is a pointer type that is*/
    /* in this scope*/
	char *dereferenced_variable_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match dereferenced_pointer\n", dereferenced_variable_identifier);
}
break;
case 103:
#line 706 "scarl_tokens.y"
{
	/* string literals are syntactic*/
	/* sugar for character arrays*/
	char *string_literal = string_stack_pop();
	if (debugging_grammar) printf("Match array_value (%s)\n", string_literal);
	
}
break;
case 104:
#line 714 "scarl_tokens.y"
{
	/* array initializer for arbitrarily typed*/
	/* initialzers.*/
	if (debugging_grammar) printf("Match array_value\n");
}
break;
case 105:
#line 720 "scarl_tokens.y"
{
	/* in order to be a valid array initializer,*/
	/* the types that make up the list of values */
	/* must be the same type or must be convertable*/
	/* to a type*/
	/* the type of the array initializer includes*/
	/* the number of elements in the array and the */
	/* type of the "parameters"*/
	if (debugging_grammar) printf("Match array_initializer\n");
}
break;
case 106:
#line 731 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match integer_value\n");
    yyval = create_typed_ast_node(NON_TERMINAL_INTEGER_VALUE, yyvsp[0]);
}
break;
case 107:
#line 736 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match integer_value\n");
    yyval = create_typed_ast_node(NON_TERMINAL_INTEGER_VALUE, yyvsp[0]);
}
break;
case 108:
#line 741 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match integer_value\n");
    yyval = create_typed_ast_node(NON_TERMINAL_INTEGER_VALUE, yyvsp[0]);
}
break;
case 109:
#line 746 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match integer_value\n");
    yyval = create_typed_ast_node(NON_TERMINAL_INTEGER_VALUE, yyvsp[0]);
}
break;
case 110:
#line 751 "scarl_tokens.y"
{
    /* ensure that the identifier is*/
    /* only a single character long.*/
    /* this identifier is going to be the*/
    /* value of the character literal, and*/
    /* not actually be an identifier in the*/
    /* language*/
	char *character_literal = string_stack_pop();
	if (debugging_grammar) printf("Match char_value (%s)\n", character_literal);
    
}
break;
case 111:
#line 763 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match bool_value\n");
    yyval = create_int_value_ast_node(NON_TERMINAL_BOOL_VALUE, TRUE);
}
break;
case 112:
#line 768 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match bool_value\n");
    yyval = create_int_value_ast_node(NON_TERMINAL_BOOL_VALUE, FALSE);
}
break;
case 113:
#line 773 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match primitive_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_PRIMITIVE_TYPE, VOID);
}
break;
case 114:
#line 778 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match primitive_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_PRIMITIVE_TYPE, INT);
}
break;
case 115:
#line 783 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match primitive_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_PRIMITIVE_TYPE, CHAR);
}
break;
case 116:
#line 788 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match primitive_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_PRIMITIVE_TYPE, VOID);
}
break;
case 117:
#line 793 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match device_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, LIGHT_ACTUATOR);
}
break;
case 118:
#line 798 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match device_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, SERVO_ACTUATOR);
}
break;
case 119:
#line 803 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match device_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, SOUND_SENSOR);
}
break;
case 120:
#line 808 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match device_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, LIGHT_SENSOR);
}
break;
case 121:
#line 813 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match device_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, DISTANCE_SENSOR);
}
break;
case 122:
#line 818 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match device_type\n");
	yyval = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, TEMPERATURE_SENSOR);
}
break;
#line 1613 "y.tab.c"
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
