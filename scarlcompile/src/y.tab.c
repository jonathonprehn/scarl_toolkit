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
#include "scarlsymboltable.h"
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

unsigned debugging_grammar = 0;

#line 40 "y.tab.c"
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
#define SERIAL_SENSOR 311
#define SERIAL_ACTUATOR 312
#define BYTE 313
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    1,    1,    2,    2,    2,    2,    2,    8,    9,
    9,   10,   10,   10,   10,   10,   10,   10,   10,   10,
   10,   10,   18,   19,   19,   19,   19,   19,   20,   21,
   23,    3,    7,   17,    6,    5,   27,   27,   29,   30,
   28,   31,   31,   32,   32,    4,   11,   11,   15,   15,
   35,   12,   37,   16,   34,   34,   13,   13,   14,   33,
   33,   33,   36,   36,   36,   26,   26,   39,   40,   40,
   38,   38,   41,   41,   42,   42,   42,   43,   43,   43,
   43,   43,   44,   44,   25,   25,   25,   45,   45,   45,
   46,   46,   46,   47,   47,   47,   47,   47,   47,   47,
   47,   47,   51,   52,   53,   53,   54,   48,   48,   48,
   48,   49,   50,   50,   22,   22,   22,   22,   22,   24,
   24,   24,   24,   24,   24,   24,   24,
};
short yylen[] = {                                         2,
    1,    1,    2,    1,    1,    1,    1,    1,    3,    1,
    2,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    2,    1,    1,    1,    1,    1,    4,    2,
    1,    4,    2,    3,    5,    2,    1,    2,    2,    2,
    3,    1,    2,    1,    1,    6,    4,    4,    3,    2,
    4,    2,    4,    2,    3,    3,    5,    7,    5,    1,
    3,    0,    1,    3,    0,    1,    1,    2,    4,    4,
    1,    3,    1,    3,    1,    3,    3,    1,    3,    3,
    3,    3,    1,    2,    1,    3,    3,    1,    3,    3,
    1,    2,    3,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    4,    2,    1,    1,    3,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,
};
short yydefred[] = {                                      0,
   31,  115,  116,  117,  118,  120,  121,  122,  123,  124,
  125,    0,    0,  126,  127,  119,    0,    1,    0,    4,
    5,    6,    7,    8,    0,    0,   24,   25,   26,   27,
   28,    0,    0,    0,    0,   39,    3,    0,   33,    0,
   30,    0,    0,   36,    0,   38,    0,   23,    0,    0,
    0,    0,    0,  108,  109,  110,  111,  113,  114,    0,
    0,  105,  112,    0,    0,    0,   98,  100,    0,   67,
    0,    0,    0,   78,    0,   88,   91,   95,   96,   97,
   99,  101,  102,  106,    0,    0,   44,   45,    0,    0,
    0,   40,    0,    0,    0,    0,   92,    0,    0,    0,
    0,    0,    0,   68,  104,    0,    0,   32,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   29,   41,   43,   35,    0,    0,    0,   56,   93,
    0,  107,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   79,   80,   81,   82,   89,   90,    0,    0,   51,
  103,   64,    0,    0,   53,   61,    0,   46,   69,   70,
    0,    0,    0,    0,    0,   12,   22,   20,   13,    0,
    0,   14,   15,   16,   17,   18,   19,   21,    0,    0,
    0,    0,    0,    0,   50,    0,    0,    9,   11,    0,
   52,   54,    0,    0,    0,   49,   34,    0,   47,    0,
    0,   48,    0,   59,    0,   58,
};
short yydgoto[] = {                                      17,
   18,   19,   20,   21,   22,   23,   24,  169,  170,  171,
  172,  173,  174,  175,  176,  177,  178,   25,   35,   27,
   28,   29,   30,   31,   64,  100,   32,   44,   33,   46,
   90,   91,  121,   66,   67,  101,   68,   69,   70,  104,
   71,   72,   73,   74,   75,   76,   77,   78,   79,   80,
   81,   82,   83,   84,
};
short yysindex[] = {                                   -251,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -110, -237,    0,    0,    0,    0,    0, -251,    0,
    0,    0,    0,    0, -270, -221,    0,    0,    0,    0,
    0, -254, -241, -191, -200,    0,    0,  -51,    0, -160,
    0,   10, -110,    0, -146,    0,  -51,    0, -220,   10,
   10,   10,  -51,    0,    0,    0,    0,    0,    0, -246,
 -143,    0,    0, -109, -149, -117,    0,    0, -113,    0,
 -118, -245,  -75,    0,  -98,    0,    0,    0,    0,    0,
    0,    0,    0,    0, -110, -224,    0,    0, -105,  -95,
 -110,    0,  -76,  -51,   10,  -52,    0, -109, -231,  -66,
  -71,  -46,  -45,    0,    0,   10,   10,    0,  -51,   -7,
   -7,   -7,   -7,   -7,   -7,   -7,   -7,   10,   10,  -55,
  -39,    0,    0,    0,    0,  -30, -204,  -82,    0,    0,
  -51,    0,  -51,  -51,  -98,  -98,  -26, -118, -245,  -75,
  -75,    0,    0,    0,    0,    0,    0, -110,  -57,    0,
    0,    0,  -25,  -22,    0,    0, -125,    0,    0,    0,
 -216,  -37,  -20,  -68,   -4,    0,    0,    0,    0,  -31,
 -125,    0,    0,    0,    0,    0,    0,    0, -217,  -24,
  -23,  -51,  -51,  -51,    0,  -17,  -14,    0,    0,  -51,
    0,    0,  -12,   -9,    5,    0,    0,    7,    0,  -57,
  -57,    0,   -6,    0,  -57,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  288,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    8,    0,    0,    0,    0,    0,    0, -132,
    0,    0,    0,    0,    0,    0,    0,    0,   55,    0,
    0,    0,   15,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  141,    0,    0,    0,    0, -108,    0,
 -157, -144,  175,    0,   78,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   24,    0,    0,    0,    0,    0,
   16,    0,    0,   35,    0,    0,    0,  163,    0, -236,
    0,    0,    0,    0,    0,    0,    0,    0,   35,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   36,
    0,    0,    0,    0,    0,    0,    0, -173,    0,    0,
 -176,    0,   35,   35,  101,  124,    0,  -70,    6,  187,
  199,    0,    0,    0,    0,    0,    0,   24,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -185,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   23,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, -194,    0,    0,    0,
};
short yygindex[] = {                                      0,
  290,    0, -134,  -35,    0,  -47,  -41, -123,  139,    0,
    0,    0,    0,    0,    0,    0,    0,  -11,    3,    0,
    0,  251,  257,    0,  -27,  -38,    0,    0,    0,    0,
  227,    0,  173,  -92,  -44,  131,  -42,    0,    0,    0,
  212,  219,   66,  156,   86,  -43,    0,    0,    0,    0,
    0,    0,    0,    0,
};
#define YYTABLESIZE 484
short yytable[] = {                                      65,
   34,   88,   26,  129,   38,    1,   97,   87,   93,   39,
    1,    2,    3,    4,   86,    5,    2,    3,    4,   36,
    5,   26,  166,   98,   99,  158,  106,  107,  112,   43,
  113,   89,   63,  106,  107,   40,  166,  130,    6,    7,
    8,    9,   10,   11,   41,   26,   12,   94,   63,   88,
  109,   94,   13,  106,  107,   87,   48,  190,  182,   14,
   15,   16,   57,   45,  179,   41,   16,  127,   57,   57,
   57,   31,   57,  120,  146,  147,  203,  204,  179,   89,
   31,  206,  122,   47,   42,   95,   57,   96,   57,   57,
   57,   96,   65,   26,   55,   57,   57,   57,   57,   57,
   57,   55,  151,   57,   57,   42,   57,   85,   65,  167,
   92,   71,  180,  105,  181,  168,   57,   57,   57,   71,
   31,   71,   71,  167,   73,  186,  180,   71,  181,  168,
  108,  161,   73,   73,   73,   73,  120,    2,    3,    4,
   73,    5,   23,  193,  194,  195,    1,   23,  106,  107,
  109,  198,    2,    3,    4,  162,    5,  163,  157,  111,
   66,  118,  119,  110,    6,    7,    8,    9,   10,   11,
   66,   66,   12,  164,   39,  165,   66,  140,  141,    6,
    7,    8,    9,   10,   11,   14,   15,   16,   49,  123,
   50,  135,  136,   51,  114,  115,  116,  117,   72,   52,
   14,   15,   16,  125,  128,   49,   72,   50,   72,   72,
   51,  185,  131,  132,   72,   53,   52,   54,   55,   56,
   57,  133,  134,  148,  126,   96,  157,   58,   59,  149,
  183,   60,   53,   61,   54,   55,   56,   57,  150,  137,
   62,   63,  155,  159,   58,   59,  160,  184,   60,   49,
   61,   50,  187,  188,   51,  191,  192,   62,   63,  200,
   52,  152,  196,  153,  154,  197,   49,  199,   50,  142,
  143,  144,  145,  201,   74,  205,   53,   52,   54,   55,
   56,   57,   74,   74,   74,   74,  202,    2,   58,   59,
   74,   37,   62,   53,   61,   54,   55,   56,   57,   65,
   42,   62,   63,   65,   60,   58,   59,   10,   37,  189,
  102,   61,   94,   94,   94,   94,  103,  124,   62,   63,
  156,  138,    0,   94,   94,   94,   94,   94,   94,  139,
   94,   94,   94,   94,   94,   85,   85,    0,    0,   94,
    0,    0,    0,    0,    0,    0,   85,   85,   85,   85,
   85,   85,    0,   85,   85,   85,   85,   85,   86,   86,
    0,   94,   85,    0,    0,    0,    0,    0,    0,   86,
   86,   86,   86,   86,   86,    0,   86,   86,   86,   86,
   86,   87,   87,    0,   85,   86,    0,    0,    0,    0,
    0,    0,   87,   87,   87,   87,   87,   87,    0,   87,
   87,   87,   87,   87,    0,    0,    0,   86,   87,   83,
   83,   83,   83,   83,   83,    0,   83,   83,   83,   83,
   83,    0,    0,    0,    0,   83,    0,    0,    0,    0,
   87,   84,   84,   84,   84,   84,   84,    0,   84,   84,
   84,   84,   84,   75,    0,    0,    0,   84,   75,    0,
   75,   75,   75,   75,   75,   76,    0,    0,    0,   75,
   76,    0,   76,   76,   76,   76,   76,   77,    0,    0,
    0,   76,   77,    0,   77,   77,   77,   77,   77,    0,
    0,    0,    0,   77,
};
short yycheck[] = {                                      38,
   12,   43,    0,   96,  275,  257,   50,   43,   47,  280,
  257,  263,  264,  265,   42,  267,  263,  264,  265,  257,
  267,   19,  157,   51,   52,  149,  258,  259,  274,  284,
  276,   43,  269,  258,  259,  257,  171,  269,  290,  291,
  292,  293,  294,  295,  266,   43,  298,  268,  285,   91,
  268,  268,  304,  258,  259,   91,  257,  275,  275,  311,
  312,  313,  257,  305,  157,  266,  313,   95,  263,  264,
  265,  257,  267,   85,  118,  119,  200,  201,  171,   91,
  266,  205,  307,  275,  306,  306,  281,  308,  283,  284,
  285,  308,  269,   91,  268,  290,  291,  292,  293,  294,
  295,  275,  307,  298,  299,  306,  301,  268,  285,  157,
  257,  269,  157,  257,  157,  157,  311,  312,  313,  277,
  306,  279,  280,  171,  269,  164,  171,  285,  171,  171,
  280,  257,  277,  278,  279,  280,  148,  263,  264,  265,
  285,  267,  275,  182,  183,  184,  257,  280,  258,  259,
  268,  190,  263,  264,  265,  281,  267,  283,  284,  278,
  269,  260,  261,  277,  290,  291,  292,  293,  294,  295,
  279,  280,  298,  299,  280,  301,  285,  112,  113,  290,
  291,  292,  293,  294,  295,  311,  312,  313,  257,  285,
  259,  106,  107,  262,  270,  271,  272,  273,  269,  268,
  311,  312,  313,  280,  257,  257,  277,  259,  279,  280,
  262,  280,  279,  285,  285,  284,  268,  286,  287,  288,
  289,  268,  268,  279,   94,  308,  284,  296,  297,  269,
  268,  300,  284,  302,  286,  287,  288,  289,  269,  109,
  309,  310,  269,  269,  296,  297,  269,  268,  300,  257,
  302,  259,  257,  285,  262,  280,  280,  309,  310,  269,
  268,  131,  280,  133,  134,  280,  257,  280,  259,  114,
  115,  116,  117,  269,  269,  282,  284,  268,  286,  287,
  288,  289,  277,  278,  279,  280,  280,    0,  296,  297,
  285,  284,  269,  284,  302,  286,  287,  288,  289,  285,
  285,  309,  310,  269,  269,  296,  297,  285,   19,  171,
   60,  302,  258,  259,  260,  261,   60,   91,  309,  310,
  148,  110,   -1,  269,  270,  271,  272,  273,  274,  111,
  276,  277,  278,  279,  280,  258,  259,   -1,   -1,  285,
   -1,   -1,   -1,   -1,   -1,   -1,  269,  270,  271,  272,
  273,  274,   -1,  276,  277,  278,  279,  280,  258,  259,
   -1,  307,  285,   -1,   -1,   -1,   -1,   -1,   -1,  269,
  270,  271,  272,  273,  274,   -1,  276,  277,  278,  279,
  280,  258,  259,   -1,  307,  285,   -1,   -1,   -1,   -1,
   -1,   -1,  269,  270,  271,  272,  273,  274,   -1,  276,
  277,  278,  279,  280,   -1,   -1,   -1,  307,  285,  269,
  270,  271,  272,  273,  274,   -1,  276,  277,  278,  279,
  280,   -1,   -1,   -1,   -1,  285,   -1,   -1,   -1,   -1,
  307,  269,  270,  271,  272,  273,  274,   -1,  276,  277,
  278,  279,  280,  269,   -1,   -1,   -1,  285,  274,   -1,
  276,  277,  278,  279,  280,  269,   -1,   -1,   -1,  285,
  274,   -1,  276,  277,  278,  279,  280,  269,   -1,   -1,
   -1,  285,  274,   -1,  276,  277,  278,  279,  280,   -1,
   -1,   -1,   -1,  285,
};
#define YYFINAL 17
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 313
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
"DOT","STRING_LITERAL","CHAR_LITERAL","SERIAL_SENSOR","SERIAL_ACTUATOR","BYTE",
};
char *yyrule[] = {
"$accept : program",
"program : statement_list",
"statement_list : statement",
"statement_list : statement statement_list",
"statement : variable_definition_statement",
"statement : function_definition_statement",
"statement : class_definition_statement",
"statement : constant_definition_statement",
"statement : variable_declaration_statement",
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
"type_declarator : any_type IDENTIFIER",
"any_type : array_type",
"any_type : pointer_type",
"any_type : primitive_type",
"any_type : user_type",
"any_type : device_type",
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
"variable_set_statement : class_attribute_identifier EQ expression SEMICOLON",
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
"primitive_type : BYTE",
"device_type : LIGHT_ACTUATOR",
"device_type : SERVO_ACTUATOR",
"device_type : SOUND_SENSOR",
"device_type : LIGHT_SENSOR",
"device_type : DISTANCE_SENSOR",
"device_type : TEMPERATURE_SENSOR",
"device_type : SERIAL_SENSOR",
"device_type : SERIAL_ACTUATOR",
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
#line 1230 "scarl_tokens.y"

void yyerror(char *s) {
	fprintf(stderr, "%s at line %i near \'%s\'\n", s, line_number, last_token_text);
}
#line 500 "y.tab.c"
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
#line 65 "scarl_tokens.y"
{
	printf("Match program\n");
	/*pass the completed AST back to the main program for further processing*/
	program_ast = yyvsp[0];
	yyval = yyvsp[0];
}
break;
case 2:
#line 72 "scarl_tokens.y"
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
#line 81 "scarl_tokens.y"
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
#line 90 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement\n");
	yyval = yyvsp[0];
}
break;
case 5:
#line 95 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement\n");
	yyval = yyvsp[0];
}
break;
case 6:
#line 100 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement\n");
	yyval = yyvsp[0];
}
break;
case 7:
#line 105 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement\n");
	yyval = yyvsp[0];
}
break;
case 8:
#line 110 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement\n");
	/* this is its own node if it is a statement and not a class field */
	yyval = yyvsp[0];
}
break;
case 9:
#line 116 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match block_statement\n");
	yyval = yyvsp[-1];
}
break;
case 10:
#line 121 "scarl_tokens.y"
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
#line 130 "scarl_tokens.y"
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
#line 139 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
	yyval = yyvsp[0];
}
break;
case 13:
#line 144 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
	yyval = yyvsp[0];
}
break;
case 14:
#line 149 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
	yyval = yyvsp[0];
}
break;
case 15:
#line 154 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
	yyval = yyvsp[0];
}
break;
case 16:
#line 159 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
	yyval = yyvsp[0];
}
break;
case 17:
#line 164 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
	yyval = yyvsp[0];
}
break;
case 18:
#line 169 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
	yyval = yyvsp[0];
}
break;
case 19:
#line 174 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
	yyval = yyvsp[0];
}
break;
case 20:
#line 179 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
	yyval = yyvsp[0];
}
break;
case 21:
#line 184 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
	yyval = yyvsp[0];
}
break;
case 22:
#line 189 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match statement_block_level\n");
	yyval = yyvsp[0];
}
break;
case 23:
#line 194 "scarl_tokens.y"
{
    /* for any variable declared with a type*/
	
	if (debugging_grammar) {
		print_string_stack();
	}
	char *declarator_identifier = string_stack_pop();
	struct scarl_ast_node *declarator_identifier_node = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, declarator_identifier);
	struct scarl_ast_node *type_node = yyvsp[-1];
	
	/* bug with grammar - user type is not reduced until the second identifier is recognized*/
	/* this makes the identifier and user type be in the wrong place*/
	/* to fix this for now, if the any_type is a user type, then swap the str_values between the identifier and type nodes*/
	if (type_node->node_type == NON_TERMINAL_IDENTIFIER_VALUE) {
		/* the string values were likely swapped*/
		char *temp = declarator_identifier_node->str_value;
		declarator_identifier_node->str_value = type_node->str_value;
		type_node->str_value = temp;
	}
	
	if (debugging_grammar) printf("Match type_declarator (type %s, identifier %s)\n", get_ast_node_type_string(type_node->node_type), declarator_identifier);
	struct scarl_ast_node *type_declarator_node = create_typed_ast_node(NON_TERMINAL_TYPE_DECLARATOR, NON_TERMINAL_TYPE_DECLARATOR);
	add_child_node(type_declarator_node, type_node);
	add_child_node(type_declarator_node, declarator_identifier_node);
	yyval = type_declarator_node;
}
break;
case 24:
#line 221 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match any_type\n");
	yyval = yyvsp[0];
}
break;
case 25:
#line 226 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match any_type\n");
	yyval = yyvsp[0];
}
break;
case 26:
#line 231 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match any_type\n");
	yyval = yyvsp[0];
}
break;
case 27:
#line 236 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match any_type\n");
	yyval = yyvsp[0];
}
break;
case 28:
#line 242 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match any_type\n");
	yyval = yyvsp[0];
}
break;
case 29:
#line 247 "scarl_tokens.y"
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
#line 257 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match pointer_type\n");
	struct scarl_ast_node *pointer_node = create_typed_ast_node(NON_TERMINAL_POINTER_TYPE, NON_TERMINAL_POINTER_TYPE);
	struct scarl_ast_node *type_node = yyvsp[-1];
	add_child_node(pointer_node, type_node);
	yyval = pointer_node;
}
break;
case 31:
#line 265 "scarl_tokens.y"
{
	if (debugging_grammar) {
		print_string_stack();
	}
	char *user_type_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match user_type (%s)\n", user_type_identifier);
	yyval = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, user_type_identifier);
}
break;
case 32:
#line 274 "scarl_tokens.y"
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
#line 288 "scarl_tokens.y"
{
	/* declares a variable without giving it a value - cannot*/
	/* refer to this variable without assigning it, otherwise */
	/* the compiler will give an error*/
	if (debugging_grammar) printf("Match variable_declaration_statement\n");
	struct scarl_ast_node *variable_declaration_node = create_typed_ast_node(NON_TERMINAL_VARIABLE_DECLARATION_STATEMENT, NON_TERMINAL_VARIABLE_DECLARATION_STATEMENT);
	add_child_node(variable_declaration_node, yyvsp[-1]);
	yyval = variable_declaration_node;
}
break;
case 34:
#line 298 "scarl_tokens.y"
{
	/* for deallocating a pointer variable*/
	/* be sure this only occurs on pointer types */
	if (debugging_grammar) {
		print_string_stack();
	}
	char *deleting_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match delete_statement (%s)\n", deleting_identifier);
	struct scarl_ast_node *delete_statement_node = create_typed_ast_node(NON_TERMINAL_DELETE_STATEMENT, NON_TERMINAL_DELETE_STATEMENT);
	struct scarl_ast_node *deleting_identifier_node = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, deleting_identifier);
	add_child_node(delete_statement_node, deleting_identifier_node);
	yyval = delete_statement_node;
}
break;
case 35:
#line 312 "scarl_tokens.y"
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
#line 326 "scarl_tokens.y"
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
#line 340 "scarl_tokens.y"
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
#line 351 "scarl_tokens.y"
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
#line 371 "scarl_tokens.y"
{
    /* ensure that the identifier is not*/
    /* being used for something else in*/
    /* this (global) scope*/
	if (debugging_grammar) {
		print_string_stack();
	}
	char *class_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match class_name (%s)\n", class_identifier);
	yyval = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, class_identifier);
}
break;
case 40:
#line 383 "scarl_tokens.y"
{
    /* we need to ensure that the*/
    /* identifier is actually a class*/
    /* name defined in the symbol table*/
	if (debugging_grammar) {
		print_string_stack();
	}
	char *extending_class_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match class_extending (%s)\n", extending_class_identifier);
	yyval = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, extending_class_identifier);
}
break;
case 41:
#line 395 "scarl_tokens.y"
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
#line 404 "scarl_tokens.y"
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
#line 413 "scarl_tokens.y"
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
#line 422 "scarl_tokens.y"
{
    /* a special location for functions*/
    /* this function definition is actually*/
    /* going to be a method for this class*/
	if (debugging_grammar) printf("Match class_attribute\n");
	yyval = yyvsp[0];
}
break;
case 45:
#line 430 "scarl_tokens.y"
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
#line 440 "scarl_tokens.y"
{
    /* functions will only be able to return*/
    /* primitives for this version. Hopefully*/
    /* extend it to pointer types later on. Can*/
    /* always pass pointer types as parameters*/
    /* to functions*/
	if (debugging_grammar) {
		print_string_stack();
	}
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
#line 463 "scarl_tokens.y"
{
    /* sets the value for the identifier to the evaluated*/
    /* value of the expression. Need to ensure that the type*/
    /* of the identifier matches or can be converted to the type*/
    /* of the expression. Also ensure that the identifier is in scope*/
	if (debugging_grammar) {
		print_string_stack();
	}
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
#line 481 "scarl_tokens.y"
{
	struct scarl_ast_node *class_attribute_ident_node = (struct scarl_ast_node *)yyvsp[-3];
	if (debugging_grammar) printf("Match variable_set_statement (class attribute form, starts with %s)\n", class_attribute_ident_node->first_child->str_value);
	struct scarl_ast_node *variable_set_statement_node = create_typed_ast_node(NON_TERMINAL_VARIABLE_SET_STATEMENT, NON_TERMINAL_VARIABLE_SET_STATEMENT);
	struct scarl_ast_node *expression_node = yyvsp[-1];
	add_child_node(variable_set_statement_node, class_attribute_ident_node);
	add_child_node(variable_set_statement_node, expression_node);
	yyval = variable_set_statement_node;
}
break;
case 49:
#line 491 "scarl_tokens.y"
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
case 50:
#line 507 "scarl_tokens.y"
{
    /* empty return statement.*/
    /* can only occur in void functions*/
	if (debugging_grammar) printf("Match return_statement\n");
	yyval = create_typed_ast_node(NON_TERMINAL_RETURN_STATEMENT, NON_TERMINAL_RETURN_STATEMENT);
}
break;
case 51:
#line 514 "scarl_tokens.y"
{
    /* invoke the function with the name*/
    /* of identifier. The types of the parameters*/
    /* must match that of a defined invocation*/

    /* this may also be a call to a constructor*/
    /* in which case the identifier must also*/
    /* be checked against a class name and*/
    /* the parameter list against the class's*/
    /* constructors*/
	if (debugging_grammar) {
		print_string_stack();
	}
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
case 52:
#line 537 "scarl_tokens.y"
{
    /* allows for there to be statements that*/
    /* only call functions*/
	if (debugging_grammar) printf("Match function_invocation_statement\n");
	yyval = yyvsp[-1];
}
break;
case 53:
#line 544 "scarl_tokens.y"
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
case 54:
#line 560 "scarl_tokens.y"
{
    /* allows for a statement to be only*/
    /* a method invocation*/
	if (debugging_grammar) printf("Match method_invocation_statement\n");
	yyval = yyvsp[-1];
}
break;
case 55:
#line 568 "scarl_tokens.y"
{
    /* the last case in the chain of*/
    /* identifiers dot identifiers for a method*/
    /* identifier*/
    /* this could also just lead to a field of*/
    /* an object instance, not a method*/
	if (debugging_grammar) {
		printf("Popping two identifiers\n");
		print_string_stack();
	}
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
case 56:
#line 590 "scarl_tokens.y"
{
    /* enables the dot operator to*/
    /* act as far as it needs to to*/
    /* get to where a field or method is*/
    /* this could also just lead to a field of*/
    /* an object instance, not a method*/
	if (debugging_grammar) {
		print_string_stack();
	}
	char *identifier = string_stack_pop();
	if (debugging_grammar) printf("Match class_attribute_identifier (%s.<more stuff>)\n", identifier);
	/* we want the children to appear in the order as  they do in the code for the AST*/
	struct scarl_ast_node *next_identifier = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, yyvsp[-2]);
	struct scarl_ast_node *class_attribute_identifier_node = yyvsp[0];
	push_child_node_front(class_attribute_identifier_node, next_identifier);
	yyval = class_attribute_identifier_node;
}
break;
case 57:
#line 608 "scarl_tokens.y"
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
case 58:
#line 619 "scarl_tokens.y"
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
case 59:
#line 632 "scarl_tokens.y"
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
case 60:
#line 645 "scarl_tokens.y"
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
case 61:
#line 655 "scarl_tokens.y"
{
    /* continue the list of formal parameters*/
	if (debugging_grammar) printf("Match formal_parameter_list\n");
	struct scarl_ast_node *type_declarator_node = yyvsp[-2];
	struct scarl_ast_node *formal_parameter_list_node = yyvsp[0];
	push_child_node_front(formal_parameter_list_node, type_declarator_node);
	yyval = formal_parameter_list_node;
}
break;
case 62:
#line 664 "scarl_tokens.y"
{
    /* allow for empty parameter lists*/
	if (debugging_grammar) printf("Match formal_parameter_list\n");
	yyval = create_typed_ast_node(NON_TERMINAL_FORMAL_PARAMETER_LIST, NON_TERMINAL_FORMAL_PARAMETER_LIST);
}
break;
case 63:
#line 670 "scarl_tokens.y"
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
case 64:
#line 680 "scarl_tokens.y"
{
    /* continue the list of argument*/
	if (debugging_grammar) printf("Match parameter_list (expression list)\n");
	struct scarl_ast_node *expression_node = yyvsp[-2];
	struct scarl_ast_node *parameter_list_node = yyvsp[0];
	push_child_node_front(parameter_list_node, expression_node);
	yyval = parameter_list_node;
}
break;
case 65:
#line 689 "scarl_tokens.y"
{
    /* allow for empty argument function calls*/
	if (debugging_grammar) printf("Match parameter_list (empty list)\n");
	/* create an empty parameter list */
	yyval = create_typed_ast_node(NON_TERMINAL_PARAMETER_LIST, NON_TERMINAL_PARAMETER_LIST);
}
break;
case 66:
#line 696 "scarl_tokens.y"
{
    /* base expression*/
	if (debugging_grammar) printf("Match expression\n");
	yyval = yyvsp[0];
}
break;
case 67:
#line 702 "scarl_tokens.y"
{
    /* allocates are a special kind of*/
    /* expression that can only occur*/
    /* by themselves*/
	if (debugging_grammar) printf("Match expression\n");
	yyval = yyvsp[0];
}
break;
case 68:
#line 710 "scarl_tokens.y"
{
    /* the allocation invocation is*/
    /* a special kind of function invocation*/
    /* that needs its own production rule to*/
    /* avoid confusion*/
	if (debugging_grammar) printf("Match allocation_expression\n");
	yyval = yyvsp[0]; /* obvious that this is an allocation, unless NON_TERMINAL_POINTER_VALUE ends up showin elsewhere*/
}
break;
case 69:
#line 730 "scarl_tokens.y"
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
case 70:
#line 741 "scarl_tokens.y"
{
    /* class type allocation*/
    /* identifier must be a class in the*/
    /* symbol table and the parameter list*/
    /* must match one of the constructors*/
	if (debugging_grammar) {
		print_string_stack();
	}
	/*char *allocating_type_identifier = string_stack_pop(); // the user type already has a value*/
	struct scarl_ast_node *allocating_type_identifier = (struct scarl_ast_node *)yyvsp[-3];
	if (debugging_grammar) printf("Match allocation_invocation (allocating user type %s)\n", allocating_type_identifier->str_value);
	struct scarl_ast_node *allocate_node = create_typed_ast_node(NON_TERMINAL_POINTER_VALUE, NON_TERMINAL_POINTER_VALUE);
	struct scarl_ast_node *parameter_list_node = yyvsp[-1];
	add_child_node(allocate_node, allocating_type_identifier); /* type defined as a pointer of this type */
	add_child_node(allocate_node, parameter_list_node); /* constructed with these parameters*/
	yyval = allocate_node;
}
break;
case 71:
#line 759 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match logical_expression\n");
	yyval = yyvsp[0];
}
break;
case 72:
#line 764 "scarl_tokens.y"
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
case 73:
#line 778 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match logical_and_expression\n");
	yyval = yyvsp[0];
}
break;
case 74:
#line 783 "scarl_tokens.y"
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
case 75:
#line 797 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match equality_expression\n");
	yyval = yyvsp[0];
}
break;
case 76:
#line 802 "scarl_tokens.y"
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
case 77:
#line 816 "scarl_tokens.y"
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
case 78:
#line 830 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match relational_expression\n");
	yyval = yyvsp[0];
}
break;
case 79:
#line 835 "scarl_tokens.y"
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
case 80:
#line 849 "scarl_tokens.y"
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
case 81:
#line 863 "scarl_tokens.y"
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
case 82:
#line 877 "scarl_tokens.y"
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
case 83:
#line 891 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match bool_expression\n");
	yyval = yyvsp[0];
}
break;
case 84:
#line 896 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match bool_expression\n");
	struct scarl_ast_node *operand = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, BANG);
	struct scarl_ast_node *expression = yyvsp[0];
	add_child_node(operand, expression);
	yyval = operand;
}
break;
case 85:
#line 904 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match arithmetic_expression\n");
	yyval = yyvsp[0];
}
break;
case 86:
#line 909 "scarl_tokens.y"
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
case 87:
#line 923 "scarl_tokens.y"
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
case 88:
#line 937 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match arithmetic_factor\n");
	yyval = yyvsp[0];
}
break;
case 89:
#line 942 "scarl_tokens.y"
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
case 90:
#line 956 "scarl_tokens.y"
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
case 91:
#line 970 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match arithmetic_unary\n");
	yyval = yyvsp[0];
}
break;
case 92:
#line 975 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match arithmetic_unary\n");
	struct scarl_ast_node *unary_node = create_typed_ast_node(NON_TERMINAL_OPERAND_VALUE, MINUS);
	struct scarl_ast_node *arithmetic_unary_node = yyvsp[0];
	add_child_node(unary_node, arithmetic_unary_node);
	yyval = unary_node;
}
break;
case 93:
#line 983 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match arithmetic_unary\n");
	yyval = yyvsp[-1];
}
break;
case 94:
#line 988 "scarl_tokens.y"
{
	if (debugging_grammar) {
		print_string_stack();
	}
	char *identifier = string_stack_pop();
	if (debugging_grammar) printf("Match unit (%s)\n", identifier);
	yyval = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, identifier);
}
break;
case 95:
#line 997 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match unit\n");
	yyval = yyvsp[0];
}
break;
case 96:
#line 1002 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match unit\n");
	yyval = yyvsp[0];
}
break;
case 97:
#line 1007 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match unit\n");
	yyval = yyvsp[0];
}
break;
case 98:
#line 1012 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match unit\n");
	yyval = yyvsp[0];
}
break;
case 99:
#line 1017 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match unit\n");
	yyval = yyvsp[0];
}
break;
case 100:
#line 1022 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match unit\n");
	yyval = yyvsp[0];
}
break;
case 101:
#line 1027 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match unit\n");
	yyval = yyvsp[0];
}
break;
case 102:
#line 1032 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match unit\n");
	yyval = yyvsp[0];
}
break;
case 103:
#line 1037 "scarl_tokens.y"
{
    /* ensure that the used identifier is*/
    /* an array type*/
	if (debugging_grammar) {
		print_string_stack();
	}
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
case 104:
#line 1053 "scarl_tokens.y"
{
    /* ensure that the identifier*/
    /* is a pointer type that is*/
    /* in this scope*/
	if (debugging_grammar) {
		print_string_stack();
	}
	char *dereferenced_variable_identifier = string_stack_pop();
	if (debugging_grammar) printf("Match dereferenced_pointer\n", dereferenced_variable_identifier);
	struct scarl_ast_node *deref_node = create_typed_ast_node(NON_TERMINAL_DEREFERENCED_VALUE, NON_TERMINAL_DEREFERENCED_VALUE); 
	struct scarl_ast_node *dereferenced_variable_node = create_str_value_ast_node(NON_TERMINAL_IDENTIFIER_VALUE, dereferenced_variable_identifier); 
	add_child_node(deref_node, dereferenced_variable_node);
	yyval = deref_node;
}
break;
case 105:
#line 1068 "scarl_tokens.y"
{
	/* string literals are syntactic*/
	/* sugar for character arrays*/
	if (debugging_grammar) {
		print_string_stack();
	}
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
case 106:
#line 1087 "scarl_tokens.y"
{
	/* array initializer for arbitrarily typed*/
	/* initialzers*/
	if (debugging_grammar) printf("Match array_value\n");
	yyval = yyvsp[0];
}
break;
case 107:
#line 1094 "scarl_tokens.y"
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
case 108:
#line 1110 "scarl_tokens.y"
{
	int decimal_value = int_stack_pop();
	if (debugging_grammar) printf("Match integer_value (%i)\n", decimal_value);
	yyval = create_int_value_ast_node(NON_TERMINAL_INTEGER_VALUE, decimal_value);
}
break;
case 109:
#line 1116 "scarl_tokens.y"
{
	int octal_value = int_stack_pop();
	if (debugging_grammar) printf("Match integer_value (%i)\n", octal_value);
	yyval = create_int_value_ast_node(NON_TERMINAL_INTEGER_VALUE, octal_value);
}
break;
case 110:
#line 1122 "scarl_tokens.y"
{
	int hex_value = int_stack_pop();
	if (debugging_grammar) printf("Match integer_value (%i)\n", hex_value);
	yyval = create_int_value_ast_node(NON_TERMINAL_INTEGER_VALUE, hex_value);
}
break;
case 111:
#line 1128 "scarl_tokens.y"
{
	int binary_value = int_stack_pop();
	if (debugging_grammar) printf("Match integer_value (%i)\n", binary_value);
	yyval = create_int_value_ast_node(NON_TERMINAL_INTEGER_VALUE, binary_value);
}
break;
case 112:
#line 1134 "scarl_tokens.y"
{
    /* ensure that the identifier is*/
    /* only a single character long.*/
    /* this identifier is going to be the*/
    /* value of the character literal, and*/
    /* not actually be an identifier in the*/
    /* language*/
	if (debugging_grammar) {
		print_string_stack();
	}
	char *character_literal = string_stack_pop();
	if (debugging_grammar) printf("Match char_value (%s)\n", character_literal);
	/* the int value of this node is the character, just cast it back to retrieve the character*/
    struct scarl_ast_node *char_value_node = create_int_value_ast_node(NON_TERMINAL_CHAR_VALUE, character_literal[1]);
	free(character_literal);
	yyval = char_value_node;
	/* NON_TERMINAL_CHAR_VALUE*/
}
break;
case 113:
#line 1153 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match bool_value\n");
    yyval = create_int_value_ast_node(NON_TERMINAL_BOOL_VALUE, TRUE);
}
break;
case 114:
#line 1158 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match bool_value\n");
    yyval = create_int_value_ast_node(NON_TERMINAL_BOOL_VALUE, FALSE);
}
break;
case 115:
#line 1163 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match primitive_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_PRIMITIVE_TYPE, VOID);
}
break;
case 116:
#line 1168 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match primitive_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_PRIMITIVE_TYPE, INT);
}
break;
case 117:
#line 1173 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match primitive_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_PRIMITIVE_TYPE, CHAR);
}
break;
case 118:
#line 1178 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match primitive_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_PRIMITIVE_TYPE, VOID);
}
break;
case 119:
#line 1183 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match primitive_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_PRIMITIVE_TYPE, BYTE);
}
break;
case 120:
#line 1188 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match device_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, LIGHT_ACTUATOR);
}
break;
case 121:
#line 1193 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match device_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, SERVO_ACTUATOR);
}
break;
case 122:
#line 1198 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match device_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, SOUND_SENSOR);
}
break;
case 123:
#line 1203 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match device_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, LIGHT_SENSOR);
}
break;
case 124:
#line 1208 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match device_type\n");
    yyval = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, DISTANCE_SENSOR);
}
break;
case 125:
#line 1213 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match device_type\n");
	yyval = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, TEMPERATURE_SENSOR);
}
break;
case 126:
#line 1218 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match device_type\n");
	yyval = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, SERIAL_SENSOR);
}
break;
case 127:
#line 1223 "scarl_tokens.y"
{
	if (debugging_grammar) printf("Match device_type\n");
	yyval = create_typed_ast_node(NON_TERMINAL_DEVICE_TYPE, SERIAL_ACTUATOR);
}
break;
#line 2043 "y.tab.c"
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
