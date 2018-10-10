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
#line 1 "parser.y" /* yacc.c:339  */

	// João Vitor de Camargo (274722) e Marcellus Farias (281984)
	#include <stdio.h>
	#include "tree.h"
	#include "lexeme.h"
	
	extern int yylineno;
	extern void* arvore;

	int yylex(void);
	void yyerror(char const *s);

#line 79 "parser.tab.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TK_PR_INT = 258,
    TK_PR_FLOAT = 259,
    TK_PR_BOOL = 260,
    TK_PR_CHAR = 261,
    TK_PR_STRING = 262,
    TK_PR_IF = 263,
    TK_PR_THEN = 264,
    TK_PR_ELSE = 265,
    TK_PR_WHILE = 266,
    TK_PR_DO = 267,
    TK_PR_INPUT = 268,
    TK_PR_OUTPUT = 269,
    TK_PR_RETURN = 270,
    TK_PR_CONST = 271,
    TK_PR_STATIC = 272,
    TK_PR_FOREACH = 273,
    TK_PR_FOR = 274,
    TK_PR_SWITCH = 275,
    TK_PR_CASE = 276,
    TK_PR_BREAK = 277,
    TK_PR_CONTINUE = 278,
    TK_PR_CLASS = 279,
    TK_PR_PRIVATE = 280,
    TK_PR_PUBLIC = 281,
    TK_PR_PROTECTED = 282,
    TK_OC_LE = 283,
    TK_OC_GE = 284,
    TK_OC_EQ = 285,
    TK_OC_NE = 286,
    TK_OC_AND = 287,
    TK_OC_OR = 288,
    TK_OC_SL = 289,
    TK_OC_SR = 290,
    TK_OC_FORWARD_PIPE = 291,
    TK_OC_BASH_PIPE = 292,
    TK_LIT_INT = 293,
    TK_LIT_FLOAT = 294,
    TK_LIT_FALSE = 295,
    TK_LIT_TRUE = 296,
    TK_LIT_CHAR = 297,
    TK_LIT_STRING = 298,
    TK_IDENTIFICADOR = 299,
    TOKEN_ERRO = 300
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 17 "parser.y" /* yacc.c:355  */

	struct Lexeme* valor_lexico;
	struct node* node;

#line 170 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 187 "parser.tab.c" /* yacc.c:358  */

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
#define YYFINAL  26
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   451

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  64
/* YYNRULES -- Number of rules.  */
#define YYNRULES  178
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  338

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    64,     2,    67,    70,    66,    65,     2,
      49,    50,    59,    55,    46,    56,    69,    60,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    48,    47,
      61,    63,    62,    58,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    53,     2,    54,    68,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,    57,    52,     2,     2,     2,     2,
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
      45
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   147,   147,   153,   158,   163,   168,   173,   177,   181,
     185,   189,   194,   198,   202,   207,   213,   219,   223,   228,
     232,   237,   241,   246,   255,   260,   265,   272,   277,   282,
     288,   295,   300,   305,   310,   315,   321,   325,   331,   336,
     341,   348,   356,   361,   367,   372,   379,   385,   389,   395,
     401,   407,   413,   420,   425,   430,   435,   440,   445,   450,
     455,   460,   465,   470,   476,   480,   485,   491,   498,   502,
     509,   522,   528,   533,   545,   558,   563,   568,   574,   591,
     596,   602,   607,   612,   616,   620,   624,   628,   632,   636,
     640,   644,   648,   652,   657,   663,   669,   674,   680,   685,
     699,   705,   710,   720,   727,   731,   736,   743,   748,   753,
     759,   765,   770,   775,   779,   783,   787,   791,   795,   799,
     804,   809,   814,   819,   828,   836,   841,   845,   849,   853,
     857,   861,   865,   869,   873,   877,   881,   885,   889,   893,
     897,   901,   906,   911,   916,   920,   924,   928,   932,   936,
     940,   945,   952,   957,   964,   969,   973,   977,   983,   987,
     991,   997,  1002,  1006,  1014,  1018,  1024,  1030,  1035,  1041,
    1046,  1053,  1058,  1062,  1067,  1073,  1077,  1083,  1088
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_PR_INT", "TK_PR_FLOAT", "TK_PR_BOOL",
  "TK_PR_CHAR", "TK_PR_STRING", "TK_PR_IF", "TK_PR_THEN", "TK_PR_ELSE",
  "TK_PR_WHILE", "TK_PR_DO", "TK_PR_INPUT", "TK_PR_OUTPUT", "TK_PR_RETURN",
  "TK_PR_CONST", "TK_PR_STATIC", "TK_PR_FOREACH", "TK_PR_FOR",
  "TK_PR_SWITCH", "TK_PR_CASE", "TK_PR_BREAK", "TK_PR_CONTINUE",
  "TK_PR_CLASS", "TK_PR_PRIVATE", "TK_PR_PUBLIC", "TK_PR_PROTECTED",
  "TK_OC_LE", "TK_OC_GE", "TK_OC_EQ", "TK_OC_NE", "TK_OC_AND", "TK_OC_OR",
  "TK_OC_SL", "TK_OC_SR", "TK_OC_FORWARD_PIPE", "TK_OC_BASH_PIPE",
  "TK_LIT_INT", "TK_LIT_FLOAT", "TK_LIT_FALSE", "TK_LIT_TRUE",
  "TK_LIT_CHAR", "TK_LIT_STRING", "TK_IDENTIFICADOR", "TOKEN_ERRO", "','",
  "';'", "':'", "'('", "')'", "'{'", "'}'", "'['", "']'", "'+'", "'-'",
  "'|'", "'?'", "'*'", "'/'", "'<'", "'>'", "'='", "'!'", "'&'", "'%'",
  "'#'", "'^'", "'.'", "'$'", "$accept", "programa", "start", "type",
  "scope", "var", "types", "bool", "pipe", "new_type", "param_begin",
  "param_body", "param_end", "global_var", "global_var_vec",
  "globar_var_begin", "global_var_type", "index", "func", "func_begin",
  "func_params", "func_params_end", "func_body", "cmd_block", "cmd",
  "input", "output", "output_vals", "if_then", "else", "while", "do_while",
  "continue", "break", "return", "for", "cmd_for", "for_fst_list",
  "for_scd_list", "foreach", "foreach_list", "switch", "case",
  "cmd_id_fix", "static_var", "const_var", "var_end", "var_lit", "attr",
  "piped_expr", "bin_op", "un_op", "not_null_un_op", "expr", "expr_begin",
  "expr_vals", "piped", "id_seq", "id_seq_field", "id_seq_field_vec",
  "id_seq_simple", "func_call_params", "func_call_params_body",
  "func_call_params_end", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,    44,    59,    58,    40,
      41,   123,   125,    91,    93,    43,    45,   124,    63,    42,
      47,    60,    62,    61,    33,    38,    37,    35,    94,    46,
      36
};
# endif

