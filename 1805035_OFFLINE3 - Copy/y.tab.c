/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "1805035.y"

#include <bits/stdc++.h>
// #include<iostream>
// #include<cstdlib>
// #include<cstring>
// #include<cmath>
#include "SymbolInfo.h"
#include "SymbolTable.h"
// #define YYSTYPE SymbolInfo*

using namespace std;

int yyparse(void);
int yylex(void);
extern FILE *yyin;
extern int line_count;
extern int error_count;
SymbolTable *table;
string space=" ";
FILE *fp,*fp1,*fp2,*fp3;
ofstream logfile2("log.txt");
ofstream errorfile("error.txt");
ofstream asmCode("code.txt");
ofstream asmData("data.txt");
vector< pair<string,string> > temporaryParameterList ;
int currentOffset=2,temporaryOffset=2;
vector<SymbolInfo*>declared_varList;
vector<SymbolInfo*>My_parameter_list;

void yyerror(char *s)
{
	errorfile<<"Error at line e"<<line_count<<" :"<<s<<endl<<endl;
	logfile2<<"Error at line e"<<line_count<<" :"<<s<<endl<<endl;
	error_count++;

}

void printMSG(string nameOfPart){
	logfile2<<"\nLine "<<line_count<<nameOfPart<<endl<<endl;
}
void printMSG(string nameOfPart,string nameOfToken){
	logfile2<<"\nLine "<<line_count<<": "<<nameOfPart<<endl<<endl<<nameOfToken<<endl<<endl;
}
bool conversionError(string a ,string b){
	if(a=="CONST_FLOAT"&&b!="CONST_FLOAT")
		return true;
	else if(a=="VOID"||b=="VOID")
		return true;
	return false;
}
void printError(string nameOfPart,string nameOfToken){
	errorfile<<"Error at line "<<line_count<<": "<<nameOfPart<<space<<nameOfToken<<endl<<endl;
	logfile2<<"Error at line "<<line_count<<": "<<nameOfPart<<space<<nameOfToken<<endl<<endl;
	error_count++;	
}
void checkParameterUniquenessForFunDefinition(){
	if(temporaryParameterList.size()!=0){
		for(int i=0;i<temporaryParameterList.size();i++){
			string name = temporaryParameterList[i].first;
			string type = temporaryParameterList[i].second;

			SymbolInfo *currentSymbol = new SymbolInfo();
			currentSymbol->setName(name);
			logfile2<<i<<"----"<<name<<" "<<type<<endl;
			currentSymbol->setType("ID");
			currentSymbol->typeOfVar = type;
			currentSymbol->offset=(i)*2;
			
			if(name==""){
				errorfile<<"Error at line "<<line_count-1<<" :"<<i+1<<"th parameter's name not given in function definition  "<<currentSymbol->getName()<<" in parameter"<<endl<<endl;
				logfile2<<"Error at line "<<line_count-1<<" :"<<i+1<<"th parameter's name not given in function definition of var"<<currentSymbol->getName()<<" in parameter"<<endl<<endl;
				error_count++;
			}
			else if(!table->Insert(currentSymbol)){
				errorfile<<"Error at line "<<line_count-1<<" :"<<"Multiple declaration of "<<currentSymbol->getName()<<" in parameter"<<endl<<endl;
				logfile2<<"Error at line "<<line_count-1<<" :"<<"Multiple declaration of "<<currentSymbol->getName()<<" in parameter"<<endl<<endl;
				error_count++;
				
			}
			

		
	}
	
	}
	
	temporaryParameterList.clear();
}
void parameterUniquenessCheckforDeclaration(){
	table->EnterScope();
	
	if(temporaryParameterList.size()!=0){
		for(int i=0;i<temporaryParameterList.size();i++){
			string name = temporaryParameterList[i].first;
			string type = temporaryParameterList[i].second;

			SymbolInfo *currentSymbol = new SymbolInfo();
			currentSymbol->setName(name);
			currentSymbol->setType("ID");
			currentSymbol->typeOfVar = type;
			if(name!=""&&!table->Insert(currentSymbol)){
				errorfile<<"Error at line "<<line_count-1<<" :"<<"Multiple declaration of "<<currentSymbol->getName()<<" in parameter"<<endl<<endl;
				logfile2<<"Error at line "<<line_count-1<<" :"<<"Multiple declaration of "<<currentSymbol->getName()<<" in parameter"<<endl<<endl;
				error_count++;
				
			}
		}
	}
	temporaryParameterList.clear();
	table->ExitScope();
}
int label_count = 0;
int temp_count = 0;
string newLabel()
{
	string label = "L";
	stringstream ss;
	ss<<label_count;
	label += ss.str();
	label_count++;
	return label;
}
//function for generating new temporary varible for assembly code
// string newTemp()
// {
// 	string temp = "t";
// 	stringstream ss;
// 	ss<<temp_count;
// 	temp += ss.str();
// 	temp_count++;
// 	var_list.push_back("\t"+temp+"\tdw\t?");
// 	return temp;
// }
string output_procedure ="\nPRINT_FUNC PROC\
						\n\tPUSH AX\
						\n\tPUSH BX\
						\n\tPUSH CX\
						\n\tPUSH DX\
						\n\n\tOR AX, AX\
						\n\tJGE END_IF1\
						\n\tPUSH AX\
						\n\tMOV DL,'-'\
						\n\tMOV AH, 2\
						\n\tINT 21H\
						\n\tPOP AX\
						\n\tNEG AX\
						\n\nEND_IF1:\
						\n\tXOR CX, CX\
						\n\tMOV BX, 10D\
						\n\nREPEAT1:\
						\n\tXOR DX, DX\
						\n\tDIV BX\
						\n\tPUSH DX\
						\n\tINC CX\
						\n\n\tOR AX, AX\
						\n\tJNE REPEAT1\
						\n\n\tMOV AH, 2\
						\n\nPRINT_LOOP:\
						\n\tPOP DX\
						\n\tOR DL, 30H\
						\n\tINT 21H\
						\n\tLOOP PRINT_LOOP\
						\n\tMOV AH, 2\
						\n\tMOV DL, 10\
						\n\tINT 21H\
						\n\n\tMOV DL, 13\
						\n\tINT 21H\
						\n\n\tPOP DX\
						\n\tPOP CX\
						\n\tPOP BX\
						\n\tPOP AX\
						\n\tRET\
						\nPRINT_FUNC ENDP\n\n";
string whileLabel,whileEnd,conditionEnd,elseLabel,forLoopStart,ENDLOOP,IncLabel,LoopLabel;
stack<string>conditionStack;

#line 247 "y.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    IF = 258,
    ELSE = 259,
    FOR = 260,
    DO = 261,
    NOT = 262,
    FLOAT = 263,
    INT = 264,
    VOID = 265,
    CHAR = 266,
    DOUBLE = 267,
    WHILE = 268,
    RETURN = 269,
    CONTINUE = 270,
    LPAREN = 271,
    RPAREN = 272,
    LCURL = 273,
    RCURL = 274,
    COMMA = 275,
    SEMICOLON = 276,
    LTHIRD = 277,
    RTHIRD = 278,
    PRINTLN = 279,
    CONST_INT = 280,
    CONST_FLOAT = 281,
    CONST_CHAR = 282,
    ID = 283,
    INCOP = 284,
    DECOP = 285,
    ADDOP = 286,
    MULOP = 287,
    RELOP = 288,
    LOGICOP = 289,
    ASSIGNOP = 290,
    LOWER_THAN_ELSE = 291,
    Unrecognized = 292
  };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define FOR 260
#define DO 261
#define NOT 262
#define FLOAT 263
#define INT 264
#define VOID 265
#define CHAR 266
#define DOUBLE 267
#define WHILE 268
#define RETURN 269
#define CONTINUE 270
#define LPAREN 271
#define RPAREN 272
#define LCURL 273
#define RCURL 274
#define COMMA 275
#define SEMICOLON 276
#define LTHIRD 277
#define RTHIRD 278
#define PRINTLN 279
#define CONST_INT 280
#define CONST_FLOAT 281
#define CONST_CHAR 282
#define ID 283
#define INCOP 284
#define DECOP 285
#define ADDOP 286
#define MULOP 287
#define RELOP 288
#define LOGICOP 289
#define ASSIGNOP 290
#define LOWER_THAN_ELSE 291
#define Unrecognized 292

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 177 "1805035.y"
double double_val; int integer_val;char char_val ; SymbolInfo* symbol_val;

#line 376 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



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
typedef yytype_uint8 yy_state_t;

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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   163

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  85
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  143

#define YYUNDEFTOK  2
#define YYMAXUTOK   292


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35,    36,    37
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   195,   195,   195,   227,   229,   236,   240,   246,   249,
     253,   260,   334,   367,   483,   482,   620,   620,   672,   681,
     688,   696,   707,   707,   719,   719,   733,   749,   753,   757,
     763,   782,   793,   816,   833,   856,   859,   865,   871,   877,
     882,   886,   888,   882,   898,   904,   904,   920,   923,   920,
     930,   948,   954,   960,   967,   968,   975,  1008,  1050,  1055,
    1055,  1096,  1101,  1101,  1134,  1139,  1139,  1185,  1192,  1192,
    1219,  1228,  1276,  1287,  1297,  1304,  1315,  1379,  1385,  1395,
    1406,  1424,  1442,  1447,  1450,  1468
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "FOR", "DO", "NOT",
  "FLOAT", "INT", "VOID", "CHAR", "DOUBLE", "WHILE", "RETURN", "CONTINUE",
  "LPAREN", "RPAREN", "LCURL", "RCURL", "COMMA", "SEMICOLON", "LTHIRD",
  "RTHIRD", "PRINTLN", "CONST_INT", "CONST_FLOAT", "CONST_CHAR", "ID",
  "INCOP", "DECOP", "ADDOP", "MULOP", "RELOP", "LOGICOP", "ASSIGNOP",
  "LOWER_THAN_ELSE", "Unrecognized", "$accept", "start", "$@1", "program",
  "unit", "func_declaration", "func_definition", "$@2", "$@3",
  "parameter_list", "compound_statement", "$@4", "$@5", "var_declaration",
  "type_specifier", "declaration_list", "statements", "statement", "$@6",
  "$@7", "$@8", "$@9", "$@10", "$@11", "CONDITIONAL_STATEMENT",
  "expression_statement", "variable", "expression", "$@12",
  "logic_expression", "$@13", "rel_expression", "$@14",
  "simple_expression", "$@15", "term", "unary_expression", "factor",
  "argument_list", "arguments", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292
};
# endif

