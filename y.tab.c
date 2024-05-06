/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "syntax.y"

#include <fstream>
#include <iostream>
#include <map>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include "bytecode_inst.h"

#define GetCurrentDir getcwd

using namespace std;

extern  int yylex();
extern  FILE *yyin;
void yyerror(const char * s);
extern int lineCounter;

#define TRUE 1
#define FALSE 0
string outfileName ;

ofstream fout("output.j");    // Archivo donde se va a guardar el output

// Genera el encabezado para la clase para poder compilar el código
void generateHeader(void);

// Genera el pie de página para la clase para poder compilar el código
void generateFooter(void);

int labelsCount = 0;        // Para generar labels
int variablesNum = 1;       // Para generar nuevas variables, Java empieza con `1`, mientras que 0 es `this`

typedef enum {INT_T, FLOAT_T, BOOL_T, VOID_T, ERROR_T} type_enum;

map<string, pair<int,type_enum> > symbTab;

void cast (string x, int type_t1);
void arithCast(int from , int to, string op);
void relaCast(string op,char * nTrue, char * nFalse);

bool checkId(string id);
string getOp(string op);
void defineVar(string name, int type);

string genLabel();
string getLabel(int n);

void backpatch(vector<int> *list, int num);
vector<int> * merge (vector<int> *list1, vector<int>* list2);

vector<string> codeList;
void writeCode(string x);

void printCode(void);

void printLineNumber(int num)
{
    writeCode(".line "+ to_string(num));
}

/* Line 371 of yacc.c  */
#line 131 "y.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
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
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
/* Line 387 of yacc.c  */
#line 64 "syntax.y"

    #include <vector>
    using namespace std;


/* Line 387 of yacc.c  */
#line 169 "y.tab.c"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     FLOAT = 259,
     BOOL = 260,
     IDENTIFIER = 261,
     ARITH_OP = 262,
     RELA_OP = 263,
     BOOL_OP = 264,
     IF_WORD = 265,
     ELSE_WORD = 266,
     WHILE_WORD = 267,
     FOR_WORD = 268,
     INT_WORD = 269,
     FLOAT_WORD = 270,
     BOOLEAN_WORD = 271,
     SEMI_COLON = 272,
     EQUALS = 273,
     LEFT_BRACKET = 274,
     RIGHT_BRACKET = 275,
     LEFT_BRACKET_CURLY = 276,
     RIGHT_BRACKET_CURLY = 277,
     SYSTEM_OUT = 278
   };
#endif
/* Tokens.  */
#define INT 258
#define FLOAT 259
#define BOOL 260
#define IDENTIFIER 261
#define ARITH_OP 262
#define RELA_OP 263
#define BOOL_OP 264
#define IF_WORD 265
#define ELSE_WORD 266
#define WHILE_WORD 267
#define FOR_WORD 268
#define INT_WORD 269
#define FLOAT_WORD 270
#define BOOLEAN_WORD 271
#define SEMI_COLON 272
#define EQUALS 273
#define LEFT_BRACKET 274
#define RIGHT_BRACKET 275
#define LEFT_BRACKET_CURLY 276
#define RIGHT_BRACKET_CURLY 277
#define SYSTEM_OUT 278



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 71 "syntax.y"

    int ival;
    float fval;
    int bval;
    char * idval;
    char * aopval;
    struct {
        int sType;
    } expr_type;
    struct {
        vector<int> *trueList, *falseList;
    } bexpr_type;
    struct {
        vector<int> *nextList;
    } stmt_type;
    int sType;


