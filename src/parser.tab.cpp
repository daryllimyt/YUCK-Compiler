/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */

#line 67 "src/parser.tab.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.hpp".  */
#ifndef YY_YY_SRC_PARSER_TAB_HPP_INCLUDED
# define YY_YY_SRC_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "src/parser.y" /* yacc.c:355  */

  #include "ast.hpp"
  #include "ast/ast_node.hpp"

  #include <fstream>
  #include <cassert>
  
  extern FILE *yyin;
  extern const Tree *g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);


#line 115 "src/parser.tab.cpp" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    REDUCE_PREC = 258,
    CASE = 259,
    DEFAULT = 260,
    IF = 261,
    SWITCH = 262,
    WHILE = 263,
    DO = 264,
    FOR = 265,
    CONTINUE = 266,
    BREAK = 267,
    RETURN = 268,
    SEMICOLON = 269,
    COMMA = 270,
    TYPEDEF = 271,
    EXTERN = 272,
    STATIC = 273,
    AUTO = 274,
    VOID = 275,
    BOOL = 276,
    CHAR = 277,
    FLOAT = 278,
    INT = 279,
    DOUBLE = 280,
    SHORT = 281,
    LONG = 282,
    SIGNED = 283,
    UNSIGNED = 284,
    CONST = 285,
    VOLATILE = 286,
    SIZEOF = 287,
    ENUM = 288,
    ELLIPSIS = 289,
    VARIABLE = 290,
    NUMBER = 291,
    STRING_LITERAL = 292,
    RBRACKET_L = 293,
    RBRACKET_R = 294,
    CBRACKET_L = 295,
    CBRACKET_R = 296,
    SBRACKET_L = 297,
    SBRACKET_R = 298,
    ELSE = 299,
    BITANDASSIGN = 300,
    BITXORASSIGN = 301,
    BITORASSIGN = 302,
    LSHIFTASSIGN = 303,
    RSHIFTASSIGN = 304,
    MULTASSIGN = 305,
    DIVASSIGN = 306,
    REMAINASSIGN = 307,
    ADDASSIGN = 308,
    SUBASSIGN = 309,
    ASSIGN = 310,
    CONDITIONAL = 311,
    COLON = 312,
    OR = 313,
    AND = 314,
    BITOR = 315,
    BITXOR = 316,
    BITAND = 317,
    EQUAL = 318,
    NOTEQUAL = 319,
    GREATER = 320,
    LESS = 321,
    GREATEREQUAL = 322,
    LESSEQUAL = 323,
    LSHIFT = 324,
    RSHIFT = 325,
    PLUS = 326,
    MINUS = 327,
    MULTIPLY = 328,
    DIVIDE = 329,
    REMAINDER = 330,
    NOT = 331,
    BITNOT = 332,
    INCREMENT = 333,
    DECREMENT = 334
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 23 "src/parser.y" /* yacc.c:355  */

  Tree *nodetype;

  double number;
  std::string *string;

#line 214 "src/parser.tab.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_PARSER_TAB_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 231 "src/parser.tab.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  40
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   942

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  80
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  64
/* YYNRULES -- Number of rules.  */
#define YYNRULES  201
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  335

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   334

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   101,   101,   104,   105,   106,   107,   108,   109,   114,
     115,   119,   120,   121,   122,   123,   124,   128,   129,   130,
     131,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   150,   151,   155,   156,   160,   161,   165,   166,
     170,   171,   172,   173,   174,   178,   179,   180,   184,   185,
     186,   187,   191,   192,   196,   197,   201,   202,   207,   208,
     213,   222,   223,   227,   228,   232,   233,   234,   238,   239,
     243,   244,   248,   249,   253,   254,   258,   259,   263,   264,
     269,   270,   271,   272,   273,   274,   278,   279,   283,   284,
     285,   289,   290,   294,   295,   296,   300,   301,   302,   304,
     309,   310,   314,   315,   325,   326,   327,   328,   338,   343,
     344,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   363,   364,   365,   369,   370,   374,   375,
     379,   380,   384,   385,   389,   390,   394,   395,   396,   400,
     401,   402,   403,   404,   408,   409,   410,   414,   415,   416,
     420,   421,   422,   423,   427,   428,   432,   433,   434,   435,
     436,   437,   438,   439,   440,   441,   442,   446,   447,   448,
     449,   451,   452,   456,   457,   461,   462,   463,   464,   469,
     470,   474,   475,   476,   477,   481,   482,   483,   487,   488,
     489,   494,   495,   496,   497,   501,   502,   503,   507,   508,
     512,   513
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "REDUCE_PREC", "CASE", "DEFAULT", "IF",
  "SWITCH", "WHILE", "DO", "FOR", "CONTINUE", "BREAK", "RETURN",
  "SEMICOLON", "COMMA", "TYPEDEF", "EXTERN", "STATIC", "AUTO", "VOID",
  "BOOL", "CHAR", "FLOAT", "INT", "DOUBLE", "SHORT", "LONG", "SIGNED",
  "UNSIGNED", "CONST", "VOLATILE", "SIZEOF", "ENUM", "ELLIPSIS",
  "VARIABLE", "NUMBER", "STRING_LITERAL", "RBRACKET_L", "RBRACKET_R",
  "CBRACKET_L", "CBRACKET_R", "SBRACKET_L", "SBRACKET_R", "ELSE",
  "BITANDASSIGN", "BITXORASSIGN", "BITORASSIGN", "LSHIFTASSIGN",
  "RSHIFTASSIGN", "MULTASSIGN", "DIVASSIGN", "REMAINASSIGN", "ADDASSIGN",
  "SUBASSIGN", "ASSIGN", "CONDITIONAL", "COLON", "OR", "AND", "BITOR",
  "BITXOR", "BITAND", "EQUAL", "NOTEQUAL", "GREATER", "LESS",
  "GREATEREQUAL", "LESSEQUAL", "LSHIFT", "RSHIFT", "PLUS", "MINUS",
  "MULTIPLY", "DIVIDE", "REMAINDER", "NOT", "BITNOT", "INCREMENT",
  "DECREMENT", "$accept", "ROOT", "PROGRAM", "VARIABLE_DECLARATION",
  "DECLARATION_SPECIFIERS", "STORAGE_CLASS", "TYPE", "QUALIFIER",
  "INIT_DECLARATION_LIST", "INIT_DECLARATION", "DECLARATION_IDENTIFIER",
  "DIRECT_DECLARATOR", "DIRECT_DECLARATOR_PARAMETER", "POINTER",
  "QUALIFIER_LIST", "INITIALIZER", "INITIALIZER_LIST",
  "FUNCTION_DECLARATION", "FORWARD_DECLARATION", "PARAMETER_TYPE_LIST",
  "PARAMETER_LIST", "PARAMETER_DECLARATION", "IDENTIFIER_LIST",
  "COMPOUND_STATEMENT", "COMPOUND_LIST", "COMPOUND_LIST_TYPE",
  "DECLARATION_LIST", "STATEMENT_LIST", "STATEMENT", "LABELLED_STATEMENT",
  "LABELLED_CONDITION", "EXPRESSION_STATEMENT", "SELECTION_STATEMENT",
  "ITERATION_STATEMENT", "INIT_STATEMENT", "ITERATION_CONDITION",
  "JUMP_STATEMENT", "CONSTANT_EXPRESSION", "EXPRESSION", "ASSIGNMENT_EXPR",
  "CONDITIONAL_EXPR", "LOGICAL_OR_EXPR", "LOGICAL_AND_EXPR",
  "INCLUSIVE_OR_EXPR", "EXCLUSIVE_OR_EXPR", "AND_EXPR", "EQUALITY_EXPR",
  "RELATIONAL_EXPR", "SHIFT_EXPR", "ADDITIVE_EXPR", "MULTIPLICATIVE_EXPR",
  "CAST_EXPR", "UNARY_EXPR", "POSTFIX_EXPR", "ARGUMENT_EXPR_LIST",
  "PRIMARY_EXPR", "TYPE_NAME", "SPECIFIER_QUALIFIER_LIST",
  "ABSTRACT_DECLARATOR", "DIRECT_ABSTRACT_DECLARATOR",
  "ABSTRACT_DECLARATOR_PARAMETER", "ENUM_SPECIFIER", "ENUMERATOR_LIST",
  "ENUMERATOR", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334
};
# endif

