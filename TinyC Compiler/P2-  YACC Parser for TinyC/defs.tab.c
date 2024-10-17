/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "defs.y"

    #include <stdio.h>
    #include "defs.h"
    extern int yylex();
    void yyerror(char* s);

    extern struct ParseTreeNode* root;
    extern struct ParseTreeNode* createNode (char* name);
    extern void addChild (struct ParseTreeNode* parent, struct ParseTreeNode* child);

#line 82 "defs.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "defs.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PTR_OP = 3,                     /* PTR_OP  */
  YYSYMBOL_INCREMENT = 4,                  /* INCREMENT  */
  YYSYMBOL_DECREMENT = 5,                  /* DECREMENT  */
  YYSYMBOL_SIZEOF = 6,                     /* SIZEOF  */
  YYSYMBOL_LSHIFT = 7,                     /* LSHIFT  */
  YYSYMBOL_RSHIFT = 8,                     /* RSHIFT  */
  YYSYMBOL_LE_OP = 9,                      /* LE_OP  */
  YYSYMBOL_GE_OP = 10,                     /* GE_OP  */
  YYSYMBOL_EQ_OP = 11,                     /* EQ_OP  */
  YYSYMBOL_NE_OP = 12,                     /* NE_OP  */
  YYSYMBOL_BINARY_AND = 13,                /* BINARY_AND  */
  YYSYMBOL_BINARY_OR = 14,                 /* BINARY_OR  */
  YYSYMBOL_MUL_ASSIGN = 15,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 16,                /* DIV_ASSIGN  */
  YYSYMBOL_MOD_ASSIGN = 17,                /* MOD_ASSIGN  */
  YYSYMBOL_ADD_ASSIGN = 18,                /* ADD_ASSIGN  */
  YYSYMBOL_SUB_ASSIGN = 19,                /* SUB_ASSIGN  */
  YYSYMBOL_LEFT_ASSIGN = 20,               /* LEFT_ASSIGN  */
  YYSYMBOL_RIGHT_ASSIGN = 21,              /* RIGHT_ASSIGN  */
  YYSYMBOL_AND_ASSIGN = 22,                /* AND_ASSIGN  */
  YYSYMBOL_XOR_ASSIGN = 23,                /* XOR_ASSIGN  */
  YYSYMBOL_OR_ASSIGN = 24,                 /* OR_ASSIGN  */
  YYSYMBOL_EXTERN = 25,                    /* EXTERN  */
  YYSYMBOL_STATIC = 26,                    /* STATIC  */
  YYSYMBOL_AUTO = 27,                      /* AUTO  */
  YYSYMBOL_REGISTER = 28,                  /* REGISTER  */
  YYSYMBOL_VOID = 29,                      /* VOID  */
  YYSYMBOL_CHAR = 30,                      /* CHAR  */
  YYSYMBOL_SHORT = 31,                     /* SHORT  */
  YYSYMBOL_INT = 32,                       /* INT  */
  YYSYMBOL_LONG = 33,                      /* LONG  */
  YYSYMBOL_FLOAT = 34,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 35,                    /* DOUBLE  */
  YYSYMBOL_SIGNED = 36,                    /* SIGNED  */
  YYSYMBOL_UNSIGNED = 37,                  /* UNSIGNED  */
  YYSYMBOL_BOOL = 38,                      /* BOOL  */
  YYSYMBOL_IMAGINARY = 39,                 /* IMAGINARY  */
  YYSYMBOL_COMPLEX = 40,                   /* COMPLEX  */
  YYSYMBOL_CONST = 41,                     /* CONST  */
  YYSYMBOL_RESTRICT = 42,                  /* RESTRICT  */
  YYSYMBOL_VOLATILE = 43,                  /* VOLATILE  */
  YYSYMBOL_INLINE = 44,                    /* INLINE  */
  YYSYMBOL_ELLIPSIS = 45,                  /* ELLIPSIS  */
  YYSYMBOL_IF = 46,                        /* IF  */
  YYSYMBOL_SWITCH = 47,                    /* SWITCH  */
  YYSYMBOL_CASE = 48,                      /* CASE  */
  YYSYMBOL_DEFAULT = 49,                   /* DEFAULT  */
  YYSYMBOL_WHILE = 50,                     /* WHILE  */
  YYSYMBOL_DO = 51,                        /* DO  */
  YYSYMBOL_FOR = 52,                       /* FOR  */
  YYSYMBOL_GOTO = 53,                      /* GOTO  */
  YYSYMBOL_CONTINUE = 54,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 55,                     /* BREAK  */
  YYSYMBOL_RETURN = 56,                    /* RETURN  */
  YYSYMBOL_IDENTIFIER = 57,                /* IDENTIFIER  */
  YYSYMBOL_INTEGER_VAL = 58,               /* INTEGER_VAL  */
  YYSYMBOL_FLOAT_VAL = 59,                 /* FLOAT_VAL  */
  YYSYMBOL_CHAR_VAL = 60,                  /* CHAR_VAL  */
  YYSYMBOL_STRING = 61,                    /* STRING  */
  YYSYMBOL_LOWER_THAN_ELSE = 62,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_ELSE = 63,                      /* ELSE  */
  YYSYMBOL_64_ = 64,                       /* '('  */
  YYSYMBOL_65_ = 65,                       /* ')'  */
  YYSYMBOL_66_ = 66,                       /* '['  */
  YYSYMBOL_67_ = 67,                       /* ']'  */
  YYSYMBOL_68_ = 68,                       /* '.'  */
  YYSYMBOL_69_ = 69,                       /* '{'  */
  YYSYMBOL_70_ = 70,                       /* '}'  */
  YYSYMBOL_71_ = 71,                       /* ','  */
  YYSYMBOL_72_ = 72,                       /* '&'  */
  YYSYMBOL_73_ = 73,                       /* '*'  */
  YYSYMBOL_74_ = 74,                       /* '+'  */
  YYSYMBOL_75_ = 75,                       /* '-'  */
  YYSYMBOL_76_ = 76,                       /* '~'  */
  YYSYMBOL_77_ = 77,                       /* '!'  */
  YYSYMBOL_78_ = 78,                       /* '/'  */
  YYSYMBOL_79_ = 79,                       /* '%'  */
  YYSYMBOL_80_ = 80,                       /* '<'  */
  YYSYMBOL_81_ = 81,                       /* '>'  */
  YYSYMBOL_82_ = 82,                       /* '^'  */
  YYSYMBOL_83_ = 83,                       /* '|'  */
  YYSYMBOL_84_ = 84,                       /* '?'  */
  YYSYMBOL_85_ = 85,                       /* ':'  */
  YYSYMBOL_86_ = 86,                       /* '='  */
  YYSYMBOL_87_ = 87,                       /* ';'  */
  YYSYMBOL_YYACCEPT = 88,                  /* $accept  */
  YYSYMBOL_primary_expression = 89,        /* primary_expression  */
  YYSYMBOL_postfix_expression = 90,        /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 91,  /* argument_expression_list  */
  YYSYMBOL_unary_expression = 92,          /* unary_expression  */
  YYSYMBOL_unary_operator = 93,            /* unary_operator  */
  YYSYMBOL_cast_expression = 94,           /* cast_expression  */
  YYSYMBOL_multiplicative_expression = 95, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 96,       /* additive_expression  */
  YYSYMBOL_shift_expression = 97,          /* shift_expression  */
  YYSYMBOL_relational_expression = 98,     /* relational_expression  */
  YYSYMBOL_equality_expression = 99,       /* equality_expression  */
  YYSYMBOL_AND_expression = 100,           /* AND_expression  */
  YYSYMBOL_exclusive_OR_expression = 101,  /* exclusive_OR_expression  */
  YYSYMBOL_inclusive_OR_expression = 102,  /* inclusive_OR_expression  */
  YYSYMBOL_logical_AND_expression = 103,   /* logical_AND_expression  */
  YYSYMBOL_logical_OR_expression = 104,    /* logical_OR_expression  */
  YYSYMBOL_conditional_expression = 105,   /* conditional_expression  */
  YYSYMBOL_assignment_expression = 106,    /* assignment_expression  */
  YYSYMBOL_assignment_expression_optional = 107, /* assignment_expression_optional  */
  YYSYMBOL_assignment_operator = 108,      /* assignment_operator  */
  YYSYMBOL_expression = 109,               /* expression  */
  YYSYMBOL_expression_optional = 110,      /* expression_optional  */
  YYSYMBOL_constant_expression = 111,      /* constant_expression  */
  YYSYMBOL_declaration = 112,              /* declaration  */
  YYSYMBOL_declaration_specifiers = 113,   /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 114,     /* init_declarator_list  */
  YYSYMBOL_init_declarator = 115,          /* init_declarator  */
  YYSYMBOL_storage_class_specifier = 116,  /* storage_class_specifier  */
  YYSYMBOL_type_specifier = 117,           /* type_specifier  */
  YYSYMBOL_specifier_qualifier_list = 118, /* specifier_qualifier_list  */
  YYSYMBOL_type_qualifier = 119,           /* type_qualifier  */
  YYSYMBOL_function_specifier = 120,       /* function_specifier  */
  YYSYMBOL_declarator = 121,               /* declarator  */
  YYSYMBOL_direct_declarator = 122,        /* direct_declarator  */
  YYSYMBOL_pointer = 123,                  /* pointer  */
  YYSYMBOL_type_qualifier_list = 124,      /* type_qualifier_list  */
  YYSYMBOL_type_qualifier_list_optional = 125, /* type_qualifier_list_optional  */
  YYSYMBOL_parameter_type_list = 126,      /* parameter_type_list  */
  YYSYMBOL_parameter_list = 127,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 128,    /* parameter_declaration  */
  YYSYMBOL_identifier_list = 129,          /* identifier_list  */
  YYSYMBOL_identifier_list_optional = 130, /* identifier_list_optional  */
  YYSYMBOL_type_name = 131,                /* type_name  */
  YYSYMBOL_initializer = 132,              /* initializer  */
  YYSYMBOL_initializer_list = 133,         /* initializer_list  */
  YYSYMBOL_designation = 134,              /* designation  */
  YYSYMBOL_designation_optional = 135,     /* designation_optional  */
  YYSYMBOL_designator_list = 136,          /* designator_list  */
  YYSYMBOL_designator = 137,               /* designator  */
  YYSYMBOL_statement = 138,                /* statement  */
  YYSYMBOL_labeled_statement = 139,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 140,       /* compound_statement  */
  YYSYMBOL_block_item_list = 141,          /* block_item_list  */
  YYSYMBOL_block_item_list_optional = 142, /* block_item_list_optional  */
  YYSYMBOL_block_item = 143,               /* block_item  */
  YYSYMBOL_expression_statement = 144,     /* expression_statement  */
  YYSYMBOL_selection_statement = 145,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 146,      /* iteration_statement  */
  YYSYMBOL_jump_statement = 147,           /* jump_statement  */
  YYSYMBOL_translation_unit = 148,         /* translation_unit  */
  YYSYMBOL_external_declaration = 149,     /* external_declaration  */
  YYSYMBOL_function_definition = 150,      /* function_definition  */
  YYSYMBOL_declaration_list = 151,         /* declaration_list  */
  YYSYMBOL_declaration_list_optional = 152, /* declaration_list_optional  */
  YYSYMBOL_program = 153                   /* program  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  45
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   782

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  88
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  66
/* YYNRULES -- Number of rules.  */
#define YYNRULES  198
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  323

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   318


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    77,     2,     2,     2,    79,    72,     2,
      64,    65,    73,    74,    71,    75,    68,    78,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    85,    87,
      80,    86,    81,    84,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    66,     2,    67,    82,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    69,    83,    70,    76,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   109,   109,   117,   125,   133,   141,   149,   160,   166,
     175,   183,   192,   200,   208,   215,   222,   233,   246,   252,
     261,   267,   274,   281,   288,   295,   305,   310,   315,   320,
     325,   330,   336,   342,   352,   358,   366,   374,   383,   389,
     397,   406,   412,   420,   429,   434,   442,   450,   458,   467,
     473,   481,   490,   496,   505,   511,   520,   526,   535,   541,
     550,   556,   565,   571,   582,   588,   597,   604,   610,   615,
     620,   625,   630,   635,   640,   645,   650,   655,   660,   666,
     672,   681,   688,   694,   702,   709,   718,   725,   732,   738,
     745,   751,   758,   764,   772,   778,   787,   793,   802,   808,
     814,   820,   827,   833,   839,   845,   851,   857,   863,   869,
     875,   881,   887,   893,   900,   906,   913,   919,   927,   933,
     939,   946,   953,   960,   967,   973,   981,   992,  1003,  1014,
    1024,  1033,  1043,  1050,  1059,  1065,  1073,  1080,  1086,  1091,
    1099,  1105,  1114,  1121,  1128,  1134,  1143,  1150,  1156,  1163,
    1169,  1177,  1187,  1194,  1204,  1212,  1219,  1225,  1231,  1239,
    1247,  1256,  1262,  1268,  1274,  1280,  1286,  1293,  1301,  1310,
    1319,  1328,  1334,  1342,  1349,  1355,  1361,  1368,  1376,  1386,
    1398,  1409,  1419,  1431,  1445,  1459,  1467,  1474,  1481,  1491,
    1497,  1505,  1511,  1518,  1528,  1534,  1542,  1549,  1555
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PTR_OP", "INCREMENT",
  "DECREMENT", "SIZEOF", "LSHIFT", "RSHIFT", "LE_OP", "GE_OP", "EQ_OP",
  "NE_OP", "BINARY_AND", "BINARY_OR", "MUL_ASSIGN", "DIV_ASSIGN",
  "MOD_ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN",
  "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN", "EXTERN", "STATIC", "AUTO",
  "REGISTER", "VOID", "CHAR", "SHORT", "INT", "LONG", "FLOAT", "DOUBLE",
  "SIGNED", "UNSIGNED", "BOOL", "IMAGINARY", "COMPLEX", "CONST",
  "RESTRICT", "VOLATILE", "INLINE", "ELLIPSIS", "IF", "SWITCH", "CASE",
  "DEFAULT", "WHILE", "DO", "FOR", "GOTO", "CONTINUE", "BREAK", "RETURN",
  "IDENTIFIER", "INTEGER_VAL", "FLOAT_VAL", "CHAR_VAL", "STRING",
  "LOWER_THAN_ELSE", "ELSE", "'('", "')'", "'['", "']'", "'.'", "'{'",
  "'}'", "','", "'&'", "'*'", "'+'", "'-'", "'~'", "'!'", "'/'", "'%'",
  "'<'", "'>'", "'^'", "'|'", "'?'", "':'", "'='", "';'", "$accept",
  "primary_expression", "postfix_expression", "argument_expression_list",
  "unary_expression", "unary_operator", "cast_expression",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "AND_expression",
  "exclusive_OR_expression", "inclusive_OR_expression",
  "logical_AND_expression", "logical_OR_expression",
  "conditional_expression", "assignment_expression",
  "assignment_expression_optional", "assignment_operator", "expression",
  "expression_optional", "constant_expression", "declaration",
  "declaration_specifiers", "init_declarator_list", "init_declarator",
  "storage_class_specifier", "type_specifier", "specifier_qualifier_list",
  "type_qualifier", "function_specifier", "declarator",
  "direct_declarator", "pointer", "type_qualifier_list",
  "type_qualifier_list_optional", "parameter_type_list", "parameter_list",
  "parameter_declaration", "identifier_list", "identifier_list_optional",
  "type_name", "initializer", "initializer_list", "designation",
  "designation_optional", "designator_list", "designator", "statement",
  "labeled_statement", "compound_statement", "block_item_list",
  "block_item_list_optional", "block_item", "expression_statement",
  "selection_statement", "iteration_statement", "jump_statement",
  "translation_unit", "external_declaration", "function_definition",
  "declaration_list", "declaration_list_optional", "program", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-208)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-198)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     738,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,  -208,   -19,   738,   738,   738,   738,   738,  -208,  -208,
      25,  -208,    20,   136,  -208,   -18,  -208,   655,    -2,   -38,
    -208,  -208,  -208,  -208,  -208,  -208,   -25,  -208,   136,    78,
      20,  -208,   438,  -208,   -19,   738,   124,   675,   -14,    -2,
    -208,  -208,  -208,  -208,   -31,   520,   520,   541,  -208,  -208,
    -208,  -208,  -208,   377,    24,  -208,  -208,  -208,  -208,  -208,
    -208,  -208,    54,   165,   581,  -208,     7,   -24,   162,     8,
      67,    68,    84,   116,   195,    -3,  -208,  -208,  -208,  -208,
     206,  -208,  -208,    20,   148,   143,  -208,   144,   152,   136,
       5,   602,   377,  -208,  -208,   377,  -208,  -208,   -22,   590,
    -208,   590,   153,   581,   163,   104,  -208,   438,   -45,  -208,
     164,  -208,  -208,   478,   581,   167,  -208,  -208,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,  -208,  -208,   581,  -208,  -208,
     581,   581,   581,   581,   581,   581,   581,   581,   581,   581,
     581,   581,   581,   581,   581,   581,   581,   581,   581,   155,
     158,   581,   145,   204,   417,   205,   171,   142,   187,   581,
     192,   213,   198,  -208,  -208,  -208,  -208,   267,   216,  -208,
    -208,  -208,  -208,  -208,  -208,  -208,   717,   230,  -208,   581,
     581,   221,  -208,   222,   225,   226,  -208,   581,  -208,  -208,
     499,  -208,   245,  -208,  -208,    94,  -208,  -208,  -208,  -208,
    -208,    52,  -208,    71,  -208,  -208,  -208,  -208,  -208,     7,
       7,   -24,   -24,   162,   162,   162,   162,     8,     8,    67,
      68,    84,   116,   195,   -41,   581,   581,   244,   417,   581,
     280,   328,   248,  -208,  -208,   251,   417,  -208,  -208,  -208,
    -208,  -208,  -208,   278,   279,  -208,  -208,   281,   281,  -208,
      24,  -208,  -208,  -208,   438,  -208,   581,  -208,   581,    59,
      70,   417,  -208,    72,   283,   261,   581,  -208,  -208,  -208,
    -208,  -208,   120,  -208,  -208,  -208,   417,   417,  -208,   417,
     581,   581,   262,  -208,    97,   288,  -208,  -208,    74,   265,
     581,  -208,   417,   286,   581,   309,  -208,  -208,   310,   417,
     417,  -208,  -208
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   118,   119,   120,
     121,   192,     0,    86,    88,    90,    92,   198,   189,   191,
       0,   124,     0,   137,    84,     0,    94,    96,   123,     0,
      87,    89,    91,    93,   190,     1,     0,   134,   136,   132,
       0,    85,     0,   194,     0,   196,     0,   147,   137,   122,
     125,   135,   133,    95,    96,     0,     0,     0,     2,     3,
       4,     5,     6,     0,   156,    26,    27,    28,    29,    30,
      31,     8,    20,    32,     0,    34,    38,    41,    44,    49,
      52,    54,    56,    58,    60,    62,    64,   149,    97,   195,
      82,   193,   144,   143,     0,   138,   140,   146,     0,   137,
     136,    67,     0,    21,    22,     0,    24,    79,     0,   114,
     148,   116,     0,     0,     0,     0,   155,     0,     0,   157,
       0,    14,    15,     0,     0,     0,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    68,     0,    32,    23,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    82,     0,     0,     0,     0,    82,
       2,    81,     0,   175,   176,   161,   162,    82,     0,   171,
     163,   164,   165,   166,   142,   130,     0,     0,   131,     0,
       0,    27,    66,     0,     0,     0,     7,     0,   115,   117,
       0,    83,     0,   160,   150,   156,   152,   154,   158,    13,
      10,     0,    18,     0,    12,    65,    35,    36,    37,    39,
      40,    42,    43,    47,    48,    45,    46,    50,    51,    53,
      55,    57,    59,    61,     0,     0,     0,     0,    82,     0,
       0,    82,     0,   186,   187,     0,    82,   177,   172,   170,
     139,   141,   145,     0,     0,   129,   126,     0,    25,    80,
     156,    33,   159,   151,     0,    11,     0,     9,     0,     0,
       0,    82,   169,     0,     0,     0,    82,   185,   188,   167,
     127,   128,     0,   153,    19,    63,    82,    82,   168,    82,
       0,    82,     0,    16,   156,   178,   180,   181,     0,     0,
      82,    17,    82,     0,    82,     0,   179,   182,     0,    82,
      82,   184,   183
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -208,  -208,  -208,  -208,   -52,  -208,   -77,    42,    46,   -32,
      43,   214,   212,   215,   218,   211,  -208,  -119,   -51,  -208,
    -208,   -73,  -157,   208,   -35,    10,  -208,   340,  -208,   -49,
      73,    88,  -208,   -16,   352,   344,   336,   -53,  -208,  -208,
     199,  -208,  -208,    56,  -124,   126,  -208,  -207,  -208,   269,
    -165,  -208,   342,  -208,  -208,   237,  -208,  -208,  -208,  -208,
    -208,   372,  -208,  -208,  -208,  -208
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    81,    82,   221,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,   117,   203,
     147,   181,   182,   212,    21,    54,    35,    36,    23,    24,
     120,    25,    26,    64,    38,    39,    48,    49,   104,   105,
     106,   107,   108,   122,    98,   125,   126,   127,   128,   129,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
      27,    28,    29,    55,    56,    30
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     118,    97,    53,   216,   211,   111,    37,   149,   274,   250,
      22,   167,   109,   113,   114,   116,    46,   157,   158,    31,
      99,   123,   255,   124,   119,    45,    32,    17,    18,    19,
     207,   200,   148,    40,    41,    42,    43,    22,    31,   118,
      60,   217,   118,   206,   278,    32,    17,    18,    19,   207,
     153,   154,   211,    50,    33,    52,   199,   130,   131,   132,
     202,   223,    57,   119,    58,   183,   119,   103,    34,    51,
     119,   148,   119,   226,   227,   228,    97,    31,   161,   162,
     150,   168,   222,   282,    32,   151,   152,   194,   159,   160,
     123,   289,   124,    33,   285,   244,   225,   274,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   298,   275,   133,   148,
     134,    47,   135,   276,   296,   233,   234,   235,   236,   302,
     207,   305,   306,   271,   307,   297,    61,   299,   277,   313,
     163,   207,   207,   207,   309,   207,    47,   316,   263,   264,
     293,    33,   183,   315,   321,   322,   269,   318,   148,   295,
     123,   121,   124,   123,   273,   124,   164,   311,   204,   155,
     156,   205,   279,   280,   214,   215,   283,    17,    18,    19,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     303,   304,   208,   100,   209,   229,   230,    47,    61,   165,
     121,   231,   232,   121,   237,   238,   103,   121,   166,   121,
      65,    66,    67,   195,   196,   197,   286,   198,   210,   245,
     213,   219,   246,    97,   224,   294,   148,   308,   252,   253,
     248,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,   146,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,    69,    70,    71,    72,   249,   251,
      73,    65,    66,    67,   254,   100,  -174,   256,    75,    76,
      77,    78,    79,    80,   207,   257,   259,   262,   265,   266,
     267,   268,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,   272,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,    69,    70,    71,    72,   281,
     284,    73,    65,    66,    67,   287,   100,  -173,   288,    75,
      76,    77,    78,    79,    80,   290,   291,   300,   301,   310,
     270,   312,   314,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,   317,   319,   320,   240,   239,   243,   247,
     241,    65,    66,    67,   242,    68,    69,    70,    71,    72,
      63,    59,    73,    62,   110,   261,   292,   218,   101,    44,
      75,    76,    77,    78,    79,    80,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    65,    66,    67,   258,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    68,    69,    70,    71,    72,     0,
       0,    73,    65,    66,    67,     0,     0,     0,     0,    75,
      76,    77,    78,    79,    80,     0,     0,     0,     0,     0,
       0,     0,     0,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,    69,    70,    71,    72,     0,
       0,    73,    65,    66,    67,     0,   100,     0,     0,    75,
      76,    77,    78,    79,    80,    68,    69,    70,    71,    72,
       0,     0,    73,    65,    66,    67,     0,    74,     0,     0,
      75,    76,    77,    78,    79,    80,     0,     0,     0,     0,
       0,     0,     0,     0,    65,    66,    67,     0,     0,     0,
       0,     0,     0,     0,     0,    68,    69,    70,    71,    72,
       0,     0,    73,   220,     0,    65,    66,    67,     0,     0,
      75,    76,    77,    78,    79,    80,    68,    69,    70,    71,
      72,     0,     0,    73,     0,     0,     0,     0,   270,     0,
       0,    75,    76,    77,    78,    79,    80,    68,    69,    70,
      71,    72,     0,     0,   112,    65,    66,    67,     0,     0,
       0,     0,    75,    76,    77,    78,    79,    80,    68,    69,
      70,    71,    72,     0,     0,   115,    65,    66,    67,     0,
       0,     0,     0,    75,    76,    77,    78,    79,    80,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,     0,     0,     0,    68,    69,
      70,    71,    72,     0,     0,    73,     0,     0,     0,     0,
       0,     0,     0,    75,    76,    77,    78,    79,    80,    68,
      69,    70,    71,    72,     0,     0,    73,     0,     0,     0,
       0,     0,     0,     0,    75,   201,    77,    78,    79,    80,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
       0,     0,     0,     0,  -197,     0,     0,     0,     0,     0,
       0,     0,   102,     0,     0,     0,     0,     0,     0,     0,
       0,    52,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,   260,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20
};