#define YYPACT_NINF -263

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-263)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     159,  -263,  -263,  -263,  -263,  -263,   326,   -17,    69,    77,
    -263,     1,   159,   159,   159,  -263,    35,  -263,    49,   331,
       6,   -13,    57,  -263,  -263,  -263,  -263,    65,  -263,  -263,
    -263,    66,   393,    70,  -263,  -263,   102,  -263,    81,    71,
    -263,   102,  -263,  -263,  -263,    79,   219,    83,  -263,   336,
    -263,    73,  -263,    17,    82,  -263,  -263,   231,  -263,     8,
    -263,  -263,    88,   251,  -263,   304,    73,  -263,  -263,  -263,
     393,  -263,  -263,  -263,    87,    92,    86,   372,   372,   372,
     346,   310,    94,    96,    98,   110,  -263,  -263,   -18,   251,
    -263,   105,  -263,   251,   103,  -263,   106,   107,   111,   113,
     114,   127,   128,   130,   135,  -263,    17,  -263,  -263,   372,
     372,   251,  -263,  -263,  -263,  -263,  -263,  -263,  -263,   402,
     372,  -263,    45,  -263,   140,   142,   141,   346,   147,  -263,
     143,   274,   372,   109,  -263,   357,   372,   154,   158,  -263,
       3,   168,   178,  -263,  -263,  -263,  -263,  -263,  -263,  -263,
    -263,  -263,  -263,  -263,  -263,   166,   170,   216,  -263,  -263,
    -263,  -263,  -263,  -263,    -6,   372,  -263,   327,  -263,   372,
    -263,  -263,  -263,   178,  -263,  -263,  -263,   181,   372,   346,
     310,   -18,   251,   188,  -263,  -263,  -263,  -263,  -263,  -263,
    -263,  -263,    23,  -263,  -263,   183,  -263,  -263,    32,    32,
      74,   185,   187,  -263,   372,   372,  -263,  -263,   372,   372,
    -263,  -263,   129,   194,   233,   235,   196,   357,    74,  -263,
     193,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,
     372,  -263,  -263,  -263,  -263,  -263,  -263,  -263,   372,  -263,
      45,  -263,   372,  -263,  -263,  -263,  -263,  -263,   178,   274,
    -263,   372,   199,   307,  -263,  -263,  -263,   372,  -263,   190,
     372,  -263,  -263,  -263,  -263,   207,  -263,  -263,  -263,  -263,
    -263,  -263,  -263,  -263,  -263,   210,   225,   372,  -263,   239,
    -263,  -263,   236,  -263,  -263,    38,  -263,    23,   250,   251,
      32,    32,  -263,   255,  -263,   246,    -6,   251,   251,   254,
      -6,   372,   372,  -263,   261,  -263,   274,  -263,  -263,  -263,
      -6,  -263,    74,   291,  -263,  -263,    74,  -263,    38,   251,
      39,    74,  -263,   268,  -263,  -263,  -263,  -263,   274,  -263,
     270,  -263,   251,    39,   251,  -263,  -263,  -263
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       6,     7,     8,     9,    10,    11,     0,     0,     0,     0,
       2,     0,     6,     6,     6,    39,     0,    38,     0,     0,
       0,     0,     0,    29,    31,    33,     1,     0,     3,     4,
       5,     0,     0,     0,    32,    35,     0,    36,     0,     0,
      34,     0,    12,    13,    14,     0,     0,     0,    25,     0,
      18,     0,    17,     0,     0,    41,    37,     0,    40,     0,
      24,    23,     0,     0,    42,     0,     0,    43,    16,    30,
       0,    28,    26,    15,     0,     0,     0,   143,   143,   143,
       0,     0,     0,     0,     0,     0,    76,    75,   167,     0,
      47,     0,    46,     0,     0,    64,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    65,     0,    44,    27,   143,
     143,     0,   144,   145,   149,   148,   146,   147,   150,     0,
     143,    66,     0,    77,     0,     0,     0,     0,     0,   108,
       0,     0,   143,     0,   104,   143,   143,     0,     0,   171,
       0,     0,   112,    48,    62,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    45,     0,     0,     0,   156,   155,
      20,    19,   158,   159,   167,   143,   161,   154,   142,   143,
      68,    67,   110,   112,    51,   107,    50,     0,   143,     0,
       0,   167,     0,     0,    92,    83,    84,    85,    86,    87,
      88,    89,     0,    90,    91,     0,   103,   172,     0,     0,
     125,     0,   169,    49,   143,   143,    21,    22,   143,   143,
     105,    63,     0,     0,     0,     0,     0,   143,   162,   164,
       0,   138,   141,   140,   139,   136,   137,   126,   127,   132,
     143,   128,   129,   135,   134,   133,   130,   131,   143,   151,
       0,   109,   143,    93,    82,    81,    79,    94,   112,     0,
      96,   143,     0,   143,   175,   174,   173,   143,   106,   167,
     143,   166,   121,   122,   120,     0,   114,   115,   119,   118,
     116,   117,   113,   111,    52,     0,     0,   143,   165,     0,
     157,   160,     0,   152,    69,     0,    80,     0,     0,     0,
       0,     0,   176,     0,   170,     0,   167,     0,     0,     0,
     167,   143,   143,   101,     0,    95,     0,   102,   178,   177,
     167,   168,   125,    72,    73,    74,   125,   153,     0,     0,
       0,   125,   123,     0,    70,   163,   100,    99,     0,    98,
       0,   124,     0,     0,     0,    71,    97,    78
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -263,  -263,    85,     0,  -263,   240,   273,  -263,  -106,  -263,
     253,   278,  -263,  -263,  -263,   287,   308,  -263,  -263,   339,
     305,   241,   295,   -88,  -263,  -128,  -263,   124,  -121,  -263,
    -116,  -115,  -114,  -111,  -110,  -109,  -238,    80,    36,  -107,
      50,   -98,  -263,   192,   197,   -76,  -155,  -263,  -263,  -262,
    -263,  -113,  -263,   -49,  -263,  -263,  -263,  -252,   119,  -263,
     -86,   162,  -190,  -263
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    10,    91,    46,    53,    54,   166,   257,    12,
      47,    48,    72,    13,    23,    24,    25,    39,    14,    15,
      55,    67,    64,    92,    93,    94,    95,   171,    96,   324,
      97,    98,    99,   100,   101,   102,   192,   251,   330,   103,
     304,   104,   105,   138,   128,   129,   213,   273,   210,   258,
     238,   119,   120,   199,   239,   167,   280,   218,   139,   261,
     219,   200,   255,   292
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      11,   141,   140,   184,   126,   143,    11,   168,    22,   256,
     185,   287,    11,    11,    11,   186,   187,   188,   241,    22,
     189,   190,   191,   157,   193,    37,   134,    18,   121,   122,
     123,   135,    45,   194,   209,   136,    52,   204,   205,   206,
     207,    52,    38,   217,   312,    27,    45,   136,   316,    52,
     322,   175,   137,    35,   325,    36,    70,    22,   321,   331,
     155,   156,    71,    65,   137,    52,   208,    66,   320,   249,
      45,   250,     1,     2,     3,     4,     5,    26,   253,    31,
     125,   125,   254,   195,   302,   328,    19,   201,   303,   329,
     333,   169,   170,   286,   247,   140,   265,    28,    29,    30,
     308,   309,    32,   244,    40,     1,     2,     3,     4,     5,
     206,   207,   279,    20,    41,    36,   220,    35,    49,    56,
     240,   184,    21,    59,    63,    57,    68,   125,   185,   243,
      61,   183,    73,   186,   187,   188,   109,   111,   189,   190,
     191,   110,   193,   130,   293,   131,    50,   132,   133,   142,
     144,   194,    51,   145,   146,   262,   263,   196,   147,   264,
     148,   149,     1,     2,     3,     4,     5,   266,   267,   268,
     269,   270,   271,   272,   150,   151,     6,   152,   184,   125,
     125,   282,   153,     7,   172,   185,   173,   177,   174,   283,
     186,   187,   188,   285,   176,   189,   190,   191,   202,   193,
     184,   307,   288,     8,   291,   203,   212,   185,   194,   313,
     314,   295,   186,   187,   188,   211,   214,   189,   190,   191,
     215,   193,     1,     2,     3,     4,     5,   216,   299,   242,
     194,   327,   248,   252,     1,     2,     3,     4,     5,   259,
     260,   274,   275,   281,   335,   277,   337,   276,    19,   183,
     289,   296,   317,   318,     1,     2,     3,     4,     5,    74,
     137,   297,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    33,   298,     1,     2,     3,
       4,     5,    74,   300,   301,    75,    76,    77,   178,    79,
     179,   180,    82,    83,    84,    88,    86,    87,   306,   310,
     311,   323,    89,    90,   315,   106,   183,     1,     2,     3,
       4,     5,   319,     1,     2,     3,     4,     5,   181,   332,
      49,   334,    62,   108,    60,   182,   127,    34,   183,     1,
       2,     3,     4,     5,     1,     2,     3,     4,     5,     1,
       2,     3,     4,     5,    69,    17,    58,   154,    50,     1,
       2,     3,     4,     5,   124,   221,   222,   223,   224,   225,
     226,   107,   112,   113,   284,   114,   115,   305,   326,   336,
      16,   116,   117,   246,   118,    33,   290,   245,   294,   278,
      50,     0,   227,   228,   229,   230,   231,   232,   233,   234,
     124,     0,   235,   236,     0,   237,     1,     2,     3,     4,
       5,     0,     0,     0,     0,     0,     0,   197,     0,     0,
       0,     0,   112,   113,     0,   114,   115,     0,    42,    43,
      44,   116,   117,     0,   118,     0,   198,   112,   113,     0,
     114,   115,     0,     0,     0,     0,   116,   117,     0,   118,
     158,   159,   160,   161,   162,   163,   164,     0,     0,     0,
       0,   165
};