#define YYPACT_NINF -211

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-211)))

#define YYTABLE_NINF -89

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     586,  -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,
    -211,  -211,  -211,  -211,  -211,  -211,  -211,    44,  -211,   -23,
     -13,    21,   586,  -211,    35,   868,   868,   868,    43,    92,
     151,  -211,  -211,  -211,    91,    28,    72,  -211,  -211,   -13,
    -211,  -211,  -211,  -211,  -211,    57,  -211,    78,    92,  -211,
    -211,  -211,   282,  -211,   310,   590,  -211,    92,    28,   -24,
     125,   157,  -211,  -211,  -211,  -211,   -23,   602,  -211,   165,
     730,  -211,   152,   160,   162,   434,   164,   171,   173,   198,
    -211,   742,   172,  -211,  -211,   522,  -211,   730,   730,   730,
     730,   730,   730,   761,   761,  -211,    35,  -211,   358,  -211,
     868,   434,  -211,  -211,   180,  -211,  -211,  -211,  -211,   193,
    -211,  -211,    71,   181,   183,   184,   186,   147,    54,   144,
     149,   143,  -211,   887,   -10,  -211,  -211,  -211,    -9,   207,
     241,  -211,    36,  -211,  -211,   215,  -211,   218,   730,  -211,
      28,  -211,   206,   602,  -211,  -211,  -211,  -211,  -211,   730,
     730,   730,   255,   462,  -211,  -211,  -211,   208,   522,  -211,
     898,   898,    67,   225,    -8,  -211,  -211,  -211,  -211,  -211,
    -211,   730,  -211,  -211,  -211,  -211,  -211,  -211,   838,  -211,
     730,   650,   730,   730,   730,   730,   730,   730,   730,   730,
     730,   730,   730,   730,   730,   730,   730,   730,   730,   730,
     730,   730,   730,   730,   730,   730,   730,   730,   730,   730,
     730,   662,   730,  -211,  -211,   384,   682,  -211,    75,  -211,
     135,  -211,  -211,   849,   230,  -211,  -211,  -211,  -211,  -211,
    -211,    -4,    77,    85,    86,   228,  -211,  -211,   462,  -211,
     229,  -211,  -211,  -211,   730,   547,   146,  -211,   838,  -211,
     730,    10,   181,   183,   184,   186,   147,    54,    54,   144,
     144,   144,   144,   149,   149,   143,   143,  -211,  -211,  -211,
    -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,
    -211,  -211,   252,   233,     1,  -211,   239,   240,  -211,   237,
     135,   825,  -211,  -211,  -211,  -211,   602,  -211,   434,   434,
     434,   730,   -23,  -211,   710,  -211,  -211,  -211,   730,   730,
    -211,  -211,  -211,  -211,  -211,  -211,   238,  -211,  -211,    87,
     226,   434,    89,  -211,  -211,   434,   270,   602,  -211,   434,
    -211,  -211,   271,  -211,  -211
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    32,    33,     0,    40,     0,
      48,     0,     2,     3,     0,    13,    11,    12,     0,    38,
       0,     4,     5,    31,   197,     0,     0,    52,    50,    49,
       1,     6,     7,     8,     9,     0,    34,    36,    38,    16,
      14,    15,     0,    59,     0,     0,    44,    39,     0,   200,
       0,   198,    41,    53,    51,    10,     0,     0,    58,    44,
       0,    90,     0,     0,     0,     0,     0,     0,     0,     0,
      91,     0,   175,   176,   177,     0,    70,     0,     0,     0,
       0,     0,     0,     0,     0,    76,     0,    80,     0,    72,
      74,    75,    78,    81,     0,    82,    83,    84,    85,     0,
     109,   111,   123,   126,   128,   130,   132,   134,   136,   139,
     144,   147,   150,   154,   156,   167,    68,    47,    67,     0,
      61,    63,     0,   175,    43,     0,   154,     0,     0,   195,
       0,    35,    36,     0,    37,    54,    60,    89,   108,     0,
       0,     0,     0,     0,   106,   107,   104,     0,     0,   165,
     181,   182,     0,     0,   179,   159,   161,   162,   160,   164,
     163,     0,   157,   158,    71,    73,    77,    79,    87,    92,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   171,   172,     0,     0,    65,   185,    66,
     186,   189,    45,     0,     0,    46,    42,   196,   201,   199,
      56,     0,     0,     0,     0,     0,   101,   100,     0,   105,
       0,   183,   184,   178,     0,     0,   185,   180,    86,   110,
       0,     0,   127,   129,   131,   133,   135,   137,   138,   140,
     141,   142,   143,   145,   146,   148,   149,   151,   152,   153,
     120,   121,   122,   118,   119,   115,   116,   117,   113,   114,
     112,   169,   173,     0,     0,   193,     0,     0,   191,     0,
     187,     0,   190,    62,    64,    69,     0,    55,     0,     0,
       0,     0,     0,   102,     0,   166,   155,   125,     0,     0,
     170,   168,   194,   188,   192,    57,    93,    95,    96,     0,
       0,     0,     0,   124,   174,     0,     0,     0,    98,     0,
      94,    97,     0,    99,   103
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -211,  -211,  -211,    23,    14,  -211,   -72,    22,  -211,   231,
     -19,   -21,   268,     4,  -211,  -121,  -211,   303,   320,   292,
    -211,   124,  -211,    34,  -211,   250,  -211,   174,   -74,  -211,
    -211,  -147,  -211,  -211,  -211,  -211,  -211,  -131,    20,   -65,
     -51,  -211,   168,   190,   167,   212,   170,    40,     3,    45,
      46,     6,   -35,  -211,    48,  -211,   234,    93,   -90,  -170,
    -210,  -211,   -50,  -211
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    21,    22,    95,   128,    25,    26,    27,    45,    46,
      28,    29,    56,    30,    39,   144,   231,    31,    32,   286,
     130,   131,   132,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   238,   304,   108,   147,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   283,   125,   163,   164,   287,   220,
     221,    33,    60,    61
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      36,   152,   145,    48,   135,    47,   237,   228,   137,    57,
     292,   296,    18,   160,    24,    19,   180,    15,    16,   148,
     136,    40,   230,    23,    38,   180,    18,   177,   211,   215,
     245,   138,   212,   216,   216,   136,    24,   297,   219,    49,
      50,    51,    37,    64,   311,    41,   159,   142,   290,    44,
      20,   224,   136,   136,   136,   136,   136,   136,   172,   173,
      20,    63,    53,    59,    20,    20,    96,   308,   213,   214,
      18,    65,    66,    19,   247,   225,   290,   142,   145,    34,
     292,    68,   180,    52,    35,   289,   160,   148,   160,   160,
     229,   303,   180,   165,   166,   167,   168,   169,   170,   157,
     180,   180,   180,   136,   180,   162,   243,   161,    20,   217,
      18,    62,    96,   215,    96,   249,   298,   216,    52,   189,
     190,   191,   192,   176,   299,   300,   326,   181,   329,   182,
      54,    58,   218,    67,    55,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   282,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   148,   139,    96,   246,   232,
     233,   234,   140,   291,   177,   315,   236,   216,   162,   146,
     161,   136,   161,   161,   245,   154,    18,   155,   216,    19,
     149,   162,   259,   260,   261,   262,    36,    57,   150,   307,
     151,   251,   153,   267,   268,   269,   332,   179,   180,   136,
     187,   188,   156,   193,   194,   136,   197,   198,   199,   218,
     195,   196,   239,   180,   316,   317,   318,   257,   258,   -88,
      81,   145,   284,   133,    83,    84,    85,   178,   263,   264,
     183,   265,   266,   184,   282,   185,   222,   328,   186,   246,
     306,   330,   302,   241,   242,   333,   223,   323,   226,   227,
      87,    67,   145,   235,   244,   295,   301,   309,   305,    88,
      89,    90,   310,   136,    91,    92,    93,    94,   312,   313,
     314,   327,   325,   320,   331,   334,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,   141,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    81,    17,    69,    82,    83,    84,
      85,   319,    52,    86,   322,    42,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    43,    17,    87,   126,   129,   294,   175,   127,
     252,   254,   248,    88,    89,    90,   256,   324,    91,    92,
      93,    94,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,   253,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      81,    17,   240,    82,    83,    84,    85,   255,    52,   174,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,     0,    17,     0,    18,
      87,     0,   215,   285,     0,     0,   216,     0,     0,    88,
      89,    90,     0,     0,    91,    92,    93,    94,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,     0,
       0,     0,     0,     0,     0,     0,     0,    20,     0,     0,
       0,     0,     0,     0,     0,     0,    81,     0,     0,    82,
      83,    84,    85,     0,    52,     0,    80,     0,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    81,    17,    87,   133,    83,    84,
      85,     0,     0,     0,     0,    88,    89,    90,     0,     0,
      91,    92,    93,    94,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    87,     0,     0,     0,     0,     0,
       0,     0,     0,    88,    89,    90,     0,     0,    91,    92,
      93,    94,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    81,    17,     0,   133,    83,    84,
      85,     0,     0,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,     0,
      17,     0,     0,     0,    87,   245,   285,     0,     0,   216,
       0,     0,     0,    88,    89,    90,     0,     0,    91,    92,
      93,    94,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,     0,    17,
      20,    18,    81,     0,    19,   133,    83,    84,    85,     0,
       0,     0,     0,   134,    81,     0,     0,   133,    83,    84,
      85,     0,   143,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    87,     0,     0,     0,     0,     0,     0,    20,
       0,    88,    89,    90,    87,     0,    91,    92,    93,    94,
       0,     0,     0,    88,    89,    90,     0,     0,    91,    92,
      93,    94,    81,     0,     0,   133,    83,    84,    85,     0,
       0,     0,     0,     0,    81,     0,     0,   133,    83,    84,
      85,   281,     0,     0,     0,     0,     0,   250,     0,     0,
       0,     0,    87,     0,    81,     0,     0,   133,    83,    84,
      85,    88,    89,    90,    87,   288,    91,    92,    93,    94,
       0,     0,     0,    88,    89,    90,     0,     0,    91,    92,
      93,    94,    81,     0,    87,   133,    83,    84,    85,   321,
       0,     0,     0,    88,    89,    90,     0,     0,    91,    92,
      93,    94,    81,     0,     0,   133,    83,    84,    85,     0,
       0,     0,    87,     0,    81,     0,     0,   133,    83,    84,
     158,    88,    89,    90,     0,     0,    91,    92,    93,    94,
       0,     0,    87,    81,     0,     0,   133,    83,    84,   171,
       0,    88,    89,    90,    87,     0,    91,    92,    93,    94,
       0,     0,     0,    88,    89,    90,     0,     0,    91,    92,
      93,    94,     0,    87,     0,     0,     0,     0,     0,     0,
       0,     0,    88,    89,    90,     0,     0,    91,    92,    93,
      94,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,     0,    17,     0,
       0,     0,     0,     0,   285,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,     0,    17,   293,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      87,    17,     0,     0,     0,     0,     0,     0,     0,    88,
      89,    90,     0,     0,    91,    92,    93,    94,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
       0,    17,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210
};

