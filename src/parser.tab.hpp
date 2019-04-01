/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 1 "src/parser.y" /* yacc.c:1909  */

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


#line 62 "src/parser.tab.hpp" /* yacc.c:1909  */

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
#line 23 "src/parser.y" /* yacc.c:1909  */

  Tree *nodetype;

  double number;
  std::string *string;

#line 161 "src/parser.tab.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_PARSER_TAB_HPP_INCLUDED  */