static const yytype_int16 yycheck[] =
{
      73,    52,    37,   127,   123,    58,    22,    84,   215,   174,
       0,    14,    26,    65,    66,    67,    32,     9,    10,    57,
      55,    66,   179,    68,    73,     0,    64,    41,    42,    43,
      71,    26,    84,    23,    24,    25,    26,    27,    57,   112,
      65,    86,   115,    65,    85,    64,    41,    42,    43,    71,
      74,    75,   171,    71,    73,    86,   109,     3,     4,     5,
     111,   134,    64,   112,    66,   100,   115,    57,    87,    87,
     119,   123,   121,   150,   151,   152,   127,    57,    11,    12,
      73,    84,   133,   248,    64,    78,    79,   103,    80,    81,
      66,   256,    68,    73,   251,   168,   147,   304,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   281,    65,    64,   171,
      66,    33,    68,    71,    65,   157,   158,   159,   160,   286,
      71,   296,   297,   210,   299,    65,    48,    65,    67,    65,
      72,    71,    71,    71,   301,    71,    58,   312,   199,   200,
     274,    73,   187,   310,   319,   320,   207,   314,   210,   278,
      66,    73,    68,    66,    70,    68,    82,    70,   112,     7,
       8,   115,   245,   246,    70,    71,   249,    41,    42,    43,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      70,    71,   119,    69,   121,   153,   154,   109,   110,    83,
     112,   155,   156,   115,   161,   162,   196,   119,    13,   121,
       4,     5,     6,    65,    71,    71,   251,    65,    65,    64,
      57,    57,    64,   274,    57,   276,   278,   300,    57,    87,
      85,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    86,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    64,    64,
      64,     4,     5,     6,    87,    69,    70,    85,    72,    73,
      74,    75,    76,    77,    71,    87,    70,    57,    67,    67,
      65,    65,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    67,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    85,
      50,    64,     4,     5,     6,    87,    69,    70,    87,    72,
      73,    74,    75,    76,    77,    67,    67,    64,    87,    87,
      69,    63,    87,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    87,    65,    65,   164,   163,   167,   171,
     165,     4,     5,     6,   166,    57,    58,    59,    60,    61,
      50,    39,    64,    49,    58,   196,   270,   128,    56,    27,
      72,    73,    74,    75,    76,    77,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,     4,     5,     6,   187,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    57,    58,    59,    60,    61,    -1,
      -1,    64,     4,     5,     6,    -1,    -1,    -1,    -1,    72,
      73,    74,    75,    76,    77,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    -1,
      -1,    64,     4,     5,     6,    -1,    69,    -1,    -1,    72,
      73,    74,    75,    76,    77,    57,    58,    59,    60,    61,
      -1,    -1,    64,     4,     5,     6,    -1,    69,    -1,    -1,
      72,    73,    74,    75,    76,    77,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     4,     5,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    57,    58,    59,    60,    61,
      -1,    -1,    64,    65,    -1,     4,     5,     6,    -1,    -1,
      72,    73,    74,    75,    76,    77,    57,    58,    59,    60,
      61,    -1,    -1,    64,    -1,    -1,    -1,    -1,    69,    -1,
      -1,    72,    73,    74,    75,    76,    77,    57,    58,    59,
      60,    61,    -1,    -1,    64,     4,     5,     6,    -1,    -1,
      -1,    -1,    72,    73,    74,    75,    76,    77,    57,    58,
      59,    60,    61,    -1,    -1,    64,     4,     5,     6,    -1,
      -1,    -1,    -1,    72,    73,    74,    75,    76,    77,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    -1,    -1,    -1,    -1,    57,    58,
      59,    60,    61,    -1,    -1,    64,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    72,    73,    74,    75,    76,    77,    57,
      58,    59,    60,    61,    -1,    -1,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,    77,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    86,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,   112,   113,   116,   117,   119,   120,   148,   149,   150,
     153,    57,    64,    73,    87,   114,   115,   121,   122,   123,
     113,   113,   113,   113,   149,     0,   121,   119,   124,   125,
      71,    87,    86,   112,   113,   151,   152,    64,    66,   122,
      65,   119,   123,   115,   121,     4,     5,     6,    57,    58,
      59,    60,    61,    64,    69,    72,    73,    74,    75,    76,
      77,    89,    90,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   132,   112,
      69,   140,    57,   113,   126,   127,   128,   129,   130,    26,
     124,   125,    64,    92,    92,    64,    92,   106,   109,   117,
     118,   119,   131,    66,    68,   133,   134,   135,   136,   137,
       3,     4,     5,    64,    66,    68,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    86,   108,    92,    94,
      73,    78,    79,    74,    75,     7,     8,     9,    10,    80,
      81,    11,    12,    72,    82,    83,    13,    14,    84,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,   109,   110,   112,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   121,    65,    71,    71,    65,   125,
      26,    73,   106,   107,   131,   131,    65,    71,   118,   118,
      65,   105,   111,    57,    70,    71,   132,    86,   137,    57,
      65,    91,   106,   109,    57,   106,    94,    94,    94,    95,
      95,    96,    96,    97,    97,    97,    97,    98,    98,    99,
     100,   101,   102,   103,   109,    64,    64,   111,    85,    64,
     138,    64,    57,    87,    87,   110,    85,    87,   143,    70,
      45,   128,    57,   106,   106,    67,    67,    65,    65,   106,
      69,    94,    67,    70,   135,    65,    71,    67,    85,   109,
     109,    85,   138,   109,    50,   110,   112,    87,    87,   138,
      67,    67,   133,   132,   106,   105,    65,    65,   138,    65,
      64,    87,   110,    70,    71,   138,   138,   138,   109,   110,
      87,    70,    63,    65,    87,   110,   138,    87,   110,    65,
      65,   138,   138
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    88,    89,    89,    89,    89,    89,    89,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    91,    91,
      92,    92,    92,    92,    92,    92,    93,    93,    93,    93,
      93,    93,    94,    94,    95,    95,    95,    95,    96,    96,
      96,    97,    97,    97,    98,    98,    98,    98,    98,    99,
      99,    99,   100,   100,   101,   101,   102,   102,   103,   103,
     104,   104,   105,   105,   106,   106,   107,   107,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   109,
     109,   110,   110,   111,   112,   112,   113,   113,   113,   113,
     113,   113,   113,   113,   114,   114,   115,   115,   116,   116,
     116,   116,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   118,   118,   118,   118,   119,   119,
     119,   120,   121,   121,   122,   122,   122,   122,   122,   122,
     122,   122,   123,   123,   124,   124,   125,   125,   126,   126,
     127,   127,   128,   128,   129,   129,   130,   130,   131,   132,
     132,   132,   133,   133,   134,   135,   135,   136,   136,   137,
     137,   138,   138,   138,   138,   138,   138,   139,   139,   139,
     140,   141,   141,   142,   142,   143,   143,   144,   145,   145,
     145,   146,   146,   146,   146,   147,   147,   147,   147,   148,
     148,   149,   149,   150,   151,   151,   152,   152,   153
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     3,     1,     4,
       3,     4,     3,     3,     2,     2,     6,     7,     1,     3,
       1,     2,     2,     2,     2,     4,     1,     1,     1,     1,
       1,     1,     1,     4,     1,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     5,     1,     3,     1,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     0,     1,     2,     3,     1,     2,     1,     2,
       1,     2,     1,     2,     1,     3,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     2,     1,     1,
       1,     1,     2,     1,     1,     3,     5,     6,     6,     5,
       4,     4,     2,     3,     1,     2,     1,     0,     1,     3,
       1,     3,     2,     1,     1,     3,     1,     0,     1,     1,
       3,     4,     2,     4,     2,     1,     0,     1,     2,     3,
       2,     1,     1,     1,     1,     1,     1,     3,     4,     3,
       3,     1,     2,     1,     0,     1,     1,     2,     5,     7,
       5,     5,     7,     9,     8,     3,     2,     2,     3,     1,
       2,     1,     1,     4,     1,     2,     1,     0,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* primary_expression: IDENTIFIER  */
#line 110 "defs.y"
{
    // printf ("primary_expression -> IDENTIFIER\n");
    char *str = (char *)malloc (1000 * sizeof (char));
    sprintf (str, "ID (%s)", (yyvsp[0].string));
    (yyval.X) = createNode ("primary_expression");
    addChild ((yyval.X), createNode (str));
}
#line 1574 "defs.tab.c"
    break;

  case 3: /* primary_expression: INTEGER_VAL  */
#line 118 "defs.y"
{
    // printf ("primary_expression -> INTEGER_VAL\n");
    char *str = (char *)malloc (100 * sizeof (char));
    sprintf (str, "INT (%d)", (yyvsp[0].num));
    (yyval.X) = createNode ("primary_expression");
    addChild ((yyval.X), createNode (str));
}
#line 1586 "defs.tab.c"
    break;

  case 4: /* primary_expression: FLOAT_VAL  */
#line 126 "defs.y"
{
    // printf ("primary_expression -> FLOAT_VAL\n");
    char *str = (char *)malloc (1000 * sizeof (char));
    sprintf (str, "FLOAT (%f)", (yyvsp[0].decimal_num));
    (yyval.X) = createNode ("primary_expression");
    addChild ((yyval.X), createNode (str));
}
#line 1598 "defs.tab.c"
    break;

  case 5: /* primary_expression: CHAR_VAL  */
#line 134 "defs.y"
{
    // printf ("primary_expression -> CHAR_VAL\n");
    char *str = (char *)malloc (100 * sizeof (char));
    sprintf (str, "CHAR ('%c')", (yyvsp[0].character));
    (yyval.X) = createNode ("primary_expression");
    addChild ((yyval.X), createNode (str));
}
#line 1610 "defs.tab.c"
    break;

  case 6: /* primary_expression: STRING  */
#line 142 "defs.y"
{
    // printf ("primary_expression -> STRING\n");
    char *str = (char *)malloc (1000 * sizeof (char));
    sprintf (str, "STRING_LITERAL ('%s')", (yyvsp[0].string));
    (yyval.X) = createNode ("primary_expression");
    addChild ((yyval.X), createNode (str));
}
#line 1622 "defs.tab.c"
    break;

  case 7: /* primary_expression: '(' expression ')'  */
#line 150 "defs.y"
{
    // printf ("primary_expression -> '(' expression ')'\n");
    (yyval.X) = createNode ("primary_expression");
    addChild ((yyval.X), createNode ("("));
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), createNode (")"));
}
#line 1634 "defs.tab.c"
    break;

  case 8: /* postfix_expression: primary_expression  */