static const yytype_int16 yycheck[] =
{
       0,    89,    88,   131,    80,    93,     6,   120,     8,   199,
     131,   249,    12,    13,    14,   131,   131,   131,   173,    19,
     131,   131,   131,   111,   131,    38,    44,    44,    77,    78,
      79,    49,    32,   131,   140,    53,    36,    34,    35,    36,
      37,    41,    55,    49,   296,    44,    46,    53,   300,    49,
     312,   127,    70,    47,   316,    49,    48,    57,   310,   321,
     109,   110,    54,    46,    70,    65,    63,    50,   306,    46,
      70,    48,     3,     4,     5,     6,     7,     0,    46,    44,
      80,    81,    50,   132,    46,    46,    17,   136,    50,    50,
     328,    46,    47,   248,   182,   181,   209,    12,    13,    14,
     290,   291,    53,   179,    47,     3,     4,     5,     6,     7,
      36,    37,   218,    44,    49,    49,   165,    47,    16,    38,
     169,   249,    53,    44,    51,    54,    44,   127,   249,   178,
      47,   131,    44,   249,   249,   249,    49,    51,   249,   249,
     249,    49,   249,    49,   257,    49,    44,    49,    38,    44,
      47,   249,    50,    47,    47,   204,   205,    48,    47,   208,
      47,    47,     3,     4,     5,     6,     7,    38,    39,    40,
      41,    42,    43,    44,    47,    47,    17,    47,   306,   179,
     180,   230,    47,    24,    44,   306,    44,    44,    47,   238,
     306,   306,   306,   242,    47,   306,   306,   306,    44,   306,
     328,   289,   251,    44,   253,    47,    28,   328,   306,   297,
     298,   260,   328,   328,   328,    47,    50,   328,   328,   328,
      50,   328,     3,     4,     5,     6,     7,    11,   277,    48,
     328,   319,    44,    50,     3,     4,     5,     6,     7,    54,
      53,    47,     9,    50,   332,    49,   334,    12,    17,   249,
      51,    44,   301,   302,     3,     4,     5,     6,     7,     8,
      70,    51,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    44,    51,     3,     4,     5,
       6,     7,     8,    44,    48,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    44,    22,    23,    48,    44,
      54,    10,    51,    52,    50,    65,   306,     3,     4,     5,
       6,     7,    51,     3,     4,     5,     6,     7,    44,    51,
      16,    51,    49,    70,    46,    51,    16,    19,   328,     3,
       4,     5,     6,     7,     3,     4,     5,     6,     7,     3,
       4,     5,     6,     7,    57,     6,    41,   106,    44,     3,
       4,     5,     6,     7,    44,    28,    29,    30,    31,    32,
      33,    66,    55,    56,   240,    58,    59,   287,   318,   333,
      44,    64,    65,   181,    67,    44,    69,   180,   259,   217,
      44,    -1,    55,    56,    57,    58,    59,    60,    61,    62,
      44,    -1,    65,    66,    -1,    68,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    55,    56,    -1,    58,    59,    -1,    25,    26,
      27,    64,    65,    -1,    67,    -1,    69,    55,    56,    -1,
      58,    59,    -1,    -1,    -1,    -1,    64,    65,    -1,    67,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    49
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,    17,    24,    44,    72,
      73,    74,    80,    84,    89,    90,    44,    90,    44,    17,
      44,    53,    74,    85,    86,    87,     0,    44,    73,    73,
      73,    44,    53,    44,    87,    47,    49,    38,    55,    88,
      47,    49,    25,    26,    27,    74,    75,    81,    82,    16,
      44,    50,    74,    76,    77,    91,    38,    54,    91,    44,
      82,    47,    77,    51,    93,    46,    50,    92,    44,    86,
      48,    54,    83,    44,     8,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    44,    51,
      52,    74,    94,    95,    96,    97,    99,   101,   102,   103,
     104,   105,   106,   110,   112,   113,    76,    93,    81,    49,
      49,    51,    55,    56,    58,    59,    64,    65,    67,   122,
     123,   124,   124,   124,    44,    74,   116,    16,   115,   116,
      49,    49,    49,    38,    44,    49,    53,    70,   114,   129,
     131,    94,    44,    94,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    92,   124,   124,    94,    38,    39,
      40,    41,    42,    43,    44,    49,    78,   126,   122,    46,
      47,    98,    44,    44,    47,   116,    47,    44,    14,    16,
      17,    44,    51,    74,    96,    99,   101,   102,   103,   104,
     105,   106,   107,   110,   112,   124,    48,    50,    69,   124,
     132,   124,    44,    47,    34,    35,    36,    37,    63,    79,
     119,    47,    28,   117,    50,    50,    11,    49,   128,   131,
     124,    28,    29,    30,    31,    32,    33,    55,    56,    57,
      58,    59,    60,    61,    62,    65,    66,    68,   121,   125,
     124,   117,    48,   124,   116,   115,   114,    94,    44,    46,
      48,   108,    50,    46,    50,   133,   133,    79,   120,    54,
      53,   130,   124,   124,   124,   122,    38,    39,    40,    41,
      42,    43,    44,   118,    47,     9,    12,    49,   132,    79,
     127,    50,   124,   124,    98,   124,   117,   107,   124,    51,
      69,   124,   134,   122,   129,   124,    44,    51,    51,   124,
      44,    48,    46,    50,   111,   108,    48,    94,   133,   133,
      44,    54,   128,    94,    94,    50,   128,   124,   124,    51,
     107,   128,   120,    10,   100,   120,   111,    94,    46,    50,
     109,   120,    51,   107,    51,    94,   109,    94
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    71,    72,    73,    73,    73,    73,    74,    74,    74,
      74,    74,    75,    75,    75,    76,    76,    77,    77,    78,
      78,    79,    79,    80,    81,    81,    82,    83,    83,    84,
      85,    85,    86,    86,    87,    87,    88,    88,    89,    89,
      90,    90,    91,    91,    92,    92,    93,    94,    94,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    96,    97,    98,    98,
      99,   100,   100,   101,   102,   103,   104,   105,   106,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   108,   108,   109,   109,   110,
     111,   111,   112,   113,   114,   114,   114,   115,   115,   116,
     116,   117,   117,   118,   118,   118,   118,   118,   118,   118,
     119,   119,   119,   119,   120,   120,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   122,   122,   123,   123,   123,   123,   123,   123,
     123,   124,   125,   125,   125,   126,   126,   126,   126,   126,
     126,   126,   127,   127,   128,   128,   129,   129,   130,   130,
     131,   131,   132,   132,   132,   133,   133,   134,   134
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     5,     2,     1,     3,     2,     1,     2,
       4,     1,     2,     1,     2,     2,     1,     2,     2,     1,
       4,     4,     2,     2,     2,     3,     2,     1,     2,     3,
       3,     3,     4,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     3,     1,     1,     2,     3,     1,     3,
       8,     3,     0,     7,     7,     1,     1,     2,    10,     2,
       3,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     3,     1,     3,     1,     8,
       3,     1,     6,     3,     1,     2,     3,     2,     1,     3,
       2,     2,     0,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     2,     5,     5,     0,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     0,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     4,     0,     1,     1,     3,     1,     1,
       3,     1,     0,     4,     1,     2,     3,     0,     3,     0,
       4,     1,     1,     2,     2,     1,     2,     2,     2
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
#line 148 "parser.y" /* yacc.c:1646  */
    { 
				(yyval.node) = (yyvsp[0].node);
				arvore = (yyval.node);
			}
#line 1542 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 154 "parser.y" /* yacc.c:1646  */
    { 
				(yyval.node) = (yyvsp[-1].node); 
				add_node((yyval.node), (yyvsp[0].node)); 
			}
#line 1551 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 159 "parser.y" /* yacc.c:1646  */
    { 
				(yyval.node) = (yyvsp[-1].node); 
				add_node((yyval.node), (yyvsp[0].node)); 
			}
#line 1560 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 164 "parser.y" /* yacc.c:1646  */
    { 
				(yyval.node) = (yyvsp[-1].node); 
				add_node((yyval.node), (yyvsp[0].node)); 
			}
#line 1569 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 169 "parser.y" /* yacc.c:1646  */
    { 
				(yyval.node) = new_node(NULL); 
			}
#line 1577 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 174 "parser.y" /* yacc.c:1646  */
    { 
				(yyval.node) = new_node((yyvsp[0].valor_lexico)); 
			}
#line 1585 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 178 "parser.y" /* yacc.c:1646  */
    { 
				(yyval.node) = new_node((yyvsp[0].valor_lexico)); 
			}
#line 1593 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 182 "parser.y" /* yacc.c:1646  */
    { 
				(yyval.node) = new_node((yyvsp[0].valor_lexico)); 
			}
#line 1601 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 186 "parser.y" /* yacc.c:1646  */
    { 
				(yyval.node) = new_node((yyvsp[0].valor_lexico)); 
			}
#line 1609 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 190 "parser.y" /* yacc.c:1646  */
    { 
				(yyval.node) = new_node((yyvsp[0].valor_lexico)); 
			}
#line 1617 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 195 "parser.y" /* yacc.c:1646  */
    { 
				(yyval.node) = new_node((yyvsp[0].valor_lexico)); 
			}
#line 1625 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 199 "parser.y" /* yacc.c:1646  */
    { 
				(yyval.node) = new_node((yyvsp[0].valor_lexico)); 
			}
#line 1633 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 203 "parser.y" /* yacc.c:1646  */
    { 
				(yyval.node) = new_node((yyvsp[0].valor_lexico)); 
			}
#line 1641 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 208 "parser.y" /* yacc.c:1646  */
    { 	
				(yyval.node) = new_node((yyvsp[-2].valor_lexico)); 
				add_node((yyval.node), (yyvsp[-1].node));
				add_node((yyval.node), new_node((yyvsp[0].valor_lexico)));
			}
#line 1651 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 214 "parser.y" /* yacc.c:1646  */
    { 	
				(yyval.node) = (yyvsp[-1].node); 
				add_node((yyval.node), new_node((yyvsp[0].valor_lexico)));
			}
#line 1660 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 220 "parser.y" /* yacc.c:1646  */
    { 
				(yyval.node) = (yyvsp[0].node); 
			}
#line 1668 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 224 "parser.y" /* yacc.c:1646  */
    { 
				(yyval.node) = new_node((yyvsp[0].valor_lexico)); 
			}
#line 1676 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 229 "parser.y" /* yacc.c:1646  */
    { 
				(yyval.node) = new_node((yyvsp[0].valor_lexico)); 
			}
#line 1684 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 233 "parser.y" /* yacc.c:1646  */
    { 
				(yyval.node) = new_node((yyvsp[0].valor_lexico)); 
			}
#line 1692 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 238 "parser.y" /* yacc.c:1646  */
    { 
				(yyval.node) = new_node((yyvsp[0].valor_lexico)); 
			}
#line 1700 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 242 "parser.y" /* yacc.c:1646  */
    { 
				(yyval.node) = new_node((yyvsp[0].valor_lexico)); 
			}
#line 1708 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 247 "parser.y" /* yacc.c:1646  */
    {	
					(yyval.node) = new_node((yyvsp[-4].valor_lexico));
					add_node((yyval.node), new_node((yyvsp[-3].valor_lexico)));
					add_node((yyval.node), new_node((yyvsp[-2].valor_lexico)));
					add_node((yyval.node), (yyvsp[-1].node));
					add_node((yyval.node), new_node((yyvsp[0].valor_lexico)));
				}
#line 1720 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 256 "parser.y" /* yacc.c:1646  */
    { 	
					(yyval.node) = (yyvsp[-1].node);
					add_node((yyval.node), (yyvsp[0].node));
				}
#line 1729 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 261 "parser.y" /* yacc.c:1646  */
    {	
					(yyval.node) = (yyvsp[0].node); 
				}
#line 1737 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 266 "parser.y" /* yacc.c:1646  */
    {	
					(yyval.node) = (yyvsp[-2].node);
					add_node((yyval.node), new_node((yyvsp[-1].valor_lexico)));
					add_node((yyval.node), (yyvsp[0].node));
				}
#line 1747 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 273 "parser.y" /* yacc.c:1646  */
    {	
					(yyval.node) = new_node((yyvsp[-1].valor_lexico));
					add_node((yyval.node), (yyvsp[0].node));
				}
#line 1756 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 278 "parser.y" /* yacc.c:1646  */
    {	
					(yyval.node) = new_node((yyvsp[0].valor_lexico));
				}
#line 1764 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 283 "parser.y" /* yacc.c:1646  */
    {	
						(yyval.node) = new_node((yyvsp[-1].valor_lexico));
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 1773 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 289 "parser.y" /* yacc.c:1646  */
    {	
						(yyval.node) = new_node((yyvsp[-3].valor_lexico));
						add_node((yyval.node), (yyvsp[-2].node));
						add_node((yyval.node), new_node((yyvsp[-1].valor_lexico)));
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 1784 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 296 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[0].node);
					}
#line 1792 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 301 "parser.y" /* yacc.c:1646  */
    {
							(yyval.node) = new_node((yyvsp[-1].valor_lexico));
							add_node((yyval.node), (yyvsp[0].node));
						}
#line 1801 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 306 "parser.y" /* yacc.c:1646  */
    {
							(yyval.node) = (yyvsp[0].node);
						}
#line 1809 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 311 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[-1].node);
						add_node((yyval.node), new_node((yyvsp[0].valor_lexico)));
					}
