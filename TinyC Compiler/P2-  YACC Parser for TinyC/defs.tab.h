/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_DEFS_TAB_H_INCLUDED
# define YY_YY_DEFS_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    PTR_OP = 258,                  /* PTR_OP  */
    INCREMENT = 259,               /* INCREMENT  */
    DECREMENT = 260,               /* DECREMENT  */
    SIZEOF = 261,                  /* SIZEOF  */
    LSHIFT = 262,                  /* LSHIFT  */
    RSHIFT = 263,                  /* RSHIFT  */
    LE_OP = 264,                   /* LE_OP  */
    GE_OP = 265,                   /* GE_OP  */
    EQ_OP = 266,                   /* EQ_OP  */
    NE_OP = 267,                   /* NE_OP  */
    BINARY_AND = 268,              /* BINARY_AND  */
    BINARY_OR = 269,               /* BINARY_OR  */
    MUL_ASSIGN = 270,              /* MUL_ASSIGN  */
    DIV_ASSIGN = 271,              /* DIV_ASSIGN  */
    MOD_ASSIGN = 272,              /* MOD_ASSIGN  */
    ADD_ASSIGN = 273,              /* ADD_ASSIGN  */
    SUB_ASSIGN = 274,              /* SUB_ASSIGN  */
    LEFT_ASSIGN = 275,             /* LEFT_ASSIGN  */
    RIGHT_ASSIGN = 276,            /* RIGHT_ASSIGN  */
    AND_ASSIGN = 277,              /* AND_ASSIGN  */
    XOR_ASSIGN = 278,              /* XOR_ASSIGN  */
    OR_ASSIGN = 279,               /* OR_ASSIGN  */
    EXTERN = 280,                  /* EXTERN  */
    STATIC = 281,                  /* STATIC  */
    AUTO = 282,                    /* AUTO  */
    REGISTER = 283,                /* REGISTER  */
    VOID = 284,                    /* VOID  */
    CHAR = 285,                    /* CHAR  */
    SHORT = 286,                   /* SHORT  */
    INT = 287,                     /* INT  */
    LONG = 288,                    /* LONG  */
    FLOAT = 289,                   /* FLOAT  */
    DOUBLE = 290,                  /* DOUBLE  */
    SIGNED = 291,                  /* SIGNED  */
    UNSIGNED = 292,                /* UNSIGNED  */
    BOOL = 293,                    /* BOOL  */
    IMAGINARY = 294,               /* IMAGINARY  */
    COMPLEX = 295,                 /* COMPLEX  */
    CONST = 296,                   /* CONST  */
    RESTRICT = 297,                /* RESTRICT  */
    VOLATILE = 298,                /* VOLATILE  */
    INLINE = 299,                  /* INLINE  */
    ELLIPSIS = 300,                /* ELLIPSIS  */
    IF = 301,                      /* IF  */
    SWITCH = 302,                  /* SWITCH  */
    CASE = 303,                    /* CASE  */
    DEFAULT = 304,                 /* DEFAULT  */
    WHILE = 305,                   /* WHILE  */
    DO = 306,                      /* DO  */
    FOR = 307,                     /* FOR  */
    GOTO = 308,                    /* GOTO  */
    CONTINUE = 309,                /* CONTINUE  */
    BREAK = 310,                   /* BREAK  */
    RETURN = 311,                  /* RETURN  */
    IDENTIFIER = 312,              /* IDENTIFIER  */
    INTEGER_VAL = 313,             /* INTEGER_VAL  */
    FLOAT_VAL = 314,               /* FLOAT_VAL  */
    CHAR_VAL = 315,                /* CHAR_VAL  */
    STRING = 316,                  /* STRING  */
    LOWER_THAN_ELSE = 317,         /* LOWER_THAN_ELSE  */
    ELSE = 318                     /* ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 12 "defs.y"

    int num;
    double decimal_num;
    char character;
    char* string;
    struct ParseTreeNode* X;

#line 135 "defs.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_DEFS_TAB_H_INCLUDED  */
