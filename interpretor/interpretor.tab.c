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
#line 1 "interpretor.y"

	using namespace std;

	#include <iostream>
	#include <stdio.h>
	#include <string.h>
	#include <iomanip>

	int yylex();
	int yyerror(const char *msg);

	int intraInIF =0;
    int EsteCorecta = 1;
	char msg[500];

	class TVAR
	{
	    char* nume;
    	int intValoare;
    	float floatValoare;
    	double doubleValoare;
    	int tipValoare; 
		//0 pentru int, 1 pentru float, 2 pentru double
    	TVAR* next;
	  
	public:
	    static TVAR* head;
	    static TVAR* tail;

	    TVAR(char* n);
	    TVAR();
	    int exists(char* n);
        void add(char* n, int tip, int intVal= -1,float floatVal= 0.0f, double doubleVal= 0.0);
		int getTipValue(char* n);
		int getIntValue(char *n);
		float getFloatValue(char* n);
		double getDoubleValue(char* n);
	    void setValue(char* n, int v);
		void setValue(char* n, float v);
    	void setValue(char* n, double v);
		void printVars();
	};

	TVAR* TVAR::head;
	TVAR* TVAR::tail;

	int GetValueBasedOnTypeInt(char* var, int tip, TVAR* ts) {
    switch(tip) {
        case 0:
            return ts->getIntValue(var);
        case 1:
            return ts->getFloatValue(var);
        case 2:
            return ts->getDoubleValue(var);
        default:
            break;
   		}
    return 0;
	}

	float GetValueBasedOnTypeFloat(char* var, int tip, TVAR* ts) {
    switch(tip) {
        case 0:
            return ts->getIntValue(var);
        case 1:
            return ts->getFloatValue(var);
        case 2:
            return ts->getDoubleValue(var);
        default:
            break;
    	}
    return 0.0f;
	}

	double GetValueBasedOnTypeDouble(char* var, int tip, TVAR* ts) {
    switch(tip) {
        case 0:
            return ts->getIntValue(var);
        case 1:
            return ts->getFloatValue(var);
        case 2:
            return ts->getDoubleValue(var);
        default:
            break;
  		}
    return 0.0;
	}

	int OperatieMatematica(char* var1, char* var2, char operand, TVAR* ts) {
    	int tip1 = ts->getTipValue(var1);
   	 	int tip2 = ts->getTipValue(var2);
    	int val1, val2;

    	val1 = GetValueBasedOnTypeInt(var1, tip1, ts);
    	val2 = GetValueBasedOnTypeInt(var2, tip2, ts);

   	 	switch(operand) {
        	case '+':
            	return val1 + val2;
        	case '-':
            	return val1 - val2;
        	case '*':
            	return val1 * val2;
        	case '/':
				if(val2 == 0)
				{
					printf("Eroare impartire 0!");
	   			} 
	  			else 
				{ 
                	return val1 / val2;
				}
        	default:
            break;
    		}
   	 	return 0;
	}

	float OperatieMatematicaFloat(char* var1, char* var2, char operand, TVAR* ts) {
    	int tip1 = ts->getTipValue(var1);
   	 	int tip2 = ts->getTipValue(var2);
    	float val1, val2;

    	val1 = GetValueBasedOnTypeFloat(var1, tip1, ts);
    	val2 = GetValueBasedOnTypeFloat(var2, tip2, ts);

   	 	switch(operand) {
        	case '+':
            	return val1 + val2;
        	case '-':
            	return val1 - val2;
        	case '*':
            	return val1 * val2;
        	case '/':
				if(val2 == 0)
				{
					printf("Eroare impartire 0!");
	   			} 
	  			else 
				{ 
                	return val1 / val2;
				}
        	default:
            break;
    		}
   	 	return 0;
	}

	double OperatieMatematicaDouble(char* var1, char* var2, char operand, TVAR* ts) {
    	int tip1 = ts->getTipValue(var1);
   	 	int tip2 = ts->getTipValue(var2);
    	double val1, val2;

    	val1 = GetValueBasedOnTypeDouble(var1, tip1, ts);
    	val2 = GetValueBasedOnTypeDouble(var2, tip2, ts);

   	 	switch(operand) {
        	case '+':
            	return val1 + val2;
        	case '-':
            	return val1 - val2;
        	case '*':
            	return val1 * val2;
        	case '/':
				if(val2 == 0)
				{
					printf("Eroare impartire 0!");
	   			} 
	  			else 
				{ 
                	return val1 / val2;
				}
        	default:
            break;
    		}
   	 	return 0;
	}

	TVAR::TVAR(char* n){
		this->nume = new char[strlen(n)+1];
		strcpy(this->nume, n);
		this->next = NULL;
	}

	TVAR::TVAR(){
		TVAR::head = NULL;
		TVAR::tail = NULL;
	}

	int TVAR::exists(char* n){
		TVAR* tmp = TVAR::head;
		while(tmp != NULL) 
		{ 
			if(strcmp(tmp->nume,n) == 0)
	      		return 1;
        	tmp = tmp->next;
	  	}
	  	return 0;
	}

    void TVAR::add(char* n, int tip, int intVal, float floatVal, double doubleVal){
		TVAR* elem = new TVAR(n);

		switch(tip)
	{
	case 0: //int
        elem->intValoare = intVal;
        elem->tipValoare = 0;
        break;
    case 1: //float
        elem->floatValoare = floatVal;
        elem->tipValoare = 1;
        break;
    case 2: //double
        elem->doubleValoare = doubleVal;
        elem->tipValoare = 2;
        break;
    default:
        break;
		}

		if(head == NULL)
		{ 
			TVAR::head = TVAR::tail = elem;
		}
		else 
		{
			TVAR::tail->next = elem;
			TVAR::tail = elem;
		}
	}

	int TVAR::getTipValue(char* n){
		TVAR* tmp = TVAR::head;
		while(tmp != NULL)
		{
			if(strcmp(tmp->nume, n)==0)
				return tmp->tipValoare;
			tmp=tmp->next;
		}
		return -1;
	}

    int TVAR::getIntValue(char* n){
		TVAR* tmp = TVAR::head;
		while(tmp != NULL)
		{
			if(strcmp(tmp->nume,n) == 0)
				return tmp->intValoare;
	     	tmp = tmp->next;
	    }
		return -1;
	}

	float TVAR::getFloatValue(char* n){
		TVAR* tmp = TVAR::head;
		while(tmp != NULL)
		{
			if(strcmp(tmp->nume,n) == 0)
				return tmp->floatValoare;
	     	tmp = tmp->next;
	    }
		return -1.0f;
	}

	double TVAR::getDoubleValue(char* n){
		TVAR* tmp = TVAR::head;
		while(tmp != NULL)
		{
			if(strcmp(tmp->nume,n) == 0)
				return tmp->doubleValoare;
	     	tmp = tmp->next;
	    }
		return -1.0;
	}

	void TVAR::setValue(char* n, int v){
		TVAR* tmp = TVAR::head;
	    while(tmp != NULL)
	    {
			if(strcmp(tmp->nume,n) == 0)
			{
				tmp->intValoare = v;
				tmp->tipValoare = 0;
			}
			tmp = tmp->next;
	    }
	}

	void TVAR::setValue(char* n, float v){
		TVAR* tmp = TVAR::head;
	    while(tmp != NULL)
	    {
			if(strcmp(tmp->nume,n) == 0)
			{
				tmp->floatValoare = v;
				tmp->tipValoare = 1;
			}
			tmp = tmp->next;
	    }
	}

	void TVAR::setValue(char* n, double v){
		TVAR* tmp = TVAR::head;
	    while(tmp != NULL)
	    {
			if(strcmp(tmp->nume,n) == 0)
			{
				tmp->doubleValoare = v;
				tmp->tipValoare = 2;
			}
			tmp = tmp->next;
	    }
	}

	void TVAR::printVars(){
		cout<<"\nPrinting table of variables...\n";
		TVAR* tmp = TVAR::head;
		while(tmp != NULL)
		{
			cout<<tmp->nume<<"=";
			if(tmp->tipValoare == 0)
				cout<<tmp->intValoare<<"\n";
			else if(tmp->tipValoare == 1)
				cout<<setprecision(2)<<tmp->floatValoare<<"f\n";
			else if(tmp->tipValoare == 2)
				cout<<setprecision(2)<<tmp->doubleValoare<<"\n";
			tmp = tmp->next;
		}	  
	}

	TVAR* ts = NULL;