#line 1818 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 316 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[-1].valor_lexico));
						add_node((yyval.node), new_node((yyvsp[0].valor_lexico)));
					}
#line 1827 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 322 "parser.y" /* yacc.c:1646  */
    {
				(yyval.node) = new_node((yyvsp[0].valor_lexico));
			}
#line 1835 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 326 "parser.y" /* yacc.c:1646  */
    {
				(yyval.node) = new_node((yyvsp[-1].valor_lexico));
				add_node((yyval.node), new_node((yyvsp[0].valor_lexico)));
			}
#line 1844 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 332 "parser.y" /* yacc.c:1646  */
    {
				(yyval.node) = new_node((yyvsp[-1].valor_lexico));
				add_node((yyval.node), (yyvsp[0].node));
			}
#line 1853 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 337 "parser.y" /* yacc.c:1646  */
    {
				(yyval.node) = (yyvsp[0].node);
			}
#line 1861 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 342 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[-3].node);
						add_node((yyval.node), new_node((yyvsp[-2].valor_lexico)));
						add_node((yyval.node), new_node((yyvsp[-1].valor_lexico)));
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 1872 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 349 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[-3].valor_lexico));
						add_node((yyval.node), new_node((yyvsp[-2].valor_lexico)));
						add_node((yyval.node), new_node((yyvsp[-1].valor_lexico)));
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 1883 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 357 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[-1].valor_lexico));
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 1892 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 362 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[-1].node);
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 1901 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 368 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[-1].valor_lexico));
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 1910 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 373 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[-2].valor_lexico));
						add_node((yyval.node), (yyvsp[-1].node));
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 1920 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 380 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[-1].valor_lexico));
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 1929 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 386 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[0].valor_lexico));
				}