#line 161 "defs.y"
{
    //printf ("postfix_expression -> primary_expression\n");
    (yyval.X) = createNode ("primary_expression");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 1644 "defs.tab.c"
    break;

  case 9: /* postfix_expression: postfix_expression '[' expression ']'  */
#line 167 "defs.y"
{
    //printf ("postfix_expression -> postfix_expression '[' expression ']'\n");
    (yyval.X) = createNode ("postfix_expression");
    addChild ((yyval.X), (yyvsp[-3].X));
    addChild ((yyval.X), createNode ("["));
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), createNode ("]"));
}
#line 1657 "defs.tab.c"
    break;

  case 10: /* postfix_expression: postfix_expression '(' ')'  */
#line 176 "defs.y"
{
    // printf ("postfix_expression -> postfix_expression '(' ')'\n");
    (yyval.X) = createNode ("postfix_expression");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode ("("));
    addChild ((yyval.X), createNode (")"));
}
#line 1669 "defs.tab.c"
    break;

  case 11: /* postfix_expression: postfix_expression '(' argument_expression_list ')'  */
#line 184 "defs.y"
{
    //printf ("postfix_expression -> postfix_expression '(' argument_expression_list ')'\n");
    (yyval.X) = createNode ("postfix_expression");
    addChild ((yyval.X), (yyvsp[-3].X));
    addChild ((yyval.X), createNode ("("));
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), createNode (")"));
}
#line 1682 "defs.tab.c"
    break;

  case 12: /* postfix_expression: postfix_expression '.' IDENTIFIER  */