#line 405 "interpretor.tab.c"

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

#include "interpretor.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOK_PLUS = 3,                   /* TOK_PLUS  */
  YYSYMBOL_TOK_MINUS = 4,                  /* TOK_MINUS  */
  YYSYMBOL_TOK_MULTIPLY = 5,               /* TOK_MULTIPLY  */
  YYSYMBOL_TOK_DIVIDE = 6,                 /* TOK_DIVIDE  */
  YYSYMBOL_TOK_LEFT = 7,                   /* TOK_LEFT  */
  YYSYMBOL_TOK_RIGHT = 8,                  /* TOK_RIGHT  */
  YYSYMBOL_TOK_PRINT = 9,                  /* TOK_PRINT  */
  YYSYMBOL_TOK_ERROR = 10,                 /* TOK_ERROR  */
  YYSYMBOL_TOK_DECLARE_INT = 11,           /* TOK_DECLARE_INT  */
  YYSYMBOL_TOK_DECLARE_FLOAT = 12,         /* TOK_DECLARE_FLOAT  */
  YYSYMBOL_TOK_DECLARE_DOUBLE = 13,        /* TOK_DECLARE_DOUBLE  */
  YYSYMBOL_TOK_IF = 14,                    /* TOK_IF  */
  YYSYMBOL_TOK_ELSE = 15,                  /* TOK_ELSE  */
  YYSYMBOL_TOK_WHILE = 16,                 /* TOK_WHILE  */
  YYSYMBOL_TOK_GREATER_THAN = 17,          /* TOK_GREATER_THAN  */
  YYSYMBOL_TOK_LESS_THAN = 18,             /* TOK_LESS_THAN  */
  YYSYMBOL_TOK_EQUALS = 19,                /* TOK_EQUALS  */
  YYSYMBOL_TOK_SCANF = 20,                 /* TOK_SCANF  */
  YYSYMBOL_TOK_PRINTF = 21,                /* TOK_PRINTF  */
  YYSYMBOL_TOK_GHILIMEA = 22,              /* TOK_GHILIMEA  */
  YYSYMBOL_TOK_MODULO_D = 23,              /* TOK_MODULO_D  */
  YYSYMBOL_TOK_MODULO_F = 24,              /* TOK_MODULO_F  */
  YYSYMBOL_TOK_INT = 25,                   /* TOK_INT  */
  YYSYMBOL_TOK_DOUBLE = 26,                /* TOK_DOUBLE  */
  YYSYMBOL_TOK_FLOAT = 27,                 /* TOK_FLOAT  */
  YYSYMBOL_TOK_VARIABLE = 28,              /* TOK_VARIABLE  */
  YYSYMBOL_29_ = 29,                       /* ';'  */
  YYSYMBOL_30_ = 30,                       /* '{'  */
  YYSYMBOL_31_ = 31,                       /* '='  */
  YYSYMBOL_32_ = 32,                       /* '}'  */
  YYSYMBOL_33_ = 33,                       /* ','  */
  YYSYMBOL_34_ = 34,                       /* '&'  */
  YYSYMBOL_YYACCEPT = 35,                  /* $accept  */
  YYSYMBOL_S = 36,                         /* S  */
  YYSYMBOL_CONTROL = 37,                   /* CONTROL  */
  YYSYMBOL_IF_STATEMENT = 38,              /* IF_STATEMENT  */
  YYSYMBOL_WHILE_STATEMENT = 39,           /* WHILE_STATEMENT  */
  YYSYMBOL_EXPRESSION = 40,                /* EXPRESSION  */
  YYSYMBOL_INPUT_OUTPUT = 41,              /* INPUT_OUTPUT  */
  YYSYMBOL_I = 42,                         /* I  */
  YYSYMBOL_E = 43,                         /* E  */
  YYSYMBOL_D = 44,                         /* D  */
  YYSYMBOL_F = 45                          /* F  */
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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  26
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   396

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  11
/* YYNRULES -- Number of rules.  */
#define YYNRULES  90
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  263

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   283


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
       2,     2,     2,     2,     2,     2,     2,     2,    34,     2,
       2,     2,     2,     2,    33,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    29,
       2,    31,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    30,     2,    32,     2,     2,     2,     2,
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
      25,    26,    27,    28
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   368,   368,   369,   370,   371,   372,   374,   375,   377,
     388,   399,   408,   498,   510,   525,   540,   555,   570,   576,
     577,   578,   579,   580,   581,   582,   583,   584,   585,   587,
     588,   595,   598,   600,   607,   614,   618,   640,   662,   684,
     705,   726,   742,   758,   774,   789,   804,   820,   841,   902,
     903,   904,   905,   918,   919,   920,   921,   922,   923,   924,
     925,   926,   927,   929,   930,   931,   932,   945,   946,   947,
     948,   949,   950,   951,   952,   953,   954,   956,   957,   958,
     959,   972,   973,   974,   975,   976,   977,   978,   979,   980,
     981
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
  "\"end of file\"", "error", "\"invalid token\"", "TOK_PLUS",
  "TOK_MINUS", "TOK_MULTIPLY", "TOK_DIVIDE", "TOK_LEFT", "TOK_RIGHT",
  "TOK_PRINT", "TOK_ERROR", "TOK_DECLARE_INT", "TOK_DECLARE_FLOAT",
  "TOK_DECLARE_DOUBLE", "TOK_IF", "TOK_ELSE", "TOK_WHILE",
  "TOK_GREATER_THAN", "TOK_LESS_THAN", "TOK_EQUALS", "TOK_SCANF",
  "TOK_PRINTF", "TOK_GHILIMEA", "TOK_MODULO_D", "TOK_MODULO_F", "TOK_INT",
  "TOK_DOUBLE", "TOK_FLOAT", "TOK_VARIABLE", "';'", "'{'", "'='", "'}'",
  "','", "'&'", "$accept", "S", "CONTROL", "IF_STATEMENT",
  "WHILE_STATEMENT", "EXPRESSION", "INPUT_OUTPUT", "I", "E", "D", "F", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-35)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     194,   -21,   -35,   -16,    18,    82,     2,   101,   120,   132,
     110,   158,   194,   -35,   -35,   134,   135,   -35,   144,   146,
     149,    53,    59,   168,   187,    -1,   -35,   -35,   194,   194,
      -4,    11,    54,    53,   -35,   260,   175,   270,   277,   183,
     184,   185,    -1,   -35,   -35,   195,   233,   287,   312,   -35,
     -35,   200,   -35,   212,   -35,   213,   -35,   217,   253,    64,
      65,    66,    70,    75,    76,    81,   203,    89,    89,    89,
      89,    89,    89,    89,    75,    76,   210,   227,    52,   166,
     226,   294,    90,    98,   100,   104,   109,   109,   109,   109,
      92,    92,    92,    92,   243,   244,   245,   -35,   -35,    89,
     316,    14,   316,    14,   316,   -35,   316,   -35,   316,   233,
     316,   233,   316,   233,   207,   316,    14,    14,   -35,   -35,
     233,   233,   233,   300,   306,   234,   235,   252,   -17,   247,
     -35,   -35,   316,    14,   316,    14,   316,   -35,   316,   -35,
     109,   320,    31,    31,   -35,   -35,    92,   324,    80,    80,
     -35,   -35,   239,   256,   257,   255,   269,   283,   309,   276,
     308,   307,   -35,   310,   322,   313,   115,   117,   129,   131,
     137,   148,   153,   154,   -35,   -35,   -35,     3,   327,   317,
     319,     7,   -35,   321,   323,   315,   325,   316,    14,   316,
      14,   316,   -35,   316,   -35,   316,    14,   316,    14,   316,
     -35,   316,   -35,   328,   326,   329,   330,   332,   342,   344,
     331,   346,   159,   160,   194,   334,   335,   161,   169,   -35,
     347,   -35,   336,   337,   338,   127,   130,   339,   -35,   -35,
     -35,   -35,   340,   341,   -35,   333,   349,   350,   351,   345,
     352,   354,   353,   355,   356,   357,   -35,   348,   358,   359,
     360,   361,   362,   194,   194,   -35,   -35,   -35,   -35,   363,
     364,   -35,   -35
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     6,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     2,     7,     8,     0,     0,    48,    39,    40,
      47,     0,     0,     0,     0,     0,     1,     5,     2,     2,
       0,     0,     0,     0,    54,     0,     0,     0,     0,     0,
       0,     0,     0,    68,    82,     0,    36,    38,    37,     4,
       3,     0,    46,     0,    44,     0,    45,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    28,    53,     0,
      55,    59,    56,    60,    57,    61,    58,    62,    25,    22,
      26,    23,    27,    24,     2,     0,    49,    50,    51,    52,
      19,    20,    21,     0,     0,     2,     0,     0,     0,     0,
      67,    81,    55,    59,    56,    60,    57,    61,    58,    62,
       0,     0,    63,    64,    65,    66,     0,     0,    77,    78,
      79,    80,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    29,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    43,    42,    41,     0,    12,     0,
       0,     0,    18,     0,     0,     0,     0,    69,    73,    70,
      74,    71,    75,    72,    76,    83,    87,    84,    88,    85,
      89,    86,    90,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     2,     0,     0,     0,     0,    32,
       0,    35,    54,    54,     0,     0,     0,    54,    30,    33,
      34,    31,     0,     0,    11,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    13,     0,     0,     0,
       0,     0,     0,     2,     2,    16,    14,    17,    15,     0,
       0,     9,    10
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -35,   -12,   -35,   -35,   -35,   -18,   -35,   -35,   -20,   -19,
     -34
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    11,    12,    13,    14,    36,    15,    16,    46,    47,
      48
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      27,    37,    37,    51,    39,   163,    42,    17,    81,    21,
      42,   164,    18,    58,    42,    57,    49,    50,    53,    69,
      70,    52,    79,    80,    34,    43,    44,    45,    34,    43,
      44,   203,    34,    43,    44,   207,    88,    89,    54,   101,
     103,   105,   107,   109,   111,   113,    19,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   148,   149,   150,   151,
      33,    55,   133,   135,   137,   139,    33,   142,   143,   144,
     145,    99,    99,    99,   127,   128,   129,    99,    34,    79,
      56,    35,    99,    99,    34,    92,    93,    38,    99,    34,
      34,    34,   100,   102,   104,    34,    99,    99,   106,   146,
      34,    34,   156,   108,   110,    99,    34,    99,    22,   112,
      20,    99,    81,   160,    34,    34,   140,   115,   132,    44,
     147,    80,    99,    34,    99,    34,   134,    23,   136,    34,
     235,   236,   138,   237,   238,    43,    99,   141,    99,    24,
      34,    25,    34,   187,    99,   189,   188,   190,   192,   194,
     196,   198,   200,   202,    34,    99,    34,   191,    26,   193,
      99,    99,    34,    28,    29,   195,    99,    99,    99,    67,
      68,    69,    70,    34,    98,    30,   197,    31,    34,    34,
      32,   199,   201,    66,   222,   223,   227,   132,   134,   134,
      40,    76,   133,   135,   228,   229,   230,   135,    82,    83,
      84,    85,   224,     1,     2,     3,     4,     5,     6,    41,
       7,    94,    77,    78,     8,     9,     1,     2,     3,     4,
       5,     6,    10,     7,    95,    97,    96,     8,     9,    86,
      87,    88,    89,   114,   130,   155,    67,    68,    69,    70,
     125,   259,   260,     1,     2,     3,     4,     5,     6,   126,
       7,   152,   153,   154,     8,     9,    67,    68,    69,    70,
     162,    98,   159,    59,    60,    61,    62,   174,   161,   165,
      71,    72,    73,    67,    68,    69,    70,    63,    64,    65,
      59,    60,    61,    62,   175,   176,   177,    71,    72,    73,
      86,    87,    88,    89,    74,    75,    65,    90,    91,    92,
      93,   178,   131,    67,    68,    69,    70,   181,   157,    67,
      68,    69,    70,   179,   158,    90,    91,    92,    93,    59,
      60,    61,    62,   166,   167,   168,   169,   170,   171,   172,
     173,   212,   213,    84,    85,    82,   217,    84,    85,   180,
     182,   183,   204,   184,   185,   205,   186,   206,   210,   208,
     218,   209,   219,   211,   221,   231,   214,     0,   242,   220,
     215,   216,   225,   226,     0,   232,   233,   247,   239,   248,
     234,     0,   240,   241,   243,   244,   245,   246,   253,     0,
       0,     0,   249,     0,   250,   251,   252,     0,   254,     0,
       0,   255,   256,   257,   258,   261,   262
};