#line 1937 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 390 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = (yyvsp[-1].node);
					add_node((yyval.node), (yyvsp[0].node));
				}
#line 1946 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 396 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[-2].valor_lexico));
						add_node((yyval.node), (yyvsp[-1].node));
						add_node((yyval.node), new_node((yyvsp[0].valor_lexico)));
					}
#line 1956 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 402 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[-2].valor_lexico));
						add_node((yyval.node), (yyvsp[-1].node));
						add_node((yyval.node), new_node((yyvsp[0].valor_lexico)));
					}
#line 1966 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 408 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[-2].valor_lexico));
						add_node((yyval.node), (yyvsp[-1].node));
						add_node((yyval.node), new_node((yyvsp[0].valor_lexico)));
					}
#line 1976 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 414 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[-3].node);
						add_node((yyval.node), new_node((yyvsp[-2].valor_lexico)));
						add_node((yyval.node), (yyvsp[-1].node));
						add_node((yyval.node), new_node((yyvsp[0].valor_lexico)));
					}
#line 1987 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 421 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[-1].node);
						add_node((yyval.node), new_node((yyvsp[0].valor_lexico)));
					}
#line 1996 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 426 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[-1].node);
						add_node((yyval.node), new_node((yyvsp[0].valor_lexico)));
					}
