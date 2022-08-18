/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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

#line 134 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