static const yytype_int16 yycheck[] =
{
      19,    75,    67,    24,    55,    24,   153,   138,    58,    30,
     220,    15,    35,    85,     0,    38,    15,    30,    31,    70,
      55,     0,   143,     0,    20,    15,    35,   101,    38,    38,
      38,    55,    42,    42,    42,    70,    22,    41,   128,    25,
      26,    27,    20,    39,    43,    22,    81,    66,   218,    14,
      73,    15,    87,    88,    89,    90,    91,    92,    93,    94,
      73,    39,    28,    35,    73,    73,    52,    57,    78,    79,
      35,    14,    15,    38,   164,    39,   246,    96,   143,    35,
     290,    47,    15,    40,    40,   216,   158,   138,   160,   161,
     140,   238,    15,    87,    88,    89,    90,    91,    92,    79,
      15,    15,    15,   138,    15,    85,    39,    85,    73,   128,
      35,    39,    98,    38,   100,   180,    39,    42,    40,    65,
      66,    67,    68,   100,    39,    39,    39,    56,    39,    58,
      38,    40,   128,    55,    42,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   216,    41,   153,   164,   149,
     150,   151,    15,    38,   248,   296,   153,    42,   158,    14,
     158,   216,   160,   161,    38,    14,    35,    14,    42,    38,
      38,   171,   189,   190,   191,   192,   215,   218,    38,   250,
      38,   181,    38,   197,   198,   199,   327,    14,    15,   244,
      63,    64,    14,    69,    70,   250,    73,    74,    75,   215,
      71,    72,    14,    15,   298,   299,   300,   187,   188,    57,
      32,   296,   212,    35,    36,    37,    38,    57,   193,   194,
      59,   195,   196,    60,   309,    61,    39,   321,    62,   245,
     244,   325,   238,   160,   161,   329,    15,   308,    43,    41,
      62,    55,   327,     8,    39,    35,    38,    15,    39,    71,
      72,    73,    39,   308,    76,    77,    78,    79,    39,    39,
      43,    55,    44,   302,    14,    14,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    66,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    48,    35,    36,    37,
      38,   301,    40,    41,   304,    22,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    22,    33,    62,    35,    54,   223,    98,    39,
     182,   184,   178,    71,    72,    73,   186,   309,    76,    77,
      78,    79,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,   183,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,   158,    35,    36,    37,    38,   185,    40,    41,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    33,    -1,    35,
      62,    -1,    38,    39,    -1,    -1,    42,    -1,    -1,    71,
      72,    73,    -1,    -1,    76,    77,    78,    79,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,    35,
      36,    37,    38,    -1,    40,    -1,    14,    -1,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    62,    35,    36,    37,
      38,    -1,    -1,    -1,    -1,    71,    72,    73,    -1,    -1,
      76,    77,    78,    79,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    72,    73,    -1,    -1,    76,    77,
      78,    79,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    -1,    35,    36,    37,
      38,    -1,    -1,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      33,    -1,    -1,    -1,    62,    38,    39,    -1,    -1,    42,
      -1,    -1,    -1,    71,    72,    73,    -1,    -1,    76,    77,
      78,    79,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    33,
      73,    35,    32,    -1,    38,    35,    36,    37,    38,    -1,
      -1,    -1,    -1,    43,    32,    -1,    -1,    35,    36,    37,
      38,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,    73,
      -1,    71,    72,    73,    62,    -1,    76,    77,    78,    79,
      -1,    -1,    -1,    71,    72,    73,    -1,    -1,    76,    77,
      78,    79,    32,    -1,    -1,    35,    36,    37,    38,    -1,
      -1,    -1,    -1,    -1,    32,    -1,    -1,    35,    36,    37,
      38,    39,    -1,    -1,    -1,    -1,    -1,    57,    -1,    -1,
      -1,    -1,    62,    -1,    32,    -1,    -1,    35,    36,    37,
      38,    71,    72,    73,    62,    43,    76,    77,    78,    79,
      -1,    -1,    -1,    71,    72,    73,    -1,    -1,    76,    77,
      78,    79,    32,    -1,    62,    35,    36,    37,    38,    39,
      -1,    -1,    -1,    71,    72,    73,    -1,    -1,    76,    77,
      78,    79,    32,    -1,    -1,    35,    36,    37,    38,    -1,
      -1,    -1,    62,    -1,    32,    -1,    -1,    35,    36,    37,
      38,    71,    72,    73,    -1,    -1,    76,    77,    78,    79,
      -1,    -1,    62,    32,    -1,    -1,    35,    36,    37,    38,
      -1,    71,    72,    73,    62,    -1,    76,    77,    78,    79,
      -1,    -1,    -1,    71,    72,    73,    -1,    -1,    76,    77,
      78,    79,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    72,    73,    -1,    -1,    76,    77,    78,
      79,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    33,    -1,
      -1,    -1,    -1,    -1,    39,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    -1,    33,    34,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      62,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      72,    73,    -1,    -1,    76,    77,    78,    79,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    33,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    33,    35,    38,
      73,    81,    82,    83,    84,    85,    86,    87,    90,    91,
      93,    97,    98,   141,    35,    40,    90,    87,    93,    94,
       0,    83,    97,    98,    14,    88,    89,    90,    91,    84,
      84,    84,    40,   103,    38,    42,    92,    91,    40,    35,
     142,   143,    39,    87,    93,    14,    15,    55,   103,    92,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    32,    35,    36,    37,    38,    41,    62,    71,    72,
      73,    76,    77,    78,    79,    83,    84,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   116,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   135,    35,    39,    84,    99,
     100,   101,   102,    35,    43,   120,   132,   142,    55,    41,
      15,    89,    90,    40,    95,   119,    14,   117,   120,    38,
      38,    38,   108,    38,    14,    14,    14,   118,    38,   132,
      86,    87,   118,   136,   137,   131,   131,   131,   131,   131,
     131,    38,   132,   132,    41,   105,    83,   108,    57,    14,
      15,    56,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    38,    42,    78,    79,    38,    42,    90,    93,   138,
     139,   140,    39,    15,    15,    39,    43,    41,   117,   142,
      95,    96,   118,   118,   118,     8,    83,   111,   114,    14,
     136,   137,   137,    39,    39,    38,    93,   138,   107,   119,
      57,   118,   122,   123,   124,   125,   126,   127,   127,   128,
     128,   128,   128,   129,   129,   130,   130,   131,   131,   131,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,    39,   119,   134,   118,    39,    99,   138,    43,   117,
     139,    38,   140,    34,   101,    35,    15,    41,    39,    39,
      39,    38,    84,   111,   115,    39,   131,   120,    57,    15,
      39,    43,    39,    39,    43,    95,   108,   108,   108,   118,
      90,    39,   118,   120,   134,    44,    39,    55,   108,    39,
     108,    14,    95,   108,    14
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    80,    81,    82,    82,    82,    82,    82,    82,    83,
      83,    84,    84,    84,    84,    84,    84,    85,    85,    85,
      85,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    87,    87,    88,    88,    89,    89,    90,    90,
      91,    91,    91,    91,    91,    92,    92,    92,    93,    93,
      93,    93,    94,    94,    95,    95,    96,    96,    97,    97,
      98,    99,    99,   100,   100,   101,   101,   101,   102,   102,
     103,   103,   104,   104,   105,   105,   106,   106,   107,   107,
     108,   108,   108,   108,   108,   108,   109,   109,   110,   110,
     110,   111,   111,   112,   112,   112,   113,   113,   113,   113,
     114,   114,   115,   115,   116,   116,   116,   116,   117,   118,
     118,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   120,   120,   120,   121,   121,   122,   122,
     123,   123,   124,   124,   125,   125,   126,   126,   126,   127,
     127,   127,   127,   127,   128,   128,   128,   129,   129,   129,
     130,   130,   130,   130,   131,   131,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   133,   133,   133,
     133,   133,   133,   134,   134,   135,   135,   135,   135,   136,
     136,   137,   137,   137,   137,   138,   138,   138,   139,   139,
     139,   140,   140,   140,   140,   141,   141,   141,   142,   142,
     143,   143
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     2,     2,     2,     2,
       3,     1,     1,     1,     2,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     3,     1,     2,
       1,     3,     4,     3,     2,     3,     3,     2,     1,     2,
       2,     3,     1,     2,     1,     3,     1,     3,     3,     2,
       4,     1,     3,     1,     3,     2,     2,     1,     1,     3,
       2,     3,     1,     2,     1,     1,     1,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     3,     2,     1,     2,
       1,     1,     2,     5,     7,     5,     5,     7,     6,     7,
       1,     1,     1,     5,     2,     3,     2,     2,     1,     1,
       3,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     5,     4,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     1,     4,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     4,     1,     4,     3,
       4,     2,     2,     1,     3,     1,     1,     1,     3,     1,
       2,     1,     1,     2,     2,     1,     1,     2,     3,     1,
       2,     2,     3,     2,     3,     4,     5,     2,     1,     3,
       1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 101 "src/parser.y" /* yacc.c:1646  */
    { g_root = new RootNode( (yyvsp[0].nodetype) ); }
#line 1701 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 104 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 1707 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 105 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 1713 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 106 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 1719 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 107 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new ProgramNode( (yyvsp[-1].nodetype), (yyvsp[0].nodetype) ); }
#line 1725 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 108 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new ProgramNode( (yyvsp[-1].nodetype), (yyvsp[0].nodetype) ); }
#line 1731 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 109 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new ProgramNode( (yyvsp[-1].nodetype), (yyvsp[0].nodetype) ); }
#line 1737 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 114 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[-1].nodetype); }
#line 1743 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 115 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new VariableDeclarationNode( (yyvsp[-2].nodetype), (yyvsp[-1].nodetype) ); }
#line 1749 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 119 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 1755 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 120 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 1761 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 121 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 1767 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 122 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new DeclarationSpecifierNode( (yyvsp[-1].nodetype), (yyvsp[0].nodetype) ); }
#line 1773 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 123 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new DeclarationSpecifierNode( (yyvsp[-1].nodetype), (yyvsp[0].nodetype) ); }
#line 1779 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 124 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new DeclarationSpecifierNode( (yyvsp[-1].nodetype), (yyvsp[0].nodetype)) ;}
#line 1785 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 128 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new StorageClassNode( "typedef" ); }
#line 1791 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 129 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new StorageClassNode( "extern" ); }
#line 1797 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 130 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new StorageClassNode( "static" ); }
#line 1803 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 131 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new StorageClassNode( "auto" ); }
#line 1809 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 136 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new TypeNode( "void" ); }
#line 1815 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 137 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new TypeNode( "bool" ); }
#line 1821 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 138 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new TypeNode( "char" ); }
#line 1827 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 139 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new TypeNode( "float" ); }
#line 1833 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 140 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new TypeNode( "int" ); }
#line 1839 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 141 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new TypeNode( "double" ); }
#line 1845 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 142 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new TypeNode( "short" ); }
#line 1851 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 143 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new TypeNode( "long" ); }
#line 1857 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 144 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new TypeNode( "signed" ); }
#line 1863 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 145 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new TypeNode( "unsigned" ); }
#line 1869 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 146 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 1875 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 150 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new QualifierNode( "const" ); }
#line 1881 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 151 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new QualifierNode( "volatile" ); }
#line 1887 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 155 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 1893 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 156 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new InitDeclarationListNode( (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 1899 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 160 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new InitDeclarationNode( (yyvsp[0].nodetype), NULL ); }
#line 1905 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 161 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new InitDeclarationNode( (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 1911 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 165 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new DeclarationIdentifierNode( NULL, (yyvsp[0].nodetype) ); }
#line 1917 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 166 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new DeclarationIdentifierNode( (yyvsp[-1].nodetype), (yyvsp[0].nodetype) ); }
#line 1923 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 170 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new Variable( *(yyvsp[0].string) ); }
#line 1929 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 171 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[-1].nodetype); }
#line 1935 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 172 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new DirectDeclarationNode( "array declaration", (yyvsp[-3].nodetype), (yyvsp[-1].nodetype) ); }
#line 1941 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 173 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new DirectDeclarationNode( "array declaration", (yyvsp[-2].nodetype), NULL ); }
#line 1947 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 174 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new DirectDeclarationNode( "direct declaration", (yyvsp[-1].nodetype), (yyvsp[0].nodetype) ); }
#line 1953 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 178 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[-1].nodetype); }
#line 1959 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 179 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[-1].nodetype); }
#line 1965 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 180 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = NULL; }
#line 1971 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 184 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new PointerNode( NULL, NULL ); }
#line 1977 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 185 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new PointerNode( (yyvsp[0].nodetype), NULL ); }
#line 1983 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 186 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new PointerNode( NULL, (yyvsp[0].nodetype) ); }
#line 1989 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 187 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new PointerNode( (yyvsp[-1].nodetype), (yyvsp[0].nodetype) ); }
#line 1995 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 191 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2001 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 192 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new QualifierListNode( (yyvsp[-1].nodetype), (yyvsp[0].nodetype) ); }
#line 2007 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 196 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2013 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 197 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new InitializerNode( (yyvsp[-1].nodetype) ); }
#line 2019 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 201 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2025 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 202 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new InitializerListNode( (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2031 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 207 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new FunctionDeclarationNode( (yyvsp[-2].nodetype), (yyvsp[-1].nodetype), (yyvsp[0].nodetype) ); }
#line 2037 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 208 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new FunctionDeclarationNode( NULL, (yyvsp[-1].nodetype), (yyvsp[0].nodetype) ); }
#line 2043 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 213 "src/parser.y" /* yacc.c:1646  */
    {
            (yyval.nodetype) = new FunctionDeclarationNode(
                  (yyvsp[-3].nodetype), 
                  new DirectDeclarationNode( "forward declaration", (yyvsp[-2].nodetype), (yyvsp[-1].nodetype) ), 
                  NULL
            ); 
      }
#line 2055 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 222 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2061 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 223 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new ParameterTypeListNode ((yyvsp[-2].nodetype), new Ellipsis( *(yyvsp[0].string) )); }
#line 2067 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 227 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2073 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 228 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new ParameterListNode( (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2079 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 232 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new ParameterDeclarationNode( (yyvsp[-1].nodetype), (yyvsp[0].nodetype) ); }
#line 2085 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 233 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new ParameterDeclarationNode( (yyvsp[-1].nodetype), (yyvsp[0].nodetype) ); }
#line 2091 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 234 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new ParameterDeclarationNode( (yyvsp[0].nodetype), NULL ); }
#line 2097 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 238 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new Variable( *(yyvsp[0].string) ); }
#line 2103 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 239 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new IdentifierListNode( (yyvsp[-2].nodetype), new Variable( *(yyvsp[0].string) ) ); }
#line 2109 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 243 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new CompoundStatementNode( NULL ); }
#line 2115 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 244 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new CompoundStatementNode( (yyvsp[-1].nodetype) ); }
#line 2121 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 248 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2127 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 249 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new CompoundListNode( (yyvsp[-1].nodetype), (yyvsp[0].nodetype) ); }
#line 2133 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 253 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2139 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 254 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2145 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 258 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2151 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 259 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new DeclarationListNode( (yyvsp[-1].nodetype), (yyvsp[0].nodetype) ); }
#line 2157 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 263 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2163 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 264 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new StatementListNode( (yyvsp[-1].nodetype), (yyvsp[0].nodetype) ); }
#line 2169 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 269 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2175 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 270 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2181 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 271 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2187 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 272 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2193 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 273 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2199 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 274 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2205 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 278 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new LabelledStatementNode( (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2211 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 279 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new LabelledStatementNode( (yyvsp[-1].nodetype), NULL ); }
#line 2217 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 283 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new Variable( *(yyvsp[0].string) ); }
#line 2223 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 284 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2229 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 285 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = NULL; }
#line 2235 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 289 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new ExpressionStatementNode( NULL ); }
#line 2241 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 290 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new ExpressionStatementNode( (yyvsp[-1].nodetype) ); }
#line 2247 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 294 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new SelectionNode( "if", (yyvsp[-2].nodetype), (yyvsp[0].nodetype), NULL ); }
#line 2253 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 295 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new SelectionNode( "if else", (yyvsp[-4].nodetype), (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2259 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 296 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new SelectionNode( "switch", (yyvsp[-2].nodetype), (yyvsp[0].nodetype), NULL ); }
#line 2265 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 300 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new IterationNode( "while", (yyvsp[-2].nodetype), NULL, NULL, (yyvsp[0].nodetype) ); }
#line 2271 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 301 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new IterationNode( "do", (yyvsp[-2].nodetype), NULL, NULL, (yyvsp[-5].nodetype) ); }
#line 2277 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 303 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new IterationNode( "for", (yyvsp[-3].nodetype), (yyvsp[-2].nodetype), NULL, (yyvsp[0].nodetype) ); }
#line 2283 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 305 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new IterationNode( "for", (yyvsp[-4].nodetype), (yyvsp[-3].nodetype), (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2289 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 309 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new ExpressionStatementNode( (yyvsp[0].nodetype) ); }
#line 2295 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 310 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2301 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 314 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new ExpressionStatementNode( (yyvsp[0].nodetype) ); }
#line 2307 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 316 "src/parser.y" /* yacc.c:1646  */
    { 
                        (yyval.nodetype) = new VariableDeclarationNode(
                              (yyvsp[-4].nodetype), 
                              new InitDeclarationNode( (yyvsp[-3].nodetype), (yyvsp[-1].nodetype) )
                        ); 
                  }
#line 2318 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 325 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new JumpNode( "return", NULL); }
#line 2324 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 326 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new JumpNode( "return", (yyvsp[-1].nodetype) ); }
#line 2330 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 327 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new JumpNode( "continue", NULL ); }
#line 2336 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 328 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new JumpNode( "break", NULL ); }
#line 2342 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 338 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2348 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 343 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2354 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 344 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new ExpressionNode( (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2360 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 348 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2366 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 349 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new AssignmentExprNode( "assign", (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2372 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 350 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new AssignmentExprNode( "+=", (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2378 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 351 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new AssignmentExprNode( "-=", (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2384 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 352 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new AssignmentExprNode( "*=", (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2390 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 353 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new AssignmentExprNode( "/=", (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2396 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 354 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new AssignmentExprNode( "%=", (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2402 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 355 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new AssignmentExprNode( "<<=", (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2408 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 356 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new AssignmentExprNode( ">>=", (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2414 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 357 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new AssignmentExprNode( "&=", (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2420 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 358 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new AssignmentExprNode( "^=", (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2426 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 359 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new AssignmentExprNode( "|=", (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2432 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 363 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2438 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 364 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new ConditionalExprNode( (yyvsp[-4].nodetype), (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2444 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 365 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new ConditionalExprNode( (yyvsp[-3].nodetype), NULL, (yyvsp[0].nodetype) ); }
#line 2450 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 369 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2456 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 370 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new LogicalExprNode( "||", (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2462 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 374 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2468 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 375 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new LogicalExprNode( "&&", (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2474 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 379 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2480 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 380 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new BitExprNode( "|" , (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2486 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 384 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2492 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 385 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new BitExprNode( "^", (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2498 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 389 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2504 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 390 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new BitExprNode( "&", (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2510 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 394 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2516 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 395 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new LogicalExprNode( "==", (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2522 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 396 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new LogicalExprNode( "!=", (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2528 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 400 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2534 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 401 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new LogicalExprNode( ">", (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2540 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 402 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new LogicalExprNode( "<", (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2546 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 403 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new LogicalExprNode( ">=", (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2552 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 404 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new LogicalExprNode( "<=", (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2558 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 408 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2564 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 409 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new ShiftExprNode( "<<", (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2570 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 410 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new ShiftExprNode( ">>", (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2576 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 414 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2582 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 415 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new AlgebraExprNode( "+", (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2588 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 416 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new AlgebraExprNode( "-", (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2594 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 420 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2600 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 421 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new AlgebraExprNode( "*", (yyvsp[-2].nodetype), (yyvsp[0].nodetype)); }
#line 2606 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 422 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new AlgebraExprNode( "/", (yyvsp[-2].nodetype), (yyvsp[0].nodetype)); }
#line 2612 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 423 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new AlgebraExprNode( "%", (yyvsp[-2].nodetype), (yyvsp[0].nodetype)); }
#line 2618 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 427 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2624 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 428 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new CastExprNode( (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2630 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 432 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2636 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 433 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new UnaryExprNode( "++_", (yyvsp[0].nodetype) ); }
#line 2642 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 434 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new UnaryExprNode( "--_", (yyvsp[0].nodetype) ); }
#line 2648 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 435 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new UnaryExprNode( "&_", (yyvsp[0].nodetype) ); }
#line 2654 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 436 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new UnaryExprNode( "*_", (yyvsp[0].nodetype) ); }
#line 2660 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 437 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new UnaryExprNode( "+_", (yyvsp[0].nodetype) ); }
#line 2666 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 438 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new UnaryExprNode( "-_", (yyvsp[0].nodetype) ); }
#line 2672 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 439 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new UnaryExprNode( "~_", (yyvsp[0].nodetype) ); }
#line 2678 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 440 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new UnaryExprNode( "!", (yyvsp[0].nodetype) ); }
#line 2684 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 441 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new UnaryExprNode( "sizeof", (yyvsp[0].nodetype) ); }
#line 2690 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 442 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new UnaryExprNode( "sizeof", (yyvsp[-1].nodetype) ); }
#line 2696 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 446 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2702 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 447 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new PostFixExprNode( "array element call", (yyvsp[-3].nodetype), (yyvsp[-1].nodetype), NULL ); }
#line 2708 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 448 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new PostFixExprNode( "direct function call", (yyvsp[-2].nodetype), NULL, NULL ); }
#line 2714 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 449 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new PostFixExprNode( "direct function call", (yyvsp[-3].nodetype), NULL, (yyvsp[-1].nodetype) ); }
#line 2720 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 451 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new PostFixExprNode( "_++", (yyvsp[-1].nodetype), NULL, NULL ); }
#line 2726 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 172:
#line 452 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new PostFixExprNode( "_--", (yyvsp[-1].nodetype), NULL, NULL ); }
#line 2732 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 173:
#line 456 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2738 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 174:
#line 457 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new ArgumentExprNode( (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2744 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 175:
#line 461 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new Variable( *(yyvsp[0].string) ); }
#line 2750 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 176:
#line 462 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new Number( (yyvsp[0].number) ); }
#line 2756 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 177:
#line 463 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new String( *(yyvsp[0].string) ); }
#line 2762 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 178:
#line 464 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new PrimaryExprNode( (yyvsp[-1].nodetype) ); }
#line 2768 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 179:
#line 469 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new TypeNameNode( (yyvsp[0].nodetype), NULL ); }
#line 2774 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 180:
#line 470 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new TypeNameNode( (yyvsp[-1].nodetype), (yyvsp[0].nodetype) ); }
#line 2780 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 181:
#line 474 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2786 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 182:
#line 475 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2792 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 183:
#line 476 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new SpecifierQualifierListNode( (yyvsp[-1].nodetype), (yyvsp[0].nodetype) ); }
#line 2798 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 184:
#line 477 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new SpecifierQualifierListNode( (yyvsp[-1].nodetype), (yyvsp[0].nodetype) ); }
#line 2804 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 185:
#line 481 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new AbstractDeclaratorNode( (yyvsp[0].nodetype), NULL ); }
#line 2810 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 186:
#line 482 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new AbstractDeclaratorNode( NULL, (yyvsp[0].nodetype) ); }
#line 2816 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 187:
#line 483 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new AbstractDeclaratorNode( (yyvsp[-1].nodetype), (yyvsp[0].nodetype) ); }
#line 2822 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 188:
#line 487 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new DirectAbstractDeclaratorNode( "bracketed abstract declarator", (yyvsp[-1].nodetype), NULL ); }
#line 2828 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 189:
#line 488 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2834 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 190:
#line 490 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new DirectAbstractDeclaratorNode( "direct abstract declarator", (yyvsp[-1].nodetype), (yyvsp[0].nodetype) ); }
#line 2840 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 191:
#line 494 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new AbstractDeclaratorParameterNode( "square abstract parameter", NULL ); }
#line 2846 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 192:
#line 495 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new AbstractDeclaratorParameterNode( "square abstract parameter", (yyvsp[-1].nodetype) ); }
#line 2852 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 193:
#line 496 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new AbstractDeclaratorParameterNode( "round abstract parameter", NULL ); }
#line 2858 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 194:
#line 497 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new AbstractDeclaratorParameterNode( "round abstract parameter", (yyvsp[-1].nodetype) ); }
#line 2864 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 195:
#line 501 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new EnumSpecifierNode( (yyvsp[-1].nodetype), std::string() ); }
#line 2870 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 196:
#line 502 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new EnumSpecifierNode( (yyvsp[-1].nodetype), *(yyvsp[-3].string) );   }
#line 2876 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 197:
#line 503 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new EnumSpecifierNode( NULL, *(yyvsp[0].string) ); }
#line 2882 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 198:
#line 507 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = (yyvsp[0].nodetype); }
#line 2888 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 199:
#line 508 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new EnumeratorListNode( (yyvsp[-2].nodetype), (yyvsp[0].nodetype) ); }
#line 2894 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 200:
#line 512 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new EnumeratorNode( *(yyvsp[0].string) , NULL ); }
#line 2900 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 201:
#line 513 "src/parser.y" /* yacc.c:1646  */
    { (yyval.nodetype) = new EnumeratorNode( *(yyvsp[-2].string) , (yyvsp[0].nodetype) ); }
#line 2906 "src/parser.tab.cpp" /* yacc.c:1646  */
    break;


#line 2910 "src/parser.tab.cpp" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 516 "src/parser.y" /* yacc.c:1906  */

const Tree *g_root; // Definition of variable (to match declaration earlier)

const Tree *parseAST(char* a, char* b){
  g_root=0;

  yyin = fopen(a, "r");
  if(yyin) { 
	  yyparse();
  }
  fclose(yyin);
	
  return g_root;
}