#line 2005 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 431 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[-1].node);
						add_node((yyval.node), new_node((yyvsp[0].valor_lexico)));
					}
#line 2014 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 436 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[-1].node);
						add_node((yyval.node), new_node((yyvsp[0].valor_lexico)));
					}
#line 2023 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 441 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[-1].node);
						add_node((yyval.node), new_node((yyvsp[0].valor_lexico)));
					}
#line 2032 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 446 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[-1].node);
						add_node((yyval.node), new_node((yyvsp[0].valor_lexico)));
					}
#line 2041 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 451 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[-1].node);
						add_node((yyval.node), new_node((yyvsp[0].valor_lexico)));
					}
#line 2050 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 456 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[-1].node);
						add_node((yyval.node), new_node((yyvsp[0].valor_lexico)));
					}
#line 2059 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 461 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[-1].node);
						add_node((yyval.node), new_node((yyvsp[0].valor_lexico)));
					}
#line 2068 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 466 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[-1].node);
						add_node((yyval.node), new_node((yyvsp[0].valor_lexico)));
					}
#line 2077 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 471 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[-2].valor_lexico));
						add_node((yyval.node), (yyvsp[-1].node));
						add_node((yyval.node), new_node((yyvsp[0].valor_lexico)));
					}
#line 2087 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 477 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[0].node);
					}
#line 2095 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 481 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[0].node);
					}
#line 2103 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 486 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[-1].valor_lexico));
					add_node((yyval.node), (yyvsp[0].node));
				}
#line 2112 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 492 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[-2].valor_lexico));
					add_node((yyval.node), (yyvsp[-1].node));
					add_node((yyval.node), (yyvsp[0].node));
				}
#line 2122 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 499 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[0].valor_lexico));
				}
#line 2130 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 503 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[-2].valor_lexico));
					add_node((yyval.node), (yyvsp[-1].node));
					add_node((yyval.node), (yyvsp[0].node));
				}
