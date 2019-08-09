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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "scarltypes.h"

int yylex(void);
void yyerror(char *);
/*int yydebug = 1;*/

/*for counting line numbers. Lines are incremented in scarl.l*/
extern unsigned lineNumber;
/*handled in scarl.l. for hinting at where error occured*/
extern char *lastTokenText;

/*for performing actions on the code file*/
/*for the compiling unit, this is intermediatary code*/
extern FILE *codeFile;


using namespace std;

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
#define DBL_QUOTE 309
#define SGL_QUOTE 310
#define YYERRCODE 256
#define YYTABLESIZE 381
#define YYFINAL 14
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 310
#ifndef YYSTYPE
typedef int YYSTYPE;
#endif
extern short yylhs[];
extern short yylen[];
extern short yydefred[];
extern short yydgoto[];
extern short yysindex[];
extern short yyrindex[];
extern short yygindex[];
extern short yytable[];
extern short yycheck[];
#if YYDEBUG
extern char *yyname[];
extern char *yyrule[];
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

void yyerror(char *s) {
	fprintf(stderr, "%s at line %i near \'%s\'\n", s, lineNumber, lastTokenText);
}



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
{
    /* nothing to do?*/
}
break;
case 2:
{
    /* finish off the statement list*/

}
break;
case 3:
{
    /* add the statement to the statement list*/

}
break;
case 4:
{

}
break;
case 5:
{

}
break;
case 6:
{

}
break;
case 7:
{

}
break;
case 8:
{

}
break;
case 9:
{

}
break;
case 10:
{
    /* finish the block level statement list*/

}
break;
case 11:
{
    /* add a block level statement to the statement list*/

}
break;
case 12:
{

}
break;
case 13:
{

}
break;
case 14:
{

}
break;
case 15:
{

}
break;
case 16:
{

}
break;
case 17:
{

}
break;
case 18:
{

}
break;
case 19:
{

}
break;
case 20:
{

}
break;
case 21:
{
    /* primitive type with augmentations*/

}
break;
case 22:
{
    /* class or user defined type with augmentations*/
    /* check to make sure that this is actually a type!*/

}
break;
case 23:
{
    /* primitive type with no augmentations*/

}
break;
case 24:
{
    /* class or user defined type with no augmentations*/
    /* check to ensure that this is actually a type!*/

}
break;
case 25:
{
    /* finish off the augmentation list*/

}
break;
case 26:
{
    /* add to the end of the type augmentation list*/

}
break;
case 27:
{
    /* pointer type augmentation, modify*/
    /* whatever is to the left of this token*/

}
break;
case 28:
{
    /* array type augmentation, modify*/
    /* whatever is to the left of this token*/

}
break;
case 29:
{
    /* ensure that the arithmetic_expression is*/
    /* a constant expression (made of only literals*/
    /* and constant variables)*/

}
break;
case 30:
{
    /* for those primitive types. We need to*/
    /* ensure that the used identifier has*/
    /* not yet been declared in this scope*/

}
break;
case 31:
{
    /* for those default types. We need to check*/
    /* that the first identifier is a valid type*/
    /* and that the second identifier is not*/
    /* declared in this scope*/

}
break;
case 32:
{
    /* we must ensure that the evaluated type*/
    /* on the right hand side of the = sign is*/
    /* the same type or can be converted to the*/
    /* type on the left hand side*/

}
break;
case 33:
{
    /* functions like the variable_definition_statement*/
    /* except it can only be in global scope and*/
    /* the value will be evaluated at compile time*/
    /* (array lengths can be defined as literals or constant values)*/

}
break;
case 34:
{
    /* add this declared class into the symbol*/
    /* table for global scope (classes can only be*/
    /* declared in global scope) and give it the*/
    /* type attributes listed in the class body*/

}
break;
case 35:
{
    /* this class declarator is a "normal"*/
    /* class. It is not derived from another*/
    /* class*/

}
break;
case 36:
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


}
break;
case 37:
{
    /* ensure that the identifier is not*/
    /* being used for something else in*/
    /* this (global) scope*/

}
break;
case 38:
{
    /* we need to ensure that the*/
    /* identifier is actually a class*/
    /* name defined in the symbol table*/

}
break;
case 39:
{
    /* a list of class attributes*/
    /* processing takes place in the*/
    /* class_definition_statement*/
    /* production rule*/

}
break;
case 40:
{
    /* finish off the class attribute list*/

}
break;
case 41:
{
    /* add another attribute to the list*/

}
break;
case 42:
{
    /* a special location for functions*/
    /* this function definition is actually*/
    /* going to be a method for this class*/

}
break;
case 43:
{
    /* a special kind of declarator*/
    /* that does not require an initial*/
    /* value. This can only take place*/
    /* in a class body. This will be*/
    /* a field for instances of this class*/

}
break;
case 44:
{
    /* no initial value required. This will*/
    /* be a field for the defining class*/

}
break;
case 45:
{
    /* functions will only be able to return*/
    /* primitives for this version. Hopefully*/
    /* extend it to pointer types later on. Can*/
    /* always pass pointer types as parameters*/
    /* to functions*/

}
break;
case 46:
{
    /* sets the value for the identifier to the evaluated*/
    /* value of the expression. Need to ensure that the type*/
    /* of the identifier matches or can be converted to the type*/
    /* of the expression. Also ensure that the identifier is in scope*/

}
break;
case 47:
{
    /* can only appear in functions.*/
    /* acts like a normal C return statement*/
    /* the expression type for all return*/
    /* statements in a function must match*/
    /* the return type for that function*/

    /* additionally, void functions cannot have*/
    /* return statements with expressions*/

}
break;
case 48:
{
    /* empty return statement.*/
    /* can only occur in void functions*/

}
break;
case 49:
{
    /* invoke the function with the name*/
    /* of identifier. The types of the parameters*/
    /* must match that of a defined invocation*/

    /* this may also be a call to a constructor*/
    /* in which case the identifier must also*/
    /* be checked against a class name and*/
    /* the parameter list against the class's*/
    /* constructors*/

}
break;
case 50:
{
    /* allows for there to be statements that*/
    /* only call functions*/

}
break;
case 51:
{
    /* requires more heavy lifting than*/
    /* a function invocation because we need*/
    /* to resolve the scope to where the*/
    /* class_attribute_identifier leads to.*/
    /* A method invocation is calling a*/
    /* method of an object instance*/

}
break;
case 52:
{
    /* allows for a statement to be only*/
    /* a method invocation*/

}
break;
case 53:
{
    /* the last case in the chain of*/
    /* identifiers dot identifiers for a method*/
    /* identifier*/

    /* this could also just lead to a field of*/
    /* an object instance, not a method*/

}
break;
case 54:
{
    /* enables the dot operator to*/
    /* act as far as it needs to to*/
    /* get to where a field or method is*/

    /* this could also just lead to a field of*/
    /* an object instance, not a method*/

}
break;
case 55:
{
    /* if without else*/

}
break;
case 56:
{
    /* if with else*/

}
break;
case 57:
{
    /* regular while statement.*/

}
break;
case 58:
{
    /* finish the rest of the formal parameter*/
    /* list or this function has 1 parameter*/

}
break;
case 59:
{
    /* continue the list of formal parameters*/

}
break;
case 60:
{
    /* allow for empty parameter lists*/
}
break;
case 61:
{
    /* finish the rest of the  parameter*/
    /* list or this function has 1 argument*/

}
break;
case 62:
{
    /* continue the list of argument*/

}
break;
case 63:
{
    /* allow for empty argument function calls*/

}
break;
case 64:
{
    /* base expression*/

}
break;
case 65:
{
    /* allocates are a special kind of*/
    /* expression that can only occur*/
    /* by themselves*/

}
break;
case 66:
{
    /* the allocation invocation is*/
    /* a special kind of function invocation*/
    /* that needs its own production rule to*/
    /* avoid confusion*/

}
break;
case 67:
{
    /* primitive allocation*/

}
break;
case 68:
{
    /* class type allocation*/
    /* identifier must be a class in the*/
    /* symbol table and the parameter list*/
    /* must match one of the constructors*/

}
break;
case 69:
{

}
break;
case 70:
{
	/*     logical_expression && logical_and_expression*/
	/*     logical_expression should be on the LEFT*/
	/*     logical_and_expression should be on the RIGHT*/
	/*     OR should be the parent node*/

}
break;
case 71:
{

}
break;
case 72:
{
	/*     logical_and_expression && equality_expression*/
	/*     logical_and_expression should be on the LEFT*/
	/*     equality_expression should be on the RIGHT*/
	/*     AND should be the parent node*/


}
break;
case 73:
{

}
break;
case 74:
{
	/*     equality_expression == relational_expression*/
	/*     equality_expression should be on the LEFT*/
	/*     relational_expression should be on the RIGHT*/
	/*     NOT_EQ should be the parent node*/

}
break;
case 75:
{
	/*     equality_expression != relational_expression*/
	/*     equality_expression should be on the LEFT*/
	/*     relational_expression should be on the RIGHT*/
	/*     NOT_EQ should be the parent node*/

}
break;
case 76:
{

}
break;
case 77:
{
	/*     relational_expression > bool_expression*/
	/*     relational_expression should be on the LEFT*/
	/*     bool_expression should be on the RIGHT*/
	/*     GTR should be the parent node*/

}
break;
case 78:
{
	/*     relational_expression < bool_expression*/
	/*     relational_expression should be on the LEFT*/
	/*     bool_expression should be on the RIGHT*/
	/*     LESS should be the parent node*/

}
break;
case 79:
{
	/*     relational_expression >= bool_expression*/
	/*     relational_expression should be on the LEFT*/
	/*     bool_expression should be on the RIGHT*/
	/*     GTR_EQ should be the parent node*/

}
break;
case 80:
{
	/*     relational_expression <= bool_expression*/
	/*     relational_expression should be on the LEFT*/
	/*     bool_expression should be on the RIGHT*/
	/*     LESS_EQ should be the parent node*/

}
break;
case 81:
{

}
break;
case 82:
{

}
break;
case 83:
{

}
break;
case 84:
{
	/*     arithmetic_expression - arithmetic_factor*/
	/*     arithmetic_expression should be on the LEFT*/
	/*     arithmetic_factor should be on the RIGHT*/
	/*     MINUS should be the parent node*/

}
break;
case 85:
{
	/*     arithmetic_expression - arithmetic_factor*/
	/*     arithmetic_expression should be on the LEFT*/
	/*     arithmetic_factor should be on the RIGHT*/
	/*     MINUS should be the parent node*/

}
break;
case 86:
{

}
break;
case 87:
{
	/*     arithmetic_factor * arithmetic_unary*/
	/*     arithmetic_factor should be on the LEFT*/
	/*     arithmetic_unary should be on the RIGHT*/
	/*     STAR should be the parent node*/

}
break;
case 88:
{
	/*     arithmetic_factor / arithmetic_unary*/
	/*     arithmetic_factor should be on the LEFT*/
	/*     arithmetic_unary should be on the RIGHT*/
	/*     SLASH should be the parent node*/

}
break;
case 89:
{

}
break;
case 90:
{

}
break;
case 91:
{

}
break;
case 92:
{

}
break;
case 93:
{

}
break;
case 94:
{

}
break;
case 95:
{

}
break;
case 96:
{

}
break;
case 97:
{

}
break;
case 98:
{

}
break;
case 99:
{

}
break;
case 100:
{
    /* ensure that the used identifier is*/
    /* an array type*/

}
break;
case 101:
{
    /* ensure that the identifier*/
    /* is a pointer type that is*/
    /* in this scope*/
	
}
break;
case 102:
{
    yyval = new SCARL_AST_Node(NON_TERMINAL_INTEGER_VALUE, yyvsp[0]);
}
break;
case 103:
{
    yyval = new SCARL_AST_Node(NON_TERMINAL_INTEGER_VALUE, yyvsp[0]);
}
break;
case 104:
{
    yyval = new SCARL_AST_Node(NON_TERMINAL_INTEGER_VALUE, yyvsp[0]);
}
break;
case 105:
{
    yyval = new SCARL_AST_Node(NON_TERMINAL_INTEGER_VALUE, yyvsp[0]);
}
break;
case 106:
{
    /* ensure that the identifier is*/
    /* only a single character long.*/
    /* this identifier is going to be the*/
    /* value of the character literal, and*/
    /* not actually be an identifier in the*/
    /* language*/
    string charValue = string(yyvsp[-1]);
    if (charValue.length() == 1) {
        yyval = new SCARL_AST_Node(NON_TERMINAL_CHAR_VALUE, charValue);
    }
    else {
        /*error*/
        yyval = nullptr;
    }
}
break;
case 107:
{
    yyval = new SCARL_AST_Node(NON_TERMINAL_BOOL_VALUE, TRUE);
}
break;
case 108:
{
    yyval = new SCARL_AST_Node(NON_TERMINAL_BOOL_VALUE, FALSE);
}
break;
case 109:
{
    yyval = new SCARL_AST_Node(NON_TERMINAL_PRIMITIVE_TYPE, VOID);
}
break;
case 110:
{
    yyval = new SCARL_AST_Node(NON_TERMINAL_PRIMITIVE_TYPE, INT);
}
break;
case 111:
{
    yyval = new SCARL_AST_Node(NON_TERMINAL_PRIMITIVE_TYPE, CHAR);
}
break;
case 112:
{
    yyval = new SCARL_AST_Node(NON_TERMINAL_PRIMITIVE_TYPE, VOID);
}
break;
case 113:
{
    yyval = new SCARL_AST_Node(NON_TERMINAL_DEVICE_TYPE, LIGHT_ACTUATOR);
}
break;
case 114:
{
    yyval = new SCARL_AST_Node(NON_TERMINAL_DEVICE_TYPE, SERVO_ACTUATOR);
}
break;
case 115:
{
    yyval = new SCARL_AST_Node(NON_TERMINAL_DEVICE_TYPE, SOUND_SENSOR);
}
break;
case 116:
{
    yyval = new SCARL_AST_Node(NON_TERMINAL_DEVICE_TYPE, LIGHT_SENSOR);
}
break;
case 117:
{
    SCARL_AST_Node *node = new SCARL_AST_Node(NON_TERMINAL_DEVICE_TYPE, DISTANCE_SENSOR);
	yyval = node;
}
break;
case 118:
{
	SCARL_AST_Node *node = new SCARL_AST_Node(NON_TERMINAL_DEVICE_TYPE, TEMPERATURE_SENSOR);
    yyval = node;
}
break;
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