#define YYPACT_NINF (-83)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-69)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       7,   -83,   -83,    11,    49,   -83,   -83,   -83,   -83,    49,
     -83,   -83,   -83,   -83,   -10,   -83,     3,     6,    45,    35,
      16,    42,   -83,    53,    30,    47,    54,    55,    70,   -83,
      63,    80,    73,    49,   -83,   -83,   -83,    74,    81,   -83,
      63,   -83,    63,    76,    83,   106,    91,   -83,   -83,   -83,
     -83,   -83,    96,   102,   110,   -83,   110,   110,   -83,   105,
     -83,   -83,    12,   110,   -83,   -83,    95,    77,   -83,   108,
     -83,    38,   107,   -83,    99,    15,    97,   -83,   -83,   -83,
     110,    14,    59,   -83,   123,   119,   125,   115,   110,   110,
     -83,   122,   -83,   -83,   106,   -83,   -83,   111,   -83,   113,
     112,   117,   110,   -83,   -83,   110,   -83,   -83,   132,   -83,
     133,   131,   129,   149,   110,   110,   110,   110,   -83,    14,
     -83,   134,   -83,   110,   -83,   -83,   -83,   -83,   126,    97,
     -83,   137,   -83,   -83,   106,   110,   106,   -83,   139,   -83,
     -83,   106,   -83
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     5,     4,     0,     0,     1,    28,    27,    29,     3,
       7,     9,    10,     8,     0,     6,    33,     0,     0,     0,
       0,     0,    26,    16,     0,    21,     0,     0,    30,    12,
       0,     0,    14,     0,    20,    34,    31,     0,    22,    17,
       0,    11,     0,    19,     0,     0,     0,    13,    15,    18,
      32,    52,     0,     0,     0,    47,     0,     0,    54,     0,
      78,    79,    56,     0,    39,    37,     0,     0,    35,     0,
      38,    75,     0,    58,    61,    64,    67,    70,    74,    25,
       0,     0,    75,    73,     0,     0,     0,     0,    83,     0,
      72,    33,    23,    36,     0,    80,    81,     0,    55,     0,
       0,     0,     0,    53,    40,     0,    51,    77,     0,    85,
       0,    82,     0,    44,     0,     0,     0,     0,    71,     0,
      48,     0,    76,     0,    57,    45,    60,    63,    66,    69,
      41,     0,    50,    84,     0,     0,     0,    46,     0,    49,
      42,     0,    43
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -83,   -83,   -83,   -83,   150,   -83,   -83,   -83,   -83,   -83,
     -20,   -83,   -83,    52,     5,   -83,   -83,   -65,   -83,   -83,
     -83,   -83,   -83,   -83,   -83,   -76,   -51,   -56,   -83,   -82,
     -83,    43,   -83,    44,   -83,    46,   -50,   -83,   -83,   -83
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     9,    10,    11,    12,    42,    30,    24,
      64,    45,    46,    65,    66,    17,    67,    68,   119,   135,
     141,   134,    84,   131,    69,    70,    71,    72,    97,    73,
      99,    74,   100,    75,   101,    76,    77,    78,   110,   111
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      85,    86,    93,    82,    83,   104,   109,    20,     1,    14,
      39,     5,    82,    90,    14,    -2,    -2,    -2,    16,    18,
      47,    54,    48,    25,   103,    19,    21,    22,    88,   113,
      57,    31,   126,   112,    89,    58,    27,    82,    43,    60,
      61,   133,    62,   130,     2,    63,   -68,    32,   -65,   120,
      33,    82,   118,     6,     7,     8,    13,     6,     7,     8,
      26,    13,    23,    82,    82,    82,    82,    95,    96,   137,
      28,   139,    82,   -59,    29,    34,   142,    35,    51,   138,
      52,    38,    53,    36,    54,     6,     7,     8,    95,    96,
      55,    56,    37,    57,    41,    38,    92,    40,    58,    44,
     -24,    59,    60,    61,    49,    62,    50,    51,    63,    52,
      79,    53,    80,    54,     6,     7,     8,    54,    81,    55,
      56,    87,    57,    91,    38,    94,    57,    58,    98,   102,
      59,    60,    61,   -62,    62,    60,    61,    63,    62,   105,
     106,    63,   107,   108,    19,   116,   114,   115,   117,   121,
     122,   123,   124,   125,   136,   132,   140,   -68,   127,    15,
     128,     0,     0,   129
};