#line 2140 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 511 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[-7].valor_lexico));
					add_node((yyval.node), new_node((yyvsp[-6].valor_lexico)));
					add_node((yyval.node), (yyvsp[-5].node));
					add_node((yyval.node), new_node((yyvsp[-4].valor_lexico)));
					add_node((yyval.node), new_node((yyvsp[-3].valor_lexico)));
					add_node((yyval.node), new_node((yyvsp[-2].valor_lexico)));
					add_node((yyval.node), (yyvsp[-1].node));
					add_node((yyval.node), (yyvsp[0].node));
				}
#line 2155 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 523 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[-2].valor_lexico));
					add_node((yyval.node), new_node((yyvsp[-1].valor_lexico)));
					add_node((yyval.node), (yyvsp[0].node));
				}
#line 2165 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 529 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node(NULL);
				}
#line 2173 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 535 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[-6].valor_lexico));
					add_node((yyval.node), new_node((yyvsp[-5].valor_lexico)));
					add_node((yyval.node), (yyvsp[-4].node));
					add_node((yyval.node), new_node((yyvsp[-3].valor_lexico)));
					add_node((yyval.node), new_node((yyvsp[-2].valor_lexico)));
					add_node((yyval.node), new_node((yyvsp[-1].valor_lexico)));
					add_node((yyval.node), (yyvsp[0].node));
				}
#line 2187 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 547 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[-6].valor_lexico));
					add_node((yyval.node), new_node((yyvsp[-5].valor_lexico)));
					add_node((yyval.node), (yyvsp[-4].node));
					add_node((yyval.node), new_node((yyvsp[-3].valor_lexico)));
					add_node((yyval.node), new_node((yyvsp[-2].valor_lexico)));
					add_node((yyval.node), (yyvsp[-1].node));
					add_node((yyval.node), new_node((yyvsp[0].valor_lexico)));

				}
#line 2202 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 559 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[0].valor_lexico));
				}
#line 2210 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 564 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[0].valor_lexico));
				}
#line 2218 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 569 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[-1].valor_lexico));
					add_node((yyval.node), (yyvsp[0].node));
				}
#line 2227 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 578 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[-9].valor_lexico));
					add_node((yyval.node), new_node((yyvsp[-8].valor_lexico)));
					add_node((yyval.node), (yyvsp[-7].node));
					add_node((yyval.node), (yyvsp[-6].node));
					add_node((yyval.node), (yyvsp[-5].node));
					add_node((yyval.node), new_node((yyvsp[-4].valor_lexico)));
					add_node((yyval.node), (yyvsp[-3].node));
					add_node((yyval.node), (yyvsp[-2].node));
					add_node((yyval.node), new_node((yyvsp[-1].valor_lexico)));
					add_node((yyval.node), (yyvsp[0].node));
				}
#line 2244 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 592 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[-1].valor_lexico));
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 2253 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 597 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[-2].node);
						add_node((yyval.node), new_node((yyvsp[-1].valor_lexico)));
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 2263 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 603 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[-1].valor_lexico));
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 2272 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 608 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[-1].valor_lexico));
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 2281 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 613 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[0].node);
					}
#line 2289 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 617 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[0].node);
					}
#line 2297 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 621 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[0].node);
					}
#line 2305 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 625 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[0].node);
					}
#line 2313 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 629 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[0].node);
					}
#line 2321 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 633 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[0].node);
					}
#line 2329 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 637 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[0].node);
					}
#line 2337 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 641 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[0].node);
					}
#line 2345 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 645 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[0].node);
					}
#line 2353 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 649 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[0].node);
					}
#line 2361 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 653 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[-1].valor_lexico));
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 2370 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 658 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[-1].valor_lexico));
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 2379 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 664 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[-2].valor_lexico));
						add_node((yyval.node), (yyvsp[-1].node));
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 2389 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 670 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2397 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 675 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[-2].valor_lexico));
						add_node((yyval.node), (yyvsp[-1].node));
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 2407 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 681 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2415 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 688 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[-7].valor_lexico));
						add_node((yyval.node), new_node((yyvsp[-6].valor_lexico)));
						add_node((yyval.node), new_node((yyvsp[-5].valor_lexico)));
						add_node((yyval.node), new_node((yyvsp[-4].valor_lexico)));
						add_node((yyval.node), (yyvsp[-3].node));
						add_node((yyval.node), (yyvsp[-2].node));
						add_node((yyval.node), new_node((yyvsp[-1].valor_lexico)));
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 2430 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 700 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[-2].valor_lexico));
						add_node((yyval.node), (yyvsp[-1].node));
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 2440 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 706 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2448 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 711 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[-5].valor_lexico));
					add_node((yyval.node), new_node((yyvsp[-4].valor_lexico)));
					add_node((yyval.node), (yyvsp[-3].node));
					add_node((yyval.node), new_node((yyvsp[-2].valor_lexico)));
					add_node((yyval.node), new_node((yyvsp[-1].valor_lexico)));
					add_node((yyval.node), (yyvsp[0].node));
				}
#line 2461 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 721 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[-2].valor_lexico));
					add_node((yyval.node), new_node((yyvsp[-1].valor_lexico)));
					add_node((yyval.node), new_node((yyvsp[0].valor_lexico)));
				}
#line 2471 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 728 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[0].valor_lexico));
				}
#line 2479 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 732 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = (yyvsp[-1].node);
					add_node((yyval.node), (yyvsp[0].node));
				}
#line 2488 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 737 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[-2].valor_lexico));
					add_node((yyval.node), (yyvsp[-1].node));
					add_node((yyval.node), (yyvsp[0].node));
				}
#line 2498 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 744 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[-1].valor_lexico));
					add_node((yyval.node), (yyvsp[0].node));
				}
#line 2507 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 749 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = (yyvsp[0].node);
				}
#line 2515 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 754 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = (yyvsp[-2].node);
					add_node((yyval.node), new_node((yyvsp[-1].valor_lexico)));
					add_node((yyval.node), (yyvsp[0].node));
				}
#line 2525 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 760 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[-1].valor_lexico));
					add_node((yyval.node), new_node((yyvsp[0].valor_lexico)));
				}
#line 2534 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 766 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[-1].valor_lexico));
					add_node((yyval.node), (yyvsp[0].node));
				}