#line 193 "defs.y"
{
    //printf ("postfix_expression -> postfix_expression '.' IDENTIFIER\n");
    (yyval.X) = createNode ("postfix_expression");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode ("."));
    addChild ((yyval.X), createNode ((yyvsp[0].string)));
}
#line 1694 "defs.tab.c"
    break;

  case 13: /* postfix_expression: postfix_expression PTR_OP IDENTIFIER  */
#line 201 "defs.y"
{
   // printf ("postfix_expression -> postfix_expression PTR_OP IDENTIFIER\n");
    (yyval.X) = createNode ("postfix_expression");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode ("->"));
    addChild ((yyval.X), createNode ((yyvsp[0].string)));
}
#line 1706 "defs.tab.c"
    break;

  case 14: /* postfix_expression: postfix_expression INCREMENT  */
#line 209 "defs.y"
{
    //printf ("postfix_expression -> postfix_expression INCREMENT\n");
    (yyval.X) = createNode ("postfix_expression");
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), createNode ("++"));
}
#line 1717 "defs.tab.c"
    break;

  case 15: /* postfix_expression: postfix_expression DECREMENT  */
#line 216 "defs.y"
{
    //printf ("postfix_expression -> postfix_expression DECREMENT\n");
    (yyval.X) = createNode ("postfix_expression");
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), createNode ("--"));
}
#line 1728 "defs.tab.c"
    break;

  case 16: /* postfix_expression: '(' type_name ')' '{' initializer_list '}'  */
#line 223 "defs.y"
{
    //printf ("postfix_expression -> '(' type_name ')' '{' initializer_list '}'\n");
    (yyval.X) = createNode ("postfix_expression");
    addChild ((yyval.X), createNode ("("));
    addChild ((yyval.X), (yyvsp[-4].X));
    addChild ((yyval.X), createNode (")"));
    addChild ((yyval.X), createNode ("{"));
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), createNode ("}"));
}
#line 1743 "defs.tab.c"
    break;

  case 17: /* postfix_expression: '(' type_name ')' '{' initializer_list ',' '}'  */
#line 234 "defs.y"
{
    //printf ("postfix_expression -> '(' type_name ')' '{' initializer_list ',' '}'\n");
    (yyval.X) = createNode ("postfix_expression");
    addChild ((yyval.X), createNode ("("));
    addChild ((yyval.X), (yyvsp[-5].X));
    addChild ((yyval.X), createNode (")"));
    addChild ((yyval.X), createNode ("{"));
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode (","));
    addChild ((yyval.X), createNode ("}"));
}
#line 1759 "defs.tab.c"
    break;

  case 18: /* argument_expression_list: assignment_expression  */