static const yytype_int16 yycheck[] =
{
      56,    57,    67,    54,    54,    81,    88,     1,     1,     4,
      30,     0,    63,    63,     9,     8,     9,    10,    28,    16,
      40,     7,    42,    18,    80,    22,    20,    21,    16,    94,
      16,     1,   114,    89,    22,    21,    20,    88,    33,    25,
      26,   123,    28,   119,    37,    31,    31,    17,    33,   105,
      20,   102,   102,     8,     9,    10,     4,     8,     9,    10,
      25,     9,    17,   114,   115,   116,   117,    29,    30,   134,
      28,   136,   123,    35,    21,    28,   141,    23,     1,   135,
       3,    18,     5,    28,     7,     8,     9,    10,    29,    30,
      13,    14,    22,    16,    21,    18,    19,    17,    21,    25,
      19,    24,    25,    26,    28,    28,    23,     1,    31,     3,
      19,     5,    16,     7,     8,     9,    10,     7,    16,    13,
      14,    16,    16,    28,    18,    17,    16,    21,    21,    32,
      24,    25,    26,    34,    28,    25,    26,    31,    28,    16,
      21,    31,    17,    28,    22,    33,    35,    34,    31,    17,
      17,    20,    23,     4,    17,    21,    17,    31,   115,     9,
     116,    -1,    -1,   117
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,    37,    39,    40,     0,     8,     9,    10,    41,
      42,    43,    44,    51,    52,    42,    28,    53,    16,    22,
       1,    20,    21,    17,    47,    52,    25,    20,    28,    21,
      46,     1,    17,    20,    28,    23,    28,    22,    18,    48,
      17,    21,    45,    52,    25,    49,    50,    48,    48,    28,
      23,     1,     3,     5,     7,    13,    14,    16,    21,    24,
      25,    26,    28,    31,    48,    51,    52,    54,    55,    62,
      63,    64,    65,    67,    69,    71,    73,    74,    75,    19,
      16,    16,    64,    74,    60,    65,    65,    16,    16,    22,
      74,    28,    19,    55,    17,    29,    30,    66,    21,    68,
      70,    72,    32,    65,    63,    16,    21,    17,    28,    67,
      76,    77,    65,    55,    35,    34,    33,    31,    74,    56,
      65,    17,    17,    20,    23,     4,    67,    69,    71,    73,
      63,    61,    21,    67,    59,    57,    17,    55,    65,    55,
      17,    58,    55
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    38,    40,    39,    39,    39,    41,    41,    42,    42,
      42,    43,    43,    44,    45,    44,    46,    44,    47,    47,
      47,    47,    49,    48,    50,    48,    51,    52,    52,    52,
      53,    53,    53,    53,    53,    54,    54,    55,    55,    55,
      56,    57,    58,    55,    55,    59,    55,    60,    61,    55,
      55,    55,    55,    62,    63,    63,    64,    64,    65,    66,
      65,    67,    68,    67,    69,    70,    69,    71,    72,    71,
      73,    73,    74,    74,    74,    75,    75,    75,    75,    75,
      75,    75,    76,    76,    77,    77
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     2,     1,     1,     1,
       1,     6,     5,     7,     0,     7,     0,     6,     4,     3,
       2,     1,     0,     4,     0,     3,     3,     1,     1,     1,
       3,     4,     6,     1,     4,     1,     2,     1,     1,     1,
       0,     0,     0,    10,     3,     0,     6,     0,     0,     7,
       5,     3,     1,     3,     1,     2,     1,     4,     1,     0,
       4,     1,     0,     4,     1,     0,     4,     1,     0,     4,
       1,     3,     2,     2,     1,     1,     4,     3,     1,     1,
       2,     2,     1,     0,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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
  case 2:
#line 195 "1805035.y"
        {
		asmData<<".MODEL BIG\n.STACK 400H"<<endl;
		asmCode<<".CODE"<<endl;
		asmCode<<output_procedure;
		asmData<<".DATA"<<endl;
		asmData<<"FUNC_RETURN_VALUE DW ?\nTEMPORARY_VALUE DW ?"<<endl;
}
#line 1667 "y.tab.c"
    break;

  case 3:
#line 202 "1805035.y"
        {
		asmCode<<"END MAIN"<<endl;
		cout<<"start"<<endl;
		logfile2<<"Line "<<line_count-1<<": start : program"<<endl;
		//write your code in this block in all the similar blocks below
		fstream f1,f2,f3; 
 		 string str1,str2; //str1 for fetching string line from file 1 and str2 for fetching string from file2
  
			f1.open("data.txt",ios::in);//opening file in reading mode
			f2.open("code.txt",ios::in);
			f3.open("asmCode.asm",ios::out);//opening file in writing mode

			while(getline(f1, str1)){ //read lines from file object and put it into string and push back to file 3.
					f3<<str1; // inserting the fetched string inside file3
					f3<<endl;
				}

			while(getline(f2, str2)){ //Same step for file 2 to file 3 fetching
					f3<<str2;
					f3<<endl;
				}
			
			f1.close();
			f2.close();
			f3.close();
	}
#line 1698 "y.tab.c"
    break;

  case 4:
#line 227 "1805035.y"
                      {
		printError("Unrecognized Character","");
	}
#line 1706 "y.tab.c"
    break;

  case 5:
#line 229 "1805035.y"
               {
		yyerror;
		yyerrok;
		yyclearin;
	}
#line 1716 "y.tab.c"
    break;

  case 6:
#line 236 "1805035.y"
                     {
		(yyval.symbol_val) = new SymbolInfo((yyvsp[-1].symbol_val)->getName()+"\n"+(yyvsp[0].symbol_val)->getName(),"");
		logfile2<<"\nLine  "<<line_count<<": program : program unit"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;
		}
#line 1725 "y.tab.c"
    break;

  case 7:
#line 240 "1805035.y"
                      {
		(yyval.symbol_val) = (yyvsp[0].symbol_val);
		logfile2<<"\nLine  "<<line_count<<": program : unit"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;
	}
#line 1734 "y.tab.c"
    break;

  case 8:
#line 246 "1805035.y"
                      {		
			(yyval.symbol_val) = (yyvsp[0].symbol_val);
			logfile2<<"\nLine  "<<line_count<<": unit : var_declaration"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;
		}
#line 1743 "y.tab.c"
    break;

  case 9:
#line 249 "1805035.y"
                                    {		
			(yyval.symbol_val) = (yyvsp[0].symbol_val);
			logfile2<<"\nLine  "<<line_count<<": unit : func_declaration"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;
		 }
#line 1752 "y.tab.c"
    break;

  case 10:
#line 253 "1805035.y"
                       {
     		(yyval.symbol_val) = (yyvsp[0].symbol_val);
			logfile2<<"\nLine  "<<line_count<<": unit : func_definition"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;
     	}
#line 1761 "y.tab.c"
    break;

  case 11:
#line 260 "1805035.y"
                                                                            {
	/* ************************************************************************ */
	/*	 				Implement the below characteristics						*/
	/*   We need to check some properties of function declaration in this step:  */
	/*           	1. Check return type is same                            */
	/*      		2. Check number of parameter is same                       */
	/*         	    3. Check parameter sequence is same                       */
	/*       	    4. No void Parameters are declared                        */
	/*              5.Check for paraemter uniqness                            */
	/* ************************************************************************ */

	
	SymbolInfo*	currentSymbol = table->LookUp((yyvsp[-4].symbol_val)->getName());			
	//IF IT IS NOT IN THE TABLE 
	if(currentSymbol==NULL){
		
		// THIS VARIABLE IS USED TO CHECK IF IT IS A VOID
		bool isVoid = false;
		// NOW WE CHECK IF NO VOID PARAMETERS ARE DECLARED
		for(int i=0;i<temporaryParameterList.size();i++){
			if(temporaryParameterList[i].second=="VOID"){
				isVoid = true; 
				break;
			}
		}
		currentSymbol = new SymbolInfo((yyvsp[-4].symbol_val)->getName(),(yyvsp[-4].symbol_val)->getType());
		currentSymbol->typeOfID = "FUNCTION";
		currentSymbol->returnTypeOfFunction = (yyvsp[-5].symbol_val)->getType();
		currentSymbol->isFunction = true;
		currentSymbol->isFunctionDeclared = true;

		if(isVoid){
			printError("Parameter cannot be void" ,currentSymbol->getName());
			currentSymbol->isFunction = false;
		}
		for(int i=0;i<temporaryParameterList.size();i++){
			currentSymbol->functionParameterList.push_back(make_pair(temporaryParameterList[i].first, temporaryParameterList[i].second));
		}
		parameterUniquenessCheckforDeclaration();
		temporaryParameterList.clear();
		table->Insert(currentSymbol);
		logfile2<<currentSymbol->functionParameterList.size()<<endl;
	
	}
	else{
		// Checking return type
		if(currentSymbol->returnTypeOfFunction != (yyvsp[-5].symbol_val)->getType()){
			printError( "Return Type Mismatch of function declaration",currentSymbol->getName() );
		}

		// Checking parameter
		if(currentSymbol->functionParameterList.size()!=temporaryParameterList.size()){
			printError(" Total number of arguments mismatch in function",currentSymbol->getName() );
			temporaryParameterList.clear();
		}
		// Checking parameter sequence
		else{
			for(int i=0;i<temporaryParameterList.size();i++){
				if(temporaryParameterList[i].second != currentSymbol->functionParameterList[i].second){
					printError("Argument Type Mismatch with previous function declaration",currentSymbol->getName() );
					
				}
			}
			parameterUniquenessCheckforDeclaration();
			temporaryParameterList.clear();
		}

	}
	
	(yyval.symbol_val) =new SymbolInfo((yyvsp[-5].symbol_val)->getName()+space+(yyvsp[-4].symbol_val)->getName()+"("+(yyvsp[-2].symbol_val)->getName()+");","func_declaration");
	printMSG(" func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON",(yyval.symbol_val)->getName());

		}
#line 1839 "y.tab.c"
    break;

  case 12:
#line 334 "1805035.y"
                                                           {
				(yyval.symbol_val)=new SymbolInfo((yyvsp[-4].symbol_val)->getName()+space+(yyvsp[-3].symbol_val)->getName()+"();","func_declaration");
				printMSG(" func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON",(yyval.symbol_val)->getName());
				SymbolInfo* currentSymbol = table->LookUp((yyvsp[-3].symbol_val)->getName());
				if(currentSymbol != NULL){
						if(currentSymbol->returnTypeOfFunction != (yyvsp[-4].symbol_val)->getType()){
							printError("Return Type Mismatch of function declaration", (yyvsp[-3].symbol_val)->getName());
							
						}
						if(currentSymbol->functionParameterList.size()!=0){
							printError("Total number of arguments mismatch in function", (yyvsp[-3].symbol_val)->getName());
							temporaryParameterList.clear();
						} 
					}
					else{
						currentSymbol = new SymbolInfo();
						currentSymbol->typeOfID = "FUNCTION";
						currentSymbol->returnTypeOfFunction = (yyvsp[-4].symbol_val)->getType();
						currentSymbol->isFunction = true;
						currentSymbol->isFunctionDeclared = true;
						currentSymbol->setName((yyvsp[-3].symbol_val)->getName());
						currentSymbol->setType((yyvsp[-3].symbol_val)->getType());

						for(int i=0;i<temporaryParameterList.size();i++){
							currentSymbol->functionParameterList.push_back(make_pair(temporaryParameterList[i].first, temporaryParameterList[i].second));
						}
						temporaryParameterList.clear();
						table->Insert(currentSymbol);
						logfile2<<currentSymbol->functionParameterList.size()<<endl;
					}
					
			}
#line 1876 "y.tab.c"
    break;

  case 13:
#line 367 "1805035.y"
                                                                                         {
		yyerror;
		yyerrok;
		yyclearin;	
		temporaryParameterList=(yyvsp[-3].symbol_val)->functionParameterList;
		cout<<"************************************************e"<<(yyvsp[-5].symbol_val)->getName()<<endl;
		for(int i=0;i<(yyvsp[-3].symbol_val)->functionParameterList.size();i++)
			cout<<(yyvsp[-3].symbol_val)->functionParameterList[i].first<<(yyvsp[-3].symbol_val)->functionParameterList[i].second<<endl;
		cout<<"************************************************"<<endl;
		SymbolInfo *currentSymbol = table->LookUp((yyvsp[-5].symbol_val)->getName());
		SymbolInfo *newSymbol = new SymbolInfo();
		bool flag = true;
		// IF IT DOESNT EXIST THEN PUT IT IN THE TABLE
		if(currentSymbol==NULL){
			bool checkVoid = false;
			//CHECK FOR VOID PARAMETERS
			for(int i=0;i<(yyvsp[-3].symbol_val)->functionParameterList.size();i++){
				if((yyvsp[-3].symbol_val)->functionParameterList[i].second == "VOID"){
					checkVoid = true;
				}
			}

			// make a new object to insert into Symbol Table
			newSymbol->typeOfID = "FUNCTION";
			newSymbol->returnTypeOfFunction = (yyvsp[-6].symbol_val)->getType();
			newSymbol->isFunction = true;
			newSymbol->isFunctionDefined = true;
			newSymbol->setName((yyvsp[-5].symbol_val)->getName());
			newSymbol->setType((yyvsp[-5].symbol_val)->getType());

			if(checkVoid){
				printError("Parameter cannot be void" ,currentSymbol->getName());
				newSymbol->isFunction = false;
			}

			for(int i=0;i<(yyvsp[-3].symbol_val)->functionParameterList.size();i++){
				newSymbol->functionParameterList.push_back(make_pair(temporaryParameterList[i].first, temporaryParameterList[i].second));
				
			}
			

			/*if(return_type_solver!=$1->getType())
			{
				numberOfErrors++;
				fprintf(errors,"Error at Line %d : return type error \n\n",numberOfLines);
				return_type_solver="";
				newSymbol->isFunction=false;
			}*/
			table->Insert(newSymbol);
			//temporaryParameterList.clear();
		}
		// NOW IF IT ALREADY EXISTS IN GLOBAL SCOPE
		else{
			// FUNCTION ALREADY EXISTS ERROR!!!!
			if(currentSymbol->isFunctionDefined){
				printError("Multiple definition of function" ,currentSymbol->getName());
				temporaryParameterList.clear();
			}else if(currentSymbol->isFunctionDeclared){
				/* 
				**************************************************
				
						THREE CASES TO BE HANDLED:
							1. Return type check 
							2. Check number of parameters and
							3. Check for sequence of parameters 
				*****************************************************
				*/
				currentSymbol->isFunctionDefined = true;
				string actualReturnType = (yyvsp[-6].symbol_val)->getType();
				string declaredReturnType = currentSymbol->returnTypeOfFunction;
				int declaredParamSize = currentSymbol->functionParameterList.size();
				int definedParamSize = temporaryParameterList.size();
				
				// Case 1: Return type Check
				if(actualReturnType != declaredReturnType){
					printError("Return type mismatch" ,currentSymbol->getName());
					flag = false;
				}
				// Case 2: Check for size of paramter list
				else if(definedParamSize != declaredParamSize){
					printError("Total number of arguments mismatch in function" ,currentSymbol->getName());
					
					temporaryParameterList.clear();
					flag = false;
				}
				// Case 3: Check for sequence of parameter list 
				else{
					for(int i = 0;i<temporaryParameterList.size();i++){
						if(temporaryParameterList[i].second != currentSymbol->functionParameterList[i].second){
							printError("Argument Type Mismatch with function declaration" ,currentSymbol->getName());
							
							// flag=false;
							break;
						}
						
					}
					// temporaryParameterList.clear();
					
				}
				
			}
			else{
				printError("Multiple definition of function" ,currentSymbol->getName());
				
			}
		}
		

		(yyval.symbol_val)=new SymbolInfo((yyvsp[-6].symbol_val)->getName()+space+(yyvsp[-5].symbol_val)->getName()+space+"( "+(yyvsp[-3].symbol_val)->getName()+space+")"+(yyvsp[0].symbol_val)->getName(),"");
		printMSG("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement",(yyval.symbol_val)->getName());
		temporaryParameterList.clear();
		

 }
#line 1995 "y.tab.c"
    break;

  case 14:
#line 483 "1805035.y"
        {	
		temporaryParameterList=(yyvsp[-1].symbol_val)->functionParameterList;
		cout<<"************************************************p"<<(yyvsp[-3].symbol_val)->getName()<<endl;
		for(int i=0;i<(yyvsp[-1].symbol_val)->functionParameterList.size();i++)
			cout<<(yyvsp[-1].symbol_val)->functionParameterList[i].first<<endl;
		cout<<"************************************************"<<endl;
		SymbolInfo *currentSymbol = table->LookUp((yyvsp[-3].symbol_val)->getName());
		SymbolInfo *newSymbol = new SymbolInfo();
		bool flag = true;
		// IF IT DOESNT EXIST THEN PUT IT IN THE TABLE
		if(currentSymbol==NULL){
			bool checkVoid = false;
			//CHECK FOR VOID PARAMETERS
			for(int i=0;i<(yyvsp[-1].symbol_val)->functionParameterList.size();i++){
				if((yyvsp[-1].symbol_val)->functionParameterList[i].second == "VOID"){
					checkVoid = true;
				}
			}

			// make a new object to insert into Symbol Table
			newSymbol->typeOfID = "FUNCTION";
			newSymbol->returnTypeOfFunction = (yyvsp[-4].symbol_val)->getType();
			newSymbol->isFunction = true;
			newSymbol->isFunctionDefined = true;
			newSymbol->setName((yyvsp[-3].symbol_val)->getName());
			newSymbol->setType((yyvsp[-3].symbol_val)->getType());

			if(checkVoid){
				printError("Parameter cannot be void" ,currentSymbol->getName());
				newSymbol->isFunction = false;
			}

			for(int i=0;i<(yyvsp[-1].symbol_val)->functionParameterList.size();i++){
				newSymbol->functionParameterList.push_back(make_pair(temporaryParameterList[i].first, temporaryParameterList[i].second));
				
			}
			

			/*if(return_type_solver!=$1->getType())
			{
				numberOfErrors++;
				fprintf(errors,"Error at Line %d : return type error \n\n",numberOfLines);
				return_type_solver="";
				newSymbol->isFunction=false;
			}*/
			table->Insert(newSymbol);
			//temporaryParameterList.clear();
			currentSymbol=newSymbol;
		}
		// NOW IF IT ALREADY EXISTS IN GLOBAL SCOPE
		else{
			// FUNCTION ALREADY EXISTS ERROR!!!!
			if(currentSymbol->isFunctionDefined){
				printError("Multiple definition of function" ,currentSymbol->getName());
				temporaryParameterList.clear();
			}else if(currentSymbol->isFunctionDeclared){
				/* 
				**************************************************
				
						THREE CASES TO BE HANDLED:
							1. Return type check 
							2. Check number of parameters and
							3. Check for sequence of parameters 
				*****************************************************
				*/
				currentSymbol->isFunctionDefined = true;
				string actualReturnType = (yyvsp[-4].symbol_val)->getType();
				string declaredReturnType = currentSymbol->returnTypeOfFunction;
				int declaredParamSize = currentSymbol->functionParameterList.size();
				int definedParamSize = temporaryParameterList.size();
				
				// Case 1: Return type Check
				if(actualReturnType != declaredReturnType){
					printError("Return type mismatch" ,currentSymbol->getName());
					flag = false;
				}
				// Case 2: Check for size of paramter list
				else if(definedParamSize != declaredParamSize){
					printError("Total number of arguments mismatch in function" ,currentSymbol->getName());
					
					temporaryParameterList.clear();
					flag = false;
				}
				// Case 3: Check for sequence of parameter list 
				else{
					for(int i = 0;i<temporaryParameterList.size();i++){
						if(temporaryParameterList[i].second != currentSymbol->functionParameterList[i].second){
							printError("Argument Type Mismatch with function declaration" ,currentSymbol->getName());
							
							// flag=false;
							break;
						}
						
					}
					// temporaryParameterList.clear();
					
				}
				
			}
			else{
				printError("Multiple definition of function" ,currentSymbol->getName());
				
			}
		}

		/* ******************* */
	/*      ICG Code       */
	/* ******************* */
	if((yyvsp[-3].symbol_val)->getName() == "main")
		asmCode<< "MAIN PROC\n\tMOV AX, @DATA\n\tMOV DS, AX\n";
	else
		asmCode<< (yyvsp[-3].symbol_val)->getName()<<" PROC"<<endl;
	temporaryOffset=currentOffset;
	currentOffset=0;
	
	for(int i=0;i<temporaryParameterList.size();i++){
		/****************************ICG CODE ***************************************/
			currentSymbol->functionParameterOffset.push_back(currentOffset);
			asmCode<<"\tMOV AX, [BP-"<<i*2<<"]\nPUSH AX"<<endl;
			
			currentOffset+=2;
	}
	asmCode<<"\tMOV BP,SP"<<endl;
		
}
#line 2125 "y.tab.c"
    break;

  case 15:
#line 609 "1805035.y"
                   {
		(yyval.symbol_val)=new SymbolInfo((yyvsp[-6].symbol_val)->getName()+space+(yyvsp[-5].symbol_val)->getName()+space+"( "+(yyvsp[-3].symbol_val)->getName()+space+")"+(yyvsp[0].symbol_val)->getName(),"");
		printMSG("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement",(yyval.symbol_val)->getName());
		temporaryParameterList.clear();
		currentOffset=temporaryOffset;
		if((yyvsp[-5].symbol_val)->getName() == "main")
			asmCode<<"MOV AH, 4CH\nMOV AL, 01 ;your return code.\nINT 21H\nMAIN ENDP"<<endl;
		else
			asmCode<<"\n\tRET\n"<<(yyvsp[-5].symbol_val)->getName()<<" ENDP\n\n";
 }
#line 2140 "y.tab.c"
    break;

  case 16:
#line 620 "1805035.y"
                                                 {

			temporaryOffset=currentOffset;
			currentOffset=0;
			if((yyvsp[-2].symbol_val)->getName() == "main")
				asmCode<< "MAIN PROC\n\tMOV AX, @DATA\n\tMOV DS, AX\n";
			else
				asmCode<< (yyvsp[-2].symbol_val)->getName()<<" PROC"<<endl;
			asmCode<<"\tMOV BP,SP"<<endl;
		}
#line 2155 "y.tab.c"
    break;

  case 17:
#line 629 "1805035.y"
                                    {


				(yyval.symbol_val)=new SymbolInfo((yyvsp[-5].symbol_val)->getName()+space+(yyvsp[-4].symbol_val)->getName()+space+"()"+(yyvsp[0].symbol_val)->getName(),"func_definition");
				printMSG("func_definition : type_specifier ID LPAREN RPAREN compound_statement",(yyval.symbol_val)->getName());

				SymbolInfo *currentSymbol = table->LookUp((yyvsp[-4].symbol_val)->getName());

				if(currentSymbol==NULL){
					SymbolInfo* newSymbol = new SymbolInfo();
					newSymbol->typeOfID = "FUNCTION";
					newSymbol->returnTypeOfFunction = (yyvsp[-5].symbol_val)->getType();
					newSymbol->isFunction = true;
					newSymbol->isFunctionDefined = true;
					newSymbol->setName((yyvsp[-4].symbol_val)->getName());
					newSymbol->setType((yyvsp[-4].symbol_val)->getType());

					table->Insert(newSymbol);
				}else{
					if(currentSymbol->isFunctionDeclared){
						string actualReturnType = (yyvsp[-5].symbol_val)->getType();
						string funcReturnType = currentSymbol->returnTypeOfFunction;

						if(actualReturnType != funcReturnType){
							printError("Return type mismatch" ,currentSymbol->getName());
							currentSymbol->isFunction = false;
						}
					}else if(currentSymbol->isFunctionDefined){
						printError("Multiple defination of function" ,currentSymbol->getName());
						temporaryParameterList.clear();
						
					}
				}
				temporaryParameterList.clear();
				if((yyvsp[-4].symbol_val)->getName() == "main")
					asmCode<<"MOV AH, 4CH\nMOV AL, 01 ;your return code.\nINT 21H\nMAIN ENDP"<<endl;
				else
					asmCode<<"\n\tRET\n"<<(yyvsp[-4].symbol_val)->getName()<<" ENDP\n\n";
				currentOffset=temporaryOffset;
			}
#line 2200 "y.tab.c"
    break;

  case 18:
#line 672 "1805035.y"
                                                        {
	//print our msg
	(yyval.symbol_val)=new SymbolInfo((yyvsp[-3].symbol_val)->getName()+","+(yyvsp[-1].symbol_val)->getName()+space+(yyvsp[0].symbol_val)->getName(),"");
	printMSG("parameter_list : parameter_list COMMA type_specifier ID",(yyval.symbol_val)->getName());
	temporaryParameterList.push_back(make_pair((yyvsp[0].symbol_val)->getName(),(yyvsp[-1].symbol_val)->getType()));
	(yyval.symbol_val)->functionParameterList=(yyvsp[-3].symbol_val)->functionParameterList;
	(yyval.symbol_val)->functionParameterList.push_back(make_pair((yyvsp[0].symbol_val)->getName(),(yyvsp[-1].symbol_val)->getType()));
	
    }
#line 2214 "y.tab.c"
    break;

  case 19:
#line 681 "1805035.y"
                                                     {
			(yyval.symbol_val)=new SymbolInfo((yyvsp[-2].symbol_val)->getName()+","+(yyvsp[0].symbol_val)->getName(),"");
			printMSG("parameter_list : parameter_list COMMA type_specifier ",(yyval.symbol_val)->getName());
			temporaryParameterList.push_back(make_pair("",(yyvsp[0].symbol_val)->getType()));
			(yyval.symbol_val)->functionParameterList=(yyvsp[-2].symbol_val)->functionParameterList;
			(yyval.symbol_val)->functionParameterList.push_back(make_pair("",(yyvsp[0].symbol_val)->getType()));
		}
#line 2226 "y.tab.c"
    break;

  case 20:
#line 688 "1805035.y"
                                   {
			
			(yyval.symbol_val)=new SymbolInfo((yyvsp[-1].symbol_val)->getName()+space+(yyvsp[0].symbol_val)->getName(),(yyvsp[-1].symbol_val)->getType());
			logfile2<<(yyvsp[-1].symbol_val)->getName();
			printMSG("parameter_list : type_specifier ID ",(yyval.symbol_val)->getName());
			temporaryParameterList.push_back(make_pair((yyvsp[0].symbol_val)->getName(),(yyvsp[-1].symbol_val)->getType()));
			(yyval.symbol_val)->functionParameterList.push_back(make_pair((yyvsp[0].symbol_val)->getName(),(yyvsp[-1].symbol_val)->getType()));
		}
#line 2239 "y.tab.c"
    break;

  case 21:
#line 696 "1805035.y"
                                  {
			
			(yyval.symbol_val)=new SymbolInfo((yyvsp[0].symbol_val)->getName(),(yyvsp[0].symbol_val)->getType());
			printMSG("parameter_list : type_specifier ",(yyval.symbol_val)->getName());
			temporaryParameterList.push_back(make_pair("",(yyvsp[0].symbol_val)->getType()));
			(yyval.symbol_val)->functionParameterList.push_back(make_pair("",(yyvsp[0].symbol_val)->getType()));
			
		}
#line 2252 "y.tab.c"
    break;

  case 22:
#line 707 "1805035.y"
                          {
	table->EnterScope();
	checkParameterUniquenessForFunDefinition();
	}
#line 2261 "y.tab.c"
    break;

  case 23:
#line 712 "1805035.y"
        {
	(yyval.symbol_val)=new SymbolInfo("{\n"+(yyvsp[-1].symbol_val)->getName()+"\n}","compound_statement");
	printMSG("compound_statement :LCURL statements RCURL",(yyval.symbol_val)->getName());
	table->printAllLex(logfile2);
	table->ExitScope();
	
}
#line 2273 "y.tab.c"
    break;

  case 24:
#line 719 "1805035.y"
                            {
				table->EnterScope();
				
				checkParameterUniquenessForFunDefinition();
			}
#line 2283 "y.tab.c"
    break;

  case 25:
#line 723 "1805035.y"
                              {
				(yyval.symbol_val)=new SymbolInfo("{\n\n}","compound_statement");
				printMSG("compound_statement :LCURL  RCURL");
				table->printAllLex(logfile2);
				table->ExitScope();
			}
#line 2294 "y.tab.c"
    break;

  case 26:
#line 733 "1805035.y"
                                                            {

				(yyval.symbol_val)=new SymbolInfo((yyvsp[-2].symbol_val)->getName()+space+(yyvsp[-1].symbol_val)->getName()+";",(yyvsp[-2].symbol_val)->getName());
				if((yyvsp[-2].symbol_val)->getName()=="void")
					printError("Variable type cannot be void",(yyval.symbol_val)->getName());
				for(int i=0;i<declared_varList.size();i++){
					 SymbolInfo*cur= table->LookUp(declared_varList[i]->getName());
					if(cur->typeOfVar=="")
						cur->typeOfVar=(yyvsp[-2].symbol_val)->getType();	
					
				}
				declared_varList.clear();
				printMSG("var_declaration : type_specifier declaration_list SEMICOLON",(yyval.symbol_val)->getName());
			}
#line 2313 "y.tab.c"
    break;

  case 27:
#line 749 "1805035.y"
                      {
						(yyval.symbol_val)= new SymbolInfo("int","CONST_INT");
						printMSG("type_specifier : INT","int");
						}
#line 2322 "y.tab.c"
    break;

  case 28:
#line 753 "1805035.y"
                        {
			(yyval.symbol_val)= new SymbolInfo("float","CONST_FLOAT");
			printMSG("type_specifier :FLOAT ","float");
			}
#line 2331 "y.tab.c"
    break;

  case 29:
#line 757 "1805035.y"
                       {
			(yyval.symbol_val)= new SymbolInfo("void","VOID");
			printMSG("type_specifier : VOID ","void");
		}
#line 2340 "y.tab.c"
    break;

  case 30:
#line 763 "1805035.y"
                                             {
				(yyval.symbol_val)=new SymbolInfo((yyvsp[-2].symbol_val)->getName()+","+(yyvsp[0].symbol_val)->getName(),"DeclarationList");
				/****************************ICG CODE*************************************/
								if(table->getCurrentScopeID()=="1"){
									asmData<<(yyvsp[0].symbol_val)->getName()<<"  DW ?"<<endl;
								}
								else {
									(yyvsp[0].symbol_val)->offset=currentOffset;
									currentOffset+=2;
									asmCode<<"\tPUSH 0\n";
								}
			/****************************************************************************/
				if(!table->Insert((yyvsp[0].symbol_val))){
					printError("Multiple declaration of"+table->LookUp((yyvsp[0].symbol_val)->getName())->typeOfVar,(yyvsp[0].symbol_val)->getName());
				}
				printMSG("declaration_list :declaration_list COMMA ID",(yyval.symbol_val)->getName());
				declared_varList.push_back((yyvsp[0].symbol_val));
			

			}
#line 2365 "y.tab.c"
    break;

  case 31:
#line 782 "1805035.y"
                                                          {
				yyerror;
				yyerrok;
				yyclearin;
				(yyval.symbol_val)=new SymbolInfo((yyvsp[-3].symbol_val)->getName()+","+(yyvsp[0].symbol_val)->getName(),"DeclarationList");
				if(!table->Insert((yyvsp[0].symbol_val))){
					printError("Multiple declaration of"+table->LookUp((yyvsp[-1].symbol_val)->getName())->typeOfVar,(yyvsp[-1].symbol_val)->getName());
				}
				printMSG("declaration_list :declaration_list COMMA ID",(yyval.symbol_val)->getName());
				declared_varList.push_back((yyvsp[0].symbol_val));
			}
#line 2381 "y.tab.c"
    break;

  case 32:
#line 793 "1805035.y"
                                                                     {
			(yyval.symbol_val)=new SymbolInfo((yyvsp[-5].symbol_val)->getName()+","+(yyvsp[-3].symbol_val)->getName()+"["+(yyvsp[-1].symbol_val)->getName()+"]","DeclarationList");
				/****************************ICG CODE*************************************/
							if(table->getCurrentScopeID()=="1"){
								asmData<<(yyvsp[-3].symbol_val)->getName()<<"  DW "<<(yyvsp[-1].symbol_val)->getName()<<"  dup( ?)"<<endl;
							}
							else {
								int len=stoi((yyvsp[-1].symbol_val)->getName().c_str());
								(yyvsp[-3].symbol_val)->offset=currentOffset;
								currentOffset+=2*len;
								for(int i=0;i<len;i++)
									asmCode<<"\tPUSH 0\n";
							}
			/****************************************************************************/
				(yyvsp[-3].symbol_val)->setType("array");
				(yyvsp[-3].symbol_val)->typeOfID="ARRAY";
				(yyvsp[-3].symbol_val)->setLen(atoi((yyvsp[-1].symbol_val)->getName().c_str()));
				if(!table->Insert((yyvsp[-3].symbol_val))){
					printError("Multiple declaration of",(yyvsp[-3].symbol_val)->getName());
				}
				printMSG("declaration_list :declaration_list COMMA ID LTHIRD CONST_INT RTHIRD",(yyval.symbol_val)->getName());
				declared_varList.push_back((yyvsp[-3].symbol_val));
		  }
#line 2409 "y.tab.c"
    break;

  case 33:
#line 816 "1805035.y"
                       {(yyval.symbol_val)=new SymbolInfo((yyvsp[0].symbol_val)->getName(),"ID");
		  	/****************************ICG CODE*************************************/
							if(table->getCurrentScopeID()=="1"){
								asmData<<(yyvsp[0].symbol_val)->getName()<<"  DW ?"<<endl;
							}
							else {
								(yyvsp[0].symbol_val)->offset=currentOffset;
								currentOffset+=2;
								asmCode<<"\tPUSH 0\n";
							}
			/****************************************************************************/
				if(!table->Insert((yyvsp[0].symbol_val))){
					printError("Multiple declaration of",(yyvsp[0].symbol_val)->getName());
				}
				printMSG("declaration_list :ID",(yyval.symbol_val)->getName());
				declared_varList.push_back((yyvsp[0].symbol_val));
				}
#line 2431 "y.tab.c"
    break;

  case 34:
#line 833 "1805035.y"
                                               {(yyval.symbol_val)=new SymbolInfo((yyvsp[-3].symbol_val)->getName()+"["+(yyvsp[-1].symbol_val)->getName()+"]","array");
			/****************************ICG CODE*************************************/
							if(table->getCurrentScopeID()=="1"){
								asmData<<(yyvsp[-3].symbol_val)->getName()<<"  DW "<<(yyvsp[-1].symbol_val)->getName()<<"  dup( ?)"<<endl;
							}
							else {
								int len=stoi((yyvsp[-1].symbol_val)->getName().c_str());
								(yyvsp[-3].symbol_val)->offset=currentOffset;
								currentOffset+=2*len;
								for(int i=0;i<len;i++)
									asmCode<<"\tPUSH 0\n";
							}
			/****************************************************************************/
				(yyvsp[-3].symbol_val)->setLen(atoi((yyvsp[-1].symbol_val)->getName().c_str()));
				(yyvsp[-3].symbol_val)->setType("array");
				if(!table->Insert((yyvsp[-3].symbol_val))){
					printError("Multiple declaration of",(yyvsp[-3].symbol_val)->getName());
				}
				printMSG("declaration_list :ID LTHIRD CONST_INT RTHIRD",(yyval.symbol_val)->getName());
				declared_varList.push_back((yyvsp[-3].symbol_val));
				}
#line 2457 "y.tab.c"
    break;

  case 35:
#line 857 "1805035.y"
                {(yyval.symbol_val) = (yyvsp[0].symbol_val);
	 	logfile2<<"Line "<<line_count<<": statements : statement"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;
	 }
#line 2465 "y.tab.c"
    break;

  case 36:
#line 859 "1805035.y"
                                {
	 	(yyval.symbol_val) = new SymbolInfo((yyvsp[-1].symbol_val)->getName()+"\n"+(yyvsp[0].symbol_val)->getName(),"statement");
	 	logfile2<<"Line "<<line_count<<": statements : statements statement"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;
	 }
#line 2474 "y.tab.c"
    break;

  case 37:
#line 866 "1805035.y"
                {
	 	
	 	(yyval.symbol_val) = (yyvsp[0].symbol_val);
	 	logfile2<<"Line "<<line_count<<": statement : var_declaration"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;
	 }
#line 2484 "y.tab.c"
    break;

  case 38:
#line 872 "1805035.y"
          {
	 	
	 	(yyval.symbol_val) = (yyvsp[0].symbol_val);
	 	logfile2<<"Line "<<line_count<<": statement : expression_statement"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;
	 }
#line 2494 "y.tab.c"
    break;

  case 39:
#line 877 "1805035.y"
                              {
	 	
	 	(yyval.symbol_val) = (yyvsp[0].symbol_val);
	 	logfile2<<"Line "<<line_count<<": statement : compound_statement"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;
	 }
#line 2504 "y.tab.c"
    break;

  case 40:
#line 882 "1805035.y"
                                           {
		forLoopStart=string(newLabel()),ENDLOOP=string(newLabel()),LoopLabel=string(newLabel());
		IncLabel=string(newLabel());
		asmCode<<forLoopStart<<":\n";
	  }
#line 2514 "y.tab.c"
    break;

  case 41:
#line 886 "1805035.y"
                                {
		asmCode<<"\tCMP AX,0\n\tJE "<<ENDLOOP<<"\n\tJMP "<<LoopLabel<<endl<<IncLabel<<":"<<endl;
	  }
#line 2522 "y.tab.c"
    break;

  case 42:
#line 888 "1805035.y"
                             {
		asmCode<<"\tJMP "<<forLoopStart<<endl<<LoopLabel<<":\n";
	  }
#line 2530 "y.tab.c"
    break;

  case 43:
#line 890 "1805035.y"
                     {
		(yyval.symbol_val) = new SymbolInfo("for("+(yyvsp[-7].symbol_val)->getName()+(yyvsp[-5].symbol_val)->getName()+(yyvsp[-3].symbol_val)->getName()+")"+(yyvsp[0].symbol_val)->getName(),"for");	 	
	 	logfile2<<"Line "<<line_count<<": statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;
		asmCode<<"\tJMP "<<IncLabel<<endl<<ENDLOOP<<":"<<endl;
		asmCode<<";OK SAKIN"<<endl;
		
	 //MARKER1
	  }
#line 2543 "y.tab.c"
    break;

  case 44:
#line 898 "1805035.y"
                                                                         {
	 	(yyval.symbol_val) = new SymbolInfo((yyvsp[-2].symbol_val)->getName()+")"+(yyvsp[0].symbol_val)->getName(),"if");	 		 	
	 	logfile2<<"Line "<<line_count<<": statement : IF LPAREN expression RPAREN statement"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;
	 	asmCode<<"\t"<<conditionEnd<<":"<<endl;

	 }
#line 2554 "y.tab.c"
    break;

  case 45:
#line 904 "1805035.y"
                                                       {
		elseLabel=conditionEnd;
		conditionEnd=string(newLabel());
		asmCode<<";jmp phase"<<endl;
		asmCode<<"\tJMP "<<conditionEnd<<endl;
	  	conditionStack.push(conditionEnd);
		asmCode<<"\t"<<elseLabel<<":"<<endl;
	  }
#line 2567 "y.tab.c"
    break;

  case 46:
#line 911 "1805035.y"
                      {
		asmCode<<";condition statements3"<<endl;
	 	(yyval.symbol_val) = new SymbolInfo((yyvsp[-5].symbol_val)->getName()+")"+(yyvsp[-3].symbol_val)->getName()+"else"+(yyvsp[0].symbol_val)->getName(),"if");
	 	logfile2<<"Line "<<line_count<<": statement : IF LPAREN expression RPAREN statement ELSE statement"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;
	 	conditionEnd=conditionStack.top();
		conditionStack.pop();
		asmCode<<"\t"<<conditionEnd<<":"<<endl;

	 }
#line 2581 "y.tab.c"
    break;

  case 47:
#line 920 "1805035.y"
                 {
		whileLabel=string(newLabel()),whileEnd=string(newLabel());
		asmCode<<"\t"<<whileLabel<<":"<<endl;
	  }
#line 2590 "y.tab.c"
    break;

  case 48:
#line 923 "1805035.y"
                             {
		asmCode<<"\tCMP AX,0\n\tJE "<<whileEnd<<endl;
	  }
#line 2598 "y.tab.c"
    break;

  case 49:
#line 925 "1805035.y"
                            {
	 	(yyval.symbol_val) = new SymbolInfo("while("+(yyvsp[-3].symbol_val)->getName()+")"+(yyvsp[0].symbol_val)->getName(),"while");
	 	logfile2<<"Line "<<line_count<<": statement : WHILE LPAREN expression RPAREN statement"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;
	 	asmCode<<"\tJMP "<<whileLabel<<"\n\t"<<whileEnd<<":"<<endl;
	 }
#line 2608 "y.tab.c"
    break;

  case 50:
#line 930 "1805035.y"
                                              {
	 	(yyval.symbol_val) = new SymbolInfo("printf("+(yyvsp[-2].symbol_val)->getName()+");","print");
	 
	 	logfile2<<"Line "<<line_count<<": statement : PRINTLN LPAREN ID RPAREN SEMICOLON"<<endl<<endl;
	 	if(table->LookUp((yyvsp[-2].symbol_val)->getName()) == nullptr){
	 		errorfile<<"Error at line "<<line_count<<" : Undeclared variable "<< ((yyvsp[-2].symbol_val)->getName())<<endl<<endl;error_count++;	
  			logfile2<<"Error at line "<<line_count<<" : Undeclared variable "<< ((yyvsp[-2].symbol_val)->getName())<<endl<<endl;  
	 	}
	 	logfile2<<(yyval.symbol_val)->getName()<<endl<<endl;

		/******************************ICG CODE********************************************/
		if(table->LookUp((yyvsp[-2].symbol_val)->getName())->getScopeTableID()=="1")
			asmCode<<"\tMOV AX,"<<(yyvsp[-2].symbol_val)->getName()<<endl;
		else
			asmCode<<"\tMOV AX,[BP-"<<table->LookUp((yyvsp[-2].symbol_val)->getName())->offset<<"]"<<endl;
		asmCode<<"\tCALL PRINT_FUNC"<<endl;
		/*********************************************************************************/
	 }
#line 2631 "y.tab.c"
    break;

  case 51:
#line 948 "1805035.y"
                                       {
	 	(yyval.symbol_val) = new SymbolInfo((yyvsp[-2].symbol_val)->getName()+space+(yyvsp[-1].symbol_val)->getName()+" ;","return");	 	

	 	logfile2<<"Line "<<line_count<<": statement : RETURN expression SEMICOLON"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;
	 	/******************************ICG CODE*******************************/
		asmCode<<"\tMOV FUNC_RETURN_VALUE,AX"<<endl;
	 }
#line 2643 "y.tab.c"
    break;

  case 52:
#line 954 "1805035.y"
                {
		yyerror;
		yyerrok;
		yyclearin;
	 }
#line 2653 "y.tab.c"
    break;

  case 53:
#line 960 "1805035.y"
                                            {
	//MARKER2
	(yyval.symbol_val) = new SymbolInfo("if("+(yyvsp[0].symbol_val)->getName(),"");
	 conditionEnd=string(newLabel());
	 asmCode<<"\t;if else  "<<endl;
		asmCode<<"\tCMP AX,0\n\tJE "<<conditionEnd<<endl;
	  }
#line 2665 "y.tab.c"
    break;

  case 54:
#line 967 "1805035.y"
                                        {(yyval.symbol_val) = new SymbolInfo(";","expression");}
#line 2671 "y.tab.c"
    break;

  case 55:
#line 968 "1805035.y"
                                               {
	 	(yyval.symbol_val) = new SymbolInfo((yyvsp[-1].symbol_val)->getName()+";","expression");
	 	
	 	logfile2<<"Line "<<line_count<<": expression_statement : expression SEMICOLON"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;
	 }
#line 2681 "y.tab.c"
    break;

  case 56:
#line 975 "1805035.y"
              {
	 	(yyval.symbol_val) = new SymbolInfo((yyvsp[0].symbol_val)->getName(),"variable");	 	
	 	
	 	SymbolInfo* currentSymbol = table->LookUp((yyvsp[0].symbol_val)->getName());
		
	 	if(currentSymbol == NULL){
  			errorfile<<"Error at line "<<line_count<<" : Undeclared variable "<< ((yyvsp[0].symbol_val)->getName())<<endl<<endl;error_count++;	
  			logfile2<<"Error at line "<<line_count<<" : Undeclared variable "<< ((yyvsp[0].symbol_val)->getName())<<endl<<endl;  				  		
  		}  		
  		else{
  			(yyval.symbol_val)->setType(currentSymbol->typeOfVar); 
						
  			
  			string str((yyvsp[0].symbol_val)->getName());
  			if(currentSymbol->getType() == "array" ){
  				 
  				errorfile<<"Error at line "<<line_count<<" : Type Mismatch, "<<(yyvsp[0].symbol_val)->getName()<<" is an array"<<endl<<endl; error_count++;
				logfile2<<"Error at line "<<line_count<<" : Type Mismatch, "<<(yyvsp[0].symbol_val)->getName()<<" is an array"<<endl<<endl;
  			}
	  		/*******************************ICG CODE****************************************************/
				if(currentSymbol->getScopeTableID()=="1"){
					asmCode<<"\tLEA SI,"<<currentSymbol->getName()<<endl;
					(yyval.symbol_val)->isGlobal=true;
				}
				else{
					asmCode<<"\tMOV SI,-"<<currentSymbol->offset<<endl;
				}
			/********************************************************************************/	 	
  		}
		logfile2<<"Line "<<line_count<<": variable : ID"<<endl<<endl;	  		
	 	logfile2<<(yyval.symbol_val)->getName()<<endl<<endl;

	 }
#line 2719 "y.tab.c"
    break;

  case 57:
#line 1008 "1805035.y"
                                       {
	 	(yyval.symbol_val) = new SymbolInfo((yyvsp[-3].symbol_val)->getName()+"["+(yyvsp[-1].symbol_val)->getName()+"]","var");
	 	SymbolInfo* currentSymbol = table->LookUp((yyvsp[-3].symbol_val)->getName());
	 	if(currentSymbol == NULL){
  			errorfile<<"Error at line "<<line_count<<" : Undeclared variable "<< ((yyvsp[-3].symbol_val)->getName())<<endl<<endl;error_count++;	
  			logfile2<<"Error at line "<<line_count<<" : Undeclared variable "<< ((yyvsp[-3].symbol_val)->getName())<<endl<<endl;
  			 		
  		}
	 	else{	 		
			(yyval.symbol_val)->setType(currentSymbol->typeOfVar); 
			if((yyval.symbol_val)->getType()=="")
				printError("************************",""); 	 
		 	printMSG("variable :ID LTHIRD expression RTHIRD",(yyval.symbol_val)->getName());
		 	if(currentSymbol->getLen()<2){
		 		errorfile<<"Error at line "<<line_count<<" : "<<(yyvsp[-3].symbol_val)->getName()<<" not an array"<<endl<<endl;error_count++;
		 		logfile2<<"Error at line "<<line_count<<" : "<<(yyvsp[-3].symbol_val)->getName()<<" not an array"<<endl<<endl;
		 	}
		 	else if((yyvsp[-1].symbol_val)->getType() != "CONST_INT"){
		 		errorfile<<"Error at line "<<line_count<<" : Expression inside third brackets not an integer"<<endl<<endl;error_count++;
		 		logfile2<<"Error at line "<<line_count<<" :Expression inside third brackets not an integer"<<endl<<endl;
		 	}
			// else if(currentSymbol->getLen()>=atoi($3->getName().c_str())){
			// 	errorfile<<"Error at line "<<line_count<<" : Out of Bound Index"<<endl<<endl;error_count++;
		 	// 	logfile2<<"Error at line "<<line_count<<" :Out of Bound Index"<<endl<<endl;
			// }		 	
	 		/*******************************ICG CODE****************************************************/
				if(currentSymbol->getScopeTableID()=="1"){
					asmCode<<"\tLEA SI,"<<currentSymbol->getName()<<endl;
					asmCode<<"\tADD SI,"<<atoi((yyvsp[-1].symbol_val)->getName().c_str())*2<<endl;
					(yyval.symbol_val)->isGlobal=true;
				}
					
				else{
					asmCode<<"\tMOV SI,-"<<currentSymbol->offset+2*atoi((yyvsp[-1].symbol_val)->getName().c_str())<<endl;
					asmCode<<";"<<currentSymbol->offset<<endl;
				}
			/********************************************************************************/	 	
		}
	 	
	 }
#line 2764 "y.tab.c"
    break;

  case 58:
#line 1050 "1805035.y"
                                {
	 	
	 	(yyval.symbol_val) = (yyvsp[0].symbol_val);
	 	logfile2<<"Line "<<line_count<<": expression : logic_expression	"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;
	 }
#line 2774 "y.tab.c"
    break;

  case 59:
#line 1055 "1805035.y"
                     {
		asmCode<<"\tMOV DI,SI"<<endl;
	   }
#line 2782 "y.tab.c"
    break;

  case 60:
#line 1057 "1805035.y"
                                       {
		//TODO
	(yyval.symbol_val) = new SymbolInfo((yyvsp[-3].symbol_val)->getName()+(yyvsp[-1].symbol_val)->getName()+(yyvsp[0].symbol_val)->getName(),(yyvsp[-3].symbol_val)->getType());

	string v_type = (yyvsp[-3].symbol_val)->getType();
	string log_exp_type = (yyvsp[0].symbol_val)->getType();
	
	if((yyvsp[0].symbol_val)->getType()=="VOID"){
			printError("Type Mismatch: cannot assign to VOID type",(yyval.symbol_val)->getName());
	} else {
		
		// if(v_type!=log_exp_type)
		// {

		// 	printError("Type Mismatch-1"+v_type+log_exp_type,$$->getName());
		// }
		if((v_type=="CONST_INT")&&(log_exp_type=="CONST_FLOAT"))
		{
			printError("Type Mismatch-3",(yyval.symbol_val)->getName());
		}
	}

	printMSG("expression : variable ASSIGNOP logic_expression",(yyval.symbol_val)->getName());

	/*******************************ICG CODE****************************************************/
				asmCode<<"\t;******************************"<<endl;
				if((yyvsp[-3].symbol_val)->isGlobal){
					asmCode<<"MOV [DI],AX"<<endl;
				}
				else{
					
					asmCode<<"\tMOV [BP+DI], AX"<<endl;
					}
			

	/********************************************************************************/	 	
	 }
#line 2824 "y.tab.c"
    break;

  case 61:
#line 1096 "1805035.y"
                                        {
	 
	 	(yyval.symbol_val) = (yyvsp[0].symbol_val);
	 	logfile2<<"Line "<<line_count<<": logic_expression : rel_expression"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;
	 }
#line 2834 "y.tab.c"
    break;

  case 62:
#line 1101 "1805035.y"
                                  {
			asmCode<<"\tPUSH AX"<<endl;
		 }
#line 2842 "y.tab.c"
    break;

  case 63:
#line 1103 "1805035.y"
                                          {
	 	(yyval.symbol_val) = new SymbolInfo((yyvsp[-3].symbol_val)->getName()+(yyvsp[-1].symbol_val)->getName()+(yyvsp[0].symbol_val)->getName(),"expression");
	 	// logfile2<<"Line "<<line_count<<": logic_expression : rel_expression LOGICOP rel_expression"<<endl<<endl;
	 	if(((yyvsp[-3].symbol_val)->getType() == "CONST_INT" || (yyvsp[-3].symbol_val)->getType() == "CONST_FLOAT") && ((yyvsp[-3].symbol_val)->getType() == "CONST_INT" || (yyvsp[-3].symbol_val)->getType() == "CONST_FLOAT")) {(yyval.symbol_val)->setType("CONST_INT");}
	 	if((yyvsp[-1].symbol_val)->getType() == "VOID" || (yyvsp[-3].symbol_val)->getType() == "VOID"){
			errorfile<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl; error_count++;
			logfile2<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl;
			(yyval.symbol_val)->setType((yyvsp[-3].symbol_val)->getType());
		}
		else if((yyvsp[-3].symbol_val)->returnTypeOfFunction == "VOID" || (yyvsp[0].symbol_val)->returnTypeOfFunction == "VOID"){
			errorfile<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl; error_count++;
			logfile2<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl;
			(yyval.symbol_val)->setType((yyvsp[-1].symbol_val)->getType());
		} 
	 	logfile2<<"Line "<<line_count<<": logic_expression : rel_expression LOGICOP rel_expression"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;
	 	/**********************ICG CODE***********************************************/
		asmCode<<"\tPOP BX"<<endl;
		string sign=(yyvsp[-1].symbol_val)->getName();
		string label1=string(newLabel()),label2=string(newLabel());
		if(sign== "&&"){
		asmCode<< "\tCMP BX, 0 \n\tJE "<<label1<<"\n\tCMP AX, 0\n\tJE "<<label1<<"\n MOV AX, 1\n\t JMP "<<label2<<"\n"<<label1<<":\n\tMOV AX,0\n"<<label2<<":"<<endl;
		}
		else{
		asmCode<< "\tCMP BX, 1 \n\tJE "<<label1<<"\n\tCMP AX, 1\n\tJE "<<label1<<"\n MOV AX, 0\n\t JMP "<<label2<<"\n"<<label1<<":\n\tMOV AX,1\n"<<label2<<":"<<endl;
		}

		/******************************************************************************/
	 
	 }
#line 2876 "y.tab.c"
    break;

  case 64:
#line 1134 "1805035.y"
                                    {
	 	
	 	(yyval.symbol_val) = (yyvsp[0].symbol_val);
	 	logfile2<<"Line "<<line_count<<": rel_expression : simple_expression"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;
	 }
#line 2886 "y.tab.c"
    break;

  case 65:
#line 1139 "1805035.y"
                                   {
			asmCode<<"\tMOV DX,AX"<<endl;

		}
#line 2895 "y.tab.c"
    break;

  case 66:
#line 1142 "1805035.y"
                                                {
	 	(yyval.symbol_val) = new SymbolInfo((yyvsp[-3].symbol_val)->getName()+(yyvsp[-1].symbol_val)->getName()+(yyvsp[0].symbol_val)->getName(),"expression");
	 	
	 	if(((yyvsp[-3].symbol_val)->getType() == "CONST_INT" || (yyvsp[-3].symbol_val)->getType() == "CONST_FLOAT") && ((yyvsp[-3].symbol_val)->getType() == "CONST_INT" || (yyvsp[-3].symbol_val)->getType() == "CONST_FLOAT")) {(yyval.symbol_val)->setType("CONST_INT");(yyval.symbol_val)->setType("CONST_INT");}
	 	// logfile2<<"Line "<<line_count<<": rel_expression : simple_expression RELOP simple_expression"<<endl<<endl;
	 	if((yyvsp[-3].symbol_val)->returnTypeOfFunction == "VOID" || (yyvsp[0].symbol_val)->returnTypeOfFunction == "VOID"){
			errorfile<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl; error_count++;
			logfile2<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl;
			(yyval.symbol_val)->setType((yyvsp[-3].symbol_val)->getType());
		}else if((yyvsp[-3].symbol_val)->getType() == "VOID" || (yyvsp[0].symbol_val)->getType() == "VOID"){
			errorfile<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl; error_count++;
			logfile2<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl;
			(yyval.symbol_val)->setType((yyvsp[-3].symbol_val)->getType());
		}
	/******************************ICG CODE***************************************************/
	//todo
	//marker
	asmCode<<"\tCMP DX,AX"<<endl;
	string sign=(yyvsp[-1].symbol_val)->getName();
	string label1=string(newLabel()),label2=string(newLabel());
	if(sign=="<"){
		asmCode<<"\tJL "<<label1<<endl<<"\tMOV AX,0"<<endl<<"\tJMP "<<label2<<endl;
	}
	else if(sign=="<="){
		asmCode<<"\tJLE "<<label1<<endl<<"\tMOV AX,0"<<endl<<"\tJMP "<<label2<<endl;
	}
	else if(sign==">"){
		asmCode<<"\tJG "<<label1<<endl<<"\tMOV AX,0"<<endl<<"\tJMP "<<label2<<endl;
	}
	else if ( sign==">="){
		asmCode<<"\tJGE "<<label1<<endl<<"\tMOV AX,0"<<endl<<"\tJMP "<<label2<<endl;
	}
	else if(sign=="=="){	asmCode<<"\tJE "<<label1<<endl<<"\tMOV AX,0"<<endl<<"\tJMP "<<label2<<endl;
	}
	else if(sign=="!="){
		asmCode<<"\tJNE "<<label1<<endl<<"\tMOV AX,0"<<endl<<"\tJMP "<<label2<<endl;
	}
	asmCode<<label1<<":"<<"\tMOV AX,1"<<endl<<label2<<":"<<endl;
	/****************************************************************************************/
	 	printMSG("rel_expression :simple_expression RELOP simple_expression",(yyval.symbol_val)->getName());
	 }
#line 2941 "y.tab.c"
    break;

  case 67:
#line 1185 "1805035.y"
                         {
	 	(yyval.symbol_val) = (yyvsp[0].symbol_val);
	 	logfile2<<"Line "<<line_count<<": simple_expression : term"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;

		
	
	 }
#line 2953 "y.tab.c"
    break;

  case 68:
#line 1192 "1805035.y"
                                     {
		/***************************************ICG CODE **********************************/
		asmCode<<"\tMOV CX,AX"<<endl;
		/*********************************************************************************/
		  }
#line 2963 "y.tab.c"
    break;

  case 69:
#line 1196 "1805035.y"
                               {
	 	(yyval.symbol_val) = new SymbolInfo((yyvsp[-3].symbol_val)->getName()+(yyvsp[-1].symbol_val)->getName()+(yyvsp[0].symbol_val)->getName(),"expression");
	 	logfile2<<"Line "<<line_count<<": simple_expression : simple_expression ADDOP term"<<endl<<endl;
	 	if((yyvsp[0].symbol_val)->returnTypeOfFunction == "VOID" || (yyvsp[-3].symbol_val)->returnTypeOfFunction == "VOID"){
			errorfile<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl; error_count++;
			logfile2<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl;			
		}
		else if((yyvsp[0].symbol_val)->getType() == "VOID" || (yyvsp[-3].symbol_val)->getType() == "VOID"){
			errorfile<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl; error_count++;
			logfile2<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl;			
		}	 	
	 	if((yyvsp[-3].symbol_val)->getType() == "CONST_FLOAT" || (yyvsp[0].symbol_val)->getType() == "CONST_FLOAT"){(yyval.symbol_val)->setType("CONST_FLOAT");}
	 	else {(yyval.symbol_val)->setType("CONST_INT");}
	 	logfile2<<(yyval.symbol_val)->getName()<<endl<<endl;
		/***************************************ICG CODE **********************************/
		if((yyvsp[-1].symbol_val)->getName()=="+")
				asmCode<<"\tADD AX,CX"<<endl;
		else
			asmCode<<"\tSUB AX,CX"<<endl;
		/*********************************************************************************/
	 }
#line 2989 "y.tab.c"
    break;

  case 70:
#line 1219 "1805035.y"
                      {
			(yyval.symbol_val) = (yyvsp[0].symbol_val);
			logfile2<<"Line "<<line_count<<": term : unary_expression"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;
			/*****************************ICG CODE *******************************************/
				
				
				asmCode<<"\tPOP AX "<<endl;
			/********************************************************************************/
		}
#line 3003 "y.tab.c"
    break;

  case 71:
#line 1228 "1805035.y"
                                   {
			(yyval.symbol_val) = new SymbolInfo((yyvsp[-2].symbol_val)->getName()+(yyvsp[-1].symbol_val)->getName()+(yyvsp[0].symbol_val)->getName(),"expression");
					
			logfile2<<"Line "<<line_count<<": term : term MULOP unary_expression"<<endl<<endl;
			if((yyvsp[-1].symbol_val)->getName() == "%"){
				if((yyvsp[-2].symbol_val)->getType() != "CONST_INT" || (yyvsp[0].symbol_val)->getType() != "CONST_INT"){
					errorfile<<"Error at line "<<line_count<<" : Non-Integer operand on modulus operator "<<endl<<endl; error_count++;
					logfile2<<"Error at line "<<line_count<<" : Non-Integer operand on modulus operator "<<endl<<endl;
					(yyval.symbol_val)->setType("undefined");
				}
				else if((yyvsp[0].symbol_val)->getName() == "0"){
					errorfile<<"Error at line "<<line_count<<" : Modulus by Zero "<<endl<<endl; error_count++;
					logfile2<<"Error at line "<<line_count<<" : Modulus by Zero"<<endl<<endl;
					(yyval.symbol_val)->setType("undefined");
				}
				else {(yyval.symbol_val)->setType("CONST_INT");}
			}
			else if((yyvsp[0].symbol_val)->getType() == "VOID" || (yyvsp[-2].symbol_val)->getType() == "VOID"){
				errorfile<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl; error_count++;
				logfile2<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl;
				(yyval.symbol_val)->setType((yyvsp[-2].symbol_val)->getType());
			}		
			else if((yyvsp[-2].symbol_val)->getType() == "CONST_FLOAT" || (yyvsp[0].symbol_val)->getType() == "CONST_FLOAT"){
				(yyval.symbol_val)->setType("CONST_FLOAT");
			}	
			else {(yyval.symbol_val)->setType("CONST_INT");}
			logfile2<<(yyval.symbol_val)->getName()<<endl<<endl;		

			/*****************************ICG CODE *******************************************/
				asmCode<<"\tPOP BX"<<endl;
				if((yyvsp[-1].symbol_val)->getName()=="*")	
					asmCode<<"\tMUL BX "<<endl;
				else if((yyvsp[-1].symbol_val)->getName()=="%"){
					asmCode<<"\tPUSH DX"<<endl;
					asmCode<<"\n\tXOR DX, DX"<<endl;
					asmCode<<"\tDIV BX\n\tMOV AX, DX\n\n\tPOP DX"<<endl;
				}else{
					asmCode<<"\tPUSH DX"<<endl;
					asmCode<<"\n\tXOR DX, DX"<<endl;
					asmCode<<"\tDIV BX\n\n\tPOP DX"<<endl;
				}
			/********************************************************************************/			
			
				
		
		}
#line 3054 "y.tab.c"
    break;

  case 72:
#line 1276 "1805035.y"
                                          {
    		(yyval.symbol_val) = new SymbolInfo((yyvsp[-1].symbol_val)->getName()+(yyvsp[0].symbol_val)->getName(),(yyvsp[0].symbol_val)->getType());
		 	logfile2<<"Line "<<line_count<<": unary_expression : ADDOP unary_expression"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;
		 	/*****************************ICG CODE ***************************************/
			if((yyvsp[-1].symbol_val)->getName()=="-"){
				asmCode<<"\tPOP BX"<<endl;
				asmCode<<"\tNEG BX"<<endl;
				asmCode<<"\tPUSH BX"<<endl;
			}
			/****************************************************************************/
		 }
#line 3070 "y.tab.c"
    break;

  case 73:
#line 1287 "1805035.y"
                                        {
    		(yyval.symbol_val) = new SymbolInfo("!"+(yyvsp[0].symbol_val)->getName(),(yyvsp[0].symbol_val)->getType());    		
		 	logfile2<<"Line "<<line_count<<": unary_expression : NOT unary_expression"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;
		 	/*****************************ICG CODE ***************************************/
			    asmCode<<"\tPOP BX"<<endl;
				asmCode<<"\tNOT [SP]"<<endl;
				asmCode<<"\tPUSH BX"<<endl;
			
			/****************************************************************************/
		 }
#line 3085 "y.tab.c"
    break;

  case 74:
#line 1297 "1805035.y"
                           {   		
		 	(yyval.symbol_val) = (yyvsp[0].symbol_val);
		 	logfile2<<"Line "<<line_count<<": unary_expression : factor"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;		 	
		 	
		 }
#line 3095 "y.tab.c"
    break;

  case 75:
#line 1304 "1805035.y"
                   {
			(yyval.symbol_val) = (yyvsp[0].symbol_val);		 	
		 	logfile2<<"Line "<<line_count<<": factor : variable"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;		
			/*****************************ICG CODE *******************************************/
				if((yyvsp[0].symbol_val)->isGlobal)
					asmCode<<"\t PUSH [SI] "<<endl;
				else {
					asmCode<<"\t PUSH [BP-SI] "<<endl;
				}
			/********************************************************************************/
		}
#line 3111 "y.tab.c"
    break;

  case 76:
#line 1315 "1805035.y"
                                         {
		//TODO
		(yyval.symbol_val)=new SymbolInfo((yyvsp[-3].symbol_val)->getName()+space+"("+space+(yyvsp[-1].symbol_val)->getName()+space+")",(yyvsp[-3].symbol_val)->returnTypeOfFunction);
		printMSG("factor : ID LPAREN argument_list RPAREN",(yyval.symbol_val)->getName());


		SymbolInfo* currentSymbol = table->LookUp((yyvsp[-3].symbol_val)->getName());
		/****************ICG CODE**************************/
		
		asmCode<<"\tMOV TEMPORARY_VALUE,BP\n\tMOV BP,SP"<<endl;
		
		
		asmCode<<"\tCALL "<<(yyvsp[-3].symbol_val)->getName()<<"\n\tMOV BP, TEMPORARY_VALUE"<<endl;
		asmCode<<"\tPUSH FUNC_RETURN_VALUE"<<endl;
		/*********************************************************/
		if(currentSymbol==NULL){
			printError("Undeclared or Undefined Function",(yyvsp[-3].symbol_val)->getName());
			(yyvsp[-1].symbol_val)->functionParameterList.clear();
		} else {
			if(currentSymbol->typeOfID=="FUNCTION"){
				if(currentSymbol->isFunction)
				{
					//CHECK NUMER OF ARGUMENTS ARE EQUAL!!!
					int given_arg_list = (yyvsp[0].symbol_val)->functionParameterList.size();
					int defined_arg_list = currentSymbol->functionParameterList.size();

					if(given_arg_list!=defined_arg_list){
						printError(" Total number of arguments mismatch in function",(yyvsp[-3].symbol_val)->getName());
						errorfile<<given_arg_list<<" "<<defined_arg_list<<endl;
						(yyvsp[-1].symbol_val)->functionParameterList.clear();
					}else{
						//CHECK FOR ARGUMENT SEQUENCE OF DEFINED AND CALLED FUNCTION
						
						for(int i=0;i<defined_arg_list;i++)
						{
							string temp1 = (yyvsp[-1].symbol_val)->functionParameterList[i].second;
							string temp2 = currentSymbol->functionParameterList[i].second;
							
							if(conversionError(temp1,temp2))
							{
								printError(to_string(i+1)+"th argument mismatch"+temp1+","+temp2+"in function func\n",(yyval.symbol_val)->getName());
								break;
							}
						}
						(yyvsp[-1].symbol_val)->functionParameterList.clear();
					}

					(yyval.symbol_val)->setType(currentSymbol->returnTypeOfFunction);
					(yyval.symbol_val)->typeOfID = currentSymbol->typeOfID;
				} else {
					printError("function not properly defined or declared","");
					(yyval.symbol_val)->setType(currentSymbol->returnTypeOfFunction);
					(yyval.symbol_val)->typeOfID = currentSymbol->typeOfID;
				}
			} else{
				printError("Function call on Non function ID","");
				(yyval.symbol_val)->setType("CONST_INT");
				
			}
		

		}
		
		}
#line 3180 "y.tab.c"
    break;

  case 77:
#line 1379 "1805035.y"
                                  {
	
	(yyval.symbol_val)=new SymbolInfo("("+(yyvsp[-1].symbol_val)->getName()+")",(yyvsp[-1].symbol_val)->getType());
	printMSG("factor : LPAREN expression RPAREN",(yyval.symbol_val)->getName());
	asmCode<<"\tPUSH AX"<<endl;
}
#line 3191 "y.tab.c"
    break;

  case 78:
#line 1385 "1805035.y"
                    {
			(yyval.symbol_val) = (yyvsp[0].symbol_val);						
			logfile2<<"Line "<<line_count<<": factor : CONST_INT"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;
			/*******************************ICG CODE****************************************************/

				asmCode<<"\tPUSH "<<(yyvsp[0].symbol_val)->getName()<<endl;
				

			/********************************************************************************/	 	
		}
#line 3206 "y.tab.c"
    break;

  case 79:
#line 1396 "1805035.y"
        {
			(yyval.symbol_val) = (yyvsp[0].symbol_val);			
			logfile2<<"Line "<<line_count<<": factor : CONST_FLOAT"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;
			/*******************************ICG CODE****************************************************/

				asmCode<<"\tPUSH"<<(yyvsp[0].symbol_val)->getName()<<endl;

			/********************************************************************************/
		
		}
#line 3221 "y.tab.c"
    break;

  case 80:
#line 1406 "1805035.y"
                         {
			(yyval.symbol_val) = new SymbolInfo((yyvsp[-1].symbol_val)->getName()+(yyvsp[0].symbol_val)->getName(),(yyvsp[-1].symbol_val)->getType());
		 	logfile2<<"Line "<<line_count<<": factor : variable INCOP"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;		
			/*****************************ICG CODE*****************/
			
			if((yyvsp[-1].symbol_val)->isGlobal){
				
				asmCode<<"\tPUSH [SI]"<<endl;
				asmCode<<"\tINC [SI]"<<endl;
			}
				else {
					
					asmCode<<"\t PUSH [BP+SI] "<<endl;
					asmCode<<"\tINC [BP+SI]"<<endl;
				}
			

		}
#line 3244 "y.tab.c"
    break;

  case 81:
#line 1424 "1805035.y"
                        {
			(yyval.symbol_val) = new SymbolInfo((yyvsp[-1].symbol_val)->getName()+(yyvsp[0].symbol_val)->getName(),(yyvsp[-1].symbol_val)->getType());
		 	logfile2<<"Line "<<line_count<<": factor : variable DECOP"<<endl<<endl<<(yyval.symbol_val)->getName()<<endl<<endl;		
			/*****************************ICG CODE*****************/
			if((yyvsp[-1].symbol_val)->isGlobal){
				
				asmCode<<"\tPUSH [SI]"<<endl;
				asmCode<<"\tINC [SI]"<<endl;
			}
				else {
					
					asmCode<<"\t PUSH [BP+SI] "<<endl;
					asmCode<<"\tDEC [BP+SI]"<<endl;
				}
		}
#line 3264 "y.tab.c"
    break;

  case 82:
#line 1442 "1805035.y"
                         {

		(yyval.symbol_val)=(yyvsp[0].symbol_val);
		printMSG("argument_list : arguments",(yyval.symbol_val)->getName());
	}
#line 3274 "y.tab.c"
    break;

  case 83:
#line 1447 "1805035.y"
         {(yyval.symbol_val)=new SymbolInfo("","");printMSG("argument_list : arguments");}
#line 3280 "y.tab.c"
    break;

  case 84:
#line 1450 "1805035.y"
                                             {
	
	(yyval.symbol_val)=new SymbolInfo((yyvsp[-2].symbol_val)->getName()+","+(yyvsp[0].symbol_val)->getName(),"");
	printMSG("arguments : arguments COMMA logic_expression",(yyval.symbol_val)->getName());
	string name = (yyvsp[0].symbol_val)->getName();
	string variable_type = (yyvsp[0].symbol_val)->getType();

	if((yyvsp[0].symbol_val)->typeOfVar == "VOID"||(yyvsp[0].symbol_val)->getType() == "VOID")
	{
		printError("Void passed as parameter","");
	}else{
		(yyval.symbol_val)->functionParameterList=(yyvsp[-2].symbol_val)->functionParameterList;  
		(yyval.symbol_val)->functionParameterList.push_back(make_pair(name,variable_type));
		asmCode<<"\tPUSH AX"<<endl;
	}

	
}
#line 3303 "y.tab.c"
    break;

  case 85:
#line 1468 "1805035.y"
                                {
			(yyval.symbol_val)=new SymbolInfo((yyvsp[0].symbol_val)->getName(),"");
			string name = (yyvsp[0].symbol_val)->getName();
			string variable_type = (yyvsp[0].symbol_val)->getType();
			printMSG("arguments : logic_expression",(yyval.symbol_val)->getName());
			(yyval.symbol_val)->functionParameterList.push_back(make_pair(name,variable_type));
		  	asmCode<<"\tPUSH AX"<<endl;
		  }
#line 3316 "y.tab.c"
    break;


#line 3320 "y.tab.c"

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp);
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
#line 1478 "1805035.y"

int main(int argc,char *argv[])
{
	cout<<"staring.............."<<endl;
	table=new SymbolTable(30);
	cout<<"table created...."<<endl;
	table->EnterScope();
	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File sakib.\n");
		exit(1);
	}
	cout<<"opened............."<<endl;
	// fp2= fopen(argv[2],"w");
	// fclose(fp2);
	// fp3= fopen(argv[3],"w");
	// fclose(fp3);
	
	// fp2= fopen(argv[2],"a");
	// fp3= fopen(argv[3],"a");
	

	yyin=fp;
	yyparse();
	

	// fclose(fp2);
	// fclose(fp3);
	cout<<"*********************************"<<endl;
	table->printAllLex(logfile2);
	delete table;
	logfile2<<"Total lines: "<<line_count-1<<endl;

	logfile2<<"Total errors: "<<error_count<<endl;
	return 0;
}