#line 2543 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 771 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node(NULL);
				}
#line 2551 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 776 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[0].valor_lexico));
				}
#line 2559 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 780 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[0].valor_lexico));
				}
#line 2567 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 784 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[0].valor_lexico));
				}
#line 2575 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 788 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[0].valor_lexico));
				}
#line 2583 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 792 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[0].valor_lexico));
				}
#line 2591 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 796 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[0].valor_lexico));
				}
#line 2599 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 800 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[0].valor_lexico));
				}
#line 2607 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 805 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[-1].valor_lexico));
					add_node((yyval.node), (yyvsp[0].node));
				}
#line 2616 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 810 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[-1].valor_lexico));
					add_node((yyval.node), (yyvsp[0].node));
				}
#line 2625 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 815 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node((yyvsp[-1].valor_lexico));
					add_node((yyval.node), (yyvsp[0].node));
				}
#line 2634 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 820 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = (yyvsp[-4].node);
					add_node((yyval.node), (yyvsp[-3].node));
					add_node((yyval.node), new_node((yyvsp[-2].valor_lexico)));
					add_node((yyval.node), (yyvsp[-1].node));
					add_node((yyval.node), (yyvsp[0].node));
				}
#line 2646 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 829 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = (yyvsp[-4].node);
					add_node((yyval.node), (yyvsp[-3].node));
					add_node((yyval.node), new_node((yyvsp[-2].valor_lexico)));
					add_node((yyval.node), (yyvsp[-1].node));
					add_node((yyval.node), (yyvsp[0].node));
				}
#line 2658 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 837 "parser.y" /* yacc.c:1646  */
    {
					(yyval.node) = new_node(NULL);
				}
#line 2666 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 842 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2674 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 846 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2682 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 850 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2690 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 854 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2698 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 858 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2706 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 862 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2714 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 866 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2722 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 870 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2730 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 874 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2738 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 878 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2746 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 882 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2754 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 886 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2762 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 890 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2770 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 894 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2778 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 898 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2786 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 902 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2794 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 907 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[-1].node);
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 2803 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 912 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node(NULL);
					}
#line 2811 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 917 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2819 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 921 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2827 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 925 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2835 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 929 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2843 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 933 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2851 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 937 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2859 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 941 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2867 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 946 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[-2].node);
						add_node((yyval.node), (yyvsp[-1].node));
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 2877 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 953 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[-1].node);
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 2886 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 958 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[-3].valor_lexico));
						add_node((yyval.node), (yyvsp[-2].node));
						add_node((yyval.node), new_node((yyvsp[-1].valor_lexico)));
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 2897 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 965 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node(NULL);
					}
#line 2905 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 970 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2913 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 974 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2921 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 978 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[-2].valor_lexico));
						add_node((yyval.node), (yyvsp[-1].node));
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 2931 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 984 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2939 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 988 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[0].valor_lexico));
					}
#line 2947 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 992 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[-2].valor_lexico));
						add_node((yyval.node), (yyvsp[-1].node));
						add_node((yyval.node), new_node((yyvsp[0].valor_lexico)));
					}
#line 2957 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 998 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[0].node);
					}
#line 2965 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1003 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node(NULL);
					}
#line 2973 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1007 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[-3].node);
						add_node((yyval.node), new_node((yyvsp[-2].valor_lexico)));
						add_node((yyval.node), (yyvsp[-1].node));
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 2984 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1015 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[0].node);
					}
#line 2992 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1019 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[-1].valor_lexico));
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 3001 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1025 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[-2].valor_lexico));
						add_node((yyval.node), new_node((yyvsp[-1].valor_lexico)));
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 3011 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1031 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node(NULL);
					}
#line 3019 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1036 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[-2].valor_lexico));
						add_node((yyval.node), (yyvsp[-1].node));
						add_node((yyval.node), new_node((yyvsp[0].valor_lexico)));
					}
#line 3029 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 1042 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node(NULL);
					}
#line 3037 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 1047 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = new_node((yyvsp[-3].valor_lexico));
						add_node((yyval.node), (yyvsp[-2].node));
						add_node((yyval.node), new_node((yyvsp[-1].valor_lexico)));
						add_node((yyval.node), (yyvsp[0].node));
					}
#line 3048 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 1054 "parser.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[0].node);
					}
#line 3056 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 1059 "parser.y" /* yacc.c:1646  */
    {
							(yyval.node) = new_node((yyvsp[0].valor_lexico));
						}
#line 3064 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 1063 "parser.y" /* yacc.c:1646  */
    {
							(yyval.node) = (yyvsp[-1].node);
							add_node((yyval.node), (yyvsp[0].node));
						}
#line 3073 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 1068 "parser.y" /* yacc.c:1646  */
    {
							(yyval.node) = new_node((yyvsp[-1].valor_lexico));
							add_node((yyval.node), (yyvsp[0].node));
						}
#line 3082 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 1074 "parser.y" /* yacc.c:1646  */
    {
							(yyval.node) = new_node((yyvsp[0].valor_lexico));
						}
#line 3090 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 1078 "parser.y" /* yacc.c:1646  */
    {
							(yyval.node) = new_node((yyvsp[-1].valor_lexico));
							add_node((yyval.node), (yyvsp[0].node));
						}
#line 3099 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 1084 "parser.y" /* yacc.c:1646  */
    {
								(yyval.node) = (yyvsp[-1].node);
								add_node((yyval.node), (yyvsp[0].node));
							}
#line 3108 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 1089 "parser.y" /* yacc.c:1646  */
    {
								(yyval.node) = new_node((yyvsp[-1].valor_lexico));
								add_node((yyval.node), (yyvsp[0].node));
							}
#line 3117 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 3121 "parser.tab.c" /* yacc.c:1646  */
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
#line 1094 "parser.y" /* yacc.c:1906  */


void yyerror(char const *s)
{
    fprintf(stderr,"ERROR: line %d - %s\n", yylineno, s);
}