#line 247 "defs.y"
{
    //printf ("argument_expression_list -> assignment_expression\n");
    (yyval.X) = createNode ("argument_expression_list");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 1769 "defs.tab.c"
    break;

  case 19: /* argument_expression_list: argument_expression_list ',' assignment_expression  */
#line 253 "defs.y"
{
    //printf ("argument_expression_list -> argument_expression_list ',' assignment_expression\n");
    (yyval.X) = createNode ("argument_expression_list");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode (","));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 1781 "defs.tab.c"
    break;

  case 20: /* unary_expression: postfix_expression  */
#line 262 "defs.y"
{
    //printf ("unary_expression -> postfix_expression\n");
    (yyval.X) = createNode ("unary_expression");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 1791 "defs.tab.c"
    break;

  case 21: /* unary_expression: INCREMENT unary_expression  */
#line 268 "defs.y"
{
    //printf ("unary_expression -> INCREMENT unary_expression\n");
    (yyval.X) = createNode ("unary_expression");
    addChild ((yyval.X), createNode ("++"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 1802 "defs.tab.c"
    break;

  case 22: /* unary_expression: DECREMENT unary_expression  */
#line 275 "defs.y"
{
    //printf ("unary_expression -> DECREMENT unary_expression\n");
    (yyval.X) = createNode ("unary_expression");
    addChild ((yyval.X), createNode ("--"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 1813 "defs.tab.c"
    break;

  case 23: /* unary_expression: unary_operator cast_expression  */
#line 282 "defs.y"
{
    //printf ("unary_expression -> unary_operator cast_expression\n");
    (yyval.X) = createNode ("unary_expression");
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 1824 "defs.tab.c"
    break;

  case 24: /* unary_expression: SIZEOF unary_expression  */
#line 289 "defs.y"
{
    //printf ("unary_expression -> SIZEOF unary_expression\n");
    (yyval.X) = createNode ("unary_expression");
    addChild ((yyval.X), createNode ("SIZEOF"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 1835 "defs.tab.c"
    break;

  case 25: /* unary_expression: SIZEOF '(' type_name ')'  */
#line 296 "defs.y"
{
    //printf ("unary_expression -> SIZEOF '(' type_name ')'\n");
    (yyval.X) = createNode ("unary_expression");
    addChild ((yyval.X), createNode ("SIZEOF"));
    addChild ((yyval.X), createNode ("("));
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), createNode (")"));
}
#line 1848 "defs.tab.c"
    break;

  case 26: /* unary_operator: '&'  */
#line 306 "defs.y"
{
    //printf ("unary_operator -> '&'\n");
    (yyval.X) = createNode ("&");
}
#line 1857 "defs.tab.c"
    break;

  case 27: /* unary_operator: '*'  */
#line 311 "defs.y"
{
    //printf ("unary_operator -> '*'\n");
    (yyval.X) = createNode ("*");
}
#line 1866 "defs.tab.c"
    break;

  case 28: /* unary_operator: '+'  */
#line 316 "defs.y"
{
    //printf ("unary_operator -> '+'\n");
    (yyval.X) = createNode ("+");
}
#line 1875 "defs.tab.c"
    break;

  case 29: /* unary_operator: '-'  */
#line 321 "defs.y"
{
    //printf ("unary_operator -> '-'\n");
    (yyval.X) = createNode ("-");
}
#line 1884 "defs.tab.c"
    break;

  case 30: /* unary_operator: '~'  */
#line 326 "defs.y"
{
    //printf ("unary_operator -> '~'\n");
    (yyval.X) = createNode ("~");
}
#line 1893 "defs.tab.c"
    break;

  case 31: /* unary_operator: '!'  */
#line 331 "defs.y"
{
    //printf ("unary_operator -> '!'\n");
    (yyval.X) = createNode ("!");
}
#line 1902 "defs.tab.c"
    break;

  case 32: /* cast_expression: unary_expression  */
#line 337 "defs.y"
{
   // printf ("cast_expression -> unary_expression\n");
    (yyval.X) = createNode ("cast_expression");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 1912 "defs.tab.c"
    break;

  case 33: /* cast_expression: '(' type_name ')' cast_expression  */
#line 343 "defs.y"
{
    //printf ("cast_expression -> '(' type_name ')' cast_expression\n");
    (yyval.X) = createNode ("cast_expression");
    addChild ((yyval.X), createNode ("("));
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode (")"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 1925 "defs.tab.c"
    break;

  case 34: /* multiplicative_expression: cast_expression  */
#line 353 "defs.y"
{
    //printf ("multiplicative_expression -> cast_expression\n");
    (yyval.X) = createNode ("multiplicative_expression");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 1935 "defs.tab.c"
    break;

  case 35: /* multiplicative_expression: multiplicative_expression '*' cast_expression  */
#line 359 "defs.y"
{
   // printf ("multiplicative_expression -> multiplicative_expression '*' cast_expression\n");
    (yyval.X) = createNode ("multiplicative_expression");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode ("*"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 1947 "defs.tab.c"
    break;

  case 36: /* multiplicative_expression: multiplicative_expression '/' cast_expression  */
#line 367 "defs.y"
{
   // printf ("multiplicative_expression -> multiplicative_expression '/' cast_expression\n");
    (yyval.X) = createNode ("multiplicative_expression");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode ("/"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 1959 "defs.tab.c"
    break;

  case 37: /* multiplicative_expression: multiplicative_expression '%' cast_expression  */
#line 375 "defs.y"
{
   // printf ("multiplicative_expression -> multiplicative_expression '%%' cast_expression\n");
    (yyval.X) = createNode ("multiplicative_expression");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode ("%"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 1971 "defs.tab.c"
    break;

  case 38: /* additive_expression: multiplicative_expression  */
#line 384 "defs.y"
{
    //printf ("additive_expression -> multiplicative_expression\n");
    (yyval.X) = createNode ("additive_expression");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 1981 "defs.tab.c"
    break;

  case 39: /* additive_expression: additive_expression '+' multiplicative_expression  */
#line 390 "defs.y"
{
    //printf ("additive_expression -> additive_expression '+' multiplicative_expression\n");
    (yyval.X) = createNode ("additive_expression");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode ("+"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 1993 "defs.tab.c"
    break;

  case 40: /* additive_expression: additive_expression '-' multiplicative_expression  */
#line 398 "defs.y"
{
    //printf ("additive_expression -> additive_expression '-' multiplicative_expression\n");
    (yyval.X) = createNode ("additive_expression");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode ("-"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2005 "defs.tab.c"
    break;

  case 41: /* shift_expression: additive_expression  */
#line 407 "defs.y"
{
    //printf ("shift_expression -> additive_expression\n");
    (yyval.X) = createNode ("shift_expression");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2015 "defs.tab.c"
    break;

  case 42: /* shift_expression: shift_expression LSHIFT additive_expression  */
#line 413 "defs.y"
{
    //printf ("shift_expression -> shift_expression LSHIFT additive_expression\n");
    (yyval.X) = createNode ("shift_expression");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode ("<<"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2027 "defs.tab.c"
    break;

  case 43: /* shift_expression: shift_expression RSHIFT additive_expression  */
#line 421 "defs.y"
{
    //printf ("shift_expression -> shift_expression RSHIFT additive_expression\n");
    (yyval.X) = createNode ("shift_expression");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode (">>"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2039 "defs.tab.c"
    break;

  case 44: /* relational_expression: shift_expression  */
#line 430 "defs.y"
{   //printf ("relational_expression -> shift_expression\n"); 
    (yyval.X) = createNode ("relational_expression");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2048 "defs.tab.c"
    break;

  case 45: /* relational_expression: relational_expression '<' shift_expression  */
#line 435 "defs.y"
{
    //printf ("relational_expression -> relational_expression '<' shift_expression\n");
    (yyval.X) = createNode ("relational_expression");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode ("<"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2060 "defs.tab.c"
    break;

  case 46: /* relational_expression: relational_expression '>' shift_expression  */
#line 443 "defs.y"
{
    //printf ("relational_expression -> relational_expression '>' shift_expression\n");
    (yyval.X) = createNode ("relational_expression");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode (">"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2072 "defs.tab.c"
    break;

  case 47: /* relational_expression: relational_expression LE_OP shift_expression  */
#line 451 "defs.y"
{
    //printf ("relational_expression -> relational_expression LE_OP shift_expression\n");
    (yyval.X) = createNode ("relational_expression");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode ("<="));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2084 "defs.tab.c"
    break;

  case 48: /* relational_expression: relational_expression GE_OP shift_expression  */
#line 459 "defs.y"
{
    //printf ("relational_expression -> relational_expression GE_OP shift_expression\n");
    (yyval.X) = createNode ("relational_expression");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode (">="));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2096 "defs.tab.c"
    break;

  case 49: /* equality_expression: relational_expression  */
#line 468 "defs.y"
{
    //printf ("equality_expression -> relational_expression\n");
    (yyval.X) = createNode ("equality_expression");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2106 "defs.tab.c"
    break;

  case 50: /* equality_expression: equality_expression EQ_OP relational_expression  */
#line 474 "defs.y"
{
    //printf ("equality_expression -> equality_expression EQ_OP relational_expression\n");
    (yyval.X) = createNode ("equality_expression");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode ("=="));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2118 "defs.tab.c"
    break;

  case 51: /* equality_expression: equality_expression NE_OP relational_expression  */
#line 482 "defs.y"
{
    //printf ("equality_expression -> equality_expression NE_OP relational_expression\n");
    (yyval.X) = createNode ("equality_expression");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode ("!="));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2130 "defs.tab.c"
    break;

  case 52: /* AND_expression: equality_expression  */
#line 491 "defs.y"
{
    //printf ("AND_expression -> equality_expression\n");
    (yyval.X) = createNode ("AND_expression");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2140 "defs.tab.c"
    break;

  case 53: /* AND_expression: AND_expression '&' equality_expression  */
#line 497 "defs.y"
{
    //printf ("AND_expression -> AND_expression '&' equality_expression\n");
    (yyval.X) = createNode ("AND_expression");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode ("&"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2152 "defs.tab.c"
    break;

  case 54: /* exclusive_OR_expression: AND_expression  */
#line 506 "defs.y"
{
    //printf ("exclusive_OR_expression -> AND_expression\n");
    (yyval.X) = createNode ("exclusive_OR_expression");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2162 "defs.tab.c"
    break;

  case 55: /* exclusive_OR_expression: exclusive_OR_expression '^' AND_expression  */
#line 512 "defs.y"
{
    //printf ("exclusive_OR_expression -> exclusive_OR_expression '^' AND_expression\n");
    (yyval.X) = createNode ("exclusive_OR_expression");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode ("^"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2174 "defs.tab.c"
    break;

  case 56: /* inclusive_OR_expression: exclusive_OR_expression  */
#line 521 "defs.y"
{
    //printf ("inclusive_OR_expression -> exclusive_OR_expression\n");
    (yyval.X) = createNode ("inclusive_OR_expression");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2184 "defs.tab.c"
    break;

  case 57: /* inclusive_OR_expression: inclusive_OR_expression '|' exclusive_OR_expression  */
#line 527 "defs.y"
{
    //printf ("inclusive_OR_expression -> inclusive_OR_expression '|' exclusive_OR_expression\n");
    (yyval.X) = createNode ("inclusive_OR_expression");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode ("|"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2196 "defs.tab.c"
    break;

  case 58: /* logical_AND_expression: inclusive_OR_expression  */
#line 536 "defs.y"
{
    //printf ("logical_AND_expression -> inclusive_OR_expression\n");
    (yyval.X) = createNode ("logical_AND_expression");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2206 "defs.tab.c"
    break;

  case 59: /* logical_AND_expression: logical_AND_expression BINARY_AND inclusive_OR_expression  */
#line 542 "defs.y"
{
    //printf ("logical_AND_expression -> logical_AND_expression BINARY_AND inclusive_OR_expression\n");
    (yyval.X) = createNode ("logical_AND_expression");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode ("&&"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2218 "defs.tab.c"
    break;

  case 60: /* logical_OR_expression: logical_AND_expression  */
#line 551 "defs.y"
{
    //printf ("logical_OR_expression -> logical_AND_expression\n");
    (yyval.X) = createNode ("logical_OR_expression");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2228 "defs.tab.c"
    break;

  case 61: /* logical_OR_expression: logical_OR_expression BINARY_OR logical_AND_expression  */
#line 557 "defs.y"
{
    //printf ("logical_OR_expression -> logical_OR_expression BINARY_OR logical_AND_expression\n");
    (yyval.X) = createNode ("logical_OR_expression");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode ("||"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2240 "defs.tab.c"
    break;

  case 62: /* conditional_expression: logical_OR_expression  */
#line 566 "defs.y"
{
    //printf ("conditional_expression -> logical_OR_expression\n");
    (yyval.X) = createNode ("conditional_expression");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2250 "defs.tab.c"
    break;

  case 63: /* conditional_expression: logical_OR_expression '?' expression ':' conditional_expression  */
#line 572 "defs.y"
{
    //printf ("conditional_expression -> logical_OR_expression '?' expression ':' conditional_expression\n");
    (yyval.X) = createNode ("conditional_expression");
    addChild ((yyval.X), (yyvsp[-4].X));
    addChild ((yyval.X), createNode ("?"));
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode (":"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2264 "defs.tab.c"
    break;

  case 64: /* assignment_expression: conditional_expression  */
#line 583 "defs.y"
{
    //printf ("assignment_expression -> conditional_expression\n");
    (yyval.X) = createNode ("assignment_expression");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2274 "defs.tab.c"
    break;

  case 65: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 589 "defs.y"
{
    //printf ("assignment_expression -> unary_expression assignment_operator assignment_expression\n");
    (yyval.X) = createNode ("assignment_expression");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2286 "defs.tab.c"
    break;

  case 66: /* assignment_expression_optional: assignment_expression  */
#line 598 "defs.y"
{
    //printf ("assignment_expression_optional -> assignment_expression\n");
    (yyval.X) = createNode ("assignment_expression_optional");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2296 "defs.tab.c"
    break;

  case 67: /* assignment_expression_optional: %empty  */
#line 604 "defs.y"
{
    //printf ("assignment_expression_optional -> ε\n");
    (yyval.X) = createNode ("assignment_expression_optional");
    addChild ((yyval.X), createNode ("ε"));
}
#line 2306 "defs.tab.c"
    break;

  case 68: /* assignment_operator: '='  */
#line 611 "defs.y"
{
    //printf ("assignment_operator -> '='\n");
    (yyval.X) = createNode ("OP(=)");
}
#line 2315 "defs.tab.c"
    break;

  case 69: /* assignment_operator: MUL_ASSIGN  */
#line 616 "defs.y"
{
    //printf ("assignment_operator -> MUL_ASSIGN\n");
    (yyval.X) = createNode ("OP(*=)");
}
#line 2324 "defs.tab.c"
    break;

  case 70: /* assignment_operator: DIV_ASSIGN  */
#line 621 "defs.y"
{
    //printf ("assignment_operator -> DIV_ASSIGN\n");
    (yyval.X) = createNode ("OP(/=)");
}
#line 2333 "defs.tab.c"
    break;

  case 71: /* assignment_operator: MOD_ASSIGN  */
#line 626 "defs.y"
{
    //printf ("assignment_operator -> MOD_ASSIGN\n");
    (yyval.X) = createNode ("OP(%=)");
}
#line 2342 "defs.tab.c"
    break;

  case 72: /* assignment_operator: ADD_ASSIGN  */
#line 631 "defs.y"
{
    //printf ("assignment_operator -> ADD_ASSIGN\n");
    (yyval.X) = createNode ("OP(+=)");
}
#line 2351 "defs.tab.c"
    break;

  case 73: /* assignment_operator: SUB_ASSIGN  */
#line 636 "defs.y"
{
    //printf ("assignment_operator -> SUB_ASSIGN\n");
    (yyval.X) = createNode ("OP(-=)");
}
#line 2360 "defs.tab.c"
    break;

  case 74: /* assignment_operator: LEFT_ASSIGN  */
#line 641 "defs.y"
{
    //printf ("assignment_operator -> LEFT_ASSIGN\n");
    (yyval.X) = createNode ("OP(<<=)");
}
#line 2369 "defs.tab.c"
    break;

  case 75: /* assignment_operator: RIGHT_ASSIGN  */
#line 646 "defs.y"
{
    //printf ("assignment_operator -> RIGHT_ASSIGN\n");
    (yyval.X) = createNode ("OP(>>=)");
}
#line 2378 "defs.tab.c"
    break;

  case 76: /* assignment_operator: AND_ASSIGN  */
#line 651 "defs.y"
{
    //printf ("assignment_operator -> AND_ASSIGN\n");
    (yyval.X) = createNode ("OP(&=)");
}
#line 2387 "defs.tab.c"
    break;

  case 77: /* assignment_operator: XOR_ASSIGN  */
#line 656 "defs.y"
{
    //printf ("assignment_operator -> XOR_ASSIGN\n");
    (yyval.X) = createNode ("OP(^=)");
}
#line 2396 "defs.tab.c"
    break;

  case 78: /* assignment_operator: OR_ASSIGN  */
#line 661 "defs.y"
{
    //printf ("assignment_operator -> OR_ASSIGN\n");
    (yyval.X) = createNode ("OP(|=)");
}
#line 2405 "defs.tab.c"
    break;

  case 79: /* expression: assignment_expression  */
#line 667 "defs.y"
{
    //printf ("expression -> assignment_expression\n");
    (yyval.X) = createNode ("expression");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2415 "defs.tab.c"
    break;

  case 80: /* expression: expression ',' assignment_expression  */
#line 673 "defs.y"
{
    //printf ("expression -> expression ',' assignment_expression\n");
    (yyval.X) = createNode ("expression");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode (","));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2427 "defs.tab.c"
    break;

  case 81: /* expression_optional: expression  */
#line 682 "defs.y"
{
    //printf ("expression_optional -> expression\n");
    (yyval.X) = createNode ("expression_optional");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2437 "defs.tab.c"
    break;

  case 82: /* expression_optional: %empty  */
#line 688 "defs.y"
{
    //printf ("expression_optional -> ε\n");
    (yyval.X) = createNode ("expression_optional");
    addChild ((yyval.X), createNode ("ε"));
}
#line 2447 "defs.tab.c"
    break;

  case 83: /* constant_expression: conditional_expression  */
#line 695 "defs.y"
{
    //printf ("constant_expression -> conditional_expression\n");
    (yyval.X) = createNode ("constant_expression");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2457 "defs.tab.c"
    break;

  case 84: /* declaration: declaration_specifiers ';'  */
#line 703 "defs.y"
{
    //printf ("declaration -> declaration_specifiers ';'\n");
    (yyval.X) = createNode ("declaration");
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), createNode (";"));
}
#line 2468 "defs.tab.c"
    break;

  case 85: /* declaration: declaration_specifiers init_declarator_list ';'  */
#line 710 "defs.y"
{
    //printf ("declaration -> declaration_specifiers init_declarator_list ';'\n");
    (yyval.X) = createNode ("declaration");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), createNode (";"));
}
#line 2480 "defs.tab.c"
    break;

  case 86: /* declaration_specifiers: storage_class_specifier  */
#line 719 "defs.y"
{
    //printf ("declaration_specifiers -> storage_class_specifier\n");
    (yyval.X) = createNode ("declaration_specifiers");
    addChild ((yyval.X), (yyvsp[0].X));

}
#line 2491 "defs.tab.c"
    break;

  case 87: /* declaration_specifiers: storage_class_specifier declaration_specifiers  */
#line 726 "defs.y"
{
    //printf ("declaration_specifiers -> storage_class_specifier declaration_specifiers\n");
    (yyval.X) = createNode ("declaration_specifiers");
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2502 "defs.tab.c"
    break;

  case 88: /* declaration_specifiers: type_specifier  */
#line 733 "defs.y"
{
    //printf ("declaration_specifiers -> type_specifier\n");
    (yyval.X) = createNode ("declaration_specifiers");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2512 "defs.tab.c"
    break;

  case 89: /* declaration_specifiers: type_specifier declaration_specifiers  */
#line 739 "defs.y"
{
    //printf ("declaration_specifiers -> type_specifier declaration_specifiers\n");
    (yyval.X) = createNode ("declaration_specifiers");
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2523 "defs.tab.c"
    break;

  case 90: /* declaration_specifiers: type_qualifier  */
#line 746 "defs.y"
{
    //printf ("declaration_specifiers -> type_qualifier\n");
    (yyval.X) = createNode ("declaration_specifiers");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2533 "defs.tab.c"
    break;

  case 91: /* declaration_specifiers: type_qualifier declaration_specifiers  */
#line 752 "defs.y"
{
    //printf ("declaration_specifiers -> type_qualifier declaration_specifiers\n");
    (yyval.X) = createNode ("declaration_specifiers");
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2544 "defs.tab.c"
    break;

  case 92: /* declaration_specifiers: function_specifier  */
#line 759 "defs.y"
{
    //printf ("declaration_specifiers -> function_specifier\n");
    (yyval.X) = createNode ("declaration_specifiers");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2554 "defs.tab.c"
    break;

  case 93: /* declaration_specifiers: function_specifier declaration_specifiers  */
#line 765 "defs.y"
{
    //printf ("declaration_specifiers -> function_specifier declaration_specifiers\n");
    (yyval.X) = createNode ("declaration_specifiers");
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2565 "defs.tab.c"
    break;

  case 94: /* init_declarator_list: init_declarator  */
#line 773 "defs.y"
{
    //printf ("init_declarator_list -> init_declarator\n");
    (yyval.X) = createNode ("init_declarator_list");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2575 "defs.tab.c"
    break;

  case 95: /* init_declarator_list: init_declarator_list ',' init_declarator  */
#line 779 "defs.y"
{
    //printf ("init_declarator_list -> init_declarator_list ',' init_declarator\n");
    (yyval.X) = createNode ("init_declarator_list");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode (","));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2587 "defs.tab.c"
    break;

  case 96: /* init_declarator: declarator  */
#line 788 "defs.y"
{
    //printf ("init_declarator -> declarator\n");
    (yyval.X) = createNode ("init_declarator");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2597 "defs.tab.c"
    break;

  case 97: /* init_declarator: declarator '=' initializer  */
#line 794 "defs.y"
{
    //printf ("init_declarator -> declarator '=' initializer\n");
    (yyval.X) = createNode ("init_declarator");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode ("="));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2609 "defs.tab.c"
    break;

  case 98: /* storage_class_specifier: EXTERN  */
#line 803 "defs.y"
{
    //printf ("storage_class_specifier -> EXTERN\n");
    (yyval.X) = createNode ("storage_class_specifier");
    addChild ((yyval.X), createNode ("EXTERN"));
}
#line 2619 "defs.tab.c"
    break;

  case 99: /* storage_class_specifier: STATIC  */
#line 809 "defs.y"
{
    //printf ("storage_class_specifier -> STATIC\n");
    (yyval.X) = createNode ("storage_class_specifier");
    addChild ((yyval.X), createNode ("STATIC"));
}
#line 2629 "defs.tab.c"
    break;

  case 100: /* storage_class_specifier: AUTO  */
#line 815 "defs.y"
{
    //printf ("storage_class_specifier -> AUTO\n");
    (yyval.X) = createNode ("storage_class_specifier");
    addChild ((yyval.X), createNode ("AUTO"));
}
#line 2639 "defs.tab.c"
    break;

  case 101: /* storage_class_specifier: REGISTER  */
#line 821 "defs.y"
{
   // printf ("storage_class_specifier -> REGISTER\n");
    (yyval.X) = createNode ("storage_class_specifier");
    addChild ((yyval.X), createNode ("REGISTER"));
}
#line 2649 "defs.tab.c"
    break;

  case 102: /* type_specifier: VOID  */
#line 828 "defs.y"
{
    //printf ("type_specifier -> VOID\n");
    (yyval.X) = createNode ("type_specifier");
    addChild ((yyval.X), createNode ("VOID"));
}
#line 2659 "defs.tab.c"
    break;

  case 103: /* type_specifier: CHAR  */
#line 834 "defs.y"
{
    //printf ("type_specifier -> CHAR\n");
    (yyval.X) = createNode ("type_specifier");
    addChild ((yyval.X), createNode ("CHAR"));
}
#line 2669 "defs.tab.c"
    break;

  case 104: /* type_specifier: SHORT  */
#line 840 "defs.y"
{
    //printf ("type_specifier -> SHORT\n");
    (yyval.X) = createNode ("type_specifier");
    addChild ((yyval.X), createNode ("SHORT"));
}
#line 2679 "defs.tab.c"
    break;

  case 105: /* type_specifier: INT  */
#line 846 "defs.y"
{
    //printf ("type_specifier -> INT\n");
    (yyval.X) = createNode ("type_specifier");
    addChild ((yyval.X), createNode ("INT"));
}
#line 2689 "defs.tab.c"
    break;

  case 106: /* type_specifier: LONG  */
#line 852 "defs.y"
{
    //printf ("type_specifier -> LONG\n");
    (yyval.X) = createNode ("type_specifier");
    addChild ((yyval.X), createNode ("LONG"));
}
#line 2699 "defs.tab.c"
    break;

  case 107: /* type_specifier: FLOAT  */
#line 858 "defs.y"
{
    //printf ("type_specifier -> FLOAT\n");
    (yyval.X) = createNode ("type_specifier");
    addChild ((yyval.X), createNode ("FLOAT"));
}
#line 2709 "defs.tab.c"
    break;

  case 108: /* type_specifier: DOUBLE  */
#line 864 "defs.y"
{
    //printf ("type_specifier -> DOUBLE\n");
    (yyval.X) = createNode ("type_specifier");
    addChild ((yyval.X), createNode ("DOUBLE"));
}
#line 2719 "defs.tab.c"
    break;

  case 109: /* type_specifier: SIGNED  */
#line 870 "defs.y"
{
    //printf ("type_specifier -> SIGNED\n");
    (yyval.X) = createNode ("type_specifier");
    addChild ((yyval.X), createNode ("SIGNED"));
}
#line 2729 "defs.tab.c"
    break;

  case 110: /* type_specifier: UNSIGNED  */
#line 876 "defs.y"
{
    //printf ("type_specifier -> UNSIGNED\n");
    (yyval.X) = createNode ("type_specifier");
    addChild ((yyval.X), createNode ("UNSIGNED"));
}
#line 2739 "defs.tab.c"
    break;

  case 111: /* type_specifier: BOOL  */
#line 882 "defs.y"
{
    //printf ("type_specifier -> BOOL\n");
    (yyval.X) = createNode ("type_specifier");
    addChild ((yyval.X), createNode ("BOOL"));
}
#line 2749 "defs.tab.c"
    break;

  case 112: /* type_specifier: IMAGINARY  */
#line 888 "defs.y"
{
    //printf ("type_specifier -> IMAGINARY\n");
    (yyval.X) = createNode ("type_specifier");
    addChild ((yyval.X), createNode ("IMAGINARY"));
}
#line 2759 "defs.tab.c"
    break;

  case 113: /* type_specifier: COMPLEX  */
#line 894 "defs.y"
{
    //printf ("type_specifier -> COMPLEX\n");
    (yyval.X) = createNode ("type_specifier");
    addChild ((yyval.X), createNode ("COMPLEX"));
}
#line 2769 "defs.tab.c"
    break;

  case 114: /* specifier_qualifier_list: type_specifier  */
#line 901 "defs.y"
{
    //printf ("specifier_qualifier_list -> type_specifier\n");
    (yyval.X) = createNode ("specifier_qualifier_list");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2779 "defs.tab.c"
    break;

  case 115: /* specifier_qualifier_list: type_specifier specifier_qualifier_list  */
#line 907 "defs.y"
{
    //printf ("specifier_qualifier_list -> type_specifier specifier_qualifier_list\n");
    (yyval.X) = createNode ("specifier_qualifier_list");
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2790 "defs.tab.c"
    break;

  case 116: /* specifier_qualifier_list: type_qualifier  */
#line 914 "defs.y"
{
    //printf ("specifier_qualifier_list -> type_qualifier\n");
    (yyval.X) = createNode ("specifier_qualifier_list");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2800 "defs.tab.c"
    break;

  case 117: /* specifier_qualifier_list: type_qualifier specifier_qualifier_list  */
#line 920 "defs.y"
{
    //printf ("specifier_qualifier_list -> type_qualifier specifier_qualifier_list\n");
    (yyval.X) = createNode ("specifier_qualifier_list");
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2811 "defs.tab.c"
    break;

  case 118: /* type_qualifier: CONST  */
#line 928 "defs.y"
{
    //printf ("type_qualifier -> CONST\n");
    (yyval.X) = createNode ("type_qualifier");
    addChild ((yyval.X), createNode ("CONST"));
}
#line 2821 "defs.tab.c"
    break;

  case 119: /* type_qualifier: RESTRICT  */
#line 934 "defs.y"
{
    //printf ("type_qualifier -> RESTRICT\n");
    (yyval.X) = createNode ("type_qualifier");
    addChild ((yyval.X), createNode ("RESTRICT"));
}
#line 2831 "defs.tab.c"
    break;

  case 120: /* type_qualifier: VOLATILE  */
#line 940 "defs.y"
{
    //printf ("type_qualifier -> VOLATILE\n");
    (yyval.X) = createNode ("type_qualifier");
    addChild ((yyval.X), createNode ("VOLATILE"));
}
#line 2841 "defs.tab.c"
    break;

  case 121: /* function_specifier: INLINE  */
#line 947 "defs.y"
{
    //printf ("function_specifier -> INLINE\n");
    (yyval.X) = createNode ("function_specifier");
    addChild ((yyval.X), createNode ("INLINE"));
}
#line 2851 "defs.tab.c"
    break;

  case 122: /* declarator: pointer direct_declarator  */
#line 954 "defs.y"
{
    //printf ("declarator -> pointer direct_declarator\n");
    (yyval.X) = createNode ("declarator");
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2862 "defs.tab.c"
    break;

  case 123: /* declarator: direct_declarator  */
#line 961 "defs.y"
{
    //printf ("declarator -> direct_declarator\n");
    (yyval.X) = createNode ("declarator");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2872 "defs.tab.c"
    break;

  case 124: /* direct_declarator: IDENTIFIER  */
#line 968 "defs.y"
{
    //printf ("direct_declarator -> IDENTIFIER\n");
    (yyval.X) = createNode ("direct_declarator");
    addChild ((yyval.X), createNode ((yyvsp[0].string)));
}
#line 2882 "defs.tab.c"
    break;

  case 125: /* direct_declarator: '(' declarator ')'  */
#line 974 "defs.y"
{
    //printf ("direct_declarator -> '(' declarator ')'\n");
    (yyval.X) = createNode ("direct_declarator");
    addChild ((yyval.X), createNode ("("));
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), createNode (")"));
}
#line 2894 "defs.tab.c"
    break;

  case 126: /* direct_declarator: direct_declarator '[' type_qualifier_list_optional assignment_expression_optional ']'  */
#line 982 "defs.y"
{
    //printf ("direct_declarator -> direct_declarator '[' type_qualifier_list_optional assignment_expression_optional']'\n");
    (yyval.X) = createNode ("direct_declarator");
    addChild ((yyval.X), (yyvsp[-4].X));
    addChild ((yyval.X), createNode ("["));
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), createNode ("]"));
}
#line 2908 "defs.tab.c"
    break;

  case 127: /* direct_declarator: direct_declarator '[' STATIC type_qualifier_list_optional assignment_expression ']'  */
#line 993 "defs.y"
{
    //printf ("direct_declarator -> direct_declarator '[' STATIC type_qualifier_list_optional assignment_expression ']'\n");
    (yyval.X) = createNode ("direct_declarator");
    addChild ((yyval.X), (yyvsp[-5].X));
    addChild ((yyval.X), createNode ("["));
    addChild ((yyval.X), createNode ("STATIC"));
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), createNode ("]"));
}
#line 2923 "defs.tab.c"
    break;

  case 128: /* direct_declarator: direct_declarator '[' type_qualifier_list STATIC assignment_expression ']'  */
#line 1004 "defs.y"
{
    //printf ("direct_declarator -> direct_declarator '[' type_qualifier_list STATIC assignment_expression ']'\n");
    (yyval.X) = createNode ("direct_declarator");
    addChild ((yyval.X), (yyvsp[-5].X));
    addChild ((yyval.X), createNode ("["));
    addChild ((yyval.X), (yyvsp[-3].X));
    addChild ((yyval.X), createNode ("STATIC"));
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), createNode ("]"));
}
#line 2938 "defs.tab.c"
    break;

  case 129: /* direct_declarator: direct_declarator '[' type_qualifier_list_optional '*' ']'  */
#line 1015 "defs.y"
{
    //printf ("direct_declarator -> direct_declarator '[' type_qualifier_list_optional '*' ']'\n");
    (yyval.X) = createNode ("direct_declarator");
    addChild ((yyval.X), (yyvsp[-4].X));
    addChild ((yyval.X), createNode ("["));
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode ("*"));
    addChild ((yyval.X), createNode ("]"));
}
#line 2952 "defs.tab.c"
    break;

  case 130: /* direct_declarator: direct_declarator '(' parameter_type_list ')'  */
#line 1025 "defs.y"
{
    //printf ("direct_declarator -> direct_declarator '(' parameter_type_list ')'\n");
    (yyval.X) = createNode ("direct_declarator");
    addChild ((yyval.X), (yyvsp[-3].X));
    addChild ((yyval.X), createNode ("("));
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), createNode (")"));
}
#line 2965 "defs.tab.c"
    break;

  case 131: /* direct_declarator: direct_declarator '(' identifier_list_optional ')'  */
#line 1034 "defs.y"
{
    //printf ("direct_declarator -> direct_declarator '(' identifier_list_optional ')'\n");
    (yyval.X) = createNode ("direct_declarator");
    addChild ((yyval.X), (yyvsp[-3].X));
    addChild ((yyval.X), createNode ("("));
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), createNode (")"));
}
#line 2978 "defs.tab.c"
    break;

  case 132: /* pointer: '*' type_qualifier_list_optional  */
#line 1044 "defs.y"
{
    //printf ("pointer -> '*' type_qualifier_list_optional\n");
    (yyval.X) = createNode ("pointer");
    addChild ((yyval.X), createNode ("*"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 2989 "defs.tab.c"
    break;

  case 133: /* pointer: '*' type_qualifier_list_optional pointer  */
#line 1051 "defs.y"
{
    //printf ("pointer -> '*' type_qualifier_list_optional pointer\n");
    (yyval.X) = createNode ("pointer");
    addChild ((yyval.X), createNode ("*"));
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3001 "defs.tab.c"
    break;

  case 134: /* type_qualifier_list: type_qualifier  */
#line 1060 "defs.y"
{
    //printf ("type_qualifier_list -> type_qualifier\n");
    (yyval.X) = createNode ("type_qualifier_list");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3011 "defs.tab.c"
    break;

  case 135: /* type_qualifier_list: type_qualifier_list type_qualifier  */
#line 1066 "defs.y"
{
    //printf ("type_qualifier_list -> type_qualifier_list type_qualifier\n");
    (yyval.X) = createNode ("type_qualifier_list");
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3022 "defs.tab.c"
    break;

  case 136: /* type_qualifier_list_optional: type_qualifier_list  */
#line 1074 "defs.y"
{
    //printf ("type_qualifier_list_optional -> type_qualifier_list\n");
    (yyval.X) = createNode ("type_qualifier_list_optional");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3032 "defs.tab.c"
    break;

  case 137: /* type_qualifier_list_optional: %empty  */
#line 1080 "defs.y"
{
    //printf ("type_qualifier_list_optional -> ε\n");
    (yyval.X) = createNode ("type_qualifier_list_optional");
    addChild ((yyval.X), createNode ("ε"));
}
#line 3042 "defs.tab.c"
    break;

  case 138: /* parameter_type_list: parameter_list  */
#line 1087 "defs.y"
{   //printf ("parameter_type_list -> parameter_list\n"); 
    (yyval.X) = createNode ("parameter_type_list");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3051 "defs.tab.c"
    break;

  case 139: /* parameter_type_list: parameter_list ',' ELLIPSIS  */
#line 1092 "defs.y"
{   //printf ("parameter_type_list -> parameter_list ',' ELLIPSIS\n"); 
    (yyval.X) = createNode ("parameter_type_list");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode (","));
    addChild ((yyval.X), createNode ("..."));
}
#line 3062 "defs.tab.c"
    break;

  case 140: /* parameter_list: parameter_declaration  */
#line 1100 "defs.y"
{
    //printf ("parameter_list -> parameter_declaration\n");
    (yyval.X) = createNode ("parameter_list");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3072 "defs.tab.c"
    break;

  case 141: /* parameter_list: parameter_list ',' parameter_declaration  */
#line 1106 "defs.y"
{
    //printf ("parameter_list -> parameter_list ',' parameter_declaration\n");
    (yyval.X) = createNode ("parameter_list");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode (","));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3084 "defs.tab.c"
    break;

  case 142: /* parameter_declaration: declaration_specifiers declarator  */
#line 1115 "defs.y"
{
    //printf ("parameter_declaration -> declaration_specifiers declarator\n");
    (yyval.X) = createNode ("parameter_declaration");
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3095 "defs.tab.c"
    break;

  case 143: /* parameter_declaration: declaration_specifiers  */
#line 1122 "defs.y"
{
    //printf ("parameter_declaration -> declaration_specifiers\n");
    (yyval.X) = createNode ("parameter_declaration");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3105 "defs.tab.c"
    break;

  case 144: /* identifier_list: IDENTIFIER  */
#line 1129 "defs.y"
{
    //printf ("identifier_list -> IDENTIFIER\n");
    (yyval.X) = createNode ("identifier_list");
    addChild ((yyval.X), createNode ((yyvsp[0].string)));
}
#line 3115 "defs.tab.c"
    break;

  case 145: /* identifier_list: identifier_list ',' IDENTIFIER  */
#line 1135 "defs.y"
{
    //printf ("identifier_list -> identifier_list ',' IDENTIFIER\n");
    (yyval.X) = createNode ("identifier_list");
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode (","));
    addChild ((yyval.X), createNode ((yyvsp[0].string)));
}
#line 3127 "defs.tab.c"
    break;

  case 146: /* identifier_list_optional: identifier_list  */
#line 1144 "defs.y"
{
    //printf ("identifier_list_optional -> identifier_list\n");
    (yyval.X) = createNode ("identifier_list_optional");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3137 "defs.tab.c"
    break;

  case 147: /* identifier_list_optional: %empty  */
#line 1150 "defs.y"
{
    //printf ("identifier_list_optional -> ε\n");
    (yyval.X) = createNode ("identifier_list_optional");
    addChild ((yyval.X), createNode ("ε"));
}
#line 3147 "defs.tab.c"
    break;

  case 148: /* type_name: specifier_qualifier_list  */
#line 1157 "defs.y"
{
    //printf ("type_name -> specifier_qualifier_list\n");
    (yyval.X) = createNode ("type_name");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3157 "defs.tab.c"
    break;

  case 149: /* initializer: assignment_expression  */
#line 1164 "defs.y"
{
    //printf ("initializer -> assignment_expression\n");
    (yyval.X) = createNode ("initializer");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3167 "defs.tab.c"
    break;

  case 150: /* initializer: '{' initializer_list '}'  */
#line 1170 "defs.y"
{
    //printf ("initializer -> '{' initializer_list '}'\n");
    (yyval.X) = createNode ("initializer");
    addChild ((yyval.X), createNode ("{"));
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), createNode ("}"));
}
#line 3179 "defs.tab.c"
    break;

  case 151: /* initializer: '{' initializer_list ',' '}'  */
#line 1178 "defs.y"
{
    //printf ("initializer -> '{' initializer_list ',' '}'\n");
    (yyval.X) = createNode ("initializer");
    addChild ((yyval.X), createNode ("{"));
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode (","));
    addChild ((yyval.X), createNode ("}"));
}
#line 3192 "defs.tab.c"
    break;

  case 152: /* initializer_list: designation_optional initializer  */
#line 1188 "defs.y"
{
    //printf ("initializer_list -> designation_optional initializer\n");
    (yyval.X) = createNode ("initializer_list");
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3203 "defs.tab.c"
    break;

  case 153: /* initializer_list: initializer_list ',' designation_optional initializer  */
#line 1195 "defs.y"
{
    //printf ("initializer_list -> initializer_list ',' designation_optional initializer\n");
    (yyval.X) = createNode ("initializer_list");
    addChild ((yyval.X), (yyvsp[-3].X));
    addChild ((yyval.X), createNode (","));
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3216 "defs.tab.c"
    break;

  case 154: /* designation: designator_list '='  */
#line 1205 "defs.y"
{
    //printf ("designation -> designator_list '='\n");
    (yyval.X) = createNode ("designation");
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), createNode ("="));
}
#line 3227 "defs.tab.c"
    break;

  case 155: /* designation_optional: designation  */
#line 1213 "defs.y"
{
    //printf ("designation_optional -> designation\n");
    (yyval.X) = createNode ("designation_optional");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3237 "defs.tab.c"
    break;

  case 156: /* designation_optional: %empty  */
#line 1219 "defs.y"
{
    //printf ("designation_optional -> ε\n");
    (yyval.X) = createNode ("designation_optional");
    addChild ((yyval.X), createNode ("ε"));
}
#line 3247 "defs.tab.c"
    break;

  case 157: /* designator_list: designator  */
#line 1226 "defs.y"
{
    //printf ("designator_list -> designator\n");
    (yyval.X) = createNode ("designator_list");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3257 "defs.tab.c"
    break;

  case 158: /* designator_list: designator_list designator  */
#line 1232 "defs.y"
{
    //printf ("designator_list -> designator_list designator\n");
    (yyval.X) = createNode ("designator_list");
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3268 "defs.tab.c"
    break;

  case 159: /* designator: '[' constant_expression ']'  */
#line 1240 "defs.y"
{
    //printf ("designator -> '[' constant_expression ']'\n");
    (yyval.X) = createNode ("designator");
    addChild ((yyval.X), createNode ("["));
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), createNode ("]"));
}
#line 3280 "defs.tab.c"
    break;

  case 160: /* designator: '.' IDENTIFIER  */
#line 1248 "defs.y"
{
    //printf ("designator -> '.' IDENTIFIER\n");
    (yyval.X) = createNode ("designator");
    addChild ((yyval.X), createNode ("."));
    addChild ((yyval.X), createNode ((yyvsp[0].string)));
}
#line 3291 "defs.tab.c"
    break;

  case 161: /* statement: labeled_statement  */
#line 1257 "defs.y"
{
    //printf ("statement -> labeled_statement\n");
    (yyval.X) = createNode ("statement");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3301 "defs.tab.c"
    break;

  case 162: /* statement: compound_statement  */
#line 1263 "defs.y"
{
    //printf ("statement -> compound_statement\n");
    (yyval.X) = createNode ("statement");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3311 "defs.tab.c"
    break;

  case 163: /* statement: expression_statement  */
#line 1269 "defs.y"
{
    //printf ("statement -> expression_statement\n");
    (yyval.X) = createNode ("statement");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3321 "defs.tab.c"
    break;

  case 164: /* statement: selection_statement  */
#line 1275 "defs.y"
{
    //printf ("statement -> selection_statement\n");
    (yyval.X) = createNode ("statement");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3331 "defs.tab.c"
    break;

  case 165: /* statement: iteration_statement  */
#line 1281 "defs.y"
{
    //printf ("statement -> iteration_statement\n");
    (yyval.X) = createNode ("statement");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3341 "defs.tab.c"
    break;

  case 166: /* statement: jump_statement  */
#line 1287 "defs.y"
{
    //printf ("statement -> jump_statement\n");
    (yyval.X) = createNode ("statement");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3351 "defs.tab.c"
    break;

  case 167: /* labeled_statement: IDENTIFIER ':' statement  */
#line 1294 "defs.y"
{
    //printf ("labeled_statement -> IDENTIFIER ':' statement\n");
    (yyval.X) = createNode ("labeled_statement");
    addChild ((yyval.X), createNode ((yyvsp[-2].string)));
    addChild ((yyval.X), createNode (":"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3363 "defs.tab.c"
    break;

  case 168: /* labeled_statement: CASE constant_expression ':' statement  */
#line 1302 "defs.y"
{
   // printf ("labeled_statement -> CASE constant_expression ':' statement\n");
    (yyval.X) = createNode ("labeled_statement");
    addChild ((yyval.X), createNode ("CASE"));
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode (":"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3376 "defs.tab.c"
    break;

  case 169: /* labeled_statement: DEFAULT ':' statement  */
#line 1311 "defs.y"
{
    //printf ("labeled_statement -> DEFAULT ':' statement\n");
    (yyval.X) = createNode ("labeled_statement");
    addChild ((yyval.X), createNode ("DEFAULT"));
    addChild ((yyval.X), createNode (":"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3388 "defs.tab.c"
    break;

  case 170: /* compound_statement: '{' block_item_list_optional '}'  */
#line 1320 "defs.y"
{
    //printf ("compound_statement -> '{' block_item_list_optional '}'\n");
    (yyval.X) = createNode ("compound_statement");
    addChild ((yyval.X), createNode ("{"));
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), createNode ("}"));
}
#line 3400 "defs.tab.c"
    break;

  case 171: /* block_item_list: block_item  */
#line 1329 "defs.y"
{
    //printf ("block_item_list -> block_item\n");
    (yyval.X) = createNode ("block_item_list");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3410 "defs.tab.c"
    break;

  case 172: /* block_item_list: block_item_list block_item  */
#line 1335 "defs.y"
{
    //printf ("block_item_list -> block_item_list block_item\n");
    (yyval.X) = createNode ("block_item_list");
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3421 "defs.tab.c"
    break;

  case 173: /* block_item_list_optional: block_item_list  */
#line 1343 "defs.y"
{
    //printf ("block_item_list_optional -> block_item_list\n");
    (yyval.X) = createNode ("block_item_list_optional");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3431 "defs.tab.c"
    break;

  case 174: /* block_item_list_optional: %empty  */
#line 1349 "defs.y"
{
    //printf ("block_item_list_optional -> ε\n");
    (yyval.X) = createNode ("block_item_list_optional");
    addChild ((yyval.X), createNode ("ε"));
}
#line 3441 "defs.tab.c"
    break;

  case 175: /* block_item: declaration  */
#line 1356 "defs.y"
{
    //printf ("block_item -> declaration\n");
    (yyval.X) = createNode ("block_item");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3451 "defs.tab.c"
    break;

  case 176: /* block_item: statement  */
#line 1362 "defs.y"
{
    //printf ("block_item -> statement\n");
    (yyval.X) = createNode ("block_item");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3461 "defs.tab.c"
    break;

  case 177: /* expression_statement: expression_optional ';'  */
#line 1369 "defs.y"
{
    //printf ("expression_statement -> expression_optional ';'\n");
    (yyval.X) = createNode ("expression_statement");
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), createNode (";"));
}
#line 3472 "defs.tab.c"
    break;

  case 178: /* selection_statement: IF '(' expression ')' statement  */
#line 1377 "defs.y"
{
    //printf ("selection_statement -> IF '(' expression ')' statement\n");
    (yyval.X) = createNode ("selection_statement");
    addChild ((yyval.X), createNode ("IF"));
    addChild ((yyval.X), createNode ("("));
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode (")"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3486 "defs.tab.c"
    break;

  case 179: /* selection_statement: IF '(' expression ')' statement ELSE statement  */
#line 1387 "defs.y"
{
    //printf ("selection_statement -> IF '(' expression ')' statement ELSE statement\n");
    (yyval.X) = createNode ("selection_statement");
    addChild ((yyval.X), createNode ("IF"));
    addChild ((yyval.X), createNode ("("));
    addChild ((yyval.X), (yyvsp[-4].X));
    addChild ((yyval.X), createNode (")"));
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode ("ELSE"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3502 "defs.tab.c"
    break;

  case 180: /* selection_statement: SWITCH '(' expression ')' statement  */
#line 1399 "defs.y"
{
    //printf ("selection_statement -> SWITCH '(' expression ')' statement\n");
    (yyval.X) = createNode ("selection_statement");
    addChild ((yyval.X), createNode ("SWITCH"));
    addChild ((yyval.X), createNode ("("));
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode (")"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3516 "defs.tab.c"
    break;

  case 181: /* iteration_statement: WHILE '(' expression ')' statement  */
#line 1410 "defs.y"
{
    //printf ("iteration_statement -> WHILE '(' expression ')' statement\n");
    (yyval.X) = createNode ("iteration_statement");
    addChild ((yyval.X), createNode ("WHILE"));
    addChild ((yyval.X), createNode ("("));
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode (")"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3530 "defs.tab.c"
    break;

  case 182: /* iteration_statement: DO statement WHILE '(' expression ')' ';'  */
#line 1420 "defs.y"
{
    //printf ("iteration_statement -> DO statement WHILE '(' expression ')' ';'\n");
    (yyval.X) = createNode ("iteration_statement");
    addChild ((yyval.X), createNode ("DO"));
    addChild ((yyval.X), (yyvsp[-5].X));
    addChild ((yyval.X), createNode ("WHILE"));
    addChild ((yyval.X), createNode ("("));
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode (")"));
    addChild ((yyval.X), createNode (";"));
}
#line 3546 "defs.tab.c"
    break;

  case 183: /* iteration_statement: FOR '(' expression_optional ';' expression_optional ';' expression_optional ')' statement  */
#line 1432 "defs.y"
{
    //printf ("iteration_statement -> FOR '(' expression_optional ';' expression_optional ';' expression_optional ')' statement\n");
    (yyval.X) = createNode ("iteration_statement");
    addChild ((yyval.X), createNode ("FOR"));
    addChild ((yyval.X), createNode ("("));
    addChild ((yyval.X), (yyvsp[-6].X));
    addChild ((yyval.X), createNode (";"));
    addChild ((yyval.X), (yyvsp[-4].X));
    addChild ((yyval.X), createNode (";"));
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode (")"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3564 "defs.tab.c"
    break;

  case 184: /* iteration_statement: FOR '(' declaration expression_optional ';' expression_optional ')' statement  */
#line 1446 "defs.y"
{
    //printf ("iteration_statement -> FOR '(' declaration expression_optional ';' expression_optional ')' statement\n");
    (yyval.X) = createNode ("iteration_statement");
    addChild ((yyval.X), createNode ("FOR"));
    addChild ((yyval.X), createNode ("("));
    addChild ((yyval.X), (yyvsp[-5].X));
    addChild ((yyval.X), (yyvsp[-4].X));
    addChild ((yyval.X), createNode (";"));
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), createNode (")"));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3581 "defs.tab.c"
    break;

  case 185: /* jump_statement: GOTO IDENTIFIER ';'  */
#line 1460 "defs.y"
{
    //printf ("jump_statement -> GOTO IDENTIFIER ';'\n");
    (yyval.X) = createNode ("jump_statement");
    addChild ((yyval.X), createNode ("GOTO"));
    addChild ((yyval.X), createNode ((yyvsp[-1].string)));
    addChild ((yyval.X), createNode (";"));
}
#line 3593 "defs.tab.c"
    break;

  case 186: /* jump_statement: CONTINUE ';'  */
#line 1468 "defs.y"
{
    //printf ("jump_statement -> CONTINUE ';'\n");
    (yyval.X) = createNode ("jump_statement");
    addChild ((yyval.X), createNode ("CONTINUE"));
    addChild ((yyval.X), createNode (";"));
}
#line 3604 "defs.tab.c"
    break;

  case 187: /* jump_statement: BREAK ';'  */
#line 1475 "defs.y"
{
    //printf ("jump_statement -> BREAK ';'\n");
    (yyval.X) = createNode ("jump_statement");
    addChild ((yyval.X), createNode ("BREAK"));
    addChild ((yyval.X), createNode (";"));
}
#line 3615 "defs.tab.c"
    break;

  case 188: /* jump_statement: RETURN expression_optional ';'  */
#line 1482 "defs.y"
{
    //printf ("jump_statement -> RETURN expression_optional ';'\n");
    (yyval.X) = createNode ("jump_statement");
    addChild ((yyval.X), createNode ("RETURN"));
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), createNode (";"));
}
#line 3627 "defs.tab.c"
    break;

  case 189: /* translation_unit: external_declaration  */
#line 1492 "defs.y"
{
    //printf ("translation_unit -> external_declaration\n");
    (yyval.X) = createNode ("translation_unit");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3637 "defs.tab.c"
    break;

  case 190: /* translation_unit: translation_unit external_declaration  */
#line 1498 "defs.y"
{
    //printf ("translation_unit -> translation_unit external_declaration\n");
    (yyval.X) = createNode ("translation_unit");
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3648 "defs.tab.c"
    break;

  case 191: /* external_declaration: function_definition  */
#line 1506 "defs.y"
{
    //printf ("external_declaration -> function_definition\n");
    (yyval.X) = createNode ("external_declaration");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3658 "defs.tab.c"
    break;

  case 192: /* external_declaration: declaration  */
#line 1512 "defs.y"
{
    //printf ("external_declaration -> declaration\n");
    (yyval.X) = createNode ("external_declaration");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3668 "defs.tab.c"
    break;

  case 193: /* function_definition: declaration_specifiers declarator declaration_list_optional compound_statement  */
#line 1519 "defs.y"
{
    //printf ("function_definition -> declaration_specifiers declarator declaration_list_optional compound_statement\n");
    (yyval.X) = createNode ("function_definition");
    addChild ((yyval.X), (yyvsp[-3].X));
    addChild ((yyval.X), (yyvsp[-2].X));
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3681 "defs.tab.c"
    break;

  case 194: /* declaration_list: declaration  */
#line 1529 "defs.y"
{
    //printf ("declaration_list -> declaration\n");
    (yyval.X) = createNode ("declaration_list");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3691 "defs.tab.c"
    break;

  case 195: /* declaration_list: declaration_list declaration  */
#line 1535 "defs.y"
{
    //printf ("declaration_list -> declaration_list declaration\n");
    (yyval.X) = createNode ("declaration_list");
    addChild ((yyval.X), (yyvsp[-1].X));
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3702 "defs.tab.c"
    break;

  case 196: /* declaration_list_optional: declaration_list  */
#line 1543 "defs.y"
{
    //printf ("declaration_list_optional -> declaration_list\n");
    (yyval.X) = createNode ("declaration_list_optional");
    addChild ((yyval.X), (yyvsp[0].X));
}
#line 3712 "defs.tab.c"
    break;

  case 197: /* declaration_list_optional: %empty  */
#line 1549 "defs.y"
{
    //printf ("declaration_list_optional -> ε\n");
    (yyval.X) = createNode ("declaration_list_optional");
    addChild ((yyval.X), createNode ("ε"));
}
#line 3722 "defs.tab.c"
    break;

  case 198: /* program: translation_unit  */
#line 1556 "defs.y"
{
    //printf ("program -> translation_unit\n");
    (yyval.X) = createNode ("program");
    addChild ((yyval.X), (yyvsp[0].X));
    root = (yyval.X);
    return 0;
}
#line 3734 "defs.tab.c"
    break;


#line 3738 "defs.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