static const yytype_int16 yycheck[] =
{
      12,    21,    22,     7,    22,    22,     7,    28,    42,     7,
       7,    28,    28,    33,     7,    33,    28,    29,     7,     5,
       6,    25,    42,    42,    25,    26,    27,    28,    25,    26,
      27,    28,    25,    26,    27,    28,     5,     6,    27,    59,
      60,    61,    62,    63,    64,    65,    28,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    90,    91,    92,    93,
       7,     7,    82,    83,    84,    85,     7,    86,    87,    88,
      89,     7,     7,     7,    22,    23,    24,     7,    25,    99,
      26,    28,     7,     7,    25,     5,     6,    28,     7,    25,
      25,    25,    28,    28,    28,    25,     7,     7,    28,     7,
      25,    25,   114,    28,    28,     7,    25,     7,     7,    28,
      28,     7,   146,   125,    25,    25,     7,    28,    28,    27,
      28,   140,     7,    25,     7,    25,    28,     7,    28,    25,
       3,     4,    28,     3,     4,    26,     7,    28,     7,     7,
      25,    31,    25,    28,     7,    28,   166,   167,   168,   169,
     170,   171,   172,   173,    25,     7,    25,    28,     0,    28,
       7,     7,    25,    29,    29,    28,     7,     7,     7,     3,
       4,     5,     6,    25,     8,    31,    28,    31,    25,    25,
      31,    28,    28,     8,    25,    25,    25,    28,    28,    28,
      22,     8,   212,   213,    25,    26,    27,   217,     3,     4,
       5,     6,   214,     9,    10,    11,    12,    13,    14,    22,
      16,    11,    28,    28,    20,    21,     9,    10,    11,    12,
      13,    14,    28,    16,    12,     8,    13,    20,    21,     3,
       4,     5,     6,    30,     8,    28,     3,     4,     5,     6,
      30,   253,   254,     9,    10,    11,    12,    13,    14,    22,
      16,     8,     8,     8,    20,    21,     3,     4,     5,     6,
       8,     8,    28,     3,     4,     5,     6,    28,    33,    22,
      17,    18,    19,     3,     4,     5,     6,    17,    18,    19,
       3,     4,     5,     6,    28,    28,    31,    17,    18,    19,
       3,     4,     5,     6,    17,    18,    19,     3,     4,     5,
       6,    32,     8,     3,     4,     5,     6,    31,     8,     3,
       4,     5,     6,    30,     8,     3,     4,     5,     6,     3,
       4,     5,     6,     3,     4,     5,     6,     3,     4,     5,
       6,     3,     4,     5,     6,     3,     4,     5,     6,    30,
      32,    34,    15,    33,    22,    28,    33,    28,    33,    28,
       8,    28,     8,    28,     8,     8,    30,    -1,    25,    28,
      31,    31,    28,    28,    -1,    29,    29,    15,    29,    15,
      32,    -1,    32,    32,    25,    25,    25,    32,    30,    -1,
      -1,    -1,    29,    -1,    29,    29,    29,    -1,    30,    -1,
      -1,    32,    32,    32,    32,    32,    32
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     9,    10,    11,    12,    13,    14,    16,    20,    21,
      28,    36,    37,    38,    39,    41,    42,    28,    28,    28,
      28,     7,     7,     7,     7,    31,     0,    36,    29,    29,
      31,    31,    31,     7,    25,    28,    40,    43,    28,    40,
      22,    22,     7,    26,    27,    28,    43,    44,    45,    36,
      36,     7,    25,     7,    27,     7,    26,    40,    43,     3,
       4,     5,     6,    17,    18,    19,     8,     3,     4,     5,
       6,    17,    18,    19,    17,    18,     8,    28,    28,    43,
      44,    45,     3,     4,     5,     6,     3,     4,     5,     6,
       3,     4,     5,     6,    11,    12,    13,     8,     8,     7,
      28,    43,    28,    43,    28,    43,    28,    43,    28,    43,
      28,    43,    28,    43,    30,    28,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    30,    22,    22,    23,    24,
       8,     8,    28,    43,    28,    43,    28,    43,    28,    43,
       7,    28,    44,    44,    44,    44,     7,    28,    45,    45,
      45,    45,     8,     8,     8,    28,    36,     8,     8,    28,
      36,    33,     8,    22,    28,    22,     3,     4,     5,     6,
       3,     4,     5,     6,    28,    28,    28,    31,    32,    30,
      30,    31,    32,    34,    33,    22,    33,    28,    43,    28,
      43,    28,    43,    28,    43,    28,    43,    28,    43,    28,
      43,    28,    43,    28,    15,    28,    28,    28,    28,    28,
      33,    28,     3,     4,    30,    31,    31,     4,     8,     8,
      28,     8,    25,    25,    36,    28,    28,    25,    25,    26,
      27,     8,    29,    29,    32,     3,     4,     3,     4,    29,
      32,    32,    25,    25,    25,    25,    32,    15,    15,    29,
      29,    29,    29,    30,    30,    32,    32,    32,    32,    36,
      36,    32,    32
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    35,    36,    36,    36,    36,    36,    37,    37,    38,
      38,    38,    38,    39,    39,    39,    39,    39,    39,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    41,
      41,    41,    41,    41,    41,    41,    42,    42,    42,    42,
      42,    42,    42,    42,    42,    42,    42,    42,    42,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    44,    44,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    45,    45,
      45
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     3,     3,     2,     1,     1,     1,    16,
      16,    11,     7,    12,    14,    14,    14,    14,     7,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     6,
      10,    10,     9,    10,    10,     9,     3,     3,     3,     2,
       2,     7,     7,     7,     4,     4,     4,     2,     2,     3,
       3,     3,     3,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     3,     3,     3,     3,     3,     3,     3,
       3
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

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 6: /* S: TOK_ERROR  */
#line 372 "interpretor.y"
                { EsteCorecta = 0; }
#line 1734 "interpretor.tab.c"
    break;

  case 9: /* IF_STATEMENT: TOK_IF TOK_LEFT EXPRESSION TOK_RIGHT '{' TOK_VARIABLE '=' TOK_VARIABLE TOK_PLUS TOK_INT ';' '}' TOK_ELSE '{' S '}'  */
#line 378 "interpretor.y"
        {
            if((yyvsp[-13].val_int) == 1){
				int value = ts->getIntValue((yyvsp[-8].sir)) + (yyvsp[-6].val_int);
				ts->setValue((yyvsp[-10].sir),value);
                printf("IF TRUE\n");
            }
            else{
                printf("IF FALSE\n");
            }
		}
#line 1749 "interpretor.tab.c"
    break;

  case 10: /* IF_STATEMENT: TOK_IF TOK_LEFT EXPRESSION TOK_RIGHT '{' TOK_VARIABLE '=' TOK_VARIABLE TOK_MINUS TOK_INT ';' '}' TOK_ELSE '{' S '}'  */
#line 389 "interpretor.y"
                        {
				if((yyvsp[-13].val_int) == 1){
				int value = ts->getIntValue((yyvsp[-8].sir)) - (yyvsp[-6].val_int);
				ts->setValue((yyvsp[-10].sir),value);
                printf("IF TRUE\n");
            }
            else{
                printf("IF FALSE\n");
            }
			}
#line 1764 "interpretor.tab.c"
    break;

  case 11: /* IF_STATEMENT: TOK_IF TOK_LEFT EXPRESSION TOK_RIGHT '{' S '}' TOK_ELSE '{' S '}'  */
#line 400 "interpretor.y"
                {
			if((yyvsp[-8].val_int) == 1){
                printf("IF TRUE\n");
            }
            else{
                printf("IF FALSE\n");
            }
		}
#line 1777 "interpretor.tab.c"
    break;

  case 12: /* IF_STATEMENT: TOK_IF TOK_LEFT EXPRESSION TOK_RIGHT '{' S '}'  */
#line 408 "interpretor.y"
                                                                         {}
#line 1783 "interpretor.tab.c"
    break;

  case 13: /* WHILE_STATEMENT: TOK_WHILE TOK_LEFT EXPRESSION TOK_RIGHT '{' TOK_VARIABLE '=' TOK_VARIABLE TOK_MINUS TOK_INT ';' '}'  */
#line 499 "interpretor.y"
                {
					printf("WHILE\n");
					int aux,aux2;
					aux = ts->getIntValue((yyvsp[-6].sir));
					aux2 = ts->getIntValue((yyvsp[-4].sir));
					while(aux2> 1){
						aux2=aux2-(yyvsp[-2].val_int);
					}
					aux = aux2;
					ts->setValue((yyvsp[-6].sir),aux);
                }
#line 1799 "interpretor.tab.c"
    break;

  case 14: /* WHILE_STATEMENT: TOK_WHILE TOK_LEFT TOK_VARIABLE TOK_GREATER_THAN E TOK_RIGHT '{' TOK_VARIABLE '=' TOK_VARIABLE TOK_MINUS TOK_INT ';' '}'  */
#line 511 "interpretor.y"
                                {
					printf("WHILE\n");
					int expresie = ts->getIntValue((yyvsp[-11].sir));
					//$5
					int aux,aux2;
					aux = ts->getIntValue((yyvsp[-6].sir));
					aux2 = ts->getIntValue((yyvsp[-4].sir));
					while(expresie > (yyvsp[-9].val_int)){
						aux2 = aux2 - (yyvsp[-2].val_int);
						expresie = expresie - (yyvsp[-2].val_int);
					}
					aux = aux2;
					ts->setValue((yyvsp[-6].sir),aux);
				}
#line 1818 "interpretor.tab.c"
    break;

  case 15: /* WHILE_STATEMENT: TOK_WHILE TOK_LEFT TOK_VARIABLE TOK_LESS_THAN E TOK_RIGHT '{' TOK_VARIABLE '=' TOK_VARIABLE TOK_MINUS TOK_INT ';' '}'  */
#line 526 "interpretor.y"
                                {
					printf("WHILE\n");
					int expresie = ts->getIntValue((yyvsp[-11].sir));
					//$5
					int aux,aux2;
					aux = ts->getIntValue((yyvsp[-6].sir));
					aux2 = ts->getIntValue((yyvsp[-4].sir));
					while(expresie < (yyvsp[-9].val_int)){
						aux2 = aux2 - (yyvsp[-2].val_int);
						expresie = expresie - (yyvsp[-2].val_int);
					}
					aux = aux2;
					ts->setValue((yyvsp[-6].sir),aux);
				}
#line 1837 "interpretor.tab.c"
    break;

  case 16: /* WHILE_STATEMENT: TOK_WHILE TOK_LEFT TOK_VARIABLE TOK_GREATER_THAN E TOK_RIGHT '{' TOK_VARIABLE '=' TOK_VARIABLE TOK_PLUS TOK_INT ';' '}'  */
#line 541 "interpretor.y"
                                {
					printf("WHILE\n");
					int expresie = ts->getIntValue((yyvsp[-11].sir));
					//$5
					int aux,aux2;
					aux = ts->getIntValue((yyvsp[-6].sir));
					aux2 = ts->getIntValue((yyvsp[-4].sir));
					while(expresie > (yyvsp[-9].val_int)){
						aux2 = aux2 + (yyvsp[-2].val_int);
						expresie = expresie + (yyvsp[-2].val_int);
					}
					aux = aux2;
					ts->setValue((yyvsp[-6].sir),aux);
				}
#line 1856 "interpretor.tab.c"
    break;

  case 17: /* WHILE_STATEMENT: TOK_WHILE TOK_LEFT TOK_VARIABLE TOK_LESS_THAN E TOK_RIGHT '{' TOK_VARIABLE '=' TOK_VARIABLE TOK_PLUS TOK_INT ';' '}'  */
#line 556 "interpretor.y"
                                {
					printf("WHILE\n");
					int expresie = ts->getIntValue((yyvsp[-11].sir));
					//$5
					int aux,aux2;
					aux = ts->getIntValue((yyvsp[-6].sir));
					aux2 = ts->getIntValue((yyvsp[-4].sir));
					while(expresie < (yyvsp[-9].val_int)){
						aux2 = aux2 + (yyvsp[-2].val_int);
						expresie = expresie + (yyvsp[-2].val_int);
					}
					aux = aux2;
					ts->setValue((yyvsp[-6].sir),aux);
				}
#line 1875 "interpretor.tab.c"
    break;

  case 18: /* WHILE_STATEMENT: TOK_WHILE TOK_LEFT EXPRESSION TOK_RIGHT '{' S '}'  */
#line 571 "interpretor.y"
                                {
					printf("WHILE\n");
				}
#line 1883 "interpretor.tab.c"
    break;

  case 19: /* EXPRESSION: E TOK_GREATER_THAN E  */
#line 576 "interpretor.y"
                                  { (yyval.val_int) = ((yyvsp[-2].val_int) > (yyvsp[0].val_int)) ? 1 : 0; }
#line 1889 "interpretor.tab.c"
    break;

  case 20: /* EXPRESSION: E TOK_LESS_THAN E  */
#line 577 "interpretor.y"
                               { (yyval.val_int) = ((yyvsp[-2].val_int) < (yyvsp[0].val_int)) ? 1 : 0; }
#line 1895 "interpretor.tab.c"
    break;

  case 21: /* EXPRESSION: E TOK_EQUALS E  */
#line 578 "interpretor.y"
                            { (yyval.val_int) = ((yyvsp[-2].val_int) == (yyvsp[0].val_int)) ? 1 : 0; }
#line 1901 "interpretor.tab.c"
    break;

  case 22: /* EXPRESSION: TOK_VARIABLE TOK_GREATER_THAN E  */
#line 579 "interpretor.y"
                                                     { (yyval.val_int) = (ts->getIntValue((yyvsp[-2].sir)) > (yyvsp[0].val_int)) ? 1 : 0; }
#line 1907 "interpretor.tab.c"
    break;

  case 23: /* EXPRESSION: TOK_VARIABLE TOK_LESS_THAN E  */
#line 580 "interpretor.y"
                                                  { (yyval.val_int) = (ts->getIntValue((yyvsp[-2].sir)) < (yyvsp[0].val_int)) ? 1 : 0; }
#line 1913 "interpretor.tab.c"
    break;

  case 24: /* EXPRESSION: TOK_VARIABLE TOK_EQUALS E  */
#line 581 "interpretor.y"
                                               { (yyval.val_int) = (ts->getIntValue((yyvsp[-2].sir)) == (yyvsp[0].val_int)) ? 1 : 0; }
#line 1919 "interpretor.tab.c"
    break;

  case 25: /* EXPRESSION: TOK_VARIABLE TOK_GREATER_THAN TOK_VARIABLE  */
#line 582 "interpretor.y"
                                                                { (yyval.val_int) = (ts->getIntValue((yyvsp[-2].sir)) > ts->getIntValue((yyvsp[0].sir))) ? 1 : 0; }
#line 1925 "interpretor.tab.c"
    break;

  case 26: /* EXPRESSION: TOK_VARIABLE TOK_LESS_THAN TOK_VARIABLE  */
#line 583 "interpretor.y"
                                                             { (yyval.val_int) = (ts->getIntValue((yyvsp[-2].sir)) < ts->getIntValue((yyvsp[0].sir))) ? 1 : 0; }
#line 1931 "interpretor.tab.c"
    break;

  case 27: /* EXPRESSION: TOK_VARIABLE TOK_EQUALS TOK_VARIABLE  */
#line 584 "interpretor.y"
                                                          { (yyval.val_int) = (ts->getIntValue((yyvsp[-2].sir)) == ts->getIntValue((yyvsp[0].sir))) ? 1 : 0; }
#line 1937 "interpretor.tab.c"
    break;

  case 28: /* EXPRESSION: TOK_LEFT EXPRESSION TOK_RIGHT  */
#line 585 "interpretor.y"
                                           { (yyval.val_int) = (yyvsp[-1].val_int); }
#line 1943 "interpretor.tab.c"
    break;

  case 29: /* INPUT_OUTPUT: TOK_PRINTF TOK_LEFT TOK_GHILIMEA TOK_VARIABLE TOK_GHILIMEA TOK_RIGHT  */
#line 587 "interpretor.y"
                                                                                    { printf("%s",(yyvsp[-2].sir)); }
#line 1949 "interpretor.tab.c"
    break;

  case 30: /* INPUT_OUTPUT: TOK_SCANF TOK_LEFT TOK_GHILIMEA TOK_VARIABLE TOK_GHILIMEA ',' '&' TOK_VARIABLE TOK_RIGHT TOK_INT  */
#line 589 "interpretor.y"
                         {
        		printf("\n%s\n",(yyvsp[-6].sir));
				//int temp=0; NU MERGE SCANF NU STIU DE CE
				//scanf("%d", &temp);
				ts->setValue((yyvsp[-2].sir),(yyvsp[0].val_int));
    		 }
#line 1960 "interpretor.tab.c"
    break;

  case 31: /* INPUT_OUTPUT: TOK_PRINTF TOK_LEFT TOK_GHILIMEA TOK_VARIABLE TOK_MODULO_D TOK_VARIABLE TOK_GHILIMEA ',' TOK_VARIABLE TOK_RIGHT  */
#line 596 "interpretor.y"
                         { printf("%s %d %s\n",(yyvsp[-6].sir),ts->getIntValue((yyvsp[-1].sir)),(yyvsp[-4].sir)); }
#line 1966 "interpretor.tab.c"
    break;

  case 32: /* INPUT_OUTPUT: TOK_PRINTF TOK_LEFT TOK_GHILIMEA TOK_VARIABLE TOK_MODULO_D TOK_GHILIMEA ',' TOK_VARIABLE TOK_RIGHT  */
#line 599 "interpretor.y"
                         { printf("%s %d\n",(yyvsp[-5].sir),ts->getIntValue((yyvsp[-1].sir))); }
#line 1972 "interpretor.tab.c"
    break;

  case 33: /* INPUT_OUTPUT: TOK_SCANF TOK_LEFT TOK_GHILIMEA TOK_VARIABLE TOK_GHILIMEA ',' '&' TOK_VARIABLE TOK_RIGHT TOK_DOUBLE  */
#line 601 "interpretor.y"
                         {
        		printf("\n%s\n",(yyvsp[-6].sir));
				//int temp=0; NU MERGE SCANF NU STIU DE CE
				//scanf("%d", &temp);
				ts->setValue((yyvsp[-2].sir),(yyvsp[0].val_double));
    		 }
#line 1983 "interpretor.tab.c"
    break;

  case 34: /* INPUT_OUTPUT: TOK_SCANF TOK_LEFT TOK_GHILIMEA TOK_VARIABLE TOK_GHILIMEA ',' '&' TOK_VARIABLE TOK_RIGHT TOK_FLOAT  */
#line 608 "interpretor.y"
                         {
        		printf("\n%s\n",(yyvsp[-6].sir));
				//int temp=0; NU MERGE SCANF NU STIU DE CE
				//scanf("%d", &temp);
				ts->setValue((yyvsp[-2].sir),(yyvsp[0].val_float));
    		 }
#line 1994 "interpretor.tab.c"
    break;

  case 35: /* INPUT_OUTPUT: TOK_PRINTF TOK_LEFT TOK_GHILIMEA TOK_VARIABLE TOK_MODULO_F TOK_GHILIMEA ',' TOK_VARIABLE TOK_RIGHT  */
#line 615 "interpretor.y"
                         { printf("%s %.2f\n",(yyvsp[-5].sir),ts->getFloatValue((yyvsp[-1].sir))); }
#line 2000 "interpretor.tab.c"
    break;

  case 36: /* I: TOK_VARIABLE '=' E  */
#line 619 "interpretor.y"
    {
		if(ts != NULL)
		{
			if(ts->exists((yyvsp[-2].sir)) == 1)
			{
				ts->setValue((yyvsp[-2].sir), (yyvsp[0].val_int));
			}
			else 
			{
				sprintf(msg,"%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost declarata!",(yylsp[-2]).first_line, (yylsp[-2]).first_column, (yyvsp[-2].sir));
	    		yyerror(msg);
	    		YYERROR;
	  		}
		}
		else
		{
	  		sprintf(msg,"%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost declarata!", (yylsp[-2]).first_line, (yylsp[-2]).first_column, (yyvsp[-2].sir));
	  		yyerror(msg);
	  		YYERROR;
		}
    }
#line 2026 "interpretor.tab.c"
    break;

  case 37: /* I: TOK_VARIABLE '=' F  */
#line 641 "interpretor.y"
        {
		if(ts != NULL)
		{
			if(ts->exists((yyvsp[-2].sir)) == 1)
			{
				ts->setValue((yyvsp[-2].sir), (yyvsp[0].val_float));
			}
			else 
			{
				sprintf(msg,"%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost declarata!", (yylsp[-2]).first_line, (yylsp[-2]).first_column, (yyvsp[-2].sir));
	    		yyerror(msg);
	    		YYERROR;
	  		}
		}
		else
		{
	  		sprintf(msg,"%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost declarata!", (yylsp[-2]).first_line, (yylsp[-2]).first_column, (yyvsp[-2].sir));
	  		yyerror(msg);
	  		YYERROR;
		}
	}
#line 2052 "interpretor.tab.c"
    break;

  case 38: /* I: TOK_VARIABLE '=' D  */
#line 663 "interpretor.y"
        {
		if(ts != NULL)
		{
			if(ts->exists((yyvsp[-2].sir)) == 1)
			{
				ts->setValue((yyvsp[-2].sir), (yyvsp[0].val_double));
			}
			else 
			{
				sprintf(msg,"%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost declarata!", (yylsp[-2]).first_line, (yylsp[-2]).first_column, (yyvsp[-2].sir));
	    		yyerror(msg);
	    		YYERROR;
	  		}
		}
		else
		{
	  		sprintf(msg,"%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost declarata!", (yylsp[-2]).first_line, (yylsp[-2]).first_column, (yyvsp[-2].sir));
	  		yyerror(msg);
	  		YYERROR;
		}
	}
#line 2078 "interpretor.tab.c"
    break;

  case 39: /* I: TOK_DECLARE_INT TOK_VARIABLE  */
#line 685 "interpretor.y"
    {
		if(ts != NULL)
		{
			if(ts->exists((yyvsp[0].sir)) == 0)
			{
				ts->add((yyvsp[0].sir), 0);
			}
			else
			{
				sprintf(msg,"%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", (yylsp[-1]).first_line, (yylsp[-1]).first_column, (yyvsp[0].sir));
				yyerror(msg);
				YYERROR;
			}
		}
		else
		{
			ts = new TVAR();
			ts->add((yyvsp[0].sir), 0);
		}
    }
#line 2103 "interpretor.tab.c"
    break;

  case 40: /* I: TOK_DECLARE_FLOAT TOK_VARIABLE  */
#line 706 "interpretor.y"
        {
		if(ts != NULL)
		{
			if(ts->exists((yyvsp[0].sir)) == 0)
			{
				ts->add((yyvsp[0].sir), 1);
			}
			else
			{
				sprintf(msg,"%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", (yylsp[-1]).first_line, (yylsp[-1]).first_column, (yyvsp[0].sir));
				yyerror(msg);
				YYERROR;
			}
		}
		else
		{
			ts = new TVAR();
			ts->add((yyvsp[0].sir), 1);
		}
	}
#line 2128 "interpretor.tab.c"
    break;

  case 41: /* I: TOK_DECLARE_DOUBLE TOK_VARIABLE '=' TOK_LEFT TOK_DECLARE_DOUBLE TOK_RIGHT TOK_VARIABLE  */
#line 727 "interpretor.y"
        {
		double value=GetValueBasedOnTypeDouble((yyvsp[0].sir),ts->getTipValue((yyvsp[0].sir)),ts);
		if (ts != NULL) {
            if (ts->exists((yyvsp[-5].sir)) == 0) {
                ts->add((yyvsp[-5].sir), 2, -1, -1.0, value); // Adaugă variabila și valoarea sa double în tabelul de variabile
            } else {
                sprintf(msg,"%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", (yylsp[-6]).first_line, (yylsp[-6]).first_column, (yyvsp[-5].sir));
                yyerror(msg);
                YYERROR;
            }
        } else {
            ts = new TVAR();
            ts->add((yyvsp[-5].sir), 2, -1, -1.0, value); // Adaugă variabila și valoarea sa double în tabelul de variabile
        }
	}
#line 2148 "interpretor.tab.c"
    break;

  case 42: /* I: TOK_DECLARE_FLOAT TOK_VARIABLE '=' TOK_LEFT TOK_DECLARE_FLOAT TOK_RIGHT TOK_VARIABLE  */
#line 743 "interpretor.y"
        {
		float value=GetValueBasedOnTypeFloat((yyvsp[0].sir),ts->getTipValue((yyvsp[0].sir)),ts);
		if (ts != NULL) {
            if (ts->exists((yyvsp[-5].sir)) == 0) {
                ts->add((yyvsp[-5].sir), 1, -1, value, -1.0); // Adaugă variabila și valoarea sa double în tabelul de variabile
            } else {
                sprintf(msg,"%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", (yylsp[-6]).first_line, (yylsp[-6]).first_column, (yyvsp[-5].sir));
                yyerror(msg);
                YYERROR;
            }
        } else {
            ts = new TVAR();
            ts->add((yyvsp[-5].sir), 1, -1, value, -1.0); // Adaugă variabila și valoarea sa double în tabelul de variabile
        }
	}
#line 2168 "interpretor.tab.c"
    break;

  case 43: /* I: TOK_DECLARE_INT TOK_VARIABLE '=' TOK_LEFT TOK_DECLARE_INT TOK_RIGHT TOK_VARIABLE  */
#line 759 "interpretor.y"
        {
		int value=GetValueBasedOnTypeInt((yyvsp[0].sir),ts->getTipValue((yyvsp[0].sir)),ts);
		if (ts != NULL) {
            if (ts->exists((yyvsp[-5].sir)) == 0) {
                ts->add((yyvsp[-5].sir), 0, value, -1.0f, -1.0); // Adaugă variabila și valoarea sa double în tabelul de variabile
            } else {
                sprintf(msg,"%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", (yylsp[-6]).first_line, (yylsp[-6]).first_column, (yyvsp[-5].sir));
                yyerror(msg);
                YYERROR;
            }
        } else {
            ts = new TVAR();
            ts->add((yyvsp[-5].sir), 0, value, -1.0f, -1.0); // Adaugă variabila și valoarea sa double în tabelul de variabile
        }
	}
#line 2188 "interpretor.tab.c"
    break;

  case 44: /* I: TOK_DECLARE_FLOAT TOK_VARIABLE '=' TOK_FLOAT  */
#line 775 "interpretor.y"
    {
        if (ts != NULL) {
            if (ts->exists((yyvsp[-2].sir)) == 0) {
                ts->add((yyvsp[-2].sir), 1, -1, (yyvsp[0].val_float)); // Adaugă variabila și valoarea sa float în tabelul de variabile
            } else {
                sprintf(msg,"%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", (yylsp[-3]).first_line, (yylsp[-3]).first_column, (yyvsp[-2].sir));
                yyerror(msg);
                YYERROR;
            }
        } else {
            ts = new TVAR();
            ts->add((yyvsp[-2].sir), 1, -1, (yyvsp[0].val_float)); // Adaugă variabila și valoarea sa float în tabelul de variabile
        }
    }
#line 2207 "interpretor.tab.c"
    break;

  case 45: /* I: TOK_DECLARE_DOUBLE TOK_VARIABLE '=' TOK_DOUBLE  */
#line 790 "interpretor.y"
    {
        if (ts != NULL) {
            if (ts->exists((yyvsp[-2].sir)) == 0) {
                ts->add((yyvsp[-2].sir), 2, -1, -1.0, (yyvsp[0].val_double)); // Adaugă variabila și valoarea sa double în tabelul de variabile
            } else {
                sprintf(msg,"%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", (yylsp[-3]).first_line, (yylsp[-3]).first_column, (yyvsp[-2].sir));
                yyerror(msg);
                YYERROR;
            }
        } else {
            ts = new TVAR();
            ts->add((yyvsp[-2].sir), 2, -1, -1.0, (yyvsp[0].val_double)); // Adaugă variabila și valoarea sa double în tabelul de variabile
        }
    }
#line 2226 "interpretor.tab.c"
    break;

  case 46: /* I: TOK_DECLARE_INT TOK_VARIABLE '=' TOK_INT  */
#line 805 "interpretor.y"
    {
        if (ts != NULL) {
            if (ts->exists((yyvsp[-2].sir)) == 0) {
                ts->add((yyvsp[-2].sir), 0);
				ts->setValue((yyvsp[-2].sir),(yyvsp[0].val_int));
            } else {
                sprintf(msg,"%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", (yylsp[-3]).first_line, (yylsp[-3]).first_column, (yyvsp[-2].sir));
                yyerror(msg);
                YYERROR;
            }
        } else {
            ts = new TVAR();
            ts->add((yyvsp[-2].sir), 0, (yyvsp[0].val_int));
        }
    }
#line 2246 "interpretor.tab.c"
    break;

  case 47: /* I: TOK_DECLARE_DOUBLE TOK_VARIABLE  */
#line 821 "interpretor.y"
        {
		if(ts != NULL)
		{
			if(ts->exists((yyvsp[0].sir)) == 0)
			{
				ts->add((yyvsp[0].sir), 2);
			}
			else
			{
				sprintf(msg,"%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", (yylsp[-1]).first_line, (yylsp[-1]).first_column, (yyvsp[0].sir));
				yyerror(msg);
				YYERROR;
			}
		}
		else
		{
			ts = new TVAR();
			ts->add((yyvsp[0].sir), 2);
		}
	}
#line 2271 "interpretor.tab.c"
    break;

  case 48: /* I: TOK_PRINT TOK_VARIABLE  */
#line 842 "interpretor.y"
    {
		if(ts != NULL)
		{
			if(ts->exists((yyvsp[0].sir)) == 1)
			{
				int tipul = ts->getTipValue((yyvsp[0].sir));
				if(tipul == 0)
				{
					if(ts->getIntValue((yyvsp[0].sir)) == -1)
					{
						sprintf(msg,"%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost initializata!", (yylsp[-1]).first_line, (yylsp[-1]).first_column, (yyvsp[0].sir));
						yyerror(msg);
						YYERROR;
					}
					else
					{
						printf("%d\n",ts->getIntValue((yyvsp[0].sir)));
					}
				}
				else if(tipul == 1)
				{
					if(ts->getFloatValue((yyvsp[0].sir)) == -1)
					{
						sprintf(msg,"%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost initializata!", (yylsp[-1]).first_line, (yylsp[-1]).first_column, (yyvsp[0].sir));
						yyerror(msg);
						YYERROR;
					}
					else
					{
						printf("%.2ff\n",ts->getFloatValue((yyvsp[0].sir)));
					}
				}
				else if(tipul == 2){
					if(ts->getDoubleValue((yyvsp[0].sir)) == -1)
					{
						sprintf(msg,"%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost initializata!", (yylsp[-1]).first_line, (yylsp[-1]).first_column, (yyvsp[0].sir));
						yyerror(msg);
						YYERROR;
					}
					else
					{
						printf("%.2f\n",ts->getDoubleValue((yyvsp[0].sir)));
					}
				}
	  		}
	  		else
	  		{
				sprintf(msg,"%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost declarata!", (yylsp[-1]).first_line, (yylsp[-1]).first_column, (yyvsp[0].sir));
				yyerror(msg);
				YYERROR;
	  		}
		}
		else
		{
			sprintf(msg,"%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost declarata!", (yylsp[-1]).first_line, (yylsp[-1]).first_column, (yyvsp[0].sir));
			yyerror(msg);
			YYERROR;
		}
    }
#line 2335 "interpretor.tab.c"
    break;

  case 49: /* E: E TOK_PLUS E  */
#line 902 "interpretor.y"
                 { (yyval.val_int) = (yyvsp[-2].val_int) + (yyvsp[0].val_int); }
#line 2341 "interpretor.tab.c"
    break;

  case 50: /* E: E TOK_MINUS E  */
#line 903 "interpretor.y"
                    { (yyval.val_int) = (yyvsp[-2].val_int) - (yyvsp[0].val_int); }
#line 2347 "interpretor.tab.c"
    break;

  case 51: /* E: E TOK_MULTIPLY E  */
#line 904 "interpretor.y"
                       { (yyval.val_int) = (yyvsp[-2].val_int) * (yyvsp[0].val_int); }
#line 2353 "interpretor.tab.c"
    break;

  case 52: /* E: E TOK_DIVIDE E  */
#line 906 "interpretor.y"
        {
		if((yyvsp[0].val_int) == 0)
		{
			sprintf(msg,"%d:%d Eroare semantica: Impartire la zero!", (yylsp[-2]).first_line, (yylsp[-2]).first_column);
	      	yyerror(msg);
	      	YYERROR;
	    } 
	  	else 
		{ 
			(yyval.val_int) = (yyvsp[-2].val_int) / (yyvsp[0].val_int); 
		} 
	}
#line 2370 "interpretor.tab.c"
    break;

  case 53: /* E: TOK_LEFT E TOK_RIGHT  */
#line 918 "interpretor.y"
                           { (yyval.val_int) = (yyvsp[-1].val_int); }
#line 2376 "interpretor.tab.c"
    break;

  case 54: /* E: TOK_INT  */
#line 919 "interpretor.y"
              { (yyval.val_int) = (yyvsp[0].val_int); }
#line 2382 "interpretor.tab.c"
    break;

  case 55: /* E: TOK_VARIABLE TOK_PLUS TOK_VARIABLE  */
#line 920 "interpretor.y"
                                             {	(yyval.val_int) = OperatieMatematica((yyvsp[-2].sir),(yyvsp[0].sir),'+',ts); }
#line 2388 "interpretor.tab.c"
    break;

  case 56: /* E: TOK_VARIABLE TOK_MINUS TOK_VARIABLE  */
#line 921 "interpretor.y"
                                              { (yyval.val_int) = OperatieMatematica((yyvsp[-2].sir),(yyvsp[0].sir),'-',ts); }
#line 2394 "interpretor.tab.c"
    break;

  case 57: /* E: TOK_VARIABLE TOK_MULTIPLY TOK_VARIABLE  */
#line 922 "interpretor.y"
                                                 { (yyval.val_int) = OperatieMatematica((yyvsp[-2].sir),(yyvsp[0].sir),'*',ts); }
#line 2400 "interpretor.tab.c"
    break;

  case 58: /* E: TOK_VARIABLE TOK_DIVIDE TOK_VARIABLE  */
#line 923 "interpretor.y"
                                                { (yyval.val_int) = OperatieMatematica((yyvsp[-2].sir),(yyvsp[0].sir),'/',ts); }
#line 2406 "interpretor.tab.c"
    break;

  case 59: /* E: TOK_VARIABLE TOK_PLUS E  */
#line 924 "interpretor.y"
                                  { (yyval.val_int) = GetValueBasedOnTypeInt((yyvsp[-2].sir),ts->getTipValue((yyvsp[-2].sir)),ts)+(yyvsp[0].val_int); }
#line 2412 "interpretor.tab.c"
    break;

  case 60: /* E: TOK_VARIABLE TOK_MINUS E  */
#line 925 "interpretor.y"
                                   { (yyval.val_int) = GetValueBasedOnTypeInt((yyvsp[-2].sir),ts->getTipValue((yyvsp[-2].sir)),ts)-(yyvsp[0].val_int); }
#line 2418 "interpretor.tab.c"
    break;

  case 61: /* E: TOK_VARIABLE TOK_MULTIPLY E  */
#line 926 "interpretor.y"
                                      { (yyval.val_int) = GetValueBasedOnTypeInt((yyvsp[-2].sir),ts->getTipValue((yyvsp[-2].sir)),ts)*(yyvsp[0].val_int); }
#line 2424 "interpretor.tab.c"
    break;

  case 62: /* E: TOK_VARIABLE TOK_DIVIDE E  */
#line 927 "interpretor.y"
                                    { (yyval.val_int) = GetValueBasedOnTypeInt((yyvsp[-2].sir),ts->getTipValue((yyvsp[-2].sir)),ts)/(yyvsp[0].val_int); }
#line 2430 "interpretor.tab.c"
    break;

  case 63: /* D: D TOK_PLUS D  */
#line 929 "interpretor.y"
                 { (yyval.val_double) = (yyvsp[-2].val_double) + (yyvsp[0].val_double); }
#line 2436 "interpretor.tab.c"
    break;

  case 64: /* D: D TOK_MINUS D  */
#line 930 "interpretor.y"
                    { (yyval.val_double) = (yyvsp[-2].val_double) - (yyvsp[0].val_double); }
#line 2442 "interpretor.tab.c"
    break;

  case 65: /* D: D TOK_MULTIPLY D  */
#line 931 "interpretor.y"
                       { (yyval.val_double) = (yyvsp[-2].val_double) * (yyvsp[0].val_double); }
#line 2448 "interpretor.tab.c"
    break;

  case 66: /* D: D TOK_DIVIDE D  */
#line 933 "interpretor.y"
        {
		if((yyvsp[0].val_double) == 0)
		{
			sprintf(msg,"%d:%d Eroare semantica: Impartire la zero!", (yylsp[-2]).first_line, (yylsp[-2]).first_column);
	      	yyerror(msg);
	      	YYERROR;
	    } 
	  	else 
		{ 
			(yyval.val_double) = (yyvsp[-2].val_double) / (yyvsp[0].val_double); 
		} 
	}
#line 2465 "interpretor.tab.c"
    break;

  case 67: /* D: TOK_LEFT D TOK_RIGHT  */
#line 945 "interpretor.y"
                           { (yyval.val_double) = (yyvsp[-1].val_double); }
#line 2471 "interpretor.tab.c"
    break;

  case 68: /* D: TOK_DOUBLE  */
#line 946 "interpretor.y"
                     {(yyval.val_double) = (yyvsp[0].val_double); }
#line 2477 "interpretor.tab.c"
    break;

  case 69: /* D: TOK_VARIABLE TOK_PLUS TOK_VARIABLE  */
#line 947 "interpretor.y"
                                             {	(yyval.val_double) = OperatieMatematicaDouble((yyvsp[-2].sir),(yyvsp[0].sir),'+',ts); }
#line 2483 "interpretor.tab.c"
    break;

  case 70: /* D: TOK_VARIABLE TOK_MINUS TOK_VARIABLE  */
#line 948 "interpretor.y"
                                              { (yyval.val_double) = OperatieMatematicaDouble((yyvsp[-2].sir),(yyvsp[0].sir),'-',ts); }
#line 2489 "interpretor.tab.c"
    break;

  case 71: /* D: TOK_VARIABLE TOK_MULTIPLY TOK_VARIABLE  */
#line 949 "interpretor.y"
                                                 { (yyval.val_double) = OperatieMatematicaDouble((yyvsp[-2].sir),(yyvsp[0].sir),'*',ts); }
#line 2495 "interpretor.tab.c"
    break;

  case 72: /* D: TOK_VARIABLE TOK_DIVIDE TOK_VARIABLE  */
#line 950 "interpretor.y"
                                                { (yyval.val_double) = OperatieMatematicaDouble((yyvsp[-2].sir),(yyvsp[0].sir),'/',ts); }
#line 2501 "interpretor.tab.c"
    break;

  case 73: /* D: TOK_VARIABLE TOK_PLUS E  */
#line 951 "interpretor.y"
                                  { (yyval.val_double) = GetValueBasedOnTypeDouble((yyvsp[-2].sir),ts->getTipValue((yyvsp[-2].sir)),ts)+(yyvsp[0].val_int); }
#line 2507 "interpretor.tab.c"
    break;

  case 74: /* D: TOK_VARIABLE TOK_MINUS E  */
#line 952 "interpretor.y"
                                   { (yyval.val_double) = GetValueBasedOnTypeDouble((yyvsp[-2].sir),ts->getTipValue((yyvsp[-2].sir)),ts)-(yyvsp[0].val_int); }
#line 2513 "interpretor.tab.c"
    break;

  case 75: /* D: TOK_VARIABLE TOK_MULTIPLY E  */
#line 953 "interpretor.y"
                                      { (yyval.val_double) = GetValueBasedOnTypeDouble((yyvsp[-2].sir),ts->getTipValue((yyvsp[-2].sir)),ts)*(yyvsp[0].val_int); }
#line 2519 "interpretor.tab.c"
    break;

  case 76: /* D: TOK_VARIABLE TOK_DIVIDE E  */
#line 954 "interpretor.y"
                                    { (yyval.val_double) = GetValueBasedOnTypeDouble((yyvsp[-2].sir),ts->getTipValue((yyvsp[-2].sir)),ts)/(yyvsp[0].val_int); }
#line 2525 "interpretor.tab.c"
    break;

  case 77: /* F: F TOK_PLUS F  */
#line 956 "interpretor.y"
                 { (yyval.val_float) = (yyvsp[-2].val_float) + (yyvsp[0].val_float); }
#line 2531 "interpretor.tab.c"
    break;

  case 78: /* F: F TOK_MINUS F  */
#line 957 "interpretor.y"
                    { (yyval.val_float) = (yyvsp[-2].val_float) - (yyvsp[0].val_float); }
#line 2537 "interpretor.tab.c"
    break;

  case 79: /* F: F TOK_MULTIPLY F  */
#line 958 "interpretor.y"
                       { (yyval.val_float) = (yyvsp[-2].val_float) * (yyvsp[0].val_float); }
#line 2543 "interpretor.tab.c"
    break;

  case 80: /* F: F TOK_DIVIDE F  */
#line 960 "interpretor.y"
        {
		if((yyvsp[0].val_float) == 0)
		{
			sprintf(msg,"%d:%d Eroare semantica: Impartire la zero!", (yylsp[-2]).first_line, (yylsp[-2]).first_column);
	      	yyerror(msg);
	      	YYERROR;
	    } 
	  	else 
		{ 
			(yyval.val_float) = (yyvsp[-2].val_float) / (yyvsp[0].val_float); 
		} 
	}
#line 2560 "interpretor.tab.c"
    break;

  case 81: /* F: TOK_LEFT F TOK_RIGHT  */
#line 972 "interpretor.y"
                           { (yyval.val_float) = (yyvsp[-1].val_float); }
#line 2566 "interpretor.tab.c"
    break;

  case 82: /* F: TOK_FLOAT  */
#line 973 "interpretor.y"
                    {(yyval.val_float) = (yyvsp[0].val_float); }
#line 2572 "interpretor.tab.c"
    break;

  case 83: /* F: TOK_VARIABLE TOK_PLUS TOK_VARIABLE  */
#line 974 "interpretor.y"
                                             {	(yyval.val_float) = OperatieMatematicaFloat((yyvsp[-2].sir),(yyvsp[0].sir),'+',ts); }
#line 2578 "interpretor.tab.c"
    break;

  case 84: /* F: TOK_VARIABLE TOK_MINUS TOK_VARIABLE  */
#line 975 "interpretor.y"
                                              { (yyval.val_float) = OperatieMatematicaFloat((yyvsp[-2].sir),(yyvsp[0].sir),'-',ts); }
#line 2584 "interpretor.tab.c"
    break;

  case 85: /* F: TOK_VARIABLE TOK_MULTIPLY TOK_VARIABLE  */
#line 976 "interpretor.y"
                                                 { (yyval.val_float) = OperatieMatematicaFloat((yyvsp[-2].sir),(yyvsp[0].sir),'*',ts); }
#line 2590 "interpretor.tab.c"
    break;

  case 86: /* F: TOK_VARIABLE TOK_DIVIDE TOK_VARIABLE  */
#line 977 "interpretor.y"
                                                { (yyval.val_float) = OperatieMatematicaFloat((yyvsp[-2].sir),(yyvsp[0].sir),'/',ts); }
#line 2596 "interpretor.tab.c"
    break;

  case 87: /* F: TOK_VARIABLE TOK_PLUS E  */
#line 978 "interpretor.y"
                                  { (yyval.val_float) = GetValueBasedOnTypeFloat((yyvsp[-2].sir),ts->getTipValue((yyvsp[-2].sir)),ts)+(yyvsp[0].val_int); }
#line 2602 "interpretor.tab.c"
    break;

  case 88: /* F: TOK_VARIABLE TOK_MINUS E  */
#line 979 "interpretor.y"
                                   { (yyval.val_float) = GetValueBasedOnTypeFloat((yyvsp[-2].sir),ts->getTipValue((yyvsp[-2].sir)),ts)-(yyvsp[0].val_int); }
#line 2608 "interpretor.tab.c"
    break;

  case 89: /* F: TOK_VARIABLE TOK_MULTIPLY E  */
#line 980 "interpretor.y"
                                      { (yyval.val_float) = GetValueBasedOnTypeFloat((yyvsp[-2].sir),ts->getTipValue((yyvsp[-2].sir)),ts)*(yyvsp[0].val_int); }
#line 2614 "interpretor.tab.c"
    break;

  case 90: /* F: TOK_VARIABLE TOK_DIVIDE E  */
#line 981 "interpretor.y"
                                    { (yyval.val_float) = GetValueBasedOnTypeFloat((yyvsp[-2].sir),ts->getTipValue((yyvsp[-2].sir)),ts)/(yyvsp[0].val_int); }
#line 2620 "interpretor.tab.c"
    break;


#line 2624 "interpretor.tab.c"

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
  *++yylsp = yyloc;

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

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 983 "interpretor.y"


int main()
{
	yyparse();
	
	if(EsteCorecta == 1)
	{
		cout<<"CORECT\n";	
	}	

	ts->printVars();
	return 0;
}

int yyerror(const char *msg)
{
	cout<<"EROARE: "<<msg<<endl;	
	return 1;
}
