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

#ifndef YY_YY_INTERPRETOR_TAB_H_INCLUDED
# define YY_YY_INTERPRETOR_TAB_H_INCLUDED
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
    TOK_PLUS = 258,                /* TOK_PLUS  */
    TOK_MINUS = 259,               /* TOK_MINUS  */
    TOK_MULTIPLY = 260,            /* TOK_MULTIPLY  */
    TOK_DIVIDE = 261,              /* TOK_DIVIDE  */
    TOK_LEFT = 262,                /* TOK_LEFT  */
    TOK_RIGHT = 263,               /* TOK_RIGHT  */
    TOK_PRINT = 264,               /* TOK_PRINT  */
    TOK_ERROR = 265,               /* TOK_ERROR  */
    TOK_DECLARE_INT = 266,         /* TOK_DECLARE_INT  */
    TOK_DECLARE_FLOAT = 267,       /* TOK_DECLARE_FLOAT  */
    TOK_DECLARE_DOUBLE = 268,      /* TOK_DECLARE_DOUBLE  */
    TOK_IF = 269,                  /* TOK_IF  */
    TOK_ELSE = 270,                /* TOK_ELSE  */
    TOK_WHILE = 271,               /* TOK_WHILE  */
    TOK_GREATER_THAN = 272,        /* TOK_GREATER_THAN  */
    TOK_LESS_THAN = 273,           /* TOK_LESS_THAN  */
    TOK_EQUALS = 274,              /* TOK_EQUALS  */
    TOK_SCANF = 275,               /* TOK_SCANF  */
    TOK_PRINTF = 276,              /* TOK_PRINTF  */
    TOK_GHILIMEA = 277,            /* TOK_GHILIMEA  */
    TOK_MODULO_D = 278,            /* TOK_MODULO_D  */
    TOK_MODULO_F = 279,            /* TOK_MODULO_F  */
    TOK_INT = 280,                 /* TOK_INT  */
    TOK_DOUBLE = 281,              /* TOK_DOUBLE  */
    TOK_FLOAT = 282,               /* TOK_FLOAT  */
    TOK_VARIABLE = 283             /* TOK_VARIABLE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 335 "interpretor.y"
 char* sir; int val_int; double val_double; float val_float; 

#line 95 "interpretor.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);


#endif /* !YY_YY_INTERPRETOR_TAB_H_INCLUDED  */