/* Line 387 of yacc.c  */
#line 249 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 277 "y.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

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
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   87

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  24
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  16
/* YYNRULES -- Number of rules.  */
#define YYNRULES  30
/* YYNRULES -- Number of states.  */
#define YYNSTATES  83

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   278

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      15,    16,    17,    18,    19,    20,    21,    22,    23
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     8,    10,    14,    15,    17,    19,
      21,    23,    25,    27,    31,    33,    35,    37,    38,    53,
      63,    79,    84,    86,    88,    92,    94,    98,   104,   106,
     111
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      25,     0,    -1,    -1,    26,    27,    28,    -1,    29,    -1,
      29,    28,    27,    -1,    -1,    30,    -1,    33,    -1,    34,
      -1,    35,    -1,    36,    -1,    38,    -1,    31,     6,    17,
      -1,    14,    -1,    15,    -1,    16,    -1,    -1,    10,    19,
      39,    20,    21,    28,    27,    32,    22,    11,    21,    28,
      27,    22,    -1,    28,    12,    19,    39,    20,    21,    28,
      27,    22,    -1,    13,    19,    36,    28,    39,    17,    28,
      36,    32,    20,    21,    28,    27,    32,    22,    -1,     6,
      18,    37,    17,    -1,     4,    -1,     3,    -1,    37,     7,
      37,    -1,     6,    -1,    19,    37,    20,    -1,    23,    19,
      37,    20,    17,    -1,     5,    -1,    39,     9,    28,    39,
      -1,    37,     8,    37,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   131,   131,   131,   141,   143,   153,   160,   161,   162,
     163,   164,   165,   169,   183,   184,   185,   189,   196,   216,
     233,   262,   289,   290,   291,   292,   312,   316,   336,   352,
     370
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "BOOL", "IDENTIFIER",
  "ARITH_OP", "RELA_OP", "BOOL_OP", "IF_WORD", "ELSE_WORD", "WHILE_WORD",
  "FOR_WORD", "INT_WORD", "FLOAT_WORD", "BOOLEAN_WORD", "SEMI_COLON",
  "EQUALS", "LEFT_BRACKET", "RIGHT_BRACKET", "LEFT_BRACKET_CURLY",
  "RIGHT_BRACKET_CURLY", "SYSTEM_OUT", "$accept", "method_body", "$@1",
  "statement_list", "marker", "statement", "declaration", "primitive_type",
  "goto", "if", "while", "for", "assignment", "expression", "system_print",
  "b_expression", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    24,    26,    25,    27,    27,    28,    29,    29,    29,
      29,    29,    29,    30,    31,    31,    31,    32,    33,    34,
      35,    36,    37,    37,    37,    37,    37,    38,    39,    39,
      39
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     1,     3,     0,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     0,    14,     9,
      15,     4,     1,     1,     3,     1,     3,     5,     1,     4,
       3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     6,     1,     0,     0,     0,    14,    15,    16,
       0,     6,     0,     6,     7,     0,     8,     9,    10,    11,
      12,     0,     0,     0,     0,     3,     0,     6,     0,    23,
      22,    25,     0,     0,    28,     0,     0,     6,     0,     0,
       5,    13,     0,     0,    21,     0,     6,     0,     0,     0,
       0,    26,    24,    30,     0,     6,     0,    27,     0,    29,
       6,     6,     6,    17,     0,     6,     0,    17,     0,     0,
       0,    19,     0,     0,     6,     6,     6,     6,     0,    17,
      18,     0,    20
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    11,    12,    13,    14,    15,    66,    16,
      17,    18,    19,    35,    20,    36
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -61
static const yytype_int8 yypact[] =
{
     -61,    14,     7,   -61,    19,    20,    21,   -61,   -61,   -61,
      38,   -61,    46,     6,   -61,    53,   -61,   -61,   -61,   -61,
     -61,    42,    28,    54,    42,   -61,    47,     7,    50,   -61,
     -61,   -61,    42,    48,   -61,     3,    -5,   -61,     5,    28,
     -61,   -61,    36,    42,   -61,    42,   -61,    49,    28,    51,
      29,   -61,    62,    62,    28,   -61,    45,   -61,    52,    63,
       7,   -61,   -61,   -61,    54,     7,    55,   -61,    56,    60,
      59,   -61,    61,    64,   -61,   -61,     7,     7,    58,   -61,
     -61,    65,   -61
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -61,   -61,   -61,   -24,   -11,   -61,   -61,   -61,   -60,   -61,
     -61,   -61,   -22,   -16,   -61,   -30
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -5
static const yytype_int8 yytable[] =
{
      25,    37,    27,    40,    46,    33,    -4,    70,    38,    50,
      43,    45,    43,     4,     3,    47,    42,     5,    56,    81,
       6,     7,     8,     9,    59,    49,    48,    52,    -4,    53,
      10,    29,    30,    34,    31,    54,    63,    21,    46,    22,
      23,    68,    67,    43,    60,    29,    30,    32,    31,    58,
      64,    65,    78,    79,    46,    43,    51,    24,    26,    28,
       4,    32,    61,    76,    77,    44,    39,    41,    57,    43,
      55,    72,    46,    62,     0,     0,     0,    69,    71,    73,
      80,     0,    74,     0,     0,    75,     0,    82
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-61)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
      11,    23,    13,    27,     9,    21,     0,    67,    24,    39,
       7,     8,     7,     6,     0,    20,    32,    10,    48,    79,
      13,    14,    15,    16,    54,    20,    37,    43,    22,    45,
      23,     3,     4,     5,     6,    46,    60,    18,     9,    19,
      19,    65,    64,     7,    55,     3,     4,    19,     6,    20,
      61,    62,    76,    77,     9,     7,    20,    19,    12,     6,
       6,    19,    17,    74,    75,    17,    19,    17,    17,     7,
      21,    11,     9,    21,    -1,    -1,    -1,    22,    22,    20,
      22,    -1,    21,    -1,    -1,    21,    -1,    22
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    25,    26,     0,     6,    10,    13,    14,    15,    16,
      23,    27,    28,    29,    30,    31,    33,    34,    35,    36,
      38,    18,    19,    19,    19,    28,    12,    28,     6,     3,
       4,     6,    19,    37,     5,    37,    39,    36,    37,    19,
      27,    17,    37,     7,    17,     8,     9,    20,    28,    20,
      39,    20,    37,    37,    28,    21,    39,    17,    20,    39,
      28,    17,    21,    27,    28,    28,    32,    36,    27,    22,
      32,    22,    11,    20,    21,    21,    28,    28,    27,    27,
      22,    32,    22
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

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
      yychar = YYLEX;
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
     `$$ = $1'.

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
/* Line 1792 of yacc.c  */
#line 131 "syntax.y"
    {   generateHeader();   }
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 134 "syntax.y"
    {
        backpatch((yyvsp[(2) - (3)].stmt_type).nextList,(yyvsp[(3) - (3)].ival));
        generateFooter();
    }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 146 "syntax.y"
    {
        backpatch((yyvsp[(1) - (3)].stmt_type).nextList,(yyvsp[(2) - (3)].ival));
        (yyval.stmt_type).nextList = (yyvsp[(3) - (3)].stmt_type).nextList;
    }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 153 "syntax.y"
    {
    (yyval.ival) = labelsCount;
    writeCode(genLabel() + ":");
}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 160 "syntax.y"
    {vector<int> * v = new vector<int>(); (yyval.stmt_type).nextList =v;}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 161 "syntax.y"
    {(yyval.stmt_type).nextList = (yyvsp[(1) - (1)].stmt_type).nextList;}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 162 "syntax.y"
    {(yyval.stmt_type).nextList = (yyvsp[(1) - (1)].stmt_type).nextList;}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 163 "syntax.y"
    {(yyval.stmt_type).nextList = (yyvsp[(1) - (1)].stmt_type).nextList;}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 164 "syntax.y"
    {vector<int> * v = new vector<int>(); (yyval.stmt_type).nextList =v;}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 165 "syntax.y"
    {vector<int> * v = new vector<int>(); (yyval.stmt_type).nextList =v;}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 170 "syntax.y"
    {
        string str((yyvsp[(2) - (3)].idval));
        if((yyvsp[(1) - (3)].sType) == INT_T)
        {
            defineVar(str,INT_T);
        }else if ((yyvsp[(1) - (3)].sType) == FLOAT_T)
        {
            defineVar(str,FLOAT_T);
        }
    }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 183 "syntax.y"
    {(yyval.sType) = INT_T;}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 184 "syntax.y"
    {(yyval.sType) = FLOAT_T;}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 185 "syntax.y"
    {(yyval.sType) = BOOL_T;}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 189 "syntax.y"
    {
    (yyval.ival) = codeList.size();
    writeCode("goto ");
}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 207 "syntax.y"
    {
        backpatch((yyvsp[(3) - (14)].bexpr_type).trueList,(yyvsp[(6) - (14)].ival));
        backpatch((yyvsp[(3) - (14)].bexpr_type).falseList,(yyvsp[(12) - (14)].ival));
        (yyval.stmt_type).nextList = merge((yyvsp[(7) - (14)].stmt_type).nextList, (yyvsp[(13) - (14)].stmt_type).nextList);
        (yyval.stmt_type).nextList->push_back((yyvsp[(8) - (14)].ival));
    }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 223 "syntax.y"
    {
        writeCode("goto " + getLabel((yyvsp[(1) - (9)].ival)));
        
        backpatch((yyvsp[(8) - (9)].stmt_type).nextList,(yyvsp[(1) - (9)].ival));
        backpatch((yyvsp[(4) - (9)].bexpr_type).trueList,(yyvsp[(7) - (9)].ival));
        (yyval.stmt_type).nextList = (yyvsp[(4) - (9)].bexpr_type).falseList;
    }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 248 "syntax.y"
    {
        backpatch((yyvsp[(5) - (15)].bexpr_type).trueList,(yyvsp[(12) - (15)].ival));
        vector<int> * v = new vector<int> ();
        v->push_back((yyvsp[(9) - (15)].ival));
        backpatch(v,(yyvsp[(4) - (15)].ival));
        v = new vector<int>();
        v->push_back((yyvsp[(14) - (15)].ival));
        backpatch(v,(yyvsp[(7) - (15)].ival));
        backpatch((yyvsp[(13) - (15)].stmt_type).nextList,(yyvsp[(7) - (15)].ival));
        (yyval.stmt_type).nextList = (yyvsp[(5) - (15)].bexpr_type).falseList;
    }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 263 "syntax.y"
    {
        string str((yyvsp[(1) - (4)].idval));
        if(checkId(str))
        {
            if((yyvsp[(3) - (4)].expr_type).sType == symbTab[str].second)
            {
                if((yyvsp[(3) - (4)].expr_type).sType == INT_T)
                {
                    writeCode("istore " + to_string(symbTab[str].first));
                }else if ((yyvsp[(3) - (4)].expr_type).sType == FLOAT_T)
                {
                    writeCode("fstore " + to_string(symbTab[str].first));
                }
            }
            else
            {
                cast(str,(yyvsp[(3) - (4)].expr_type).sType);    /* do casting */
            }
        }else{
            string err = "El identificador: "+str+" no está declarado en este ámbito";
            yyerror(err.c_str());
        }
    }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 289 "syntax.y"
    {(yyval.expr_type).sType = FLOAT_T; writeCode("ldc "+to_string((yyvsp[(1) - (1)].fval)));}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 290 "syntax.y"
    {(yyval.expr_type).sType = INT_T;  writeCode("ldc "+to_string((yyvsp[(1) - (1)].ival)));}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 291 "syntax.y"
    {arithCast((yyvsp[(1) - (3)].expr_type).sType, (yyvsp[(3) - (3)].expr_type).sType, string((yyvsp[(2) - (3)].aopval)));}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 292 "syntax.y"
    {
        string str((yyvsp[(1) - (1)].idval));
        if(checkId(str))
        {
            (yyval.expr_type).sType = symbTab[str].second;
            if(symbTab[str].second == INT_T)
            {
                writeCode("iload " + to_string(symbTab[str].first));
            }else if (symbTab[str].second == FLOAT_T)
            {
                writeCode("fload " + to_string(symbTab[str].first));
            }
        }
        else
        {
            string err = "El identificador: "+str+" no está declarado en este ámbito";
            yyerror(err.c_str());
            (yyval.expr_type).sType = ERROR_T;
        }
    }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 312 "syntax.y"
    {(yyval.expr_type).sType = (yyvsp[(2) - (3)].expr_type).sType;}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 317 "syntax.y"
    {
        if((yyvsp[(3) - (5)].expr_type).sType == INT_T)
        {
            writeCode("istore " + to_string(symbTab["1syso_int_var"].first));
            writeCode("getstatic      java/lang/System/out Ljava/io/PrintStream;");
            writeCode("iload " + to_string(symbTab["1syso_int_var"].first ));
            writeCode("invokevirtual java/io/PrintStream/println(I)V");

        }else if ((yyvsp[(3) - (5)].expr_type).sType == FLOAT_T)
        {
            writeCode("fstore " + to_string(symbTab["1syso_float_var"].first));
            writeCode("getstatic      java/lang/System/out Ljava/io/PrintStream;");
            writeCode("fload " + to_string(symbTab["1syso_float_var"].first ));
            writeCode("invokevirtual java/io/PrintStream/println(F)V");
        }
    }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 337 "syntax.y"
    {
        if((yyvsp[(1) - (1)].bval))
        {
            (yyval.bexpr_type).trueList = new vector<int> ();
            (yyval.bexpr_type).trueList->push_back(codeList.size());
            (yyval.bexpr_type).falseList = new vector<int>();
            writeCode("goto ");
        }else
        {
            (yyval.bexpr_type).trueList = new vector<int> ();
            (yyval.bexpr_type).falseList= new vector<int>();
            (yyval.bexpr_type).falseList->push_back(codeList.size());
            writeCode("goto ");
        }
    }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 356 "syntax.y"
    {
        if(!strcmp((yyvsp[(2) - (4)].aopval), "&&"))
        {
            backpatch((yyvsp[(1) - (4)].bexpr_type).trueList, (yyvsp[(3) - (4)].ival));
            (yyval.bexpr_type).trueList = (yyvsp[(4) - (4)].bexpr_type).trueList;
            (yyval.bexpr_type).falseList = merge((yyvsp[(1) - (4)].bexpr_type).falseList,(yyvsp[(4) - (4)].bexpr_type).falseList);
        }
        else if (!strcmp((yyvsp[(2) - (4)].aopval),"||"))
        {
            backpatch((yyvsp[(1) - (4)].bexpr_type).falseList,(yyvsp[(3) - (4)].ival));
            (yyval.bexpr_type).trueList = merge((yyvsp[(1) - (4)].bexpr_type).trueList, (yyvsp[(4) - (4)].bexpr_type).trueList);
            (yyval.bexpr_type).falseList = (yyvsp[(4) - (4)].bexpr_type).falseList;
        }
    }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 371 "syntax.y"
    {
        string op ((yyvsp[(2) - (3)].aopval));
        (yyval.bexpr_type).trueList = new vector<int>();
        (yyval.bexpr_type).trueList ->push_back (codeList.size());
        (yyval.bexpr_type).falseList = new vector<int>();
        (yyval.bexpr_type).falseList->push_back(codeList.size()+1);
        writeCode(getOp(op)+ " ");
        writeCode("goto ");
    }
    break;


/* Line 1792 of yacc.c  */
#line 1828 "y.tab.c"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 382 "syntax.y"


int main(int argv, char * argc[])
{
    FILE *miArchivo;
    miArchivo = fopen(argc[1], "r");
    outfileName = string(argc[1]);
    if (!miArchivo) {
        string err = "Error: No se ha podido abrir el archivo indicado\n";
        yyerror(err.c_str());
        char cCurrentPath[200];
         if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
             {
             return -1;
             }
        printf("%s\n",cCurrentPath);  
                getchar();

        return -1;

    }
    yyin = miArchivo;
    yyparse();
    printCode();
    return 0;
}

void yyerror(const char * s)
{
    printf("Error@%d: %s\n",lineCounter, s);
}

void generateHeader()
{
    writeCode(".source " + outfileName);
    writeCode(".class public test\n.super java/lang/Object\n"); //código para definir la clase
    writeCode(".method public <init>()V");
    writeCode("aload_0");
    writeCode("invokenonvirtual java/lang/Object/<init>()V");
    writeCode("return");
    writeCode(".end method\n");
    writeCode(".method public static main([Ljava/lang/String;)V");
    writeCode(".limit locals 100\n.limit stack 100");

    defineVar("1syso_int_var",INT_T);
    defineVar("1syso_float_var",FLOAT_T);

    // Genera nueva linea
    writeCode(".line 1");
}

void generateFooter()
{
    writeCode("return");
    writeCode(".end method");
}

void cast (string str, int t1)
{
    yyerror("Error: Casting todavía no implementado :)");
}

void arithCast(int from , int to, string op)
{
    if(from == to)
    {
        if(from == INT_T)
        {
            writeCode("i" + getOp(op));
        }else if (from == FLOAT_T)
        {
            writeCode("f" + getOp(op));
        }
    }
    else
    {
        yyerror("Error: Casting todavía no implementado");
    }
}


string getOp(string op)
{
    if(inst_list.find(op) != inst_list.end())
    {
        return inst_list[op];
    }
    return "";
}

bool checkId(string op)
{
    return (symbTab.find(op) != symbTab.end());
}

void defineVar(string name, int type)
{
    if(checkId(name))
    {
        string err = "La variable: " + name + " ya ha sido declarada anteriormente.";
        yyerror(err.c_str());
    }else
    {
        if(type == INT_T)
        {
            writeCode("iconst_0\nistore " + to_string(variablesNum));
        }
        else if ( type == FLOAT_T)
        {
            writeCode("fconst_0\nfstore " + to_string(variablesNum));
        }
        symbTab[name] = make_pair(variablesNum++,(type_enum)type);
    }
}

string genLabel()
{
    return "L_"+to_string(labelsCount++);
}

string getLabel(int n)
{
    return "L_"+to_string(n);
}

vector<int> * merge(vector<int> *list1, vector<int> *list2)
{
    if(list1 && list2){
        vector<int> *list = new vector<int> (*list1);
        list->insert(list->end(), list2->begin(),list2->end());
        return list;
    }else if(list1)
    {
        return list1;
    }else if (list2)
    {
        return list2;
    }else
    {
        return new vector<int>();
    }
}

void backpatch(vector<int> *lists, int ind)
{
    if(lists)
    for(int i =0 ; i < lists->size() ; i++)
    {
        codeList[(*lists)[i]] = codeList[(*lists)[i]] + getLabel(ind);
    }
}

void writeCode(string x)
{
    codeList.push_back(x);
}

void printCode(void)
{
    for ( int i = 0 ; i < codeList.size() ; i++)
    {
        fout<<codeList[i]<<endl;
    }
}
